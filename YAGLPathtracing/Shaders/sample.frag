#version 450 core

#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define HALF_PI 1.57079632679
#define ONE_OVER_PI 0.31830988618

//https://www.shadertoy.com/view/lltBWX
float randSeed;

uint tausStep(uint z,int s1,int s2,int s3,uint M){
    uint b=(((z << s1) ^ z) >> s2);
    return (((z & M) << s3) ^ b);
}

void initRandom(uint seed1,uint seed2,uint seed3){
    uint seed = seed1 * 1099087573U;
    uint seedb = seed2 * 1099087573U;
    uint seedc = seed3 * 1099087573U;

    // Round 1: Randomise seed
    uint z1 = tausStep(seed,13,19,12,429496729U);
    uint z2 = tausStep(seed,2,25,4,4294967288U);
    uint z3 = tausStep(seed,3,11,17,429496280U);
    uint z4 = (1664525U*seed + 1013904223U);

    // Round 2: Randomise seed again using second seed
    uint r1 = (z1^z2^z3^z4^seedb);

    z1 = tausStep(r1,13,19,12,429496729U);
    z2 = tausStep(r1,2,25,4,4294967288U);
    z3 = tausStep(r1,3,11,17,429496280U);
    z4 = (1664525U*r1 + 1013904223U);

    // Round 3: Randomise seed again using third seed
    r1 = (z1^z2^z3^z4^seedc);

    z1 = tausStep(r1,13,19,12,429496729U);
    z2 = tausStep(r1,2,25,4,4294967288U);
    z3 = tausStep(r1,3,11,17,429496280U);
    z4 = (1664525U*r1 + 1013904223U);

    randSeed = float(z1^z2^z3^z4) * 2.3283064365387e-10;
}

float getRand(){
    uint hashed_seed = uint(randSeed * float(1099087573U));

    uint z1 = tausStep(hashed_seed,13,19,12,429496729U);
    uint z2 = tausStep(hashed_seed,2,25,4,4294967288U);
    uint z3 = tausStep(hashed_seed,3,11,17,429496280U);
    uint z4 = (1664525U*hashed_seed + 1013904223U);

    float old_seed = randSeed;

    randSeed = float(z1^z2^z3^z4) * 2.3283064365387e-10;

    return old_seed;
}

vec3 sampleUnitSphere(){
    float theta=getRand()*PI;
    float phi=getRand()*TWO_PI;
    float c_t=cos(theta);
    float s_t=sin(theta);
    float c_p=cos(phi);
    float s_p=sin(phi);
    return vec3(s_t*c_p,s_t*s_p,c_t);
}

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

struct Material {
	vec3 color;
	vec3 light_color;
	float roughness;
};

struct Sphere {
    vec3 pos;
    float rad;
    Material mat;
};

struct Plane {
    vec3 pos;
    vec3 normal;
    Material mat;
};

const int MAX_SPHERES=10;
uniform int numSpheres;
uniform Sphere spheres[MAX_SPHERES];

const int MAX_PLANES=10;
uniform int numPlanes;
uniform Plane planes[MAX_PLANES];

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

vec3 material_shade(Material material,ShadeInfo si){
    vec3 hitPoint=si.ray.pos+si.ray.dir*si.t;
    vec3 normal=normalize(si.normal);
    return vec3(dot(normal,normalize(vec3(3.0,2.0,1.0)-hitPoint)));
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

uniform vec3 background;

uniform int numFrames;

vec3 tracePixel(Ray camRay){
    Ray r=camRay;
    vec3 accum=vec3(0.0);
    vec3 mask=vec3(1.0);

    for(int i=0;i<3;i++){
        float t;
        vec3 normal;
        Material mat;

        ShadeInfo si=intersectWorld(r);
        if(!si.hit){
            return accum+mask*background;
        }

        t=si.t;
        normal=normalize(si.normal);
        if(si.objectType==OBJECT_SPHERE)mat=spheres[si.objectIndex].mat;
        if(si.objectType==OBJECT_PLANE)mat=planes[si.objectIndex].mat;

        vec3 normal_facing=dot(normal,r.dir)<0.0?normal:-normal;

        vec3 hemisphereSample=sampleUnitSphere();

        vec3 hitPoint=r.pos+r.dir*t;

        vec3 newdir_diffuse=hemisphereSample;
        vec3 newdir_reflect=reflect(normalize(hitPoint-r.pos),normal);

        vec3 newdir=normalize(mix(newdir_reflect,newdir_diffuse,mat.roughness));
        r.pos=hitPoint+newdir*0.01;
        r.dir=newdir;

        accum+=mask*mat.light_color;
        mask*=mat.color;
        mask*=mix(1.0,dot(newdir,normal_facing),mat.roughness);

    }
    return accum;
}

void main(){
    initRandom(int(uv.x*1000000.0),uint(uv.y*10000000.0),uint(numFrames));
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

    vec3 shaded=tracePixel(camRay);

    if(shaded.x>1.0||shaded.y>1.0||shaded.z>1.0){
    	shaded/=max(shaded.x,max(shaded.y,shaded.z));
    }
    fragColor=vec4(shaded,1.0);
}