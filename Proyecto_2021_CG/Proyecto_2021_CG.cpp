// Proyecto_2021_CG.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
/*
* Ivan Marin Roldan
* Computacion Grafica
* Semestre 2021-1
*/
//

#include <iostream>
#include <cmath>
#include <GL/glut.h>

#include "texture0.cpp"

/*Constantes de estados posibles*/
const int EDO_INICIAL = 0;
const int EDO_CAYENDO = 1;
const int EDO_GOLPE_SUELO = 2;
const int EDO_REBOTANDO = 3;
const int EDO_HALT = 4;

/*constantes de Cadenas de texto*/
char mensajeInicial[] = "Presione \'Espacio\' para iniciar";
char mensajeReiniciar[] = "Presione \'R\' para repetir";
int msjInicialTam = 31;
int msjReiniciarTam = 25;

/*Valores iniciales*/
float x = 10.0, y = 175.0;
float t = 0.0;
int estadoActual = EDO_INICIAL;

/*firmas de funciones*/
void dibujarW();
void caidaLibre(float);
void rebote(float);
void animacion();
void mostrarTexto(int, int, char*, int);

/*
* funciones necesarias para la visualizacion
*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//std::cout << "dibujando en ( " << x << ", " << y << " )" << std::endl;
	glPushMatrix();
	glTranslatef(x, y, 0);
	dibujarW();
	glPopMatrix();


	// textos
	glColor3f(1, 1, 1);
	switch (estadoActual) {
	case EDO_INICIAL:
		mostrarTexto(70, 15, mensajeInicial, msjInicialTam);
		break;
	case EDO_HALT:
		mostrarTexto(70, 15, mensajeReiniciar, msjReiniciarTam);
		break;
	default:
		break;
	}


	// prueba de coordenadas
	// glColor3f(0, 0, 0);
	// glPointSize(6);
	// glBegin(GL_POINTS);
	// glVertex2f(0, 0);
	// glVertex2f(199, 199);
	// glVertex2f(0, 199);
	// glVertex2f(199, 0);
	// glVertex2f(100, 100);
	// glEnd();

	glutSwapBuffers();
}

void init() {
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, 199, 0, 199, -1, 1);
}

/*
* Funciones del proyecto
*/

/*
* Funcion que dibuja la letra W
* la letra se dibuja a partir del origen de coordenadas definido en la esquina
* inferior izquierda
*/
void dibujarW() {

	//generacion de la textura del primer segmento
	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	gluBuild2DMipmaps(GL_TEXTURE_2D, gimp_image.bytes_per_pixel, gimp_image.width, gimp_image.height, GL_RGB, GL_UNSIGNED_BYTE, gimp_image.pixel_data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE ,GL_REPLACE);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2d(0, 0);
	glVertex2f(0, 20);
	glTexCoord2d(0, 1);
	glVertex2f(0, 1);
	glTexCoord2d(1, 0.3);
	glVertex2f(3, 6);
	glTexCoord2d(1, 1);
	glVertex2f(3, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 0.4);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(4, 0);
	glVertex2f(15, 20);
	glVertex2f(11, 20);
	glVertex2f(0, 0);
	glEnd();

	glColor3f(1, 0.2, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(10.0f, 10);
	glVertex2f(10.0f, 0);
	glVertex2f(13.0f, 0);
	glVertex2f(13.0f, 15);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(10.0f, 0);
	glVertex2f(13.0f, 0);
	glVertex2f(22, 20);
	glVertex2f(18, 20);
	glEnd();
}

/*
* Funcion de caida libre y(t) = 1/2 g t^2
* se calcula el valor respecto al tiempo y se resta de la posicion vertical actual
* Cuando y llega a cero, cambia el estado para detener la animacion
*/
void caidaLibre(float t) {
	//calcular caida libre
	//std::cout << "caidaLibre( t = " << t << ", y = " << y << " )" << std::endl;
	float yn = 0.5 * 9.81 * pow(t, 2);
	//restar de la posicion actual
	y -= yn;
	if (y <= 0) {
		estadoActual = EDO_GOLPE_SUELO;
		std::cout << "golpe en el suelo" << std::endl;
		y = 0;
	}
}

/*
* Funcion de rebote. y = 180e^(-0.1t)|sen((2PI/20)t)|
* Calcula la posicion y de la W durante un espacio de valores x
*/
void rebote(float t) {
	if (x <= 199) {
		y = 180 * exp(-0.1 * t) * fabs(sin((2*3.14159/20) * t));
	}
	else {
		y = 0;
		estadoActual = EDO_HALT;
		std::cout << "rebote terminado" << std::endl;
	}
}

/*
/ Funcion que ejecuta los calculos de las animaciones dependiendo del
* estado actual
*/
void animacion() {
	switch (estadoActual)
	{
	case EDO_INICIAL:

		break;
	case EDO_CAYENDO:
		//std::cout << "t = " << t << ", y = " << y << std::endl;
		caidaLibre(t);
		t += 0.01;
		glutPostRedisplay();
		break;
	case EDO_GOLPE_SUELO: // por el momento pasamos directo al rebote
		estadoActual = EDO_REBOTANDO;
		t = 0;
		break;
	case EDO_REBOTANDO:
		rebote(t);
		x += 0.5;
		t += 0.1;
		//std::cout << x << "," << y << std::endl;
		glutPostRedisplay();
		break;
	case EDO_HALT:
		break;
	default:
		break;
	}
}

void mostrarTexto(int x, int y, char *cadena, int cadenaSize) {
	glRasterPos2i(x, y);
	for (int i = 0; i < cadenaSize; i++)
	{
		//std::cout << cadena[i];
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cadena[i]);
	}
}
/*funcion de teclado*/
void teclado(unsigned char key, int xi, int yi) {
	switch (key)
	{
	case ' ': // se presiona la tecla espacio
		if (estadoActual == EDO_INICIAL)
		{
			estadoActual = EDO_CAYENDO;
			std::cout << "tecla espacio presionada, cayendo" << std::endl;
		}
		break;
	case 'R':// las letras R y r funcionan igual,
	case 'r':// provocando la repeticion de la animacion
		x = 10;
		y = 175;
		t = 0;
		estadoActual = EDO_INICIAL;
		break;
	case 27: // salir presinando escape
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    std::cout << "Universidad Nacional Autonoma de Mexico" << std::endl;
	std::cout << "Facultad de Ingenieria" << std::endl;
	std::cout << "Computacion Grafica. Semestre 2021-1" << std::endl;
	std::cout << "Marin Roldan Ivan" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(150, 50);
	glutCreateWindow("Computacion Grafica. Semestre 2021-1. Marin Roldan Ivan");

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutIdleFunc(animacion);


	glutMainLoop();

	return 0;
}
