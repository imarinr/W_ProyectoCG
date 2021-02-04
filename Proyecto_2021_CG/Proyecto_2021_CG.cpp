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
#include "door_tex.cpp"
#include "win_tex.cpp"
#include "wall_tex.cpp"

#include "letra_H.cpp"
#include "letra_C.cpp"
#include "letra_E.cpp"
#include "letra_L.cpp"
#include "letra_M.cpp"
#include "letra_O.cpp"

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
int xi = 10;
int anchoLetra = 22;
int altoLetra = 20;
int interlineado = 3;
int yi = 175;
float x = 10, y = 175;
float t = 0.0;
int estadoActual = EDO_INICIAL;
GLuint texturaW, texturaPuerta, texturaVentana, texturaPared;
GLuint texturaLetras[6];

/*vectores de iluminacion*/
GLfloat luz_color[] = { 1, 1, 1, 1 };
GLfloat luz_ambient[] = { 0.2, 0.2, 0.2, 1 };

GLfloat luz0_pos[] = { 50, 5, 0, 1.0 }; //posicion de la luz

GLfloat luz1_pos[] = { 100, 5, 0, 1 };

GLfloat luz2_pos[] = {150, 5, 0, 1 };

GLfloat spot_dir[] = { 0, 1, 0 };

/*vectores de color de material*/
GLfloat mat_seg2_color[] = { 0.5, 0.5, 0.5, 1.0 };//color del material
GLfloat mat_seg2_specular[] = { 0.8, 0.8, 0.8, 1.0 };//componente brillante del material
GLfloat mat_seg2_emision[] = { 0.3, 0.3, 0.3, 1.0 }; // color que emite el material

GLfloat mat_seg3_color[] = { 0.5, 0.5, 0, 1 };
GLfloat mat_seg3_specular[] = { 0.9, 0.9, 0, 1.0 };
GLfloat mat_seg3_emision[] = { 0.5, 0.5, 0, 1.0 };

GLfloat mat_pared_color[] = { 0, 0, 0, 1 };
GLfloat mat_pared_specular[] = { 0.7, 0.7, 0.7, 1 };
GLfloat mat_pared_emision[] = { 1, 1, 1, 1 };

/*firmas de funciones*/
void dibujarW();
void caidaLibre(float);
void rebote(float);
void animacion();
void mostrarTexto(int, int, char*, int);
void iluminacion();
void dibujarCasa();
void dibujarLetrero();
void ventana();
void puerta();
void pared();

/*
* funciones necesarias para la visualizacion
*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//std::cout << "dibujando en ( " << x << ", " << y << " )" << std::endl;
	iluminacion();

	//dibujo del fondo
	dibujarCasa();
	dibujarLetrero();

	//Dibujo de la letra W
	glPushMatrix();
	glTranslatef(x, y, 0);
	dibujarW();
	glPopMatrix();

	glDisable(GL_LIGHTING);

	// textos
	glColor3f(0, 0.3, 0.6);
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
	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

void init() {
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glLoadIdentity();
	glOrtho(0, 199, 0, 199, -1, 1);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_COLOR_MATERIAL);
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
	glGenTextures(1, &texturaW);
	glBindTexture(GL_TEXTURE_2D, texturaW);
	gluBuild2DMipmaps(GL_TEXTURE_2D, gimp_image.bytes_per_pixel, gimp_image.width, gimp_image.height, GL_RGB, GL_UNSIGNED_BYTE, gimp_image.pixel_data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE ,GL_REPLACE);

	// Creacion del primer segmento
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2d(0, 0);
	glVertex2f(0, 20);
	glTexCoord2d(0, 1);
	glVertex2f(0, 1);
	glTexCoord2d(1, 0.3);
	glVertex2f(3, 6);
	glTexCoord2d(1, 0);
	glVertex2f(3, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// segundo segmento
	//Material
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_seg2_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_seg2_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_seg2_emision);
	glMaterialf(GL_FRONT, GL_SHININESS, 9);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glNormal3i(1, -1, 1);
	glVertex2f(4, 0);
	glNormal3i(-1, -1, 1);
	glVertex2f(15, 20);
	glNormal3i(-1, 1, 1);
	glVertex2f(11, 20);
	glNormal3i(1, 1, 1);
	glVertex2f(0, 0);
	glEnd();

	//tercer segmento
	//material
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_seg3_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_seg3_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_seg3_emision);
	glMaterialf(GL_FRONT, GL_SHININESS, 9);

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

void iluminacion()
{
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_color);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_color);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luz_color);//difusa = no brillante
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_color);//especular = luz brillante
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_color);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luz_color);
	glLightfv(GL_LIGHT0, GL_POSITION, luz0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, luz1_pos);
	glLightfv(GL_LIGHT2, GL_POSITION, luz2_pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 75);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 65);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 55);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
}

void dibujarCasa()
{
	pared();
	puerta();
	ventana();
	
}

void ventana() {
	//textura de la ventana
	glGenTextures(1, &texturaVentana);
	glBindTexture(GL_TEXTURE_2D, texturaVentana);
	gluBuild2DMipmaps(GL_TEXTURE_2D, gimp_window.bytes_per_pixel, gimp_window.width, gimp_window.height, GL_RGB, GL_UNSIGNED_BYTE, gimp_window.pixel_data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1);
	glVertex2i(142, 35);
	glTexCoord2d(1, 1);
	glVertex2d(190, 35);
	glTexCoord2d(1, 0);
	glVertex2i(190, 130);
	glTexCoord2d(0, 0);
	glVertex2i(142, 130);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void puerta() {
	//textura de la puerta
	glGenTextures(1, &texturaPuerta);
	glBindTexture(GL_TEXTURE_2D, texturaPuerta);
	gluBuild2DMipmaps(GL_TEXTURE_2D, gimp_door.bytes_per_pixel, gimp_door.width, gimp_door.height, GL_RGB, GL_UNSIGNED_BYTE, gimp_door.pixel_data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.1, 0.3, 0.5);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex2i(28, 0);
	glTexCoord2d(1, 1);
	glVertex2i(85, 0);
	glTexCoord2d(1, 0);
	glVertex2i(85, 130);
	glTexCoord2d(0, 0);
	glVertex2i(28, 130);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void pared() {
	//material de la pared
	/*glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_pared_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_pared_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_pared_emision);
	glMaterialf(GL_FRONT, GL_SHININESS, 9);*/
	//textura de la pared
	glGenTextures(1, &texturaPared);
	glBindTexture(GL_TEXTURE_2D, texturaPared);
	gluBuild2DMipmaps(GL_TEXTURE_2D, gimp_wall.bytes_per_pixel, gimp_wall.width, gimp_wall.height, GL_RGB, GL_UNSIGNED_BYTE, gimp_wall.pixel_data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex2i(0, 0);
	glTexCoord2d(10, 10);
	glVertex2i(199, 0);
	glTexCoord2d(0, 10);
	glVertex2i(199, 199);
	glTexCoord2d(0, 0);
	glVertex2i(0, 199);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void dibujarLetrero() {
	glGenTextures(6, texturaLetras);
	glBindTexture(GL_TEXTURE_2D, texturaLetras[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, letra_E.bytes_per_pixel, letra_E.width, letra_E.height, GL_RGB, GL_UNSIGNED_BYTE, letra_E.pixel_data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	//W'E'LCOME
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + anchoLetra, yi + altoLetra);
	glTexCoord2d(0, 1);
	glVertex2i(xi + anchoLetra, yi);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (anchoLetra * 2), yi);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (2 * anchoLetra), yi + altoLetra);
	glEnd();
	//WELCOM'E'
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (6 * anchoLetra), yi + altoLetra);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (6 * anchoLetra), yi);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (7 * anchoLetra), yi);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (7 * anchoLetra), yi + altoLetra);
	glEnd();
	//HOM'E'
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (5 * anchoLetra), yi - interlineado);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (5 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (6 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (6 * anchoLetra), yi - interlineado);
	glEnd();
	//WELC'O'ME
	glBindTexture(GL_TEXTURE_2D, texturaLetras[1]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, letra_O.bytes_per_pixel, letra_O.width, letra_O.height, GL_RGB, GL_UNSIGNED_BYTE, letra_O.pixel_data);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (4 * anchoLetra), yi + altoLetra);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (4 * anchoLetra), yi);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (5 * anchoLetra), yi);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (5 * anchoLetra), yi + altoLetra);
	glEnd();
	//H'O'ME
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (3 * anchoLetra), yi - interlineado);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (3 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (4 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (4 * anchoLetra), yi - interlineado);
	glEnd();
	//WELCO'M'E
	glBindTexture(GL_TEXTURE_2D, texturaLetras[2]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, letra_M.bytes_per_pixel, letra_M.width, letra_M.height, GL_RGB, GL_UNSIGNED_BYTE, letra_M.pixel_data);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (5 * anchoLetra), yi + altoLetra);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (5 * anchoLetra), yi);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (6 * anchoLetra), yi);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (6 * anchoLetra), yi + altoLetra);
	glEnd();
	//HO'M'E
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (4 * anchoLetra), yi -interlineado);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (4 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (5 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (5 * anchoLetra), yi - interlineado);
	glEnd();
	//WE'L'COME
	glBindTexture(GL_TEXTURE_2D, texturaLetras[3]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, letra_L.bytes_per_pixel, letra_L.width, letra_L.height, GL_RGB, GL_UNSIGNED_BYTE, letra_L.pixel_data);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (2 * anchoLetra), yi + altoLetra);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (2 * anchoLetra), yi);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (3 * anchoLetra), yi);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (3 * anchoLetra), yi + altoLetra);
	glEnd();
	//WEL'C'OME
	glBindTexture(GL_TEXTURE_2D, texturaLetras[4]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, letra_C.bytes_per_pixel, letra_C.width, letra_C.height, GL_RGB, GL_UNSIGNED_BYTE, letra_C.pixel_data);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (3 * anchoLetra), yi + altoLetra);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (3 * anchoLetra), yi);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (4 * anchoLetra), yi);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (4 * anchoLetra), yi + altoLetra);
	glEnd();
	//'H'OME
	glBindTexture(GL_TEXTURE_2D, texturaLetras[5]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, letra_H.bytes_per_pixel, letra_H.width, letra_H.height, GL_RGB, GL_UNSIGNED_BYTE, letra_H.pixel_data);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2i(xi + (2 * anchoLetra), yi - interlineado);
	glTexCoord2d(0, 1);
	glVertex2i(xi + (2 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 1);
	glVertex2i(xi + (3 * anchoLetra), yi - interlineado - altoLetra);
	glTexCoord2d(1, 0);
	glVertex2i(xi + (3 * anchoLetra), yi - interlineado);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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
