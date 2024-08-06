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

/* Inclui o arquivo header com a textura */
#include "glm.h"
#include "glut_text.h"
#include "map.h"
#include "montagem.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <sstream>
using std::stringstream;
#include <string>
using std::string;


/*
 * Declaracao de constantes e variaveis
 */
#define MAX_FPS 70 // Maximo de Frames Por Segundo (FPS) desejado
#define FPS 60 // FPS desejado atualmente
#define KEYFRAME_RATE 3 // taxa de repeticoes do keyframe da animacao nos quadros da video
#define POSY -1.04  //posicao do modelo 3D no eixo y
#define CAMZ 5.0    //posicao da camera no eixo z

#define ESC 27 // ASCII para a tecla ESC
#define SPACE 32 // ASCII para a tecla de ESPACO
#define teclaA 65
#define teclaD 68
#define teclaa 97
#define teclad 100
#define teclaF 70
#define teclaf 102
#define SETA_CIMA "\033[A"
#define SETA_BAIXO "\033[B"
#define SETA_ESQUERDA "\033[D"
#define SETA_DIREITA "\033[C"
#define ENTER 13
#define BACKSPACE 127

int isFullscreen = 1; // Flag para controlar o estado da tela cheia
int windowWidth = 920; // Largura padrão da janela
int windowHeight = 740; // Altura padrão da janela
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
 
void keyboard(unsigned char key, int x, int y)
{
    case SPACE: if(!is_paused) keyPlayAnimation(jumping); break; // Tecle SPACE para ativar a animacao de salto
        case 'p':case 'P':
            is_paused = !is_paused;
            animation_id = paused;
            keyframe = 0;
        break;
    	case 'f':case 'F':
    		if(!is_paused) keyPlayAnimation(shooting); break;
        case 'd': case 'D': //Rotaciona a camera em torno do eixo Y no sentido anti-horario
            float radianos;
            cam_roty += graus;
            if (cam_roty >= 360.0) cam_roty = 0.0;
            radianos = (cam_roty * M_PI)/180.0;
            camx = 0.0; camz = CAMZ;
            camx =  camx*cosf(radianos) + camz*sinf(radianos);
            camz =  - camx*sinf(radianos) + camz*cosf(radianos) ;
        break;
        case 'a': case 'A': //Rotaciona a camera em torno do eixo Y no sentido horario
            cam_roty -= graus;
            if (cam_roty <= -360.0) cam_roty = 0.0;
            radianos = (cam_roty * M_PI)/180.0;
            camx = 0.0; camz = CAMZ;
            camx =    camx*cosf(radianos) + camz*sinf(radianos);
            camz =  - camx*sinf(radianos) + camz*cosf(radianos);
        break;
        case 'w': case 'W': //Rotaciona a camera em torno do eixo X no sentido anti-horatio
            if (cam_rotx >= 360.0) cam_rotx = 0.0;
            cam_rotx += graus;
            if (cam_rotx >= 52.0 && cam_rotx < 309.0) cam_up = -1.0;
            else cam_up = 1.0;
            radianos = (cam_rotx * M_PI)/180.0;
            camy = 0.0; camz = CAMZ;
            camy =  camy*cosf(radianos) - camz*sinf(radianos);
            camz =  camy*sinf(radianos) + camz*cosf(radianos);
        break;
        case 's': case 'S': //Rotaciona a camera em torno do eixo X no sentido horatio
            if (cam_rotx <= 0.0) cam_rotx = 360.0;
            cam_rotx -= graus;
            if (cam_rotx >= 52.0 && cam_rotx < 309.0) cam_up = -1.0;
            else cam_up = 1.0;
            radianos = (cam_rotx * M_PI)/180.0;
            camy = 0.0; camz = CAMZ;
            camy =  camy*cosf(radianos) - camz*sinf(radianos);
            camz =  camy*sinf(radianos) + camz*cosf(radianos);
        break;
        case 'r': case 'R': //Reseta as posicoes da camera e do objeto para os parametroz iniciais
            cam_rotx -= 0.0; cam_roty -= 0.0;
            camx = 0.0; camy =  0.0; camz = CAMZ;
            posx = 0.0; posy = POSY; posz = 0.0;
            rotx = 0.0; roty =  0.0; rotz = 0.0;
        break;

        case ESC: // Tecla ESC para sair do programa
            exit(EXIT_SUCCESS); break;
	    case 'F': case 'f': 
		    toggleFullscreen(); break;
	
}
*/
/*
 * Atualiza a direcao do personagem

void update_direcaoGirl(){
    if(rotyGirl ==  0.0 || rotyGirl == 360.0){
        direcao = frente;
        roty = 0.0;
    }
    if(roty == 180.0 || roty == -180.0){
        direcao = tras;
        roty = 180.0;
    }
    if(roty ==  90.0) direcao = direita;
    if(roty == -90.0 || roty == 270.0) direcao = esquerda;
}
*/ 
/*
 * Atualiza a direcao do personagem

void update_direcaoBoy(){
    if(roty ==  0.0 || roty == 360.0){
        direcao = frente;
        roty = 0.0;
    }
    if(roty == 180.0 || roty == -180.0){
        direcao = tras;
        roty = 180.0;
    }
    if(roty ==  90.0) direcao = direita;
    if(roty == -90.0 || roty == 270.0) direcao = esquerda;
}*/ 
/*
 * Controle das teclas especiais do teclado
 */
void specialKeys(int key, int x, int y)
{
    switch(key){    
        case teclaA: case teclaa: // Move o personagem para esquerda
            //posx -= deslocamento;
            break;
/*
        //Use as setas do teclado para movimentar o personagem
        case GLUT_KEY_RIGHT: // Move o personagem para direita
            if(!is_paused){
                if(is_jumping) keyPlayAnimation(jumping);
                else if(is_shooting) keyPlayAnimation(shooting);
                else keyPlayAnimation(running);
                if(direcao==direita){
                    if(roty == 90.0) posx += deslocamento;
                    else if (roty < 90.0 ) roty -= graus;
                    else roty += graus;
                }else if (direcao == esquerda){
                    if( roty >= 180.0) roty -= graus;
                    else roty += graus;
                }else if (direcao == frente) roty += graus;
                else roty -= graus;
                update_direcao();
            }
        break;
        case GLUT_KEY_LEFT: // Move o personagem para esquerda
            if(!is_paused){
                if(is_jumping) keyPlayAnimation(jumping);
                else if(is_shooting) keyPlayAnimation(shooting);
                else keyPlayAnimation(running);
                if(direcao==esquerda){
                    if(roty == -90.0 || roty == 270.0) posx -= deslocamento;
                    else if ( roty < -90.0 || roty < 270.0 ) roty += graus;
                    else roty -= graus;
                }else if (direcao == direita){
                    if(roty >= 90.0) roty += graus;
                    else roty -= graus;
                }else if (direcao == frente) roty -= graus;
                else roty += graus;
                update_direcao();
            }
        break;
        case GLUT_KEY_UP: // Move o personagem para tras
            if(!is_paused){
                if(is_jumping) keyPlayAnimation(jumping);
                else if(is_shooting) keyPlayAnimation(shooting);
                else keyPlayAnimation(running);
                if(direcao == tras){
                    if(roty == 180.0) posz -= deslocamento;
                    else if(roty < 180.0) roty += graus;
                    else if(roty > 180.0) roty -= graus;
                }else if (direcao==frente){
                    if (roty >= 0.0) roty += graus;
                    else roty -= graus;
                }else if (direcao == direita) roty += graus;
                else roty -= graus;
                update_direcao();
            }
        break;
        case GLUT_KEY_DOWN: // Move o personagem para frente
                if(!is_paused){
                    if(is_jumping) keyPlayAnimation(jumping);
                    else if(is_shooting) keyPlayAnimation(shooting);
                    else keyPlayAnimation(running);
                    if(direcao == frente){
                        if (roty == 0.0) posz += deslocamento;
                        else if (roty < 0.0) roty += graus;
                        else if (roty > 0.0) roty -= graus;
                    }else if(direcao == tras){
                        if (roty >= 180.0) roty += graus;
                        else roty -= graus;
                    }else if(direcao == direita) roty -= graus;
                    else roty += graus;
                    update_direcao();
                }
        break;*/
    }
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
