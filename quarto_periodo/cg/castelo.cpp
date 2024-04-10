/*
 * FreeGLUT Shapes Demo
 *
 * Autora: Yasmine Martins da Costa e Silva
 * Computacao Grafica
 * Codigo Tarefa Aula 6: Castelo GLUT/OpenGL
 */
 
// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__ // MacOS
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else // Windows e Linux
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <cstdlib>

#include "formas.h"
#define ESC 27

//Variaveis Globais usadas para definicao de cores
float R,G,B;


// Declaracoes antecipadas (forward) de funcoes para as funcoes callback do OpenGL
void init(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void display(void);


/*
 * Funcao principal
 */
int main(int argc, char** argv){
    glutInit(&argc, argv); // Passagens de parametros C para o glut
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
    glutInitWindowSize (1080, 1080);  // Tamanho da janela do OpenGL
    glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
    glutCreateWindow ("Computação Grafica: Castelo 2D"); // Da nome para uma janela OpenGL
    init(); // Chama a funcao init();
    glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
    glutDisplayFunc(display); //funcao callback de desenho
    glutKeyboardFunc(keyboard); //funcao callback do teclado
    glutSpecialFunc(keyboard_special);	//funcao callback do teclado especial
    glutMainLoop(); // executa o loop do OpenGL
    return EXIT_SUCCESS; // retorna 0 para o tipo inteiro da funcao main()
}



/*
 * Inicializa alguns parametros do GLUT
 */
void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
    R = 0.0;
    G = 0.0;
    B = 0.0;
}


/*
 * Ajusta a projecao para o redesenho da janela
 */
void reshape(int w, int h)
{
	// Reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    // Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);
	
    glOrtho (-(w/2), (w/2),-(h/2),(h/2), -1 ,1);   // Nesse caso, ficamos com a quantidade de pixels variavel,
                                                    // dependente da largura e altura da janela, e o
                                                    // centro dos eixos continua a se localizar no centro
                                                    // da tela.
    
   // muda para o modo GL_MODELVIEW (nao pretendemos alterar a projecao
   // quando estivermos desenhando na tela)
	glMatrixMode(GL_MODELVIEW);
}

/*
 * Funcao usada na funcao callback para controlar as teclas comuns (1 Byte) do teclado
 */
void keyboard(unsigned char key, int x, int y){
    switch (key) { // key - variavel que possui valor ASCII da tecla precionada
        case ESC: exit(EXIT_SUCCESS); break; //encerra o programa com sucesso
    }
}

/*
 *Funcao usada na fucao callback para controlar as teclas especiais (2 Byte) do teclado
 */
void keyboard_special(int key, int x, int y){
    switch(key){
      case GLUT_KEY_F1: R=0.0; G=0.0; B=1.0; break; // F1: muda a cor para azul
      case GLUT_KEY_F2: R=0.0; G=1.0; B=0.0; break; // F2: muda a cor para verde
      case GLUT_KEY_F3: R=1.0; G=0.0; B=0.0; break; // F3: muda a cor para vermelho
      default: break;
    }
    glutPostRedisplay();
}

/*
* Função da torre
*/

void torre(){
	glTranslatef(100,100, 0);
	glRotatef(180, 0, 0, 0);	
	glTranslatef(100,0,0);
	retanguloVertical();
	
	glColor3f(0.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 1);
	glTranslatef(-410,180, 0);
	glRotatef(0, 0, 0, 1);
	desenhaCirculo(100,100,true);
	
	glColor3f(1.0,0,0);
	glTranslatef(340,-170,0);
	glRotatef(180,0,0,0);
	triangulo();
	
	glColor3f(1,1,0);
	glTranslatef(610,-400,0);
	retanguloHorizontal();
	
	glTranslatef(-170, -135,0);
	retanguloHorizontal();
	
	glTranslatef(170, -135,0);
	retanguloHorizontal();
	
	glTranslatef(40,1150,0);
	bandeira();
	
	glTranslatef(-180,-180,0);
	traco();
	
}
/*
Desenvolvendo a frente do castelo (porta e retangulo principal)
*/
void frente(){
	base();
	glTranslatef(260,0,0);
	quadrado();
	glTranslatef(190,160,0);
	glColor3f(1,1,0);
	desenhaCirculo(45,100,true);
	glTranslatef(0,0,0);
	glColor3f(0,0,0);
	desenhaCirculo(35,100,true);
	glTranslatef(0,36,0);
	glColor3f(1,1,0);
	desenhaCirculo(18,100,true);
	glTranslatef(-20,235,0);
	glColor3f(1,0.5,0);
	retanguloHorizontal();
	glTranslatef(400,0,0);
	retanguloHorizontal();
	glTranslatef(120,-300,0);
	retanguloHorizontal();
	glTranslatef(-630,0,0);
	retanguloHorizontal();
}
/*
 * Funcao usada na funcao callback para desenhar na tela
 */
void display(void){
	//Limpa o Buffer de Cores e reinicia a matriz
    glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();

	/* COMANDOS:
		retanguloHorizontal()
		retanguloVertical()
		quadrado()
		desenhaCirculo(float raio, int num_linhas,bool preenchido)
		
		glRotatef(180, 1, 0, 0);// grau, x, y, z
	    glTranslatef(-200, -100, 0); x, y, z
	    glScalef(-0.5, -1, 1);
		*/
	
    // Transformacoes usadas no triangulo com vertice esquerdo na origem dos eixos cartesianos
	glScalef(0.5, 0.5, 0);
	glTranslatef(600,0,0);
	torre();
	
	glScalef(2,2,0);
	glRotatef(180,0,1,0);
	glTranslatef(500,-245,0);
	torre();
	glScalef(2,2,0);
	glTranslatef(-590,-200,0);
	torre();
	glTranslatef(-580,-1160,0);
	frente();
	
    glFlush(); // manda o OpenGl renderizar as primitivas

}


