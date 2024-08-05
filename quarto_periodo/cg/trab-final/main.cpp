// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <mmsystem.h>

#include "map.h"
#include "brick.h"

#include <sstream>
using std::stringstream;
#include <string>
using std::string;

int isFullscreen = 1; // Flag para controlar o estado da tela cheia
int windowWidth = 800; // Largura padrão da janela
int windowHeight = 600; // Altura padrão da janela
int windowPosX = 100; // Posição X inicial da janela
int windowPosY = 100; // Posição Y inicial da janela

/*
 Declaracoes antecipadas (forward) das funcoes (assinaturas das funcoes)
 */

void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);

/*
 * Inicializa alguns parametros do GLUT
 */
void init(void)
{
	glClearColor (0.4, 0.4, 0.4, 0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer

	// Ativa o modelo de sombreamento de Gouraud.
	glShadeModel(GL_SMOOTH);
}

void toggleFullscreen()
{
	
	if (isFullscreen)
	{
		 // Se a janela está atualmente em tela cheia, vai para ao modo janela
		glutReshapeWindow(windowWidth, windowHeight);
		glutPositionWindow(windowPosX, windowPosY);
		isFullscreen = 0;
	}
	else
	{
		// Se a janela está atualmente em modo janela, vai para o modo tela cheia
		windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		windowPosX = glutGet(GLUT_WINDOW_X);
		windowPosY = glutGet(GLUT_WINDOW_Y);
		glutFullScreen();
		isFullscreen = 1;
	}
}

/*
 * Controla os desenhos na tela
 */
void display()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cores e reinicia a matriz
	glLoadIdentity();
	criaMapa();
	glutSwapBuffers();
}

/*
 * Ajusta a projecao para o redesenho da janela
 */

void reshape (int w, int h)
{
	// Muda para o modo de projecao e reinicializa o sistema de coordenadas
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	// Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);	
	
	//Ângulo de Visão (fovy), Proporção da Tela (aspect), Plano Próximo (near),Plano Distante (far) 
	gluPerspective(55, (float)w / (float)h, 5.0, 100.0);

	gluLookAt(
	
	   //A câmera está posicionada no ponto:
		8.5, 4.0, 23.0, 	
		
		//A câmera está olhando para o ponto:
		8.5, 7.0, 0.0, 	
		
		//O vetor UP está definido como:
		0.0, 1.0, 0.0			  
			  
	);

	glMatrixMode (GL_MODELVIEW);
	
	glLoadIdentity();
}

/*
 * Controle das teclas comuns do teclado
 */
void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)   // Tecla ESC para sair do programa
	{
		exit(0);
	}
	else if (key == 'f' || key == 'F')     // Tecla F para alternar entre tela cheia e modo janela
	{
		toggleFullscreen();
	}
}

/*
 * Controle das teclas especiais do teclado
 */
void specialKeys(int key, int x, int y)
{
}

/*
 * Função Principal
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);// Passagens de parametro C para o glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow ("BrickGame - Tank 3D"); //Da nome para uma janela OpenGL
	glutFullScreen();

	init();// Chama funcao init();
	glutReshapeFunc(reshape);// Função callback para redesenhar a tela
	glutKeyboardFunc(keyboard);// Função callback do teclado
	glutSpecialFunc(specialKeys);// Função callback do teclado (teclas especiais)
	glutDisplayFunc(display);// Função callback de desenho

	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat light_color[] = {0.0, 0.0, 1.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING); //Ativa o modelo de iluminacao
	glEnable(GL_LIGHT0); //Ativa a Luz 0. O OpenGL suporta pelo menos 8 pontos de luz

	// Inicia as caracteristicas gerais dos materiais
	GLfloat mat_ambient_diffuse[] = {.0, 0.0, 0.0, 0.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL); //Um ou mais parametros do material rastreiam a cor atual do glColor.

	glutMainLoop();

	return EXIT_SUCCESS;
}
