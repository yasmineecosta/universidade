/*
 * Computacao Grafica
 * Codigo: Trabalho de Rasterizacao com GLUT/OpenGL
 * Yasmine Martins da Costa e Silva
 */

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

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <forward_list>
#include "glut_text.h"

using namespace std;

// Variaveis Globais
#define ESC 27

//Enumeracao com os tipos de formas geometricas
enum tipo_forma{LIN = 1, TRI, RET, POL, CIR }; // Linha, Triangulo, Retangulo Poligono, Circulo

//Verifica se foi realizado o primeiro clique do mouse
bool click1 = false;

//Coordenadas da posicao atual do mouse
int m_x, m_y;

//Coordenadas do primeiro clique e do segundo clique do mouse
int x_1, y_1, x_2, y_2;

//Indica o tipo de forma geometrica ativa para desenhar
int modo = LIN;

//Largura e altura da janela
int width = 512, height = 512;

// Definicao de vertice
struct vertice{
    int x;
    int y;
};

// Definicao das formas geometricas
struct forma{
    int tipo;
    forward_list<vertice> v; //lista encadeada de vertices
};

// Lista encadeada de formas geometricas
forward_list<forma> formas;

// Funcao para armazenar uma forma geometrica na lista de formas
// Armazena sempre no inicio da lista
void pushForma(int tipo){
    forma f;
    f.tipo = tipo;
    formas.push_front(f);
}

// Funcao para armazenar um vertice na forma do inicio da lista de formas geometricas
// Armazena sempre no inicio da lista
void pushVertice(int x, int y){
    vertice v;
    v.x = x;
    v.y = y;
    formas.front().v.push_front(v);
}

//Fucao para armazenar uma Linha na lista de formas geometricas
void pushLinha(int x1, int y1, int x2, int y2){
    pushForma(LIN);
    pushVertice(x1, y1);
    pushVertice(x2, y2);
}

/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas das funcoes)
 */
void init(void);
void reshape(int w, int h);
void display(void);
void menu_popup(int value);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mousePassiveMotion(int x, int y);
void drawPixel(int x, int y);
// Funcao que percorre a lista de formas geometricas, desenhando-as na tela
void drawFormas();
// Funcao que implementa o Algoritmo Imediato para rasterizacao de segmentos de retas
void retaImediata(double x1,double y1,double x2,double y2);
// Funcao que implementa o Algoritmo de Bresenham para rasterizacao de segmentos de retas
void retaBresenham(double x1, double x2, double y1, double y2);

/*
 * Funcao principal
 */
int main(int argc, char** argv){
    glutInit(&argc, argv); // Passagens de parametro C para o glut
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //Selecao do Modo do Display e do Sistema de cor
    glutInitWindowSize (width, height);  // Tamanho da janela do OpenGL
    glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
    glutCreateWindow ("Computacao Grafica: Paint"); // Da nome para uma janela OpenGL
    init(); // Chama funcao init();
    glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
    glutKeyboardFunc(keyboard); //funcao callback do teclado
    glutMouseFunc(mouse); //funcao callback do mouse
    glutPassiveMotionFunc(mousePassiveMotion); //fucao callback do movimento passivo do mouse
    glutDisplayFunc(display); //funcao callback de desenho
    
    // Define o menu pop-up
    glutCreateMenu(menu_popup);
    glutAddMenuEntry("Linha", LIN);
//    glutAddMenuEntry("Retangulo", RET);
    glutAddMenuEntry("Sair", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    
    glutMainLoop(); // executa o loop do OpenGL
    return EXIT_SUCCESS; // retorna 0 para o tipo inteiro da funcao main();
}

/*
 * Inicializa alguns parametros do GLUT
 */
void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
}

/*
 * Ajusta a projecao para o redesenho da janela
 */
void reshape(int w, int h)
{
	// Muda para o modo de projecao e reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);
	
	width = w;
	height = h;
    glOrtho (0, w, 0, h, -1 ,1);  

   // muda para o modo de desenho
	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();

}

/*
 * Controla os desenhos na tela
 */
void display(void){
    glClear(GL_COLOR_BUFFER_BIT); //Limpa o buffer de cores e reinicia a matriz
    glColor3f (0.0, 0.0, 0.0); // Seleciona a cor default como preto
    drawFormas(); // Desenha as formas geometricas da lista
    //Desenha texto com as coordenadas da posicao do mouse
    draw_text_stroke(0, 0, "(" + to_string(m_x) + "," + to_string(m_y) + ")", 0.2);
    glutSwapBuffers(); // manda o OpenGl renderizar as primitivas

}

/*
 * Controla o menu pop-up
 */
void menu_popup(int value){
    if (value == 0) exit(EXIT_SUCCESS);
    modo = value;
}


/*
 * Controle das teclas comuns do teclado
 */
void keyboard(unsigned char key, int x, int y){
    switch (key) { // key - variavel que possui valor ASCII da tecla precionada
        case ESC: exit(EXIT_SUCCESS); break;
    }
}

/*
 * Controle dos botoes do mouse
 */
void mouse(int button, int state, int x, int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
            switch(modo){
                case LIN:
                    if (state == GLUT_DOWN) {
                        if(click1){
                            x_2 = x;
                            y_2 = height - y - 1;
                            printf("Clique 2(%d, %d)\n",x_2,y_2);
                            retaBresenham(x_1,y_1, x_2,y_2);
                            pushLinha(x_1, y_1, x_2, y_2);
                            click1 = false;
                            glutPostRedisplay();
                        }else{
                            click1 = true;
                            x_1 = x;
                            y_1 = height - y - 1;
                            printf("Clique 1(%d, %d)\n",x_1,y_1);
                        }
                    }
                break;
            }
        break;

//        case GLUT_MIDDLE_BUTTON:
//            if (state == GLUT_DOWN) {
//                glutPostRedisplay();
//            }
//        break;
//
//        case GLUT_RIGHT_BUTTON:
//            if (state == GLUT_DOWN) {
//                glutPostRedisplay();
//            }
//        break;
            
    }
}

/*
 * Controle da posicao do cursor do mouse
 */
void mousePassiveMotion(int x, int y){
    m_x = x; m_y = height - y - 1;
    glutPostRedisplay();
}

/*
 * Funcao para desenhar apenas um pixel na tela
 */
void drawPixel(int x, int y){
    glBegin(GL_POINTS); // Seleciona a primitiva GL_POINTS para desenhar
        glVertex2i(x, y);
    glEnd();  // indica o fim do ponto
}

/*
 *Funcao que desenha a lista de formas geometricas
 */
void drawFormas(){
    //Apos o primeiro clique, desenha a reta com a posicao atual do mouse
    if(click1) retaImediata(x_1, y_1, m_x, m_y);
    //if(click1) retaBresenham(x_1, y_1, m_x, m_y);
    
    //Percorre a lista de formas geometricas para desenhar
    for(forward_list<forma>::iterator f = formas.begin(); f != formas.end(); f++){
        switch (f->tipo) {
            case LIN:
                int i = 0, x[2], y[2];
                //Percorre a lista de vertices da forma linha para desenhar
                for(forward_list<vertice>::iterator v = f->v.begin(); v != f->v.end(); v++, i++){
                    x[i] = v->x;
                    y[i] = v->y;
                }
                //Desenha o segmento de reta apos dois cliques
                //retaImediata(x[0], y[0], x[1], y[1]);
                //Desenha o segmento de reta apos dois cliques COM BASE NO ALGORITMO DE BRESENHAM
                retaBresenham(x[0], y[0], x[1], y[1]);
            break;
//            case RET:
//            break;
        }
    }
}

/*
 * Fucao que implementa o Algoritmo de Rasterizacao da Reta Imediata
 */
void retaImediata(double x1, double y1, double x2, double y2){
    double m, b, yd, xd;
    double xmin, xmax,ymin,ymax;
    
    drawPixel((int)x1,(int)y1);
    if(x2-x1 != 0){ //Evita a divisao por zero
        m = (y2-y1)/(x2-x1);
        b = y1 - (m*x1);

        if(m>=-1 && m <= 1){ // Verifica se o declive da reta tem tg de -1 a 1, se verdadeira calcula incrementando x
            xmin = (x1 < x2)? x1 : x2;
            xmax = (x1 > x2)? x1 : x2;

            for(int x = (int)xmin+1; x < xmax; x++){
                yd = (m*x)+b;
                yd = floor(0.5+yd);
                drawPixel(x,(int)yd);
            }
        }else{ // Se tg menor que -1 ou maior que 1, calcula incrementado os valores de y
            ymin = (y1 < y2)? y1 : y2;
            ymax = (y1 > y2)? y1 : y2;

            for(int y = (int)ymin + 1; y < ymax; y++){
                xd = (y - b)/m;
                xd = floor(0.5+xd);
                drawPixel((int)xd,y);
            }
        }

    }else{ // se x2-x1 == 0, reta perpendicular ao eixo x
        ymin = (y1 < y2)? y1 : y2;
        ymax = (y1 > y2)? y1 : y2;
        for(int y = (int)ymin + 1; y < ymax; y++){
            drawPixel((int)x1,y);
        }
    }
    drawPixel((int)x2,(int)y2);
}


void retaBresenham(double x1, double y1, double x2, double y2){
	
	double dx, dy, d, incE, incNE, xmin, xmax, ymin, ymax, ytemp, x, y, m;

    dx = x2 - x1;
    dy = y2 - y1;
    
    // pegando o delta da variacao de x e de y
	xmin = (x1 < x2)? x1 : x2;
    xmax = (x1 > x2)? x1 : x2;

	ymin = (y1 < y2)? y1 : y2;
    ymax = (y1 > y2)? y1 : y2;
    
	if(xmin == x1) ytemp = y1;
	else ytemp = y2;
	
	dx = xmax - xmin;
	dy = ymax - ymin;
	drawPixel(xmin,ytemp);
	
	d = (2*dy) - dx;
	incE = 2 * dy;
	incNE = 2 *(dy - dx);
	
	while(xmin < xmax){
		if(d <= 0) d+= incE;
		else{
			d += incNE;
			ytemp++;
		}
		drawPixel(xmin,ytemp);
		xmin++;
	}
	/*
	
    // Pegando os pontos de início e fim
    if (dx >= 0) {
        x = x1;
        y = y1;
    } else {
        x = x2;
        y = y2;
        dx = -dx; // Garantindo que dx seja positivo
    }

    drawPixel(x, y);
    
    if (dx >= dy) {
        d = 2 * dy - dx;
        incE = 2 * dy;
        incNE = 2 * (dy - dx);

        while (x < x2) {
            if (d <= 0) {
                d += incE;
                x++;
            } else {
                d += incNE;
                x++;
                y++;
            }
            drawPixel(x, y);
        }
    } else {
        d = 2 * dx - dy;
        incE = 2 * dx;
        incNE = 2 * (dx - dy);

        while (y < y2) {
            if (d <= 0) {
                d += incE;
                y++;
            } else {
                d += incNE;
                x++;
                y++;
            }
            drawPixel(x, y);
        }
    }
	/* test1
	// pegando o delta da variacao de x e de y
	xmin = (x1 < x2)? x1 : x2;
    xmax = (x1 > x2)? x1 : x2;

	ymin = (y1 < y2)? y1 : y2;
    ymax = (y1 > y2)? y1 : y2;
    
	if(xmin == x1) ytemp = y1;
	else ytemp = y2;
	
	dx = xmax - xmin;
	dy = ymax - ymin;
	drawPixel(xmin,ytemp);
	
	d = (2*dy) - dx;
	incE = 2 * dy;
	incNE = 2 *(dy - dx);
	
	while(xmin < xmax){
		if(d <= 0) d+= incE;
		else{
			d += incNE;
			ytemp++;
		}
		drawPixel(xmin,ytemp);
		xmin++;
	}
	
	/*test2
	double dx, dy, d, incE, incNE, temp1, temp2, xmin, xmax, ymin, ymax;
	int deltabsx, deltabsy;
	bool invH = false, invV = false;
	/*
	dx = x2 - x1;
	dy = y2 - y1;
	
	xmin = (x1 < x2)? x1 : x2;
    xmax = (x1 > x2)? x1 : x2;

	ymin = (y1 < y2)? y1 : y2;
    ymax = (y1 > y2)? y1 : y2;

	dx = xmax - xmin;
	dy = ymax - ymin;
	deltabsx = fabs(dx);
	deltabsy = fabs(dy);
	drawPixel(xmin,ymin);
	
	if((dx*dy) < 0){
		y1 = -y1;
		y2 = -y2;
		dy = y2 - y1;
		invV = true; 
	}
	
	if(deltabsx < deltabsy){
		temp1 = x1;
		x1 = y1;
		y1 = temp1;
		
		temp2 = x2;
		x2 = y2;
		y2 = temp2;
		
		dx = x2 - x1;
		dy = y2 - y1;
		invH = true;
	}
	if(x1 > x2){
		temp1 = x1;
		x1 = x2;
		x2 = temp1;
		
		temp2 = y1;
		y1 = y2;
		y2 = temp2;
		
		dx = x2 - x1;
		dy = y2 - y1;
	// variaveis a serem trabalhadas com base no Algoritmo
	int x, y;
	x = int(x1);
	y = int(y1);
	
	d = (2*dy) - dx;
	incE = 2 * dy;
	incNE = 2 *(dy - dx);
	
	drawPixel(x,y);
	
	for(int i = x+1; i <= int(xmax); i++){
		if(d <= 0) d += incE;
		else{
			d += incNE;
			y++;
		}
		
		if(invH && invV) drawPixel(y, -x);
		else if(invH) drawPixel(y,x);
		else if(invV) drawPixel(x, -y);
		else drawPixel(x, y);
	}
	
	/
	while(x <= int(x2)){
		if(d <= 0) d+= incE;
		else{
			d += incNE;
			y += swapY;
		}
		int dX, dY;
		dX = int(dx);
		dY = int(dy);
		
		if(dX < 0 && dY < 0) drawPixel(-y,-x);
		else if(dX < 0) drawPixel(y, -x);
		else if(dY < 0) drawPixel(-y, x);
		else drawPixel(x, y);
		
		x+= swapX;
	}
	//test3
	// determinando qual ponto sera o inicio e o fim
	xmin = (x1 < x2)? x1 : x2;
    xmax = (x1 > x2)? x1 : x2;
    ymin = (y1 < y2)? y1 : y2;
    ymax = (y1 > y2)? y1 : y2;
    drawPixel(xmin, ymin);
    
    while(xmin < xmax){
		xmin++;
		if(d < 0) d += incE;
		else{
			ymin++;
			d += incNE;
		}
		drawPixel(xmin, ymin);
	}
	*/
}
    