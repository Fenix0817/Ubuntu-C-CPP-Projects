#define TRUE 1
#define FALSE 0
typedef struct {
	float3 pos;
	float3 dir;
} Ray;

typedef struct {
	float radius;
	float3 pos;
	float3 color;
} Sphere;

typedef struct {
	float3 pos;
	float3 normal;
} Plane;

typedef struct {
	bool hit;
	float3 pos;
	float3 dir;
	float t;
	float3 normal;
} ShadeInfo;

typedef struct {
	constant Sphere*spheres;
	constant Plane*planes;
	int numSpheres;
	int numPlanes;
} World;

float squareLength(float3 f){
	return f.x*f.x+f.y*f.y+f.z*f.z;
}

bool solvableQuadratic(float a,float b,float c){
	return b*b-4*a*c>=0;
}

bool solveQuadratic(float a,float b,float c,float*t1,float*t2){
	float discr=sqrt(b*b-4*a*c);
	if(discr<0)return FALSE;
	*t1=(-b+discr)/(2*a);
	*t2=(-b-discr)/(2*a);
	return TRUE;
}

Ray createCamera(float2 uv, float3 camPos, float3 lookAt, float zoom){
	float3 f = normalize(lookAt-camPos); 
	float3 r = cross((float3)(0,1,0),f);
	float3 u = cross(f,r);

	float3 c=camPos+f*zoom;
	float3 i=c+uv.x*r+uv.y*u;
	float3 dir=i-camPos;
	Ray cam;
	cam.pos=camPos;
	cam.dir=normalize(dir);
	return cam;
}

ShadeInfo intersectSphere(Sphere sph,Ray ray){
	ShadeInfo si;
	si.hit=FALSE;
	float a=squareLength(ray.dir);
	float b=2*dot(ray.pos-sph.pos,ray.dir);
	float c=squareLength(ray.pos-sph.pos)-sph.radius*sph.radius;
	if(!solvableQuadratic(a,b,c))return si;
	si.hit=TRUE;
	float t1;
	float t2;
	solveQuadratic(a,b,c,&t1,&t2);
	float t=min(t1,t2);
	si.t=t;
	si.normal=normalize(ray.pos+t*ray.dir-sph.pos);
	si.pos=ray.pos;
	si.dir=ray.dir;
	return si;
}


kernel void createImage(int IMG_W, int IMG_H, global float* rComp, global float* gComp, global float* bComp,constant Sphere*spheres,constant Plane*planes,int numSpheres,int numPlanes) {
	float x=get_global_id(0);
	float y=get_global_id(1);
	
	int ind=(int)(x+IMG_W*y);

	float2 uv={2.0*x/IMG_W-1,2.0*y/IMG_H-1};
	uv.x*=(float)IMG_W/IMG_H;

	Ray ray=createCamera(uv, (float3)(3,2,1), (float3)(0,0,0), 1);
	
	World world;
	world.spheres=spheres;
	world.planes=planes;
	world.numSpheres=numSpheres;
	world.numPlanes=numPlanes;
	
	ShadeInfo si;
	si.hit=FALSE;
	si=intersectSphere(spheres[0],ray);
	
	//float3 col=(float3)(uv.x,uv.y,0);
	float3 col=2*si.normal-1;
	if(si.hit)col=(float3)(1);
	else col=(float3)(0);

	float gamma=1;

	rComp[ind]=((float)x)/((float)IMG_W);
	gComp[ind]=((float)y)/((float)IMG_H);
	bComp[ind]=0;
	
}
