/*
 * FreeGLUT Shapes Demo
 *
 * Autora: Yasmine Martins da Costa e Silva
 * Computacao Grafica
 * Codigo Tarefa Aula 7: Braço Robotico GLUT/OpenGL
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
#include <stdio.h>
#include <stdlib.h>
#define ESC 27

// Variaveis globais a serem usadas nas funções
int ombro = 0, cotovelo = 0, mao = 0, indicador = 0,
	polegar = 0, anelar = 0, eixoy = 0, eixox = 0;

	
// Declaracoes antecipadas (forward) de funcoes para as funcoes callback do OpenGL
void init(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void display(void);


int main(int argc, char** argv){
	glutInit(&argc, argv); // Passagens de parametros C para o glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1080,1080);	// Tamanho da janela do OpenGL
	glutInitWindowPosition(100,100); //Posicao inicial da janela do OpenGL
	glutCreateWindow("Computação Grafica: Braço Robótico");	// Da nome para uma janela OpenGL
    
	init(); // Chama a funcao init();
    glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
    glutDisplayFunc(display); //funcao callback de desenho
    glutKeyboardFunc(keyboard); //funcao callback do teclado
    
    glutMainLoop(); // executa o loop do OpenGL
    return EXIT_SUCCESS; // retorna 0 para o tipo inteiro da funcao main()
    
}	

/*
 * Inicializa alguns parametros do GLUT
 */
void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
    glEnable(GL_DEPTH_TEST); 
}


/*
 * Ajusta a projecao para o redesenho da janela
 */
void reshape (int w, int h){
	// Reinicializa o sistema de coordenadas
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    // Definindo o Viewport para o tamanho da janela
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    gluPerspective(60, (float)w/(float)h , 1.0, 9.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt(0.0,0.0,8.0,  // posicao da camera (olho)
              0.0,1.0,0.0,  // direcao da camera (geralmente para centro da cena)
              0.0,1.0,1.0); // sentido ou orientacao da camera (de cabeca para cima)

    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {	// key - variavel que possui valor ASCII da tecla precionada
	
	/*
	 * para melhor visualizar o movimento, será usado uma variação pequena nos movimentos,
	 * representado pelo calculo: (variável - 5) % 360
	 */
	
		/*
		 * Movimento da camera
		 */
	// cases responsáveis pela rotação do braço em torno do eixo y
		case 'y': eixoy = (eixoy - 5) % 360; break; 
		case 'Y': eixoy = (eixoy + 5) % 360; break; 
	// cases responsáveis pela rotação do braço em torno do eixo x	
		case 'x': eixox = (eixox - 5) % 360; break; 
		case 'X': eixox = (eixox + 5) % 360; break; 
		
		/*
		 * Movimento do braço
		 */	
	// cases responsáveis pelo movimento do "ombro" do braço
		case 'o': ombro = (ombro - 5) % 360; break;
		case 'O': ombro = (ombro + 5) % 360; break; 
	// cases responsáveis pelo movimento do "cotovelo" do braço
		case 'c': cotovelo = (cotovelo - 5) % 360; break; 
		case 'C': cotovelo = (cotovelo + 5) % 360; break;
	// cases responsáveis pelo movimento da "mao" do braço
		case 'm': mao = (mao - 5) % 360; break; 
		case 'M': mao = (mao + 5) % 360; break; 
		
		/*
		 * Movimento dos "dedos"
		 */		
	// cases responsáveis pelo movimento do dedo indicador
		case 'i': indicador = (indicador - 5) % 360; break; 
		case 'I': indicador = (indicador + 5) % 360; break; 
	// cases responsáveis pelo movimento do dedo anelar	
		case 'a': anelar = (anelar - 5) % 360; break; 
		case 'A': anelar = (anelar + 5) % 360; break; 
	// cases responsáveis pelo movimento do polegar
		case 'p': polegar = (polegar - 5) % 360; break; 
		case 'P': polegar = (polegar + 5) % 360; break; 
		
		case ESC: exit(EXIT_SUCCESS); break;  //encerra o programa com sucesso
	}
    glutPostRedisplay();
}


/*
 * Funcao usada na funcao callback para desenhar na tela
 */
void display(void){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    //rotação da camera
    glRotatef((GLfloat) eixoy, 0, 1, 0);
    glRotatef((GLfloat) eixox, 1, 0, 0);
    
    //articulacao ombro
    glPushMatrix();
    	glTranslatef(0, -1, 0);
    	glColor3f(0, 0, 0);
    	glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
    
    //movimento braço
    glPushMatrix();
    	glTranslatef(0, -1, 0);
    	glRotatef((GLfloat) ombro, 0, 0, 1);
    	glTranslatef(0, 1, 0);
    	
    	//braço
    	glPushMatrix();
			glRotatef(90, 0, 0, 1);
			glScalef(2, 0.5, 0.5);
			glColor3f(0.6, 1, 1);
			glutSolidCube(1);
    	glPopMatrix();
    	
    	//articulacao cotovelo
    	glPushMatrix();
    		glTranslatef(0, 1, 0);
    		glColor3f(0, 0, 0);
    		glutSolidSphere(0.4, 30, 30);
    	glPopMatrix();
    	
    	//movimento antebraço
    	glPushMatrix();
    		glTranslatef(0, 1, 0);
    		glRotatef((GLfloat) cotovelo, 0, 0, 1);
    		glTranslatef(0, 1, 0);
    		
    		//antebraço
    		glPushMatrix();
				glRotatef(90, 0, 0, 1);
				glScalef(2, 0.4, 0.4);
				glColor3f(0.9, 0.50, 1);
				glutSolidCube(1);    			
    		glPopMatrix();
    		
    		//articulacao mão
    		glPushMatrix();
    			glTranslatef(0, 1, 0);
    			glColor3f(0, 0, 0);
    			glutSolidSphere(0.35, 30, 30);
    		glPopMatrix();
    		
    		//movimento mão
    		glPushMatrix();
    			glTranslatef(0, 1, 0);
    			glRotatef((GLfloat) mao, 0, 0, 1);
    			glTranslatef(0, 0.5, 0);
    			
    			//mao
    			glPushMatrix();
    				glRotatef(90, 0, 0, 1);
    				glScalef(1, 0.45, 0.45);
    				glColor3f(0.6, 0, 0.8);
    				glutSolidCube(1);
    			glPopMatrix();
    			
    			//movimento polegar
    			glPushMatrix();
    				glTranslatef(0.15, 0.4, 0);
    				glRotatef((GLfloat) polegar, 0, 0, 1);
    				glTranslatef(0, 0.2, 0);
    				
    				//polegar
    				glPushMatrix();
    					glRotatef(90, 0, 0, 1);
    					glScalef(0.5, 0.25, 0.25);
    					glColor3f(1, 1, 0);
    					glutSolidCube(0.5);
    				glPopMatrix();
    			glPopMatrix();
    			
    			//movimento indicador
    			glPushMatrix();
    				glTranslatef(-0.15, 0.4, -0.15);
    				glRotatef((GLfloat) indicador, -1, 0, 1);
    				glTranslatef(0, 0.2, 0);
    				
    				//indicador
    				glPushMatrix();
    					glRotatef(90, 0, 0, 1);
    					glScalef(0.5, 0.25, 0.25);
    					glColor3f(1, 0, 0);
    					glutSolidCube(0.5);
    				glPopMatrix();
    			glPopMatrix();
    			
    			//movimento anelar
    			glPushMatrix();
    				glTranslatef(-0.15, 0.4, 0.15);
    				glRotatef((GLfloat) anelar, 1, 0, 1);
    				glTranslatef(0, 0.2, 0);
    				
    				//anelar
    				glPushMatrix();
    					glRotatef(90, 0, 0, 1);
    					glScalef(0.5, 0.25, 0.25);
    					glColor3f(0, 0, 1);
    					glutSolidCube(0.5);
    				glPopMatrix();
    			glPopMatrix();
    		glPopMatrix();
    	glPopMatrix();
    	
    glPopMatrix();
	
	glutSwapBuffers();
}
