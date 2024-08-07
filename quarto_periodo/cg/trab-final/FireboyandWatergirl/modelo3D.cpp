/*
 * Computacao Grafica
 * Codigo: Fireboy and Watergirl
 * Autores: Yasmine Martins da Costa e Silva e Felipe
 */

/* Inclui os headers do OpenGL, GLU, e GLUT */
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

/* Inclui o arquivo header com a textura */
#include "glm.h"
#include "glut_text.h"
#include "montagem.h"
#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
    // Defina as constantes para o tamanho do mapa
#define TAM_X 19
#define TAM_Y 21
#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif
#ifndef M_PI
    #define M_PI 3.14159265358979323846
    
#endif



/*
 * Declaracao de constantes e variaveis
 */
#define ESC 27 // ASCII para a tecla ESC
#define SPACE 32 // ASCII para a tecla de ESPACO
#define MAX_FPS 70 // Maximo de Frames Por Segundo (FPS) desejado
#define FPS 60 // FPS desejado atualmente
#define KEYFRAME_RATE 3 // taxa de repeticoes do keyframe da animacao nos quadros da video
#define KEYFRAME_RATEG 3
#define ENTER 13
#define POSY -1.04  //posicao do modelo 3D no eixo y
#define POSGY -1.04
#define CAMZ 50.0    //posicao da camera no eixo z
#define CAMX 10.0
#define CAMY 10.0

vector<pair<double, double> > positions;

int fps_desejado = FPS/2; // variavel para alterar os frames por segundo desejado
int fps = 0; //contador de frames por segundo
float reshape_ratio = 1.0; // Manter proporcional a projecao
GLuint width = 640, height = 480; // Largura e altura da janela

//Enumeracoes com as direcoes do Objeto 3D em relacao a camera para realizar movimentacoes
enum direcao_acam{frente, tras, esquerda, direita};
enum direcao_acamg{frenteg, trasg, esquerdag, direitag};
int direcao = frente, direcaog = frenteg;

//Enumearacao com os identificadores das animacoes
enum animation_ids{paused, idle, jumping, running, shooting};
enum animation_idsg{pausedg, idleg, jumpingg, runningg, shootingg};
int animation_id = idle; //Indica a animacao a ser desenhada atualmente
int animation_idg = idleg;
int current_animation = idle; // Salva qual e a animacao atual
int current_animationg = idleg;
bool is_jumping = false;
bool is_jumpingg = false;

GLManimation * animation = NULL;   //Ponteiro usado no armazenamento de uma animacao
GLManimation * animationg = NULL;
map <int, GLManimation *> animations; //Mapeamento dos identificadores com as animacoes
map <int, GLManimation *> animationsg;
int keyframe = 0, keyframeg = 0; // numero do modelo 3D (keyframe) da animacao que sera desenhado no momento
int keyframe_rate = KEYFRAME_RATE, keyframe_rateg = KEYFRAME_RATEG; // alterar a taxa de repeticoes do keyframe na reproducao da animacao
int count_rate = -1, count_rateg = -1; //Conta a quantidade de repeticoes do keyframe ate atingir a taxa keyframe_rate
int frames_playing = 0, frames_playingg = 0; //Conta a quantidade de quadros enquanto reproduz uma mesma animacao ate troca-la
int faces_animacao = 0, vertices_animacao = 0, faces_animacaog = 0, vertices_animacaog = 0;//Numero de faces e vertices do objeto 3D
float graus = 15.0, deslocamento = 0.2, grausg = 15.0, deslocamentog = 0.2; //incrementos do angulo de graus e do deslocamento
float scale = 1, scaleg = 1; // fator de escala proporcional em todos os eixos do modelo 3D
float rotx = 0.0, roty = 0.0, rotz = 0.0, rotgx = 0.0, rotgy = 0.0, rotgz = 0.0; // angulo de graus do modelo 3D no eixo x, y e z
float posx = 0.0, posy = POSY, posz = 0.0, posgx = 0.0, posgy = POSGY, posgz = 0.0; // deslocamento do modelo 3D no eixo x, y e z
float R = 1.0, G = 1.0, B = 1.0; //Cores do desenho controladas pelo glColor (inicial: cor branca)
float camx = CAMX, camy = CAMY, camz = CAMZ; // posicao da camera no eixo x, y e z
float cam_rotx = 0.0, cam_roty = 0.0; // angulo de graus da camera no eixo x e y
float cam_up = 1.0; //direcao do vetor para cima da camera

bool use_perspective = true; // Determina se usa projecao perspectiva ou ortografica
bool use_gouraud = true; // Determina o uso de Gouraud ou Flat shading
bool use_texture = true; // Determina o uso de texturas
bool use_color_material = false; // Determina o uso da glColor como parametro do material
bool use_depth_test = true; // Determina o uso ou nÃ£o do Z-buffering
bool use_light = true; // Determina se liga ou desliga a luz
bool render_solid = true; // Determina se renderiza o objeto solido ou em wireframe
bool is_paused = false; // Determina se a animacao esta tocando ou em pausa
bool is_pausedg = false;
GLint apply_texture = GL_DECAL; //Determina como a textura sera aplicada no objeto
std::string apply_texture_name = "Decal"; //Nome da fucao que sera usada para aplicar a textura no objeto


/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas)
 */
void init_glut(const char *window_name, int argc, char** argv);
void reshape(int w, int h);
void display(void);
void drawAnimation(int type, GLuint mode);
void drawAnimationg(int type, GLuint mode);
void drawFloor(GLuint mode);
GLuint loadBMP(const char* filename);
void renderBackground();
GLuint backgroundTexture;
void playAnimation(int id);
void playAnimationg(int id);
void computeFPS(int keyframe_rate);
void timer(int value);
void keyPlayAnimationg(int id);
void keyPlayAnimation(int id);
void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void menu(int value);

/*
 * Funcao principal
 */
int main(int argc, char** argv){
    // inicia o GLUT e alguns parametros do OpenGL
    init_glut("Fireboy e Watergirl", argc, argv);
    // funcao de controle do GLUT
    glutMainLoop();
    return EXIT_SUCCESS;
}

/*
 * Funcao para inicializacao do GLUT e de alguns parametros do OpenGL
 */
void init_glut(const char *nome_janela, int argc, char** argv){
    // inicia o GLUT
    glutInit(&argc,argv);

    // Inicia o display usando RGB, double-buffering e Z-buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);
    
    // Define as funcoes de callback
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard_special);
    glutTimerFunc(1000/fps_desejado, timer, 0); //(mseg, timer, value)

    // Define o menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Sair", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    /*
     *  Ativacao dos parametros do modelo de iluminacao para a Luz 0
     */
    
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_color[] = {0.0, 0.0, 1.0, 0.0};
    /*
     *  Ativacao dos parametros do modelo de iluminacao para a Luz 0
     */
    /*
     *  Ativacao dos parametros do material para uso do modelo de iluminacao
     *  Para usar este material a iluminacao (GL_LIGHTING) deve estar ativa
     *  e a cor do material (GL_COLOR_MATERIAL) desativada
     */
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING); //Ativa o modelo de iluminacao
	glEnable(GL_LIGHT0); //Ativa a Luz 0. O OpenGL suporta pelo menos 8 pontos de luz

	// Inicia as caracteristicas gerais dos materiais
	GLfloat mat_ambient_diffuse[] = {.0, 0.0, 0.0, 0.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL); //Um ou mais parametros do material rastreiam a cor atual do glColor.

    /*
     *  Configurando o OpenGL para o uso de Texturas
     */
    //Define como a textura sera aplicada ao objeto
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, apply_texture);

    //Ativa a visualizacao de texturas 2D (Texturizacao 2D)
    glEnable(GL_TEXTURE_2D);
    
    // Ativa o modelo de sombreamento de "Gouraud" (Smooth
    glShadeModel(GL_SMOOTH);
    
    // Ativa o Back-face Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Ativa o z-buffering, de modo a remover as superficies escondidas
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
        
    //Define a cor de fundo (branco)
    //glClearColor(0.17, 0.18, 0.03,1);
    backgroundTexture = loadBMP("textures/fundo.bmp");
    /*
     *  Carregando Modelos 3Ds, Texturas e Animacoes
     */
    
    printf("Loading 3D Models, Textures and Animations");
    animation = glmLoadAnimation("models/Boy/animations/idle/idle1.obj", paused, 1);
    animationg = glmLoadAnimation("models/Girl/animations/idleg/idleg1.obj", pausedg, 1);
    animation->name = "paused";
    animationg->name = "paused";
    animations[paused] = animation;
    animationsg[pausedg] = animationg;
    faces_animacao = animation->models[0]->numtriangles;
    vertices_animacao = animation->models[0]->numvertices;
    faces_animacaog = animationg->models[0]->numtriangles;
    vertices_animacaog = animationg->models[0]->numvertices;
    printf(".");
    animation = glmLoadAnimation("models/Boy/animations/idle", idle, 500);
    animations[idle] = animation;
    animationg = glmLoadAnimation("models/Girl/animations/idleg", idleg, 301);
    animationsg[idleg] = animationg;
    printf(".");
    animation = glmLoadAnimation("models/Boy/animations/shooting", shooting, 77);
    animations[shooting] = animation;
    animationg = glmLoadAnimation("models/Girl/animations/shootingg", shootingg, 58);
    animationsg[shootingg] = animationg;
    printf(".");
    animation = glmLoadAnimation("models/Boy/animations/jumping", jumping, 58);
    animations[jumping] = animation;
    animationg = glmLoadAnimation("models/Girl/animations/jumpingg", jumpingg, 58);
    animationsg[jumpingg] = animationg;
    printf(".");
    animation = glmLoadAnimation("models/Boy/animations/running", running, 22);
    animations[running] = animation;
    animationg = glmLoadAnimation("models/Girl/animations/runningg", runningg, 22);
    animationsg[runningg] = animationg;
    printf(" done.\n");
}

/*
 * Processa o reshape da janela
 */
void reshape(int w, int h){
    // muda para o modo GL_PROJECTION e reinicia a projecao
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    
    // define a zona da janela onde se vai desenhar
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    //Define a projecao perspectiva
    reshape_ratio = (float)w/(float)h;
    width = w;
    height = h;

    if(use_perspective){
        gluPerspective(30, reshape_ratio, 1.0, 100.0);
    }else{
        float ratioh = 1.34, ratiow = reshape_ratio * ratioh;
        glOrtho (-ratiow, ratiow, -ratioh, ratioh, 1.0 , 15.0);
    }
    
    // muda para o modo GL_MODELVIEW para preparar o desenho
    glMatrixMode (GL_MODELVIEW);
}


/*
 * Funcao para controlar o display
 */
void display(void){
    // Computa a taxa  de desenho de frames por segundo
    computeFPS(keyframe_rate); // Incrementa o keyframe da animacao a ser desenhado
    computeFPS(keyframe_rateg);
    // Apaga o video e o depth buffer, e reinicia a matriz
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    renderBackground();
    // Translada a camera no eixo Z se distanciando do objeto
    gluLookAt(camx, camy, camz, 6.0, 8.0, 0.0, 0.0, cam_up, 0.0);

    // Ativa/Desativa a Texturizacao 2D (Visualizacao de Texturas 2D)
    if(use_texture) glEnable(GL_TEXTURE_2D);
    else glDisable(GL_TEXTURE_2D);
    
    // Liga/Desliga a luz
    if(use_light) glEnable(GL_LIGHTING);
    else glDisable(GL_LIGHTING);
    
    //Define se desenha usando sombreamento Gouraud ou Flat
    GLuint mode;
    if(use_gouraud) mode = (GLM_SMOOTH | GLM_TEXTURE);
    else mode = (GLM_FLAT  |GLM_TEXTURE);
            
    //Define a cor dos objetos da animacao
    //glColor3f(R, G, B);

    glPushMatrix();
    	glColor3f(0.74,0.23,0.23);
        glScaled(scale, scale, scale);
        glTranslated (posx, posy, posz);
        glRotated (rotx, 1.0f, 0.0f, 0.0f);
        glRotated (roty, 0.0f, 1.0f, 0.0f);
        glRotated (rotz, 0.0f, 0.0f, 1.0f);
        drawAnimation(animation_id, mode);
    glPopMatrix();
    
    glPushMatrix();
    	glColor3f(0.11,0.34,0.48);
    	glScaled(scaleg, scaleg, scaleg);
        glTranslated (posgx+0.8, posgy, posgz);
        glRotated (rotgx, 1.0f, 0.0f, 0.0f);
        glRotated (rotgy, 0.0f, 1.0f, 0.0f);
        glRotated (rotgz, 0.0f, 0.0f, 1.0f);
        drawAnimationg(animation_idg, mode);
    glPopMatrix();
    drawFloor(mode); //Desenha o chao
    
    if(is_jumping && keyframe == animations[jumping]->keyframes - 1) is_jumping = false;
    if(is_jumpingg && keyframeg == animationsg[jumpingg]->keyframes - 1) is_jumpingg = false;
    // Translada a camera no eixo Z se distanciando do objeto
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // Desenhando textos na janela GLUT
    glDisable(GL_TEXTURE_2D); //Desativa a Texturizacao 2D para desenhar o texto
    glDisable(GL_LIGHTING); // Desliga a Luz para desenhar o texto
    glColor3f(0.0, 0.0, 0.0); // seleciona a cor preta para o texto
    
    // Troca os buffers, mostrando o que acabou de ser desenhado
    glutSwapBuffers();
}

/*
 * Coloca para reproduzir a animacao identificada
 */
void playAnimation(int id){
    keyframe = 0; // atribui o modelo 3D (keyframe) zero da animacao selecionada para ser desenhado
    frames_playing = 1; // reinicia a contagem de frames da reproducao da mesma animacao
    count_rate = 0; // Reinicia o contador de repeticoes do mesmo keyframe
    animation_id = id; // ativa a animacao com o identificador id
    current_animation = animation_id; // salva qual e a animacao atual
}

void playAnimationg(int id){
	keyframeg = 0; // atribui o modelo 3D (keyframe) zero da animacao selecionada para ser desenhado
    frames_playingg = 1; // reinicia a contagem de frames da reproducao da mesma animacao
    count_rateg = 0; // Reinicia o contador de repeticoes do mesmo keyframe
    animation_idg = id; // ativa a animacao com o identificador id
    current_animationg = animation_idg; // salva qual e a animacao atual
}

/*
 * Computa a quantidade de frames por segundo da animacao
 * Baseado no FPS e de acordo com o keyframe_rate, incrementa o keyframe da animacao a ser desenhado
 */
void computeFPS(int keyframe_rate){
    static GLuint frames = 0;       //Conta os frames em 1000 milissegundos, computando o FPS
    static GLuint clock;            // em milissegudos
    static GLuint next_clock = 0;   // em milissegudos

    count_rate++;
    frames_playing++;
    frames++;
    clock = glutGet(GLUT_ELAPSED_TIME); //NÃºmero de milissegundos desde a chamada a glutInit()

    if(!is_paused){ // Verifica se a animacao esta em pausa
        if(count_rate == keyframe_rate){ // Ao atigir a taxa de keyframes
            keyframe++; // incrementa o keyframe atual
            count_rate = 0; // reinicia o contador da taxa de keyframes
        }
                
        int size = animations[current_animation]->keyframes; // Quantidade de frames da animacao atual
        
        //Se animacao == idle, depois de reproduzir 5 vezes a animacao idle reproduz a animacao bored
        if(animation_id == idle && frames_playing >= (size * keyframe_rate * 5) + 1) playAnimation(idle);

        //Verifica se foi alterada a animacacao atual e reinicia os contadores para a nova animacao
        else if(current_animation != animation_id) playAnimation(animation_id);

        //Se uma animacao diferente de idle ou bored nao for mais reiniciada, reproduz a animacao idle
        else if(animation_id!= idle && keyframe>= size && frames_playing>= size) playAnimation(idle);

        //reinicia a mesma animacao
        else if(keyframe >= size) keyframe = 0;

    }
    
    if(!is_pausedg){ // Verifica se a animacao esta em pausa
        if(count_rateg == keyframe_rateg){ // Ao atigir a taxa de keyframes
            keyframeg++; // incrementa o keyframe atual
            count_rateg = 0; // reinicia o contador da taxa de keyframes
        }
                
        int size = animationsg[current_animationg]->keyframes; // Quantidade de frames da animacao atual
        
        //Se animacao == idle, depois de reproduzir 5 vezes a animacao idle reproduz a animacao bored
        if(animation_idg == idleg && frames_playingg >= (size * keyframe_rateg * 5) + 1) playAnimationg(idleg);

        //Verifica se foi alterada a animacacao atual e reinicia os contadores para a nova animacao
        else if(current_animationg != animation_idg) playAnimationg(animation_idg);

        //Se uma animacao diferente de idle ou bored nao for mais reiniciada, reproduz a animacao idle
        else if(animation_idg!= idleg && keyframeg>= size && frames_playingg>= size) playAnimationg(idleg);

        //reinicia a mesma animacao
        else if(keyframeg >= size) keyframeg = 0;
	}
    
    if (clock < next_clock ) return;
    fps = frames; // guarda o nÃºmero de frames por segundo
    // Evita o reinicio da contagem dos frames na primeira iteracao
    if(next_clock != 0) frames = 0;//Reinicia a contagem dos frames a cada 1000 milissegundos
    next_clock = clock + 1000; //A cada 1000 milissegundos = 1 segundo
}


void drawAnimation(int id, GLuint mode){
    glmDrawAnimation(animations[id], keyframe, mode);
}

void drawAnimationg(int id, GLuint mode){
    glmDrawAnimation(animationsg[id], keyframeg, mode);
}

void drawFloor(GLuint mode){
	int mapa[TAM_X][TAM_Y] =
	{
		{2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 2, 2, 2, 4, 4, 4, 2, 2, 2, 2, 0, 0, 0, 0, 2},
        {2, 2, 2, 7, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 8, 8, 2, 7, 2, 2},
        {2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 0, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 6, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			
	};
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0;
    if(mode & GLM_SMOOTH) glEnable(GL_SMOOTH);
    else glEnable(GL_FLAT);
    glDisable(GL_TEXTURE_2D);
	glTranslatef(-1, -1, 0);
    for(int i = 0; i <= TAM_Y; i++ ){
        for (int j = 0; j <= TAM_X+1; j++){
            glPushMatrix();
            if (mapa[i][j] == 0) //fundo
			{
				
				fundoMapa(i, j, x, y, h, w);
			}
			else if (mapa[i][j] == 1) // lava
			{
				
				lava(i, j, x, y, h, w);
			}
			else if (mapa[i][j] == 2) // Chao e Paredes
			{
				positions.push_back({i*1.0,j*1.0});
				parede(i, j, x, y, h, w);
			}
			else if (mapa[i][j] == 3) //agua
			{
				
				agua(i, j, x, y, h, w);
			}
			else if (mapa[i][j] == 4) //veneno
			{
				
				veneno(i, j, x, y, h, w);
			}
			else if (mapa[i][j] == 5)
			{
				portalV(i, j, x, y, h, w); //portalVermelho
			}
			else if (mapa[i][j] == 6)
			{
				portalA(i, j, x, y, h, w); //portalAzul
			}
			else if (mapa[i][j] == 7)
			{
				botao(i, j, x, y, h, w); //ativar elevador
			}
			else if (mapa[i][j] == 8)
			{
				elevador(i, j, x, y, h, w); // transladar
			} 
            glPopMatrix();
            
        }
    }
    glEnable(GL_TEXTURE_2D);
	
}

/*
 * Funcao utilizada para a animacao com temporizador
 */
void timer(int value){
    glutTimerFunc(1000/(fps_desejado), timer, 0);
    glutPostRedisplay(); // Manda redesenhar a tela em cada frame
}

/*
 * Reproduz uma animacao acionada por uma tecla
 */
void keyPlayAnimation(int id){
    frames_playing = 0;
    animation_id = id;
    if(id == jumping) is_jumping = true;
}

void keyPlayAnimationg(int id){
	frames_playingg = 0;
    animation_idg = id;
    if(id == jumpingg) is_jumpingg = true;
}

bool colisao_esquerda()
{
    if (posx - 1 <= -1) return true;
    if (posx - 1 <= 5 && posy >= POSY + 4 && posy < POSY + 5) return true;
    if (posy >= POSY + 10 && posy < POSY + 10.5 && posx >= 14 && posx < 15) return true;
    if (posy >= POSY + 11 && posy < POSY + 11.5 && posx >= 13 && posx < 14) return true;
    if (posy >= POSY + 12 && posy < POSY + 12.5 && posx >= 12 && posx < 13) return true;
    if (posy >= POSY + 11 && posy < POSY + 13 && posx < 2) return true;
    return false;
}
 
bool colisao_direita()
{
    if (posx + 1 >= 19) return true;
    if (posx + 1 >= 16 && posy < POSY + 2) return true;
    return false;
}
 
bool colisao_chao()
{
    if (posy - 1 <= POSY) return true;
    if (posy >= POSY + 2 && posy <= POSY + 3 && posx >= 15) return true;
    if (posy >= POSY + 3 && posy <= POSY + 5 && posx <= 13) return true;
    if (posy >= POSY + 4 && posy <= POSY + 6 && posx <= 5) return true;
    if (posy >= POSY + 5.4 && posy <= POSY + 7 && posx <= 1) return true;
    if (posy >= POSY + 7 && posy <= POSY + 9 && posx >= 1 && posx <= 7) return true;
    if (posy >= POSY + 6 && posy <= POSY + 8 && posx > 7) return true;
    if (posy >= POSY + 8 && posy <= POSY + 10 && posx >= 16) return true;
    if (posy >= POSY + 10 && posy <= POSY + 11 && posx >= 10 && posx <= 14) return true;
    if (posy >= POSY + 11 && posy <= POSY + 12 && posx >= 10 && posx < 13) return true;
    if (posy >= POSY + 12 && posy <= POSY + 13 && posx >= 10 && posx < 12) return true;
    if (posy >= POSY + 11 && posy <= POSY + 12 && posx < 11) return true;
    if (posy >= POSY + 13 && posy <= POSY + 14 && posx < 5) return true;
    if (posy >= POSY + 15 && posy <= POSY + 16 && posx > 3.5) return true;
    return false;
}


bool colisao_esquerdag()
{
    if (posgx - 1 <= -1.8) return true;
    //if (posgx - 1 <= 4.2 && posgy >= POSGY + 3 && posy < POSY + 4) return true;
    if (posgy >= POSGY + 10 && posgy < POSGY + 10.5 && posgx >= 11.2 && posgx < 12.2) return true;
    if (posgy >= POSGY + 11 && posgy < POSGY + 11.5 && posgx >= 10.2 && posgx < 11.2) return true;
    if (posgy >= POSGY + 12 && posgy < POSGY + 12.5 && posgx >= 9.2 && posgx < 10.2) return true;
    if (posgy >= POSGY + 11 && posgy < POSGY + 13 && posgx < 0.2) return true;
    return false;
}
 
bool colisao_direitag()
{
    if (posgx + 1 >= 18.2) return true;
    if (posgx + 1 >= 15.2 && posgy < POSGY + 2) return true;
    return false;
}
 
bool colisao_chaog()
{
    if (posgy - 1 <= POSGY) return true;
    if (posgy >= POSGY + 2 && posgy <= POSGY + 3 && posgx >= 14.2) return true;
    if (posgy >= POSGY + 3 && posgy <= POSGY + 5 && posgx <= 12.2) return true;
    if (posgy >= POSGY + 4 && posgy <= POSGY + 6 && posgx <= 4.2) return true;
    if (posgy >= POSGY + 5.4 && posgy <= POSGY + 7 && posgx <= 0.2) return true;
    if (posgy >= POSGY + 7 && posgy <= POSGY + 9 && posgx >= 0.2 && posgx <= 6.2) return true;
    if (posgy >= POSGY + 6 && posgy <= POSGY + 8 && posgx > 6.2) return true;
    if (posgy >= POSGY + 8 && posgy <= POSGY + 10 && posgx >= 15.2) return true;
    if (posgy >= POSGY + 10 && posgy <= POSGY + 11 && posgx >= 9.2 && posgx <= 13.2) return true;
    if (posgy >= POSGY + 11 && posgy <= POSGY + 12 && posgx >= 9.2 && posgx < 12.2) return true;
    if (posgy >= POSGY + 12 && posgy <= POSGY + 13 && posgx >= 9.2 && posgx < 11.2) return true;
    if (posgy >= POSGY + 11 && posgy <= POSGY + 12 && posgx < 10.2) return true;
    if (posgy >= POSGY + 13 && posgy <= POSGY + 14 && posgx < 4.2) return true;
    if (posgy >= POSGY + 15 && posgy <= POSGY + 16 && posgx > 2.7) return true;
    return false;
}
/*
 * Controle das teclas comuns
 */
void keyboard(unsigned char key, int x, int y){
    switch(key){
    	
        case ENTER: if(!is_pausedg && colisao_chaog()) {
					keyPlayAnimationg(jumpingg);
        			posgy+=2;
					}
					break;
		case SPACE: 
                    if(!is_paused && colisao_chao())
                    {
                        keyPlayAnimation(jumping);
                        posy+=2;
                    }
                    break; // Tecle SPACE para ativar a animacao de salto
        case 'p':case 'P':
            is_paused = !is_paused;
            animation_id = paused;
            keyframe = 0;
            break;
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
 
        // Tecle < ou > para alterar o FPS desejado
        case ',': case '<': if(fps_desejado > 1) fps_desejado -= 1; break;
        case '.': case '>': if(fps_desejado*2 < MAX_FPS) fps_desejado += 1; break;
        case ESC: exit(EXIT_SUCCESS); break; // Tecle ESC para sair do programa
    }
}

/*
 * Atualiza a direcao do personagem
 */
void update_direcao(){
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
}

void update_direcaog(){
    if(rotgy ==  0.0 || rotgy == 360.0){
        direcaog = frenteg;
        rotgy = 0.0;
    }
    if(rotgy == 180.0 || rotgy == -180.0){
        direcaog = trasg;
        rotgy = 180.0;
    }
    if(rotgy ==  90.0) direcaog = direitag;
    if(rotgy == -90.0 || rotgy == 270.0) direcaog = esquerdag;
}


/*
 * Controle das teclas especiais (Cursores, F1 a F12, etc...)
 */
void keyboard_special(int key, int x, int y){
    switch(key){
            
        //Use as setas do teclado para movimentar o personagem
        case GLUT_KEY_RIGHT: // Move o personagem para direita
            if(!is_paused){
                if(is_jumping) keyPlayAnimation(jumping);
                else keyPlayAnimation(running);
                if(!colisao_direita()){
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
            }
        break;
        case GLUT_KEY_LEFT: // Move o personagem para esquerda
            if(!is_paused){
                if(is_jumping) keyPlayAnimation(jumping);
                else keyPlayAnimation(running);
                if (!colisao_esquerda()){
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
            }
        break;
	    case GLUT_KEY_UP:
			if(!is_pausedg){
                if(is_jumpingg) keyPlayAnimationg(jumpingg);
                else keyPlayAnimationg(runningg);
                if (!colisao_esquerdag()){
	                if(direcaog==esquerdag){
	                    if(rotgy == -90.0 || rotgy == 270.0) posgx -= deslocamentog;
	                    else if ( rotgy < -90.0 || rotgy < 270.0 ) rotgy += grausg;
	                    else rotgy -= grausg;
	                }else if (direcaog == direitag){
	                    if(rotgy >= 90.0) rotgy += grausg;
	                    else rotgy -= grausg;
	                }else if (direcaog == frenteg) rotgy -= grausg;
	                else rotgy += grausg;
	                update_direcaog();
				}
            }	 	
	    break;
		case GLUT_KEY_DOWN:
			if(!is_pausedg){
                if(is_jumpingg) keyPlayAnimationg(jumpingg);
                else keyPlayAnimationg(runningg);
                if (!colisao_direitag()){
	                if(direcaog==direitag){
	                    if(rotgy == 90.0) posgx += deslocamentog;
	                    else if (rotgy < 90.0 ) rotgy -= grausg;
	                    else rotgy += grausg;
	                }else if (direcaog == esquerdag){
	                    if( rotgy >= 180.0) rotgy -= grausg;
	                    else rotgy += grausg;
	                }else if (direcaog == frenteg) rotgy += grausg;
	                else rotgy -= grausg;
	                update_direcaog();
                }
			}
  	     break;	
 	}
	 if(!colisao_chao()) posy -=0.035;	
	 if(!colisao_chaog()) posgy -=0.035;
}



GLuint loadBMP(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Image could not be opened\n");
        return 0;
    }

    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54) {
        printf("Not a correct BMP file\n");
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        fclose(file);
        return 0;
    }

    unsigned int dataPos = *(int*)&(header[0x0A]);
    unsigned int imageSize = *(int*)&(header[0x22]);
    unsigned int width = *(int*)&(header[0x12]);
    unsigned int height = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    unsigned char* data = new unsigned char[imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    delete[] data;
    return textureID;
}

void renderBackground() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Desativa o teste de profundidade
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Garante que a cor seja branca
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1024, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1024, 1024);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 1024);
    glEnd();
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(1024, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(2048, 0); // Ajustado para a segunda parte da textura
        glTexCoord2f(1.0f, 1.0f); glVertex2f(2048, 1024); // Ajustado para a segunda parte da textura
        glTexCoord2f(0.0f, 1.0f); glVertex2f(1024, 1024); // Ajustado para a segunda parte da textura
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

/*
 * Controle do menu pop-up
 */
void menu(int value){
    switch(value){
        case 0: exit(EXIT_SUCCESS); break; //Sai do programa
    }
}
