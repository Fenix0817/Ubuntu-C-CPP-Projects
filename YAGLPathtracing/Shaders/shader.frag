#version 450 core

in vec2 uv;

out vec4 fragColor;

#define MATERIAL_MATTE 0
#define MATERIAL_PHONG 1

#define BRDF_LAMBERTIAN 0
#define BRDF_GLOSSY_SPECULAR 1

#define OBJECT_PLANE 0
#define OBJECT_SPHERE 1

#define PI 3.14159265359
#define ONE_OVER_PI 0.31830988618

struct Ray {
    vec3 pos;
    vec3 dir;
};

struct ShadeInfo {
    float t;
    Ray ray;
    vec3 normal;
    bool hit;
    int objectIndex;
    int objectType;
};

struct Sphere {
    vec3 pos;
    float rad;
};

struct Plane {
    vec3 pos;
    vec3 normal;
};

struct BRDF {
	//lambertian
	float lambertian_intensity;
	vec3 lambertian_color;

	//glossy specular
	float glossy_specular_intensity;
	vec3 glossy_specular_color;
	float glossy_specular_exp;

	int type;
};

struct Material {
	//matte
	BRDF matte_ambient;
	BRDF matte_diffuse;

	//phong
	BRDF phong_ambient;
	BRDF phong_diffuse;
	BRDF phong_specular;

	int type;
};

const int MAX_SPHERES=50;
uniform int numSpheres;
uniform Sphere spheres[MAX_SPHERES];
uniform Material sphereMaterials[MAX_SPHERES];

const int MAX_PLANES=50;
uniform int numPlanes;
uniform Plane planes[MAX_PLANES];
uniform Material planeMaterials[MAX_PLANES];

uniform vec3 lightPos;

ShadeInfo minSI(ShadeInfo a,ShadeInfo b){
    if(!a.hit)return b;
    if(!b.hit)return a;
    if(a.t<b.t)return a;
    return b;
}

ShadeInfo minSI(ShadeInfo a,ShadeInfo b,ShadeInfo c){
    return minSI(a,minSI(b,c));
}

ShadeInfo minSI(ShadeInfo a,ShadeInfo b,ShadeInfo c,ShadeInfo d){
    return minSI(a,minSI(b,c,d));
}

float dot2(vec3 v){
    return dot(v,v);
}

ShadeInfo intersectSphere(int index,vec3 pos,float rad,Ray ray){
    float a=dot2(ray.dir);
    float b=2.0*dot(ray.pos-pos,ray.dir);
    float c=dot2(ray.pos-pos)-rad*rad;
    ShadeInfo si;
    si.hit=false;
    if(b*b-4.0*a*c<0.0)return si;//no hit
    float discr=sqrt(b*b-4.0*a*c);
    float t1=(-b+discr)/(2.0*a);
    float t2=(-b-discr)/(2.0*a);
    si.t=min(t1,t2);
    if(si.t<0.001)return si;
    si.hit=true;
    si.normal=normalize(ray.pos+si.t*ray.dir-pos);
    si.objectIndex=index;
    si.objectType=OBJECT_SPHERE;
    return si;
}

ShadeInfo intersectPlane(int index,vec3 pos,vec3 normal,Ray ray){
    float t=dot(pos-ray.pos,normal)/dot(ray.dir,normal);
    ShadeInfo si;
    si.hit=false;
    if(t<0.001)return si;
    si.hit=true;
    si.normal=normal;
    si.t=t;
    si.objectIndex=index;
    si.objectType=OBJECT_PLANE;
    return si;
}

vec3 brdf_f(BRDF brdf,ShadeInfo si,vec3 wi,vec3 wo){
    if(brdf.type==BRDF_LAMBERTIAN){
        return brdf.lambertian_intensity*brdf.lambertian_color*ONE_OVER_PI;
    }else if(brdf.type==BRDF_GLOSSY_SPECULAR){
    	float dotwi=dot(si.normal,wi);
    	vec3 r=-wi+2.0*si.normal*dotwi;
    	float dotwo=dot(r,wo);
    	if(dotwo>0.0){
    		return brdf.glossy_specular_intensity*brdf.glossy_specular_color*pow(dotwo,brdf.glossy_specular_exp);
    	}
    }
    return vec3(0.0);
}
vec3 brdf_rho(BRDF brdf,ShadeInfo si,vec3 wo){
    if(brdf.type==BRDF_LAMBERTIAN){
        return brdf.lambertian_intensity*brdf.lambertian_color;
    }else if(brdf.type==BRDF_GLOSSY_SPECULAR){
    	return vec3(0.0);
    }
    return vec3(0.0);
}

vec3 material_shade(Material material,ShadeInfo si){
    vec3 hitPoint=si.ray.pos+si.ray.dir*si.t;
    vec3 normal=si.normal;
    if(material.type==MATERIAL_MATTE){
        vec3 wo=-si.ray.dir;
        vec3 wi=normalize(lightPos-hitPoint);
        vec3 col=brdf_rho(material.matte_ambient,si,wo);
        float widotn=dot(wi,normal);

        if(widotn>0.0)col+=brdf_f(material.matte_diffuse,si,wi,wo)*widotn;
        return col;
    }else if(material.type==MATERIAL_PHONG){
    	vec3 wo=-si.ray.dir;
    	vec3 col=brdf_rho(material.phong_ambient,si,wo);

    	vec3 wi=normalize(lightPos-hitPoint);
    	float widotn=dot(wi,normal);

    	if(widotn>0.0)col+=(brdf_f(material.phong_diffuse,si,wi,wo)+brdf_f(material.phong_specular,si,wi,wo))*widotn;
    	return col;
    }
    return vec3(0.5);
}

ShadeInfo intersectWorld(Ray ray){
    ShadeInfo si;
    si.hit=false;
    for(int i=0;i<MAX_SPHERES;i++){
        if(i>=numSpheres)continue;
        si=minSI(si,intersectSphere(i,spheres[i].pos,spheres[i].rad,ray));
    }
    for(int i=0;i<MAX_PLANES;i++){
        if(i>=numPlanes)continue;
        si=minSI(si,intersectPlane(i,planes[i].pos,planes[i].normal,ray));
    }
    si.ray=ray;
    return si;
}


uniform vec2 windowSize;

uniform vec3 camPos;
uniform vec3 lookAt;
uniform float zoom;

void main(){
    vec2 coords=uv;
    coords*=2.0;
    coords-=1.0;
    coords.x*=windowSize.x/windowSize.y;

    vec3 f=normalize(lookAt-camPos);
    vec3 r=cross(vec3(0.0,1.0,0.0),f);
    vec3 u=cross(f,r);

    vec3 c=camPos+f*zoom;
    vec3 i=c+coords.x*r+coords.y*u;

    Ray camRay;
    camRay.pos=camPos;
    camRay.dir=normalize(i-camPos);

    ShadeInfo si=intersectWorld(camRay);
    if(!si.hit){
    	fragColor=vec4(0.0);
    	return;
    }
    Material material;
    if(si.objectType==OBJECT_SPHERE)material=sphereMaterials[si.objectIndex];
    if(si.objectType==OBJECT_PLANE)material=planeMaterials[si.objectIndex];
    vec3 shaded=material_shade(material,si);
    if(shaded.x>1.0||shaded.y>1.0||shaded.z>1.0){
    	// shaded/=max(shaded.x,max(shaded.y,shaded.z));
    	shaded=vec3(1.0,0.0,0.0);
    }
    fragColor=vec4(shaded,1.0);
}