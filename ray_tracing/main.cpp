#include "line.h"
#include "bezier_curve.h"
#include "bezier_surface.h"
#include "raytracer.h"
#include <ctime>

#define MX 1000
#define MY 1000

Vec3 standard_point[100];
Vec3 standard_matrix[4][4];
int n = 1000, m = 1000;

Vec3 viewpoint;
Vec3 **viewplain;
Color color;
Vec3 pos;
Vec3 dir;
Vec3 center;
double radius;
double reflection;
double refraction;
Raytracer tracer;

void InitialMatrix();

void InitialParameter();

int main() {
	srand((unsigned)time(NULL));
	/*
	/////////////////////bezier_curve;
	Mat M(MY, MX, CV_8UC3, Scalar::all(255));
	memset(standard_point, 0, sizeof(Vec3));
	standard_point[0].x = 50;
	standard_point[0].y = 500;
	standard_point[1].x = 200;
	standard_point[1].y = 50;
	standard_point[2].x = 612;
	standard_point[2].y = 81;
	
	standard_point[3].x = 890;
	standard_point[3].y = 700;
	standard_point[4].x = 500;
	standard_point[4].y = 500;
	
	for (int i = 0; i < n-1; ++i) {
		IntegerBresenhamline(standard_point[i].x, standard_point[i].y, standard_point[(i+1)%n].x, standard_point[(i+1)%n].y, M);
	}
	BezierCurve curve(n, standard_point);
	for (double t = 0; t < 1; t += 0.001) {
		Vec3 p = curve.GetPoint(t);
		//cout << p.x << " " << p.y << endl;
		drawpixel(p.x+0.5, p.y+0.5, M, 0);
	}
	imshow("original", M);
	imwrite("line1.png", M);
	*/

	/*
	////////////bezier_surface
	Mat M2(MY, MX, CV_8UC3, Scalar::all(255));
	InitialMatrix();
	
	//drawsurface
	BezierSurface surface(n, m, standard_matrix);
	for (double u = 0; u < 1; u += 0.005) {
		for (double v = 0; v < 1; v += 0.005) {
			Vec3 p = surface.GetPoint(u, v);
			//cout << p.x << " " << p.y << endl;
			drawpixel(p.x + 0.5, p.y + 0.5, M2);
		}
	}

	//drawcontrolline;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n - 1; ++j) {
			IntegerBresenhamline(standard_matrix[i][j].x, standard_matrix[i][j].y, standard_matrix[i][j + 1].x, standard_matrix[i][j + 1].y, M2);
		}
	}
	for (int i = 0; i <= n - 1; ++i) {
		for (int j = 0; j <= n; ++j) {
			IntegerBresenhamline(standard_matrix[i][j].x, standard_matrix[i][j].y, standard_matrix[i + 1][j].x, standard_matrix[i + 1][j].y, M2);
		}
	}

	imshow("original", M2);
	imwrite("surface.png", M2);
	waitKey(0);
	*/
	
	InitialParameter();

	tracer.camera = new Camera(viewpoint, n, m, viewplain);
	tracer.light = new Pointlight(color, pos);
	tracer.thing = new Ball(center, radius, reflection, refraction);
	tracer.Calculate();

	Mat M(m, n, CV_8UC3, Scalar::all(0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			//printf("%lf %lf %lf ", tracer.camera->viewlines[i][j].
			drawpixel(i, j, M, tracer.image[i][j]);
		}
	}
	imshow("original", M);
	imwrite("draw.png", M);
	waitKey(0);
	
	return 0;
}

void InitialParameter() {
	viewpoint = Vec3::Vec3(500, 500, -100);//相机视点
	viewplain = new Vec3*[n];
	for (int i = 0; i < n; ++i) {
		viewplain[i] = new Vec3[m];
		for (int j = 0; j < m; ++j) {
			viewplain[i][j] = Vec3::Vec3(250 + 0.5*i, 250 + 0.5*j, 0);
		}
	}
	tracer.n = n;
	tracer.m = m;
	color = Color::Color(255, 255, 255);//white light
	pos = Vec3::Vec3(700, 700, 200);
	center = Vec3::Vec3(500, 500, 100);
	radius = 100;
	reflection = 0.6;
	refraction = 0.4;
}


void InitialMatrix() {
	
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			standard_matrix[i][j].x = rand() % 1000;
			standard_matrix[i][j].y = rand() % 1000;
			standard_matrix[i][j].z = rand() % 1000;
		}
	}
	
	/*
	standard_matrix[0][0].x = 100;
	standard_matrix[0][0].y = 400;
	standard_matrix[0][1].x = 200;
	standard_matrix[0][1].y = 300;
	standard_matrix[0][2].x = 300;
	standard_matrix[0][2].y = 320;
	standard_matrix[0][3].x = 400;
	standard_matrix[0][3].y = 400;
	standard_matrix[1][0].x = 110;
	standard_matrix[1][0].y = 300;
	standard_matrix[1][1].x = 210;
	standard_matrix[1][1].y = 280;
	standard_matrix[1][2].x = 300;
	standard_matrix[1][2].y = 280;
	standard_matrix[1][3].x = 380;
	standard_matrix[1][3].y = 320;
	standard_matrix[2][0].x = 130;
	standard_matrix[2][0].y = 250;
	standard_matrix[2][1].x = 250;
	standard_matrix[2][1].y = 200;
	standard_matrix[2][2].x = 330;
	standard_matrix[2][2].y = 180;
	standard_matrix[2][3].x = 410;
	standard_matrix[2][3].y = 200;
	standard_matrix[3][0].x = 150;
	standard_matrix[3][0].y = 350;
	standard_matrix[3][1].x = 280;
	standard_matrix[3][1].y = 250;
	standard_matrix[3][2].x = 360;
	standard_matrix[3][2].y = 250;
	standard_matrix[3][3].x = 480;
	standard_matrix[3][3].y = 280;
	*/
}