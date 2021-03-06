#pragma once

#pragma once
#include <cmath>

int CMID(int x, int min, int max)
{
	return (x < min) ? min : ((x > max) ? max : x);
}
float interp(float x1, float x2, float t)
{
	return x1 + (x2 - x1) * t;
}
const float PI = 3.141527;
struct Vector3
{
	float x;
	float y;
	float z;
	float w;
	Vector3(float xv, float vy, float vz, float W = 1)
	{
		x = xv;
		y = vy;
		z = vz;
		w = 1;
	}
	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
	/*Vector3(const Vector3 &Vector3)
	{
		x = Vector3.x;
		y = Vector3.y;
		z = Vector3.z;
		w = 1;
	}*/


	Vector3 operator+(Vector3 vector3)
	{
		return Vector3{ x + vector3.x,y + vector3.y,z + vector3.z ,w = 1 };
	}
	Vector3 operator-(Vector3 vector3)
	{
		return Vector3{ x - vector3.x,y - vector3.y,z - vector3.z ,w = 1 };
	}

	float length()
	{
		return abs(sqrt((x*x) + (y * y) + (z * z)));
	}
	float lengthsq(Vector3 vector3)
	{
		return abs((x*x) + (y * y) + (z * z));
	}

	Vector3 operator*(float k)
	{
		return Vector3{ x*k,y*k,z*k,w = 1 };
	}

	
};
Vector3 addvector(Vector3 vector, float k)
{
	vector.x = k + vector.x;
	vector.y = k + vector.y;
	vector.z = k + vector.x;
	return vector;
}
void Normalizevector(Vector3 &vector)
{
	float inv=vector.length();
	vector.x = vector.x / inv;
	vector.y = vector.y / inv;
	vector.z = vector.z / inv;
	vector.w = 1;
}
Vector3 vectorlerp(Vector3 v1, Vector3 v2, float alpha)
{
	return Vector3(interp(v1.x, v2.x, alpha), interp(v1.y, v1.y, alpha), interp(v1.z, v1.z, alpha), 1);
}
float Dot(Vector3 vector1, Vector3 vector2)
{
	return vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z;
}
float angle(Vector3 vector1, Vector3 vector2)
{
	float v3 = Dot(vector1, vector2) / (vector1.length()*vector2.length());
	return acosf(v3);
}
Vector3 Corss(Vector3 vector1, Vector3 vector2)
{
	return Vector3(vector1.y*vector2.z - vector1.z*(vector2.y), vector1.z*vector2.x - vector1.x*(vector2.z), vector1.x*vector2.y - vector1.y*(vector2.x), 1);
}
struct Matrix4x
{
	float matrix4x[4][4];
	Matrix4x()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				matrix4x[i][j] = 0;
			}
		}
	}
	Matrix4x(float data11, float data12, float data13, float data14,
		float data21, float data22, float data23, float data24,
		float data31, float data32, float data33, float data34,
		float data41, float data42, float data43, float data44)
	{
		matrix4x[0][0] = data11;
		matrix4x[0][1] = data12;
		matrix4x[0][2] = data13;
		matrix4x[0][3] = data14;
		matrix4x[1][0] = data21;
		matrix4x[1][1] = data22;
		matrix4x[1][2] = data23;
		matrix4x[1][3] = data24;
		matrix4x[2][0] = data31;
		matrix4x[2][1] = data32;
		matrix4x[2][2] = data33;
		matrix4x[2][3] = data34;
		matrix4x[3][0] = data41;
		matrix4x[3][1] = data42;
		matrix4x[3][2] = data43;
		matrix4x[3][3] = data44;
	}
	Matrix4x operator*(Matrix4x matrix4)
	{
		Matrix4x z;
		int i, j;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				z.matrix4x[j][i] = (matrix4x[j][0] * matrix4.matrix4x[0][i]) +
					(matrix4x[j][1] * matrix4.matrix4x[1][i]) +
					(matrix4x[j][2] * matrix4.matrix4x[2][i]) +
					(matrix4x[j][3] * matrix4.matrix4x[3][i]);
			}
		}
		return z;
	}
};
void setzero(Matrix4x &matrix4)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matrix4.matrix4x[i][j] = 0;
		}
	}
}
void setidentity(Matrix4x &matrix4)
{
	matrix4.matrix4x[0][0] = matrix4.matrix4x[1][1] = matrix4.matrix4x[2][2] = matrix4.matrix4x[3][3] = 1;
	matrix4.matrix4x[0][1] = matrix4.matrix4x[0][2] = matrix4.matrix4x[0][3] = 0;
	matrix4.matrix4x[1][2] = matrix4.matrix4x[1][2] = matrix4.matrix4x[1][2] = 0;
	matrix4.matrix4x[2][0] = matrix4.matrix4x[2][1] = matrix4.matrix4x[2][2] = 0;
	matrix4.matrix4x[3][0] = matrix4.matrix4x[3][1] = matrix4.matrix4x[3][2] = 0;
}

void VMulM(Vector3 v1,Vector3 &v2 ,Matrix4x m1)
{
	v2.x = v1.x*m1.matrix4x[0][0] + v1.y*m1.matrix4x[1][0] + v1.z*m1.matrix4x[2][0] + v1.w*m1.matrix4x[3][0];
	v2.y=  v1.x*m1.matrix4x[0][1] + v1.y*m1.matrix4x[1][1] + v1.z*m1.matrix4x[2][1] + v1.w*m1.matrix4x[3][1];
	v2.z = v1.x*m1.matrix4x[0][2] + v1.y*m1.matrix4x[1][2] + v1.z*m1.matrix4x[2][2] + v1.w*m1.matrix4x[3][2];
	v2.w = v1.x*m1.matrix4x[0][3] + v1.y*m1.matrix4x[1][3] + v1.z*m1.matrix4x[2][3] + v1.w*m1.matrix4x[3][3];
	
}
void TranslateMatrix(Matrix4x &Matrix4, float x, float y, float z)
{
	setidentity(Matrix4);
	Matrix4.matrix4x[3][0] = x;
	Matrix4.matrix4x[3][1] = y;
	Matrix4.matrix4x[3][2] = z;
}
void ScaleMatrix(Matrix4x &Matrix4, float x, float y, float z)
{
	setidentity(Matrix4);
	Matrix4.matrix4x[0][0] = x;
	Matrix4.matrix4x[1][1] = y;
	Matrix4.matrix4x[2][2] = z;
}
void RotateMatrix(Matrix4x &Matrix4, float x, float y, float z, float agnel)
{
	float qsin = (float)sin(agnel * 0.5f);
	float qcos = (float)cos(agnel * 0.5f);
	Vector3 vec = { x, y, z, 1.0f };
	float w = qcos;
	Normalizevector(vec);
	x = vec.x * qsin;
	y = vec.y * qsin;
	z = vec.z * qsin;
	Matrix4.matrix4x[0][0] = 1 - 2 * y * y - 2 * z * z;
	Matrix4.matrix4x[1][0] = 2 * x * y - 2 * w * z;
	Matrix4.matrix4x[2][0] = 2 * x * z + 2 * w * y;
	Matrix4.matrix4x[0][1] = 2 * x * y + 2 * w * z;
	Matrix4.matrix4x[1][1] = 1 - 2 * x * x - 2 * z * z;
	Matrix4.matrix4x[2][1] = 2 * y * z - 2 * w * x;
	Matrix4.matrix4x[0][2] = 2 * x * z - 2 * w * y;
	Matrix4.matrix4x[1][2] = 2 * y * z + 2 * w * x;
	Matrix4.matrix4x[2][2] = 1 - 2 * x * x - 2 * y * y;
	Matrix4.matrix4x[0][3] = Matrix4.matrix4x[1][3] = Matrix4.matrix4x[2][3] = 0.0f;
	Matrix4.matrix4x[3][0] = Matrix4.matrix4x[3][1] = Matrix4.matrix4x[3][2] = 0.0f;
	Matrix4.matrix4x[3][3] = 1.0f;

}
void CameraMatrix(Matrix4x &m, Vector3 cameraloction, Vector3 lookat, Vector3 up)
{
	
	Vector3 xaxis, yaxis, zaxis;

	zaxis=lookat-cameraloction;
    Normalizevector(zaxis);
	xaxis= Corss(up, zaxis)  ;
	Normalizevector(xaxis);
	yaxis= Corss(zaxis,xaxis);

	m.matrix4x[0][0] = xaxis.x;
	m.matrix4x[1][0] = xaxis.y;
	m.matrix4x[2][0] = xaxis.z;
	m.matrix4x[3][0] = -Dot(xaxis, cameraloction);

	m.matrix4x[0][1] = yaxis.x;
	m.matrix4x[1][1] = yaxis.y;
	m.matrix4x[2][1] = yaxis.z;
	m.matrix4x[3][1] = -Dot(yaxis, cameraloction);

	m.matrix4x[0][2] = zaxis.x;
	m.matrix4x[1][2] = zaxis.y;
	m.matrix4x[2][2] = zaxis.z;
	m.matrix4x[3][2] = -Dot(zaxis, cameraloction);

	m.matrix4x[0][3] = m.matrix4x[1][3] = m.matrix4x[2][3] = 0.0f;
	m.matrix4x[3][3] = 1.0f;

}
void MatrixProjection(Matrix4x &matrixPro, float n, float f, float fov, float aspect)
{
	setzero(matrixPro);
	matrixPro.matrix4x[0][0] = 1/aspect*tan(fov / 2);
	matrixPro.matrix4x[1][1] = 1/tan(fov / 2);
	matrixPro.matrix4x[2][2] = f / (f - n);
	matrixPro.matrix4x[3][2] = -f*n / (f - n);
	matrixPro.matrix4x[2][3] = 1;
}

struct Transforma_t
{
	Matrix4x Worldmatrix;
	Matrix4x Cameramatrix;
	Matrix4x Projectionmatrix;
	Matrix4x Transform;
	float w;
	float h;
};

void TransformaUpdate(Transforma_t &transformt)
{
	Matrix4x tmp = transformt.Worldmatrix.operator*(transformt.Cameramatrix);
	transformt.Transform = tmp.operator*(transformt.Projectionmatrix);
}
void Transforminitial(Transforma_t &tansform, int width, int height)
{
	float aspect = (float)width / (float)height;
	setidentity(tansform.Worldmatrix);
	setidentity(tansform.Cameramatrix);
	MatrixProjection(tansform.Projectionmatrix, 1, 500, PI*0.5, aspect);
	tansform.h = (float)height;
	tansform.w = (float)width;
	TransformaUpdate(tansform);
}
void Transformapplytovector(Transforma_t tansform,Vector3 &v1, Vector3 vector)
{
	VMulM(vector,v1,tansform.Transform);
}

bool Frustumculling(Vector3 *vector)
{
	float w = vector->w;
	bool biscull = false;
	if (vector->z < 0.0)
		biscull = true;
	if (vector->z>w)
		biscull = true;
	if (vector->x > w)
		biscull = true;
	if (vector->x < -w)
		biscull = true;
	if (vector->y> w)
		biscull = true;
	if (vector->y <-w)
		biscull = true;
	return biscull;
}

void getviewprotpostion(const Transforma_t transform, Vector3 &vectorview,const Vector3 vectorcvv)
{
	float rhw = 1 / vectorcvv.w;
	vectorview.x = (vectorcvv.x*rhw + 1.0f)*transform.w*0.5f;
	vectorview.y = (1 - vectorcvv.y*rhw)*transform.w*0.5f;
	vectorview.z = vectorcvv.z*rhw;
	vectorview.w = 1.0f;
}
struct Light
{
	//Vector3 lightpos;
	Vector3 lightdirection;
	float lightstregth;
};



struct Fcolor
{
	float r, g, b;
};
struct texcoord
{
	float u;
	float v;
};
struct  Vertex
{
	Vector3 pos;
	texcoord tc;
	Fcolor fcolor;
	float rhw;
	float ka = 0.1;
	float kd = 0.8;
	float ks = 0.2f;
	int n = 10;
	Vector3 normal;
	float IA;
	Vector3 ID;
	Vector3 IS;
	Vector3 LS;
};

struct edge
{
	Vertex v, v1, v2;
};

struct Trapezoide
{
	float top, bottom;
	edge left, right;
};

struct Scanline
{
	Vertex v, step;
	int x, y, w;
};
float posx = 3;
float posy = 0;
float posz = 0;
Vector3 eyepos(posx, posy, posz);

void calnormal(Vertex &vertexa, Vertex &vertexb, Vertex &vertexc)
{
	vertexa.normal = Corss(vertexb.pos - vertexa.pos, vertexc.pos - vertexa.pos);
	vertexb.normal = Corss(vertexa.pos - vertexb.pos, vertexc.pos - vertexb.pos);
	vertexc.normal = Corss(vertexa.pos - vertexc.pos, vertexb.pos - vertexb.pos);
	Normalizevector(vertexa.normal);
	Normalizevector(vertexb.normal);
	Normalizevector(vertexc.normal);
}

void callight(Vertex &vertex,Light light,Vector3 eye)
{
	vertex.IA = vertex.ka*light.lightstregth;
	Vector3 tmp = light.lightdirection - vertex.pos;
	Normalizevector(tmp);
	vertex.ID = vertex.ID*vertex.kd*Dot(vertex.normal,tmp)*light.lightstregth;
	Normalizevector(eye);
	Dot(vertex.normal*Dot(vertex.normal, tmp) * 2 - tmp,eye);
	vertex.IS = vertex.IS*vertex.ks*pow(Dot(vertex.normal*Dot(vertex.normal, tmp) * 2 - tmp, eye),10)*light.lightstregth;
	vertex.LS = addvector(vertex.IS + vertex.ID, vertex.IA);
}

int RGBtoh(Vertex &vertex)
{
	int r = (int)vertex.LS.x;
	int g = (int)vertex.LS.y;
	int b = (int)vertex.LS.z;
	return r << 16 | g << 8 | b;
}
void vertexrhwinit(Vertex &vertex)
{
	float rhw = 1.0f / vertex.pos.w;
	vertex.rhw = rhw;
	vertex.fcolor.b *= rhw;
	vertex.fcolor.g *= rhw;
	vertex.fcolor.r *= rhw;
	vertex.tc.u *= rhw;
	vertex.tc.v *= rhw;
}

void vertexlerp(Vertex &v, Vertex v1, Vertex v2, float t)
{
	v.pos = vectorlerp(v1.pos, v2.pos, t);
	v.tc.u = interp(v1.tc.u, v2.tc.u, t);
	v.tc.v = interp(v1.tc.v, v2.tc.v, t);
	v.fcolor.r = interp(v1.fcolor.r, v2.fcolor.r, t);
	v.fcolor.g = interp(v1.fcolor.g, v2.fcolor.g, t);
	v.fcolor.b = interp(v1.fcolor.b, v2.fcolor.b, t);
	v.rhw = interp(v1.rhw, v2.rhw, t);
}

void vertexdiv(Vertex &v, Vertex v1, Vertex v2, float w)
{
	float inv = 1.0f / w;
	v.pos.x = (v2.pos.x - v1.pos.x) * inv;
	v.pos.y = (v2.pos.y - v1.pos.y) * inv;
	v.pos.z = (v2.pos.z - v1.pos.z) * inv;
	v.pos.w = (v2.pos.w - v1.pos.w) * inv;
	v.tc.u = (v2.tc.u - v1.tc.u) * inv;
	v.tc.v = (v2.tc.v - v1.tc.v) * inv;
	v.fcolor.r = (v2.fcolor.r - v1.fcolor.r) * inv;
	v.fcolor.g = (v2.fcolor.g - v1.fcolor.g) * inv;
	v.fcolor.b = (v2.fcolor.b - v1.fcolor.b) * inv;
	v.rhw = (v2.rhw - v1.rhw) * inv;
}

void vertexadd(Vertex &v, Vertex v1)
{
	v.pos.x += v1.pos.x;
	v.pos.y += v1.pos.y;
	v.pos.z += v1.pos.z;
	v.pos.w += v1.pos.w;
	v.rhw += v1.rhw;
	v.tc.u += v1.tc.u;
	v.tc.v += v1.tc.v;
	v.fcolor.r += v1.fcolor.r;
	v.fcolor.g += v1.fcolor.g;
	v.fcolor.b += v1.fcolor.b;
}

int trianletotrapezoid(Trapezoide *trap, Vertex v1, Vertex v2, Vertex v3)
{

	Vertex v;
	float k, x;

	if (v1.pos.y > v2.pos.y)v = v1, v1 = v2, v2 = v;
	if (v1.pos.y > v3.pos.y) v = v1, v1 = v3, v3 = v;
	if (v2.pos.y > v3.pos.y) v = v2, v2 = v3, v3 = v;
	if (v1.pos.y == v2.pos.y && v1.pos.y == v3.pos.y) return 0;
	if (v1.pos.x == v2.pos.x && v1.pos.x == v3.pos.x) return 0;

	if (v1.pos.y == v2.pos.y) {	// triangle down
		if (v1.pos.x > v2.pos.x) v = v1, v1 = v2, v2 = v;
		trap[0].top = v1.pos.y;
		trap[0].bottom = v3.pos.y;
		trap[0].left.v1 = v1;
		trap[0].left.v2 = v3;
		trap[0].right.v1 = v2;
		trap[0].right.v2 = v3;
		return (trap[0].top < trap[0].bottom) ? 1 : 0;
	}

	if (v2.pos.y == v3.pos.y) {	// triangle up
		if (v2.pos.x > v3.pos.x) v = v2, v2 = v3, v3 = v;
		trap[0].top = v1.pos.y;
		trap[0].bottom = v3.pos.y;
		trap[0].left.v1 = v1;
		trap[0].left.v2 = v2;
		trap[0].right.v1 = v1;
		trap[0].right.v2 = v3;
		return (trap[0].top < trap[0].bottom) ? 1 : 0;
	}

	trap[0].top = v1.pos.y;
	trap[0].bottom = v2.pos.y;
	trap[1].top = v2.pos.y;
	trap[1].bottom = v3.pos.y;

	k = (v3.pos.y - v1.pos.y) / (v2.pos.y - v1.pos.y);
	x = v1.pos.x + (v2.pos.x - v1.pos.x) * k;

	if (x <= v3.pos.x) {		// triangle left
		trap[0].left.v1 = v1;
		trap[0].left.v2 = v2;
		trap[0].right.v1 = v1;
		trap[0].right.v2 = v3;
		trap[1].left.v1 = v2;
		trap[1].left.v2 = v3;
		trap[1].right.v1 = v1;
		trap[1].right.v2 = v3;
	}
	else {					// triangle right
		trap[0].left.v1 = v1;
		trap[0].left.v2 = v3;
		trap[0].right.v1 = v1;
		trap[0].right.v2 = v2;
		trap[1].left.v1 = v1;
		trap[1].left.v2 = v3;
		trap[1].right.v1 = v2;
		trap[1].right.v2 = v3;
	}
	return 2;
}

void trapeziodedge(Trapezoide *trap, float y)
{
	float l1 = trap->left.v1.pos.y - trap->left.v2.pos.y;
	float r1 = trap->right.v1.pos.y - trap->right.v2.pos.y;
	float l2 = (trap->left.v1.pos.y - y) / l1;
	float r2 = (trap->right.v1.pos.y - y) / r1;
	vertexlerp(trap->left.v, trap->left.v1, trap->left.v2, l2);
	vertexlerp(trap->right.v, trap->right.v1, trap->right.v2, r2);
}

void scanlineinit(Trapezoide *trap, Scanline *scanline, int y)
{
	float width = trap->right.v.pos.x - trap->left.v.pos.x;
	scanline->x = (int)(trap->left.v.pos.x + 0.5f);
	scanline->w = (int)(trap->right.v.pos.x + 0.5f) - scanline->x;
	scanline->y = y;
	scanline->v = trap->left.v;
	if (trap->left.v.pos.x >= trap->right.v.pos.x) scanline->w = 0;
	vertexdiv(scanline->step, trap->left.v, trap->right.v, width);
}

struct Device
{
	Transforma_t transform;
	int width;
	int height;
	unsigned int **framebuffer;
	float **zbuffer;
	unsigned int **texture;
	int texwidth;
	int texheight;
	float max_u;
	float max_v;
	int renderstate;
	unsigned int backgroundcolor;
	unsigned int foregroundcolor;
};

#define renderstatewirframe 1
#define renderstatetexture 2
#define renderstatecolor 4

void deviceinit(Device *device, int wdith, int height, void *fb)
{
	int bufferneed = sizeof(void*)*(height * 2 + 1024) + wdith*height * 8;
	char *prt = (char*)malloc(bufferneed + 64);
	char* framebuf, *zbuf;
	int j;
	device->framebuffer = (unsigned int**)prt;
	device->zbuffer = (float**)(prt + sizeof(void*)*height);
	prt += sizeof(void*)*height * 2;
	device->texture = (unsigned int**)prt;
	prt += sizeof(void*) * 1024;
	framebuf = (char*)prt;
	zbuf = (char*)prt + wdith*height * 4;
	prt += wdith*height * 8;
	if (fb != nullptr)
	{
		framebuf = (char*)fb;
	}
	for (j = 0; j<height; j++)
	{
		device->framebuffer[j] = (unsigned int*)(framebuf + wdith * 4 * j);
		device->zbuffer[j] = (float*)(zbuf + wdith * 4 * j);
	}
	device->texture[0] = (unsigned int*)prt;
	device->texture[1] = (unsigned int*)(prt + 16);
	memset(device->texture[0], 0, 64);
	device->texwidth = 2;
	device->texheight = 2;
	device->max_u = 1.0f;
	device->max_v = 1.0f;
	device->width = wdith;
	device->height = height;
	device->backgroundcolor = 0xc0c0c0;
	device->foregroundcolor = 0;
	Transforminitial(device->transform, wdith, height);
	device->renderstate = renderstatewirframe;
}

void devicedelete(Device *device)
{
	if (device->framebuffer)
	{
		free(device->framebuffer);
		device->framebuffer = nullptr;
		device->zbuffer = nullptr;
		device->texture = nullptr;
	}
}

void Devicetextrue(Device *device, void* bits, long pitch, int w, int h)
{
	char *prt = (char*)bits;
	int j;
	for (j = 0; j<h; prt += pitch, j++)
	{
		device->texture[j] = (unsigned int*)prt;
	}
	device->texheight = h;
	device->texwidth = w;
	device->max_u = (float)(w - 1);
	device->max_v = (float)(h - 1);
}

void deviceclear(Device *device, int mode)
{
	int y, x, height = device->height;
	for (y = 0; y<device->height; y++)
	{
		unsigned int* bufprt = device->framebuffer[y];
		unsigned int vc = (height - 1 - y) * 230 / (height - 1);
		vc = (vc <<16) | (vc << 8) | vc;
		if (mode == 0)
		{
			vc = device->backgroundcolor;
		}
		for (x = device->width; x > 0; bufprt++, x--)
		{
			bufprt[0] = vc;
		}
	}
	for (y = 0; y<device->height; y++)
	{
		float* bufprt = device->zbuffer[y];
		for (x = device->width; x>0; bufprt++, x--)
		{
			bufprt[0] = 0.0f;
		}
	}
}

void drawpoint(Device *device, int x, int y, unsigned int color)
{
	if ((unsigned int)x<(unsigned int)device->width && ((unsigned int)y<(unsigned int)device->height))
	{
		device->framebuffer[y][x] = color;
	}
}

void swapint(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;


}
void drawline(Device *device, int x1, int y1, int x2, int y2, unsigned int c)
{
	/*int x, y, rem = 0;
	if (x1 == x2 && y1 == y2) {
		drawpoint(device, x1, y1, c);
	}
	else if (x1 == x2) {
		int inc = (y1 <= y2) ? 1 : -1;
		for (y = y1; y != y2; y += inc) drawpoint(device, x1, y, c);
		drawpoint(device, x2, y2, c);
	}
	else if (y1 == y2) {
		int inc = (x1 <= x2) ? 1 : -1;
		for (x = x1; x != x2; x += inc) drawpoint(device, x, y1, c);
		drawpoint(device, x2, y2, c);
	}
	else {
		int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
		int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
		if (dx >= dy) {
			if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; x <= x2; x++) {
				drawpoint(device, x, y, c);
				rem += dy;
				if (rem >= dx) {
					rem -= dx;
					y += (y2 >= y1) ? 1 : -1;
					drawpoint(device, x, y, c);
				}
			}
			drawpoint(device, x2, y2, c);
		}
		else {
			if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; y <= y2; y++) {
				drawpoint(device, x, y, c);
				rem += dx;
				if (rem >= dy) {
					rem -= dy;
					x += (x2 >= x1) ? 1 : -1;
					drawpoint(device, x, y, c);
				}
			}
			drawpoint(device, x2, y2, c);
		}
	}*/
	int dx = abs(x2 - x1),
		dy = abs(y2 - y1),
		yy = 0;

	if (dx < dy) {
		yy = 1;
		swapint(x1, y1);
		swapint(x2, y2);
		swapint(dx, dy);
	}

	int ix = (x2 - x1) > 0 ? 1 : -1,
		iy = (y2 - y1) > 0 ? 1 : -1,
		cx = x1,
		cy = y1,
		n2dy = dy * 2,
		n2dydx = (dy - dx) * 2,
		d = dy * 2 - dx;

	if (yy) { // 如果直线与 x 轴的夹角大于 45 度
		while (cx != x2) {
			if (d < 0) {
				d += n2dy;
			}
			else {
				cy += iy;
				d += n2dydx;
			}
			drawpoint(device, cy, cx, c);
			cx += ix;
		}
	}
	else { // 如果直线与 x 轴的夹角小于 45 度
		while (cx != x2) {
			if (d < 0) {
				d += n2dy;
			}
			else {
				cy += iy;
				d += n2dydx;
			}
			drawpoint(device, cx, cy, c);
			cx += ix;
		}
	}


}

void drawcircle(Device *device, int xc, int yc, int r, unsigned int c)
{
	int y=r;
	int x=0;
	int d = 1 - r;
	while (y>x)
	{
		drawpoint(device, x, y, c);
		if (d<0)
		{
			d = d + 2 * x +3;
		}
		else
		{
			d = d + 2 * x - 2 * y + 5;
			y--;
		}
		x++;
	}
}


unsigned int devicetextureread(Device *device, float u, float v)
{
	int x, y;
	u = u*device->max_u;
	v = v*device->max_v;
	x = (int)(u + 0.5);
	y = (int)(v + 0.5);
	x = CMID(x, 0, device->texwidth - 1);
	y = CMID(y, 0, device->texheight - 1);
	return device->texture[y][x];
}

void devicescanline(Device *device, Scanline *scanline, Light light, Vector3 eye)
{
	unsigned int*framebuffer = device->framebuffer[scanline->y];
	float* zbuffer = device->zbuffer[scanline->y];
	int x = scanline->x;
	int w = scanline->w;
	int width = device->width;
	int reder_state = device->renderstate;
	for (; w>0; x++, w--)
	{
		if (x>0 && x<width)
		{
			float rhw = scanline->v.rhw;
			if (rhw>zbuffer[x])
			{
				float w = 1.0f / rhw;
				zbuffer[x] = rhw;
			
			
			if (reder_state&renderstatecolor)
			{
				float r = scanline->v.fcolor.r*w;
				float g = scanline->v.fcolor.g*w;
				float b = scanline->v.fcolor.b*w;
				int R = (int)(r*255.0f);
				int G = (int)(g*255.0f);
				int B = (int)(b*255.0f);
				R = CMID(R, 0, 255);
				G = CMID(G, 0, 255);
				B = CMID(B, 0, 255);
				framebuffer[x] = (R << 16) | (G << 8) | (B);
			}

		    if (reder_state&renderstatetexture)
			{
				float u = scanline->v.tc.u*w;
				float v = scanline->v.tc.v*w;
				callight(scanline->v, light, eyepos);
				unsigned int cc = devicetextureread(device, u, v);
				framebuffer[x] = cc+ RGBtoh(scanline->v);
			}
		}
	}
		vertexadd(scanline->v, scanline->step);
		if (x >= width)
			break;
	}

}

void devicerendertrap(Device *device, Trapezoide *trap, Light light, Vector3 eye)
{
	Scanline scanline;
	int j, top, bottom;
	top = (int)(trap->top + 0.5f);
	bottom = (int)(trap->bottom + 0.5f);
	for (j = top; j < bottom; j++) {
		if (j >= 0 && j < device->height) {
			trapeziodedge(trap, (float)j + 0.5f);
			scanlineinit(trap, &scanline, j);
			devicescanline(device, &scanline,light,eye);
		}
		if (j >= device->height) break;
	}
}

void device_draw_primitive(Device *device, Vertex *v1,
	Vertex *v2, Vertex *v3, Light light, Vector3 eye) {
	Vector3 p1, p2, p3, c1, c2, c3;
	int render_state = device->renderstate;

	calnormal(*v1, *v2, *v3);
	
	Transformapplytovector(device->transform, c1, v1->pos);
	Transformapplytovector(device->transform, c2, v2->pos);
	Transformapplytovector(device->transform, c3, v3->pos);



	if (Frustumculling(&c1)) return;
	if (Frustumculling(&c2)) return;
	if (Frustumculling(&c3)) return;


	// 归一化
	getviewprotpostion(device->transform, p1, c1);
	getviewprotpostion(device->transform, p2, c2);
	getviewprotpostion(device->transform, p3, c3);
	
	// 纹理或者色彩绘制
	if (render_state & (renderstatetexture | renderstatecolor) ){
		Vertex t1 = *v1, t2 = *v2, t3 = *v3;
		Trapezoide traps[2];
		int n;
		
		t1.pos = p1;
		t2.pos = p2;
		t3.pos = p3;
		t1.pos.w = c1.w;
		t2.pos.w = c2.w;
		t3.pos.w = c3.w;

		vertexrhwinit(t1);	// 初始化 w
		vertexrhwinit(t2);	// 初始化 w
		vertexrhwinit(t3);	// 初始化 w

							// 拆分三角形为0-2个梯形，并且返回可用梯形数量
		n = trianletotrapezoid(traps, t1, t2, t3);

		if (n >= 1)
			devicerendertrap(device, &traps[0],light,eye);
			

		if (n >= 2)
			devicerendertrap(device, &traps[1],light,eye);
	
	}

	if (render_state & renderstatewirframe) {		// 线框绘制
		drawline(device, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, device->foregroundcolor);
		drawline(device, (int)p1.x, (int)p1.y, (int)p3.x, (int)p3.y, device->foregroundcolor);
		drawline(device, (int)p3.x, (int)p3.y, (int)p2.x, (int)p2.y, device->foregroundcolor);
		//drawcircle(device, (int)p3.x, (int)p3.y, 100, device->foregroundcolor);
	}
}

