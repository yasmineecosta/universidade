/*
 * Computacao Grafica
 * Autora: Yasmine Martins da Costa e Silva
 */

#ifndef circulo_h
#define circulo_h

#include <cmath>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265f
#endif

void retanguloVertical(){
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.55, 0.0);
	
	glVertex2f(-300.0, 0.0);
	glVertex2f(-300.0, 390.0);
	glVertex2f(-110.0, 390.0);
	glVertex2f(-110.0, 0.0);

	glEnd();
}

void traco(){
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.0);
	
	glVertex2f(-125.0, -20.0);
	glVertex2f(-125.0, 370.0);
	glVertex2f(-110.0, 370.0);
	glVertex2f(-110.0, -20.0);

	glEnd();
}

void bandeira(){
	glBegin(GL_POLYGON);
	glColor3f(0,0.99,0);
	glVertex2f(-300.0, 0.0);
	glVertex2f(-300.0, 190.0);
	glVertex2f(50.0, 190.0);
	glVertex2f(50.0, 0.0);

	glEnd();
}

void retanguloHorizontal(){
	glBegin(GL_POLYGON);
	glVertex2f(-270.0, 0.0);
	glVertex2f(-270.0, 70.0);
	glVertex2f(-100.0, 70.0);
	glVertex2f(-100.0, 0.0);

	glEnd();
}

void triangulo(){
	glBegin(GL_TRIANGLES);
        // Coordenadas com vertice esquerdo do triangulo na origem dos eixos cartesianos
		glVertex2f(350, 280);
		glVertex2f(0, 0);
		glVertex2f(700, 0);
		
		glEnd();
}

void base(){
	glBegin(GL_QUADS);
	glColor3f(1,1,0);
	glVertex2f(00.0, 0.0);
	glVertex2f(00.0, 560.0);
	glVertex2f(900.0, 560.0);
	glVertex2f(900.0, 0.0);

	glEnd();
}

void quadrado(){
	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex2f(00.0, 0.0);
	glVertex2f(00.0, 400.0);
	glVertex2f(380.0, 400.0);
	glVertex2f(380.0, 0.0);

	glEnd();
}

void desenhaCirculo(float raio, int num_linhas,bool preenchido)
{
    int i;
    GLfloat angulo;
   
    angulo = (2 * M_PI) / num_linhas; //divide 360 graus em radianos pela quantidade de linhas que serao desenhadas
 
    if(preenchido) glBegin(GL_TRIANGLE_FAN);   // Primitiva que liga os vertices, gerando triangulos com o primeiro vertice em comum
    else glBegin(GL_LINE_LOOP);     // Primitiva que liga os vertices, gerando segmentos de reta em um loop
    
    for(i = 1; i <= num_linhas; i++) // FOR usado para o calculo de cada ponto pertencente aos extremos das retas
    {
		// comando que calcula as coord. da rotacao e desenha as retas na tela
        glVertex2f(-raio*sin(i * angulo) , raio*cos(i * angulo));	// centro = (0,0), x = 0 e y = raio;
//		glVertex2f(raio*cos(i * angulo) , raio*sin(i * angulo));	// centro = (0,0), x = raio e y = 0;
	}
    glEnd(); 
}
#endif /* formas_h */
