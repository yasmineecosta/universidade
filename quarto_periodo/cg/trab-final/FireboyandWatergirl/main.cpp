/*
 * Computacao Grafica
 * Codigo Exemplo: Renderizacao de Modelo 3D Complexo e Animacoes
 * Autor: Prof. Laurindo de Sousa Britto Neto
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
    // Defina as constantes para o tamanho do mapa
#define TAM_X 19
#define TAM_Y 21

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
enum animation_ids{paused, idle, bored, jumping, running, shooting};
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
map<int, GLManimation *> animationsg;
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
 *  Definicao dos parametros do modelo de iluminacao
 */
GLfloat light_pos[] = {-2.0, 2.0, 2.0, 0.0};
GLfloat light_Ka[] = {0.4, 0.4, 0.4, 0.0};
GLfloat light_Kd[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light_Ks[] = {1.0, 1.0, 1.0, 0.0};

/*
 *  Definicao dos parametros do material para o modelo de iluminacao
 *  Parametros para material amarelado, cor de latao (Brass)
 */
GLfloat material_Ka[] = {0.33, 0.22, 0.03, 1.00};
GLfloat material_Kd[] = {0.78, 0.57, 0.11, 1.00};
GLfloat material_Ks[] = {0.99, 0.94, 0.81, 1.00};
GLfloat material_Ke[] = {0.00, 0.00, 0.00, 0.00};
GLfloat material_Se = 28;

/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas)
 */
void init_glut(const char *window_name, int argc, char** argv);
void reshape(int w, int h);
void display(void);
void drawAnimation(int type, GLuint mode);
void drawAnimationg(int type, GLuint mode);
void drawFloor(GLuint mode);
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
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    /*
     *  Ativacao dos parametros do material para uso do modelo de iluminacao
     *  Para usar este material a iluminacao (GL_LIGHTING) deve estar ativa
     *  e a cor do material (GL_COLOR_MATERIAL) desativada
     */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

    glEnable(GL_LIGHTING); // Ativa o modelo de iluminacao
    glEnable(GL_LIGHT0); // Ativa a Luz 0. O OpenGL suporta pelo menos 8 pontos de luz.

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
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    /*
     *  Carregando Modelos 3Ds, Texturas e Animacoes
     */
    printf("Loading 3D Models, Textures and Animations");
    animation = glmLoadAnimation("models/Boy/animations/idle/idle1.obj", paused, 1);
    animationg = glmLoadAnimation("models/Girl/animations/idle/idle1.obj", pausedg, 1);
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
    animationg = glmLoadAnimation("models/Girl/animations/idle", idleg, 301);
    animationsg[idleg] = animationg;
    printf(".");
    animation = glmLoadAnimation("models/ironman/animations/bored", bored, 50);
    //animation = glmLoadAnimation("models/Boy/animations/shooting", shooting, 77);
    animations[bored] = animation;
    printf(".");
    animation = glmLoadAnimation("models/Boy/animations/jumping", jumping, 58);
    animations[jumping] = animation;
    animationg = glmLoadAnimation("models/Girl/animations/jumping", jumpingg, 58);
    animationsg[jumpingg] = animationg;
    printf(".");
    animation = glmLoadAnimation("models/Boy/animations/running", running, 22);
    animations[running] = animation;
    animationg = glmLoadAnimation("models/Girl/animations/running", runningg, 22);
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
    glColor3f(R, G, B);

    glPushMatrix();
        glScaled(scale, scale, scale);
        glTranslated (posx, posy, posz);
        glRotated (rotx, 1.0f, 0.0f, 0.0f);
        glRotated (roty, 0.0f, 1.0f, 0.0f);
        glRotated (rotz, 0.0f, 0.0f, 1.0f);
        drawAnimation(animation_id, mode);
    glPopMatrix();
    
    glPushMatrix();
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
        if(animation_id == idle && frames_playing >= (size * keyframe_rate * 5) + 1) playAnimation(bored);

        //Verifica se foi alterada a animacacao atual e reinicia os contadores para a nova animacao
        else if(current_animation != animation_id) playAnimation(animation_id);

        //Se uma animacao diferente de idle ou bored nao for mais reiniciada, reproduz a animacao idle
        else if(animation_id!= idle && animation_id!= bored && keyframe>= size && frames_playing>= size) playAnimation(idle);

        //reinicia a mesma animacao
        else if(keyframe >= size) keyframe = 0;

        
//        printf("animation: %d, keyframe: %d ,size: %d, rate: %d, frames_playing: %d\n", animation_id, keyframe, size, count_rate, frames_playing);
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
        else if(animation_idg!= idleg && animation_idg!= idleg && keyframeg>= size && frames_playingg>= size) playAnimationg(idleg);

        //reinicia a mesma animacao
        else if(keyframeg >= size) keyframeg = 0;

        
//        printf("animation: %d, keyframe: %d ,size: %d, rate: %d, frames_playing: %d\n", animation_id, keyframe, size, count_rate, frames_playing);
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
	    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
		{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 2},
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 0, 0, 0, 0, 0, 0, 2},
		{2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2},
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
/*
 * Controle das teclas comuns
 */
void keyboard(unsigned char key, int x, int y){
    switch(key){
    	
        case SPACE: if(!is_paused) keyPlayAnimation(jumping);
		   	   	    posy+=2;
			break; // Tecle SPACE para ativar a animacao de salto
        case ENTER: if(!is_pausedg) keyPlayAnimationg(jumpingg);
        			posgy+=2;
			break;
        case 'p':case 'P':
            is_paused = !is_paused;
            animation_id = paused;
            keyframe = 0;
        break;
        case 'g': case 'G': //Rotaciona a camera em torno do eixo Y no sentido anti-horario
            float radianos;
            cam_roty += graus;
            if (cam_roty >= 360.0) cam_roty = 0.0;
            radianos = (cam_roty * M_PI)/180.0;
            camx = 0.0; camz = CAMZ;
            camx =  camx*cosf(radianos) + camz*sinf(radianos);
            camz =  - camx*sinf(radianos) + camz*cosf(radianos) ;
        break;
        case 'y': case 'Y': //Rotaciona a camera em torno do eixo Y no sentido horario
            cam_roty -= graus;
            if (cam_roty <= -360.0) cam_roty = 0.0;
            radianos = (cam_roty * M_PI)/180.0;
            camx = 0.0; camz = CAMZ;
            camx =    camx*cosf(radianos) + camz*sinf(radianos);
            camz =  - camx*sinf(radianos) + camz*cosf(radianos);
        break;
        case 'b': case 'B': //Rotaciona a camera em torno do eixo X no sentido anti-horatio
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
        break;/*
        case GLUT_KEY_UP: // Move o personagem para tras
            if(!is_paused){
                if(is_jumping) keyPlayAnimation(jumping);
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
                update_direcao(roty);
            }
        break;
        case GLUT_KEY_DOWN: // Move o personagem para frente
                if(!is_paused){
                    if(is_jumping) keyPlayAnimation(jumping);
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
                    update_direcao(roty);
                }
        break;*/
	    case GLUT_KEY_UP:
			if(!is_pausedg){
                if(is_jumpingg) keyPlayAnimationg(jumpingg);
                else keyPlayAnimationg(runningg);
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
	    break;
		case GLUT_KEY_DOWN:
			if(!is_pausedg){
                if(is_jumpingg) keyPlayAnimationg(jumpingg);
                else keyPlayAnimationg(runningg);
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
  	     break;
			
    }
}

/*
 * Controle do menu pop-up
 */
void menu(int value){
    switch(value){
        case 0: exit(EXIT_SUCCESS); break; //Sai do programa
    }
}
