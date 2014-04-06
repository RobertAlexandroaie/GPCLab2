#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}

double distanceTox(double x1) {
	double dx = fabs((int) x1 - x1);

	if (dx > 0.5) {
		dx = 1.0 - dx;
	}

	return dx;
}

//2.1 f(x) = d(x)/x V x \ x=0;
void Display3() {
	double xmax = 0.0, ymax = 1.0;
	double ratia = 0.05;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double x = ratia; x <= 100.0; x += ratia) {
		double x1, y1;
		x1 = x;
		double dx = distanceTox(x1);
		xmax = (xmax > x1) ? xmax : x1;

		y1 = dx / x;
		ymax = (ymax > y1) ? ymax : y1;

		printf("x1=%f; dtx=%f; -x=%d; +x=%d	y1=%f;\n", x1, dx, (int) x1,
				((int) x1) + 1, y1);
	}

	glVertex2f(0.0, 1.0);
	for (double x = ratia; x <= 100.0; x += ratia) {
		double x1, y1;
		x1 = x;
		double dx = distanceTox(x1);

		y1 = dx / x;

		x1 /= 33;
		//y1 /= ymax;
		printf("x1=%f; dtx=%f; -x=%d; +x=%d	y1=%f;\n", x1, dx, (int) x1,
				((int) x1) + 1, y1);

		glVertex2f(x1, y1);
	}
	glEnd();
}

//2.2.1 melcul lui Pascal
void Display4() {
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double t;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (t = -pi + ratia; t < pi; t += ratia) {
		double x1, y1;
		x1 = 2 * (a * cos(t) + b) * cos(t);
		y1 = 2 * (a * cos(t) + b) * sin(t);
		glVertex2f(x1, y1);
	}
	glEnd();
}

//2.2.2 trisectoarea anului
void Display5() {
	double a = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.01;

	double t;
	double i, j;

	double ratie1 = 0.100, ratie2 = 0.095;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_TRIANGLES);
	for (i = 0.95, j = 0.88; i > 0.2 && j > 0.2; i -= ratie1, j -= ratie2) {
		glVertex2f(-1, 1);
		glVertex2f(-0.07, i);
		glVertex2f(-0.07, j);
		ratie1 -= 0.005;
		ratie2 -= 0.0052;
	}
	glEnd();

	ratie1 = 0.100, ratie2 = 0.095;
	glBegin(GL_TRIANGLES);
	for (i = -0.80, j = -0.73; i < -0.2 && j < -0.2; i += ratie1, j += ratie2) {
		glVertex2f(-1, 1);
		glVertex2f(j, 0.15);
		glVertex2f(i, 0.15);
		ratie1 -= 0.005;
		ratie2 -= 0.0052;
	}
	glEnd();

	glColor3f(0.01, 0.01, 1.0); // albastru
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t != pi / 6 && t != -pi / 6) {
			double x1, y1;
			x1 = a / (4 * cos(t) * cos(t) - 3);
			y1 = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);
			if (x1 < 0 && y1 > 0) {
				glColor3f(0.01, 0.01, 1.0); // albastru
				glVertex2f(x1, y1);
			}
		}
	}
	glEnd();
	glColor3f(1, 0.1, 0.1); // rosu

	glColor3f(1, 1, 1); //alb
	glBegin(GL_QUADS);
	glVertex2f(-1, 0.65);
	glVertex2f(-0.2, 0.19);
	glVertex2f(0, -0.5);
	glVertex2f(-1, 0.15);
	glEnd();
}

//2.2.3 cicloida
void Display6() {
	double a = 0.1, b = 0.2;
	double ratia = 0.01;
	double t;

	glColor3f(1, 0.1, 0.1); // rosu

	glBegin(GL_LINE_STRIP);
	for (t = -10; t < 10; t += ratia) {
		double x1, y1;
		x1 = (a * t) - (b * sin(t));
		y1 = a - (b * cos(t));
		glVertex2f(x1, y1);
	}
	glEnd();
}

//2.2.4 epicicloida
void Display7() {
	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double R = 0.1;
	double r = 0.3;
	double t;

	glColor3f(1, 0.1, 0.1); // rosu

	glBegin(GL_LINE_STRIP);
	for (t = 0; t <= 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R + r) * cos(r / R * t) - r * cos(t + r / R * t);
		y1 = (R + r) * sin(r / R * t) - r * sin(t + r / R * t);
		glVertex2f(x1, y1);
	}
	glEnd();
}

//2.2.5 hipocicloida
void Display8() {
	double R = 0.1;
	double r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double t;

	glColor3f(1, 0.1, 0.1); // rosu

	glBegin(GL_LINE_STRIP);
	for (t = 0; t <= 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R - r) * cos(r / R * t) - r * cos(t - r / R * t);
		y1 = (R - r) * sin(r / R * t) - r * sin(t - r / R * t);
		glVertex2f(x1, y1);
	}
	glEnd();
}

//3.1 lemniscata lui Bernoulli
void Display9() {
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double ratia = 0.001;
	double r;
	double t;

	glColor3f(1, 0.1, 0.1); // rosu

	glBegin(GL_LINE_LOOP);
	for (t = -pi / 4; t <= pi / 4; t += ratia) {
		double x1, y1;
		r = -a * sqrt(2 * cos(2 * t));
		x1 = r * cos(t);
		y1 = r * sin(t);
		glVertex2f(x1, y1);
	}

	for (t = -pi / 4; t <= pi / 4; t += ratia) {
		double x1, y1;
		r = a * sqrt(2 * cos(2 * t));
		x1 = r * cos(t);
		y1 = r * sin(t);
		glVertex2f(x1, y1);
	}
	glEnd();
}

//3.2 spirala logaritmica
void Display10() {
	double a = 0.02;
	double e = 2.7182818284;
	double ratia = 0.01;
	double r;
	double t;

	glColor3f(1, 0.1, 0.1); // rosu

	glBegin(GL_LINE_STRIP);
	for (t = 0; t <= 1000; t += ratia) {
		double x1, y1;
		r = a * pow(e, (t + 1));
		x1 = r * cos(t);
		y1 = r * sin(t);
		glVertex2f(x1, y1);
	}

	glEnd();
}
void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display10();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
