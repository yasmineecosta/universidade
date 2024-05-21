/*
 * Computacao Grafica
 * Codigo: Trabalho de Rasterização
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
#include <algorithm>
#include <list>
#include <vector>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <forward_list>
#include <utility>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "glut_text.h"

using namespace std;

// Variaveis Globais
#define ESC 27
#define SPACE 32
#define TRANSFORM_NONE 0

//Enumeracao com os tipos de formas geometricas
enum tipo_forma{LIN = 1, TRI, RET, POL, CIR}; // Linha, Triangulo, Retangulo Poligono, Circulo
enum tipo_transf{TRA = 6, SCA, CIS, REF, ROT};
enum tipo_fill{TRA_FILL = 11, RET_FILL, POL_FILL};
enum tipo_FloodFill{FF = 14};

int transformacao_atual = TRANSFORM_NONE;
int valorAtual_Submenu = 0;

//Verifica se foi realizado o primeiro clique do mouse
//Instanciando variáveis e booleanos para interação
bool click1 = false, click2 = false;
bool poligon = false, tri1 = false, tri2 = false, ret = false, circ = false;
bool fillTRI = false;
bool fillRET = false;
bool fillPOL = false;

//Indica o tipo de forma geometrica ativa para desenhar
int modo = -1;
int transf = TRA;
int i_pol = 0;

//Coordenadas da posicao atual do mouse
int x_m, y_m;
int x_p[99], y_p[99];


//cores pro floodFill
float fR = 0, fG = 0, fB = 0;

//Largura e altura da janela
int width = 1000, height = 900;

// Definicao de vertice
struct vertice{
    int x;
    int y;
};

// Definicao das formas geometricas
struct forma{
    int tipo;
    float cx, cy;
    int tX, tY;
    forward_list<vertice> vertexList; //lista encadeada de vertices
    forma(): tX(0), tY(0) {}
};

struct ponto{
	int x, y;
	ponto(int x, int y) : x(x), y(y) {}
};

// Lista encadeada de formas geometricas
forward_list<forma> formList;
vector<vertice> vertices_cor;
vector<int> x_v, y_v; //armazenar poligono - vertices
int x_tri[3], y_tri[3]; //armazenar triangulo - vertices
int x_origin, y_origin;

//preenchimento
vector<vertice> colored;
GLfloat cor[3] = {0.0, 0.0, 0.0}; //preto

/*
 * Atualizar o centroide da forma para as transformacoes
 */
void centroide(forma& f){
	if(f.vertexList.empty()) return;
	float cx = 0, cy = 0; //centro x e centro y
	for(auto it = f.vertexList.begin(); it != f.vertexList.end(); ++it){
		vertice& v = *it;
		cx += v.x;
		cy += v.y;
	}
	int size = distance(f.vertexList.begin(), f.vertexList.end());
	cx /= size;
	cy /= size;
	f.cx = cx;
	f.cy = cy;
}

// Funcao para armazenar uma forma geometrica na lista de formas
// Armazena sempre no inicio da lista
void pushForma(int tipo){
    forma f;
    f.tipo = tipo;
    f.cx = 0; 
    f.cy = 0;
    formList.push_front(f);
}

// Funcao para armazenar um vertice na forma do inicio da lista de formas geometricas
// Armazena sempre no inicio da lista
void pushVertice(int x, int y){
    vertice v;
    v.x = x;
    v.y = y;
    formList.front().vertexList.push_front(v);
    centroide(formList.front());
}

//Fucao para armazenar uma Linha na lista de formas geometricas
void pushLinha(int x1, int y1, int x2, int y2){
    pushForma(LIN);
    pushVertice(x1, y1);
    pushVertice(x2, y2);
}
/*
void pushTri(int x[], int y[]){
	pushForma(TRI);
	pushVertice(x[0],y[0]);
	pushVertice(x[1],y[1]);
	pushVertice(x[2],y[2]);
}
*/
void pushTri(int x1, int y1, int x2, int y2, int x3, int y3){
	pushForma(TRI);
	pushVertice(x1,y1);
	pushVertice(x2,y2);
	pushVertice(x3,y3);
}

void pushRetang(int x1, int y1, int x2, int y2){
	pushForma(RET);
	pushVertice(x1,y1);
	pushVertice(x2,y1);
	pushVertice(x2,y2);
	pushVertice(x1,y2);
}

void pushPolig(vector<vertice> &pts){
	pushForma(POL);
	for(vector<vertice>::iterator v = pts.begin(); v != pts.end(); ++v){
		pushVertice(v->x, v->y);	
	} 
}

void pushCirc(int x1, int y1, int x2, int y2){
	pushForma(CIR);
	pushVertice(x1,y1);
	pushVertice(x2,y2);
}

void pushFloodFill(int x1, int y1){
	vertice v;
	v.x = x1;
	v.y = y1;
	vertices_cor.push_back(v);
}

//void pushPoligFill(vector)
/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas das funcoes)
 */
void init(void);
void reshape(int w, int h);
void display(void);
void menu_popup(int value);
void submenu_Transf(int value);
void keyboard(unsigned char key, int x, int y);
void movementKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mousePassiveMotion(int x, int y);
void drawPixel(int x, int y);
void borrachaFull();

// Funcao que percorre a lista de formas geometricas, desenhando-as na tela
void drawFormas();
void centroide(forma& f);
void drawPOL(vector<int>& x, vector<int>& y);
//void drawTRI(int x1, int y1, int x2, int y2, int x3, int y3);
void drawTRI(int x1, int y1, int x2, int y2, int x3, int y3);
void drawRET(int x1, int y1, int x2, int y2);
// Funcao que implementa o Algoritmo Imediato para rasterizacao de segmentos de retas
void retaImediata(double x1,double y1,double x2,double y2);
// Funcao que implementa o Algoritmo de Bresenham para rasterizacao de segmentos de retas
void retaBresenham(double x1, double y1, double x2, double y2);
// Funcao que implementa o Alg de Bresenham para rasterizacao de circulos
void bresenhamCirculo(double x1, double y1, double R);

// transformações
void floodFill(int x, int y);
void translation(int dx, int dy,forma& f);
void scaling(float sx, float sy,forma& f);
void shear(float shx, float shy,forma& f);
void reflection(char eixo, forma& f);
void rotation(float angle, forma& f);


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
    glutSpecialFunc(movementKeys);
    
    int submenuTransf = glutCreateMenu(submenu_Transf);
    glutAddMenuEntry("Translacao", TRA);
    glutAddMenuEntry("Escala", SCA);
    glutAddMenuEntry("Cisalhamento", CIS);
    glutAddMenuEntry("Reflexao", REF);
    glutAddMenuEntry("Rotacao", ROT);
    
    // Define o menu pop-up
    glutCreateMenu(menu_popup);
    glutAddMenuEntry("Linha", LIN);
    glutAddMenuEntry("Triangulo", TRI);
    glutAddMenuEntry("Quadrilatero", RET);
	glutAddMenuEntry("Poligono", POL);
	glutAddMenuEntry("Circunferencia", CIR);
	glutAddMenuEntry("Flood Fill", FF);
	glutAddMenuEntry("Apagar formas(B/b)", -1);
	glutAddSubMenu("Transformações", submenuTransf);
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
    
    glPushMatrix();
	drawFormas(); // Desenha as formas geometricas da lista
    //Desenha texto com as coordenadas da posicao do mouse
    draw_text_stroke(0, 0, "(" + to_string(x_m) + "," + to_string(y_m) + ")", 0.2);
    glPopMatrix();
    glutSwapBuffers(); // manda o OpenGl renderizar as primitivas
}

/*
 * Controla o menu pop-up
 */
void menu_popup(int value){
    if (value == 0) exit(EXIT_SUCCESS);
    if (value == -1) borrachaFull();
    if (value >= TRA && value <= REF) translation(0,1, formList.front());
    modo = value;
}

/*
 * Teclas pra usar nas transformacoes
*/
void movementKeys(int key, int x, int y){
	switch(transformacao_atual){
		case TRA:
    		switch(key){
		  		case GLUT_KEY_UP:
		  			translation(0, 10, formList.front());
		  			glutPostRedisplay();
		  			break;
		  		case GLUT_KEY_LEFT:
		  			translation(-10, 0, formList.front());
		  			glutPostRedisplay();
		  			break;
		  		case GLUT_KEY_RIGHT:
					translation(10, 0, formList.front());
					glutPostRedisplay();
				break;
				case GLUT_KEY_DOWN:
					translation(0, -10, formList.front());
					glutPostRedisplay();
					break;
				default:
					break;
			} break;
			
		case SCA:
			switch(key){
				case GLUT_KEY_UP:
					scaling(1.1, 1.1, formList.front());
					glutPostRedisplay();
					break;
				case GLUT_KEY_DOWN:
					scaling(0.9, 0.9, formList.front());
					glutPostRedisplay();
					break;
			} break;
			
		case CIS:
		   	switch(key){
				case GLUT_KEY_LEFT:
					shear(-0.1, 0.0, formList.front());
					glutPostRedisplay();
					break;
				case GLUT_KEY_RIGHT:
					shear(0.1, 0.0, formList.front());
					glutPostRedisplay();
					break;	   
			} break;
			
		case REF:
		   	switch(key){
				case GLUT_KEY_UP:
					reflection('x', formList.front());
					glutPostRedisplay();
					break;
				case GLUT_KEY_DOWN:
					reflection('x', formList.front());
					glutPostRedisplay();
					break;
				case GLUT_KEY_LEFT:
					reflection('y', formList.front());
					glutPostRedisplay();
					break;
				case GLUT_KEY_RIGHT:
					reflection('y', formList.front());
					glutPostRedisplay();
					break;	   
			} break;
			
		case ROT:
			switch(key){
				 case GLUT_KEY_LEFT:
					rotation(1, formList.front());
					glutPostRedisplay();
					break;
				case GLUT_KEY_RIGHT:
					rotation(-1, formList.front());
					glutPostRedisplay(); 	
					break;
			} break;
			
		default: break;
	}
	
}
/*
 * SUBMENU - transformações - Controle das formas por meio de casos
 */
void submenu_Transf(int value){
	if (value == 0) exit(EXIT_SUCCESS);
	switch(value){
		case TRA: transformacao_atual = TRA; break;
		case SCA: transformacao_atual = SCA; break;
		case CIS: transformacao_atual = CIS; break;
		case REF: transformacao_atual = REF; break;
		case ROT: transformacao_atual = ROT; break;
	}
	modo = value;
}
	
/*
 * Função apagar formas
 */
void borrachaFull(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	formList.clear(); // Remove todas as formas da lista
	vertices_cor.clear();
	modo = -1; // Atualiza o modo para um valor não utilizado
	poligon = false; // Reinicia a variável para desenhar polígonos
	fillTRI = false, fillRET = false, fillPOL = false;
	glutPostRedisplay();
}

/*
 * Controle das teclas comuns do teclado
 */
void keyboard(unsigned char key, int x, int y){
    switch (key) { // key - variavel que possui valor ASCII da tecla precionada
        case ESC: exit(EXIT_SUCCESS); break;
        case 'b': borrachaFull(); break;
	    case 'B': borrachaFull(); break;
        case 32: // tecla do espaço em ASCII
        	poligon = false; break;
        	/*if(poligon){
				poligon: false;
				x_p[0] = 0;
				y_p[0] = 0;
				click1 = false;
				glutPostRedisplay();
			break;}*/
    }
    glutPostRedisplay();
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
                            x_p[1] = x;
                            y_p[1] = height - y - 1;
                            retaBresenham(x_p[0], y_p[0], x_p[1], y_p[1]);
                            pushLinha(x_p[0], y_p[0], x_p[1], y_p[1]);
                            click1 = false;
                            glutPostRedisplay();
                        }else{
                            click1 = true;
                            x_p[0] = x;
                            y_p[0] = height - y - 1;
                        }
                        cout << "test linha\n";
                        //retaBresenham(x_p[0], y_p[0], x_p[1], y_p[1]);
                    }
                	break;
				
        		case TRI:
        			if(state == GLUT_DOWN){
                        if(tri1){
                        	x_p[1] = x;
                        	y_p[1] = height - y - 1;
                            x_tri[1] = x_p[1];
                            y_tri[1] = y_p[1];
                            tri1 = false;
                            tri2 = true;
							cout << "test tri1\n";
                            glutPostRedisplay();
                        }else if(tri2){
							x_tri[2] = x;
							y_tri[2] = height - y - 1;
							//pushTri(x_tri, y_tri);
							pushTri(x_p[0], y_p[0], x_p[1], y_p[1], x_p[2], y_p[2]);
							//tri1 = true;
							tri2 = false;
							cout << "test tri1\n";
							glutPostRedisplay();
						}else{
                            tri1 = true;
                            x_p[0] = x;
                            y_p[0] = height - y - 1;
                            cout << "test tri0\n";
                             x_tri[0] = x_p[0];
                             y_tri[0] = y_p[0];
                        }
                    }
                	break;
                
                case RET:
                	if(state == GLUT_DOWN){
                        if(ret){
                            x_p[1] = x;
                            y_p[1] = height - y - 1;
                            pushRetang(x_p[0], y_p[0], x_p[1], y_p[1]);
                            ret = false;
                            cout << "test ret\n";
                            glutPostRedisplay();
                        }else{
                            ret = true;
                            cout << "test ret1\n";
                            x_p[0] = x;
                            y_p[0] = height - y - 1;
                        }
                    }
                	break;
                
                case POL:
                	if(state == GLUT_DOWN){
                		// x_p[1] = x;
						// y_p[1] = height - y -1;
						vertice v = {x, height - y - 1};
                		vector<vertice> pol;
						if(!poligon){
							pol.push_back(v);
							pushPolig(pol);
							poligon = true;
							cout << "test pol\n";
						}else{
							formList.front().vertexList.push_front(v);
							centroide(formList.front());
							pol.clear();
							cout << "test pol\n";
							glutPostRedisplay();
						}
						/*	swap(x_p[0], x_p[1]);
							swap(y_p[0], y_p[1]);
							x_p[1] = x;
							y_p[1] = height - y -1;
							pushVertice(x_p[1], y_p[1]);
							glutPostRedisplay();
						}
						else{
							click1 = true;
							x_p[0] = x_p[1] = x;
							y_p[0] = y_p[1] = height - y -1;
							x_origin = x_p[0];
							y_origin = y_p[0];
							poligon = true;
							pushForma(POL);
							pushVertice(x_p[0], y_p[0]);
						}
						
						vertice vi = {x, height - y - 1};
						vector<vertice> pol;
						if (!poligon)
						{
							pol.push_back(vi);
							pushPolig(pol);
							poligon = true;
						}
						else
						{
							formList.front().vertexList.push_front(vi);
							pol.clear();
							glutPostRedisplay();
						}
					*/
					}
					break;
					
                case CIR:
                	if(state == GLUT_DOWN){
						if(circ){
							x_p[1] = x;
							y_p[1] = height - y - 1;
							pushCirc(x_p[0], y_p[0], x_p[1], y_p[1]);
							circ = false;
							cout << "test circ1\n";
							glutPostRedisplay();
						}
						else{
							circ = true;
							x_p[0] = x;
							y_p[0] = height - y -1;
							cout << "test circ\n";
						}
					}
					break;
				
				case FF:
					if(state == GLUT_DOWN){
						x_p[0] = x;
						y_p[0] = height - y - 1;
						pushFloodFill(x_p[0], y_p[0]);
						floodFill(x_p[0], y_p[0]);
					}
					break;
					
            }
 			break;

    }
}

/*
 * Controle da posicao do cursor do mouse
 */
void mousePassiveMotion(int x, int y){
    x_m = x; y_m = height - y - 1;
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
	
	for(vector<vertice>::iterator it = vertices_cor.begin(); it != vertices_cor.end(); ++it){
		int x = it->x;
		int y = it->y;
		glPointSize(1.0f);
		glColor3f(fR, fG, fB);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
	}
	glColor3f(0.0, 0.0, 0.0);
	float r = sqrt(pow(x_p[0] - x_m, 2) + pow(y_p[0] - y_m, 2));
	/*if(click1){
		switch(modo){
			case LIN:
				retaBresenham(x_p[0], y_p[0], x_m, y_m);
				break;
			
			case TRI:
				tri1 = true;
				tri2 = true;
				retaBresenham(x_p[0], y_p[0], x_m, y_m);
				break;
			
			case RET:
				ret = true;
				drawRET(x_p[0], y_p[0], x_m, y_m);
				break;
			
			case POL:
				retaBresenham(formList.front().vertexList.front().x, formList.front().vertexList.front().y, x_m, y_m);
				break;
			
			case CIR:
				bresenhamCirculo(x_p[0], y_p[0], r);
				break;
		}
	}else if(tri2){
		switch(modo){
			case TRI:
				x_p[3] = x_m;
				y_p[3] = y_m;
				drawTRI(x_p, y_p);
				break;
		}
	}*/
	
	if(click1) retaBresenham(x_p[0], y_p[0], x_m, y_m);
	else if(circ) bresenhamCirculo(x_p[0], y_p[0], r);
	else if(tri1) retaBresenham(x_p[0], y_p[0], x_m, y_m);
	else if(tri2) drawTRI(x_p[0], y_p[0], x_p[1], y_p[1], x_m, y_m);
	else if(ret) drawRET(x_p[0], y_p[0], x_m, y_m);
	else if(poligon) retaBresenham(formList.front().vertexList.front().x, formList.front().vertexList.front().y, x_m, y_m);
	/*
    //Apos o primeiro clique, desenha a forma desejada
    if(click1){
	//if(click1) retaImediata(x_1, y_1, m_x, m_y);
    //if(click1) retaBresenham(x_1, y_1, m_x, m_y);
		switch(modo){
			case LIN:
				retaBresenham(x_p[0], y_p[0], x_m, y_m);
				break;
			
			case TRI:
				retaBresenham(x_p[0], y_p[0], x_m, y_m);
				break;
			
			case RET:
        		retaBresenham(x_p[0], y_p[0], x_m, y_p[0]);
                retaBresenham(x_m, y_p[0], x_m, y_m);
                retaBresenham(x_m, y_m, x_p[0], y_m);
                retaBresenham(x_p[0], y_m, x_p[0], y_p[0]);
                break;
            
			case POL:
				poligon = true;
				retaBresenham(formList.front().vertexList.front().x, formList.front().vertexList.front().y, x_m, y_m);
				//retaBresenham(x_p[0], y_p[0], x_p[1], y_p[1]);
				//retaBresenham(x_p[1], y_p[1], x_m, y_m);
				break;
			
            case CIR:
            	bresenhamCirculo(x_p[0], y_p[0], R);
            	break;
		}
	}else if(click2){
		switch(modo){
			case TRI:
				retaBresenham(x_p[0], y_p[0], x_p[1], y_p[1]);
				retaBresenham(x_p[1], y_p[1], x_m, y_m);
				retaBresenham(x_m, y_m, x_p[0], y_p[0]);
				break;
		}
	}*/
    //Percorre a lista de formas geometricas para desenhar
    for(forward_list<forma>::iterator f = formList.begin(); f != formList.end(); f++){
        //bool f == formList.begin();
        //int i=0, x[3], y[3];
        int i=0;
        vector<int> x,y;
        //int x1[3], y1[3];
				
		switch (f->tipo) {
            case LIN:
            	cout << "draw lin\n";
                //int i = 0, x[2], y[2];
                //Percorre a lista de vertices da forma linha para desenhar
                for(forward_list<vertice>::iterator v = f->vertexList.begin(); v != f->vertexList.end(); v++, i++){
                    x.push_back(v->x);
					y.push_back(v->y);
					//x[i] = v->x;
                    //y[i] = v->y;
                }
                //Desenha o segmento de reta apos dois cliques
                //retaImediata(x[0], y[0], x[1], y[1]);
                //Desenha o segmento de reta apos dois cliques COM BASE NO ALGORITMO DE BRESENHAM
                retaBresenham(x[0], y[0], x[1], y[1]);
            	break;
            
        	case TRI:
        		cout << "draw tri\n";
        		//Percorre a lista de vertices da forma triangulo para desenhar
        		for(forward_list<vertice>::iterator v = f->vertexList.begin(); v != f->vertexList.end(); v++, i++){
					x.push_back(v->x);
					y.push_back(v->y);
					//x[i] = v->x;
   					//y[i] = v->y;
				}
				drawTRI(x[0], y[0], x[1], y[1], x[2], y[2]);
				cout << "drawned lin\n";
				//desenha o triangulo apos tres cliques
				/*
  				retaBresenham(x[0], y[0], x[1], y[1]);
        		retaBresenham(x[1], y[1], x[2], y[2]);
        		retaBresenham(x[2], y[2], x[0], y[0]);
        		*/
    			break;
    		
            case RET:
            	cout << "draw ret\n";
            	//Percorre a lista de vertices da forma retangulo para desenhar
                for(forward_list<vertice>::iterator v = f->vertexList.begin(); v != f->vertexList.end(); v++, i++){
                    x.push_back(v->x);
					y.push_back(v->y);
					//x[i] = v->x;
                    //y[i] = v->y;
                }
				//Desenha o retangulo apos dois cliques
                // retaBresenham(x[0], y[0], x[1], y[0]);
                // retaBresenham(x[1], y[0], x[1], y[1]);
                // retaBresenham(x[1], y[1], x[0], y[1]);
                // retaBresenham(x[0], y[1], x[0], y[0]);
				drawPOL(x, y);
            	break;
            
            case POL:
            	cout << "draw pol\n";
            	/*
  			  	auto start = f->vertexList.begin();
				auto final = f->vertexList.end();
				auto aux = start;  
				while(aux != final){
					auto after = next(aux);
					if(after == final){  
						if(poligon && last){
							break;	
						} 
						after  = start;
					}
					retaBresenham(aux->x,aux->y,after->x,after->y);
					aux++;
				}*/
				for(forward_list<vertice>::iterator v = f->vertexList.begin(); v != f-> vertexList.end(); v++, i++){
					x.push_back(v->x);
					y.push_back(v->y);
					//x[i] = v->x;
					//y[i] = v->y;
				}
				drawPOL(x,y);
				break;    
			
			case CIR:
            	 //Percorre a lista de vertices da forma circulo para desenhar
                for(forward_list<vertice>::iterator v = f->vertexList.begin(); v != f->vertexList.end(); v++, i++){
                    x.push_back(v->x);
					y.push_back(v->y);
					//x[i] = v->x;
                    //y[i] = v->y;
                }
				float R = sqrt(pow(x[0] - x[1], 2) + pow(y[0] - y[1], 2));
				//Desenha o circulo apos dois cliques
				bresenhamCirculo(x[1], y[1], R);
                break;

        }
    }
}

/*
 * Funcao de preenchimento Flood Fill com vizinhanca 4
 */
void floodFill(int x, int y){
	if(x<0 || y<0 || x>width || y>height) return;
	float pixelColor[3];

	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelColor);
	
	if(pixelColor[0] != fR || pixelColor[1] != fG || pixelColor[2] != fB){
		if(pixelColor[0] == 0.0f && pixelColor[1] == 0.0f && pixelColor[2] == 0.0f) return;
		glPointSize(1.0f);
		glColor3f(fR, fG, fB);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		pushFloodFill(x, y);
		glutSwapBuffers();
		
		//pixels adjacentes
		floodFill(x + 1, y);
		floodFill(x, y + 1);
		floodFill(x - 1, y);		
		floodFill(x, y - 1);
	}
}
/*
 * Funcao que implementa o Algoritmo de Rasterizacao da Reta Imediata
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
	
	double dx, dy, d, incE, incNE, temp;
	// Passo 1
	bool S = false, D = false;

	// Passo 2
    dx = x2 - x1;
    dy = y2 - y1;
    
    // pegando o delta da variacao de x e de y
	//xmin = (x1 < x2)? x1 : x2;
    //xmax = (x1 > x2)? x1 : x2;

	//ymin = (y1 < y2)? y1 : y2;
    //ymax = (y1 > y2)? y1 : y2;
    
    //Redução ao Primeiro Octante (Passo 3)
    if((dx * dy) < 0){
		y1 = -y1;
		y2 = -y2;
		dy = (y2 - y1);
		// simetrico = 1
		S = true;
	} 
	
	// Passo 4
	if(fabs(dx) < fabs(dy)){
		temp = x1;
		x1 = y1;
		y1 = temp;
		
		temp = x2;
		x2 = y2;
		y2 = temp;
		
		dx = x2 - x1;
		dy = y2 - y1;
		D = true;
	}
	
	// Passo 5
	if(x1 > x2){
		temp = x1;
		x1 = x2;
		x2 = temp;
		
		temp = y1;
		y1 = y2;
		y2 = temp;
		
		dx = x2 - x1;
		dy = y2 - y1;
	}
	
	int y = int(y1);
	d = (2*dy) - dx;
	incE = 2 * dy;
	incNE = 2 *(dy - dx);
	
	drawPixel(int(x1), int(y1));
	for(int x = int(x1)+1; x<=int(x2); x++){
		if(d <= 0) d += incE;
		else{
			d += incNE;
			y++;
		}
		
		if(D && S)	drawPixel(y, -x);
		else if(D)	drawPixel(y, x);
		else if(S) 	drawPixel(x, -y);
	 	else        drawPixel(x, y);
	}
}

void bresenhamCirculo(double x1, double y1, double R){
	int temp_circ = int(R);
	
	int d = 1 - temp_circ;
	int incE = 3;
	int incSE = -2*temp_circ + 5;
	
	drawPixel(x1, y1 + temp_circ);
	drawPixel(x1, y1 - temp_circ);
	drawPixel(x1 + temp_circ, y1);
	drawPixel(x1 - temp_circ, y1);
	
	int y = temp_circ;
	
	for(int x = 1; y>x; x++){
		if(d<0){
			d += incE;
			incE += 2;
			incSE += 2;
			
		}
		else{
			d += incSE;
			incE += 2;
			incSE += 4;
			y--;

		}

		drawPixel(x1 + x, y1 + y);
		drawPixel(x1 + y, y1 + x);
		drawPixel(x1 - x, y1 + y);
		drawPixel(x1 + y, y1 - x);
		drawPixel(x1 + x, y1 - y);
		drawPixel(x1 - y, y1 + x);
		drawPixel(x1 - x, y1 - y);
		drawPixel(x1 - y, y1 - x);

	}
}

void drawRET(int x1, int y1, int x2, int y2){
	retaBresenham(x1, y1, x2, y1);
	retaBresenham(x1, y2, x2, y2);
	retaBresenham(x1, y1, x1, y2);
	retaBresenham(x2, y1, x2, y2);
}

void drawTRI(int x1, int y1, int x2, int y2, int x3, int y3)
{
	retaBresenham(x1, y1, x2, y2);
	retaBresenham(x2, y2, x3, y3);
	retaBresenham(x3, y3, x1, y1);

}

void drawPOL(vector<int>& x, vector<int>& y){
	int tam = x.size();
	
	for(int i=0; i<tam-1; i++){
		retaBresenham(x[i], y[i], x[i + 1], y[i + 1]);
	}	
	retaBresenham(x.back(), y.back(), x.front(), y.front());
}

void translation(int dx, int dy, forma& f){
	if(f.vertexList.empty()) return;
	for(auto it = f.vertexList.begin(); it != f.vertexList.end(); ++it){
		vertice& v = *it;
		v.x += dx;
		v.y += dy;
	}
	centroide(f);
	glutPostRedisplay();
}

void scaling(float sx, float sy, forma& f){
	if(f.vertexList.empty()) return;
	for(auto it = f.vertexList.begin(); it != f.vertexList.end(); ++it){
		vertice& v = *it;
		float dx = v.x - f.cx;
		float dy = v.y - f.cy;
		float dist = sqrt(dx * dx + dy * dy);
		
		if((sx > 1 && dist >= 500) || (sx < 1 && dist <= 30))
		{
			sx = 1;
			sy = 1;
		}
		// Aplica a transformacao de escala na forma selecionada
		v.x = round((v.x - f.cx) * sx + f.cx);
		v.y = round((v.y - f.cy) * sy + f.cy);
	}
	centroide(f);
	glutPostRedisplay();
}

void shear(float shx, float shy, forma& f){
	if(f.vertexList.empty()) return;
	for(auto it = f.vertexList.begin(); it != f.vertexList.end(); ++it){
		vertice& v = *it;
		
		v.x -= f.cx;
		v.y -= f.cy;
		
		float x_att = v.x + shy * v.y;
		float y_att = v.y + shx * v.x;

		v.x = round(x_att);
		v.y = round(y_att);

		v.x += f.cx;
		v.y += f.cy;
	}
	
	glutPostRedisplay();
}

void reflection(char eixo, forma& f){
	if(f.vertexList.empty()) return;
	float signal = (eixo == 'x' ? -1.0 : -1.0);
 
	for (auto it = f.vertexList.begin(); it != f.vertexList.end(); ++it){
		vertice& v = *it;

		v.x -= f.cx;
		v.y -= f.cy;

		if (eixo == 'x'){
			v.y *= signal;
		}else{
			v.x *= signal;
		}
		v.x += f.cx;
		v.y += f.cy;
	}

	glutPostRedisplay();
}

void rotation(float angle, forma& f) {
    float radians = angle * 3.14159265 / 180.0;
	float cosA = cos(radians);
	float sinA = sin(radians);
	if(f.vertexList.empty()) return;
	
    for (auto it_form = f.vertexList.begin(); it_form != f.vertexList.end(); ++it_form) {
        vertice& v = *it_form;
        float dx = v.x - f.cx;
        float dy = v.y - f.cy;
        
        v.x = round(f.cx + dx * cosA - dy * sinA);
        v.y = round(f.cy + dy * cosA - dx * sinA);
	}
	
    glutPostRedisplay();
}

/*

void fulfill(oq){
	
}
*/

	/*
		// Encontrar o centro do objeto
        float centro_x = 0.0;
        float centro_y = 0.0;

        // Contar o número de vértices
        int numVertexes = 0;

        for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
            centro_x += it_vertex->x;
            centro_y += it_vertex->y;
            numVertexes++;
        }

        if (numVertexes > 0) {
            centro_x /= numVertexes;
            centro_y /= numVertexes;

            // Transladar para a origem
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                it_vertex->x -= centro_x;
                it_vertex->y -= centro_y;
            }

            // Rotacionar
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                int x = static_cast<int>(it_vertex->x * cos(radians) - it_vertex->y * sin(radians));
                int y = static_cast<int>(it_vertex->x * sin(radians) + it_vertex->y * cos(radians));
                it_vertex->x = x;
                it_vertex->y = y;
            }

            // Transladar de volta para a posição original
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                it_vertex->x += centro_x;
                it_vertex->y += centro_y;
            }
        }
    }*/

/*
void translation(int dx, int dy) {
    for (forward_list<forma>::iterator it_form = formList.begin(); it_form != formList.end(); ++it_form) {
        for (forward_list<vertice>::iterator it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
            it_vertex->x += dx;
            it_vertex->y += dy;
        }
    }
    glutPostRedisplay();
}


void scaling(float sx, float sy) {
    for (auto it_form = formList.begin(); it_form != formList.end(); ++it_form) {
        // Encontrar o centro do objeto
        float center_x = 0.0;
        float center_y = 0.0;

        // Contar o número de vértices
        int numVertexes = 0;

        for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
            center_x += it_vertex->x;
            center_y += it_vertex->y;
            numVertexes++;
        }

        if (numVertexes > 0) {
            center_x /= numVertexes;
            center_y /= numVertexes;

            // Escala em relação ao centro do objeto
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                it_vertex->x = static_cast<int>((it_vertex->x - center_x) * sx + center_x);
                it_vertex->y = static_cast<int>((it_vertex->y - center_y) * sy + center_y);
            }
        }
    }
    glutPostRedisplay();
}

void shear(float shx, float shy) {
    for (auto it_form = formList.begin(); it_form != formList.end(); ++it_form) {
        // Encontrar o centro do objeto
        float center_x = 0.0;
        float center_y = 0.0;

        // Contar o número de vértices
        int numVertexes = 0;

        for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
            center_x += it_vertex->x;
            center_y += it_vertex->y;
            numVertexes++;
        }

        if (numVertexes > 0) {
            center_x /= numVertexes;
            center_y /= numVertexes;

            // Aplicar cisalhamento em relação ao centro do objeto
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                int x = it_vertex->x + static_cast<int>(shx * (it_vertex->y - center_y));
                int y = it_vertex->y + static_cast<int>(shy * (it_vertex->x - center_x));
                it_vertex->x = x;
                it_vertex->y = y;
            }
        }
    }
    glutPostRedisplay();
}

void reflection(char eixo, forma& f){
	if(f.vertexList.empty()) return;
	
	float signal = (eixo == 'x' ? -1.0 : -1.0);
	
	for(auto it = f.vertexList.begin(); 
}
/*
void reflection(bool horizontal, bool vertical) {
    int h = (horizontal) ? -1 : 1;
    int v = (vertical) ? -1 : 1;

    for (auto it_form = formList.begin(); it_form != formList.end(); ++it_form) {
        // Encontrar o centro do objeto
        float center_x = 0.0;
        float center_y = 0.0;

        // Contar o número de vértices
        int numVertexes = 0;

        for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
            center_x += it_vertex->x;
            center_y += it_vertex->y;
            numVertexes++;
        }

        if (numVertexes > 0) {
            center_x /= numVertexes;
            center_y /= numVertexes;

            // Transladar para a origem
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                it_vertex->x -= center_x;
                it_vertex->y -= center_y;
            }

            // Aplicar a reflexão
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                it_vertex->x *= h;
                it_vertex->y *= v;
            }

            // Transladar de volta para a posição original
            for (auto it_vertex = it_form->vertexList.begin(); it_vertex != it_form->vertexList.end(); ++it_vertex) {
                it_vertex->x += center_x;
                it_vertex->y += center_y;
            }
        }
    }
    glutPostRedisplay();
}
*/

    