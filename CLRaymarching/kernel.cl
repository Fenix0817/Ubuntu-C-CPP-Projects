
typedef struct {
	float3 pos;
	float3 dir;
} ray;

#define abs(a) (a<0?-a:a)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a<b?b:a)
#define EPSILON 0.001
#define vec3(a,b,c) (float3)(a,b,c)
#define vec2(a,b) (float2)(a,b)
#define clamp(a,b,c) (max(min(a,c),b))
#define reflect(i,n) (i-2*dot(n,i)*n)

#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define HALF_PI 1.57079632679

#define deg2rad(d) (d*PI/180)

float2 rotate2(float2 v,float theta){
	float c=cos(theta);
	float s=sin(theta);
	float x=v.x;
	float y=v.y;
	return (float2)(c*x-s*y,s*x+c*y);
}

float3 rotateX(float3 p,float theta){
	float2 v=(float2)(p.y,p.z);
	v=rotate2(v,theta);
	return (float3)(p.x,v.x,v.y);
}

float3 rotateY(float3 p,float theta){
	float2 v=(float2)(p.x,p.z);
	v=rotate2(v,theta);
	return (float3)(v.x,p.y,v.y);
}

float3 rotateZ(float3 p,float theta){
	float2 v=(float2)(p.x,p.y);
	v=rotate2(v,theta);
	return (float3)(v.x,v.y,p.z);
}

float3 abs3(float3 p){
	return (float3)(abs(p.x),abs(p.y),abs(p.z));
}

float3 min3(float3 a,float3 b){
	return (float3)(min(a.x,b.x),min(a.y,b.y),min(a.z,b.z));
}

float3 max3(float3 a,float3 b){
	return (float3)(max(a.x,b.x),max(a.y,b.y),max(a.z,b.z));
}

ray createCamera(float2 uv, float3 camPos, float3 lookAt, float zoom){
	float3 f = normalize(lookAt-camPos); 
	float3 r = cross((float3)(0,1,0),f);
	float3 u = cross(f,r);

	float3 c=camPos+f*zoom;
	float3 i=c+uv.x*r+uv.y*u;
	float3 dir=i-camPos;
	ray cam;
	cam.pos=camPos;
	cam.dir=normalize(dir);
	return cam;
}

float sdBox(float3 p,float3 b){
	float3 d=abs3(p)-b;
	return min(max(d.x,max(d.y,d.z)),0)+length(max3(d,(float3)(0,0,0)));
}

#define scale 2
#define CX 2
#define CY 1
#define CZ 1

void transform1(float x,float y,float z,float*ox,float*oy,float*oz){
	float3 p=(float3)(x,y,z);
	
	//p=rotateY(p,1.0);
	p=rotateZ(p,-1.0);
	//p=rotateY(p,deg2rad(25));
	
	*ox=p.x;
	*oy=p.y;
	*oz=p.z;
}

void transform2(float x,float y,float z,float*ox,float*oy,float*oz){
	float3 p=(float3)(x,y,z);
	
	//p=rotateX(p,TWO_PI/3);
	
	*ox=p.x;
	*oy=p.y;
	*oz=p.z;
}

float coolMenger(float3 p){
	float mul=5;
	p/=mul;
	float x=p.x;
	float y=p.y;
	float z=p.z;
	float ox;
	float oy;
	float oz;
	float r=x*x+y*y+z*z;
	int i;
	for(i=0;i<30;i++){
		
		transform1(x,y,z,&ox,&oy,&oz);
		x=ox;
		y=oy;
		z=oz;
	
		x=abs(x);
		y=abs(y);
		z=abs(z);
		float x1;
		float y1;
		float z1;
		if(x-y<0){x1=y;y=x;x=x1;}
		if(x-z<0){x1=z;z=x;x=x1;}
		if(y-z<0){y1=z;z=y;y=y1;}
		
		transform2(x,y,z,&ox,&oy,&oz);
		x=ox;
		y=oy;
		z=oz;
		
		x=scale*x-CX*(scale-1);
		y=scale*y-CY*(scale-1);
		z=scale*z;
		
		if(z>.5*CZ*(scale-1))z-=CZ*(scale-1);
		
		r=x*x+y*y+z*z;
	}
	float d=sqrt(r)*pow(scale,-(float)i)-0.1;
	return d*mul;
}

float map(float3 p){
	return coolMenger(p);
}

float3 estimateNormal(float3 p){
	return normalize((float3)(
	map(p+(float3)(EPSILON,0,0))-map(p-(float3)(EPSILON,0,0)),
	map(p+(float3)(0,EPSILON,0))-map(p-(float3)(0,EPSILON,0)),
	map(p+(float3)(0,0,EPSILON))-map(p-(float3)(0,0,EPSILON))));
}

kernel void createImage(int IMG_W, int IMG_H, global float* rComp, global float* gComp, global float* bComp) {
	int x=get_global_id(0);
	int y=get_global_id(1);
	
	int ind=x+IMG_W*y;

	float2 uv=2*(float2)((float)x/IMG_W,(float)y/IMG_H)-(float2)1;
	uv.x*=IMG_W/IMG_H;

	float rot=PI;
	ray camRay=createCamera(uv, (float3)(50*cos(rot),6.7,20*sin(rot)), (float3)(0,0,0), 1);

	float3 pos=camRay.pos;
	float3 dir=camRay.dir;
	float t;
	for(t=EPSILON;t<500;){
		float h=map(pos+dir*t);
		t+=h;
		if(h<EPSILON)break;
	}

	float3 end=pos+dir*t;

	float3 normal=estimateNormal(pos+dir*t);

	float3 lightPos=(float3)(-12,6.7,-6);
	float3 reflected=reflect(normalize(end-pos),normal);
	float phong=clamp(dot(normalize(lightPos-end),normal),0,1)*0.9+1*pow(clamp(dot(reflected,normalize(lightPos-end)),      0,1),200);
	phong=phong*0.5+0.5;
	//float3 col=(float3)(uv.x,uv.y,0);
	float3 col=phong*(0.5+0.5*normal);
	
	if(t>500)col=normalize(end-pos)*0.5+0.5;

	float gamma=0.9;

	rComp[ind]=pow(col.x,gamma);
	gComp[ind]=pow(col.y,gamma);
	bComp[ind]=pow(col.z,gamma);
	
}
