/* Autores: Pedro F. Soares e Thales R. Martins */
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <AudioToolbox/AudioToolbox.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <windows.h>
	#include <mmsystem.h>
#endif


#include "glm.h"
#include <ctime>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
#include <iostream>
#include <sstream>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif


#define ENEMY_SHOOT_INTERVAL 2000
int last_enemy_shot_time = 0;


#define ESC 27 // ASCII para a tecla ESC
#define SPACE 32 // ASCII para a tecla de ESPACO
#define MAX_FPS 70 // Maximo de Frames Por Segundo (FPS) desejado
#define FPS 60 // FPS desejado atualmente
#define SHOOT_INTERVAL 700 // Intervalo de tempo entre disparos em milissegundos

int fps_desejado = FPS/2; 
int fps = 0; 
float reshape_ratio = 1.0;
GLuint width = 640, height = 480;

GLMmodel* model = NULL;
GLMmodel* xwing_model = NULL; 
GLMmodel* tie_model = NULL;   
GLMmodel* xwing_laser_model = NULL; 
GLMmodel* tie_interceptor_model = NULL; 
GLMmodel* tie_vader_model = NULL;
GLMmodel*tie_laser_model= NULL;
float deslocamento = 0.2; 
float deslocamento_inimigos = 0.2;
float posx = 0.0, posy = -1.04, posz = 0.0; 
float posxT = 0.0, posyT = -1.04, poszT = 0.0; 
float camx = 0.0, camy = 0.0, camz = 0.0; 
float cam_rotx = 0.0, cam_roty = 0.0; 
float cam_up = 1.0; 
int sorteado;

bool use_perspective = true; 
bool render_solid = true; 
bool is_paused = false;
bool enemies_initialized = false;
bool move_direction_right = true; 


struct Laser {
    float x, y, z;
    bool active;

    Laser(float x, float y , float z) : x(x), y(y), z(z), active(true) {}
};
struct Enemy {
    float x, y, z;
    float size;
    bool active;
    GLMmodel* model;

    Enemy(float x, float y, float z, float size, GLMmodel* model) : x(x), y(y), z(z), size(size), active(true), model(model) {}
};
struct EnemyLaser {
    float x, y, z;
    bool active;

    EnemyLaser(float x, float y, float z) : x(x), y(y), z(z), active(true) {}
};

struct BossLaser {
    float x, y, z;
    bool active;

    BossLaser(float x, float y, float z) : x(x), y(y), z(z), active(true) {}
};

std::vector<EnemyLaser> enemyLasers;
std::vector<Enemy> enemies;
std::vector<Laser> lasers;
std::vector<BossLaser> bossLasers;

int playerhealth = 10;
int bosshealth = 10;

int last_shot_time = 0; 
bool key_a = false;
bool key_d = false;
bool key_space = false;

int wave = 1;
bool waveInProgress = true;
int orda = 0;

Enemy boss(0.0f, 0.0f, 0.0f, 1.0f, NULL);
bool boss_initialized = false;
float deslocamento_boss = 0.4f; 

void init_glut(const char *window_name, int argc, char** argv);
void reshape(int w, int h);
void display(void);
void drawModel(GLMmodel* model, GLuint mode);
void computeFPS();
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void criarVariosInimigos();
void criarXwing();
void criarXwing_laser();
void keyboardUp(unsigned char key, int x, int y);
void updateMovement();
void updateLasers();
GLuint loadBMP(const char* filename);
void renderBackground();
GLuint backgroundTexture;
void playSound(const char* soundFile);
void onPlayerShoot();
void playExplosionSound();
void* playMusicThread(void* arg);
void playMusic();
void drawStrokeText(const char* text, float x, float y, float scale);
void drawText(const char *text, int length, int x, int y);
void textosNaTela();
void waves();
int quantEnemy();
void afterDelay();
void timerCallback(int value);
GLMmodel* sorteiaInimigos();
void drawHealthBar();
void updateEnemyLasers();
void criarInimigoLaser();
void drawEnemyLasers();
void criarBoss();
void criarBossLaser();
void updateBossLasers();
void drawBossLasers();
void drawBossHealthBar();

int main(int argc, char** argv) {
    // Inicia o GLUT e alguns parâmetros do OpenGL
    init_glut("Computacao Grafica: Renderizacao de Modelo 3D Complexo", argc, argv);
    playMusic(); 

    // Função de controle do GLUT
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
    
   
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp); 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(1000/fps_desejado, timer, 0); 


    glClearColor(1.0, 1.0, 1.0, 1.0);
   
    xwing_model = glmReadOBJ("models/xwing.obj");
    if(!xwing_model){
        printf("Erro ao carregar o modelo 3D: xwing.obj\n");
        exit(0);
    }
    glmUnitize(xwing_model);
    glmFacetNormals(xwing_model);
    glmVertexNormals(xwing_model, 90.0);


    tie_model = glmReadOBJ("models/tie.obj");
    if(!tie_model){
        printf("Erro ao carregar o modelo 3D: tie.obj\n");
        exit(0);
    }
    glmUnitize(tie_model);
    glmFacetNormals(tie_model);
    glmVertexNormals(tie_model, 90.0);
    
    tie_interceptor_model = glmReadOBJ("models/tie_interceptor.obj");
    if(!tie_interceptor_model){
        printf("Erro ao carregar o modelo 3D: tie_interceptor.obj\n");
        exit(0);
    }
    glmUnitize(tie_interceptor_model);
    glmFacetNormals(tie_interceptor_model);
    glmVertexNormals(tie_interceptor_model, 90.0);
    
    xwing_laser_model = glmReadOBJ("models/xwing_laser.obj");
    if(!xwing_laser_model){
        printf("Erro ao carregar o modelo 3D: xwing.obj\n");
        exit(0);
    }
    
    tie_vader_model = glmReadOBJ("models/tie_vader.obj");
    if(!tie_vader_model){
        printf("Erro ao carregar o modelo 3D: tie_vader.obj\n");
        exit(0);
    }
    glmUnitize(tie_vader_model);
    glmFacetNormals(tie_vader_model);
    glmVertexNormals(tie_vader_model, 90.0);
    
	tie_laser_model = glmReadOBJ("models/tie_laser.obj");
    if(!tie_laser_model){
        printf("Erro ao carregar o modelo 3D: tie_vader.obj\n");
        exit(0);
    }
    
    backgroundTexture = loadBMP("textures/stars4.bmp");
}

/*
 * Funcao de renderizacao do objeto 3D
 */
void drawModel(GLMmodel* model, GLuint mode){
    if(!model)
        return;
    glmDraw(model, GLM_NONE);
}

void display(void){
    // Limpa a tela (usando a cor de fundo definida anteriormente) e o Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
   
    renderBackground();

    
    gluLookAt(camx, camy+5.0, camz + 15.0, camx + sin(cam_roty * M_PI/180), camy + sin(-5 * M_PI/180), camz - cos(cam_roty * M_PI/180), 0.0, cam_up, 0.0);
	
	waves();

		
	drawHealthBar();
	if(boss_initialized)drawBossHealthBar();
	
   
    glutSwapBuffers();
    
}

/*
 * Funcao de callback para tratar o redimensionamento da janela
 */
void reshape(int w, int h){
    // Evita divisao por zero, caso a janela seja muito pequena
    if (h == 0)
        h = 1;

    // Atualiza as variaveis de largura e altura da janela
    width = w;
    height = h;

   
    reshape_ratio = 1.0 * w / h;

    
    glViewport(0, 0, w, h);

    // Define a projecao perspectiva (ou ortografica)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(use_perspective){
        gluPerspective(45.0, reshape_ratio, 0.1, 100.0);
    } else {
        glOrtho(-5 * reshape_ratio, 5 * reshape_ratio, -5, 5, 0.1, 100.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Funcao para calcular os frames por segundo
 */
void computeFPS(){
    static int frameCount = 0;
    static int previousTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - previousTime;

    if(elapsedTime > 1000){
        fps = frameCount * 1000 / elapsedTime;
        previousTime = currentTime;
        frameCount = 0;
    }

    frameCount++;
}

/*
 * Funcao de callback para o temporizador
 */
void timer(int value){
    if(!is_paused){
        computeFPS();
        updateMovement(); // Atualiza o movimento baseado nas teclas pressionadas
        updateLasers();
        updateEnemyLasers();
        updateBossLasers();
        glutPostRedisplay();
    }

    glutTimerFunc(1000/fps_desejado, timer, 0);
}

/*
 * Funcao de callback para tratar eventos de teclado
 */
void keyboard(unsigned char key, int x, int y) {
	int current_time = glutGet(GLUT_ELAPSED_TIME); // Obter o tempo atual em milissegundos
    switch (key) {
        case ESC:
            exit(0);
            break;
        case 'p': case 'P':
            is_paused = !is_paused;
            break;
        case 'a': case 'A':
            key_a = true;
            break;
        case 'd': case 'D':
            key_d = true;
            break;
        case SPACE:
        	if(!is_paused){
            if (current_time - last_shot_time >= SHOOT_INTERVAL) {
            	onPlayerShoot();
                lasers.push_back(Laser(posx, posy, posz + 3));
                last_shot_time = current_time; // Atualiza o tempo do último disparo
            }}
            break;
    }
}

void criarVariosInimigos() {
	
    if (wave % 2 == 0) {
        for (size_t i = 0; i < enemies.size(); ++i) {
            enemies[i].active = false;
        }
        criarBoss();
        return; // Não desenha os inimigos normais na wave do BOSS
    }

    if (!enemies_initialized) {
        // Desenha várias linhas de naves inimigas (TIE Fighters)
        int num_rows = 6; // Número de linhas de naves inimigas
        int num_columns = 3; // Número de colunas de naves inimigas
        float start_x = posxT - 9.0; // Ponto de início no eixo X
        float start_z = poszT - 10.0; // Ponto de início no eixo Z
        float spacing_x = 4.5f; // Espaçamento entre naves no eixo X
        float spacing_z = 6.0f; // Espaçamento entre naves no eixo Z

        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                float enemy_x = start_x + j * spacing_x;
                float enemy_z = start_z - i * spacing_z;
                model = sorteiaInimigos(); // Sorteia o modelo para cada inimigo
                if (model == NULL) break;
                enemies.push_back(Enemy(enemy_x, posy, enemy_z, 1.0f, model)); // Adiciona inimigo ao vetor com o modelo sorteado
            }
        }
        enemies_initialized = true; // Marca que os inimigos foram inicializados
    }

    // Verifica se algum inimigo atinge as bordas
    bool change_direction = false;
    for (size_t i = 0; i < enemies.size(); ++i) {
        Enemy& enemy = enemies[i];
        if (enemy.active) {
            if (enemy.x >= 12.0 || enemy.x <= -12.0) {
                change_direction = true;
                break;
            }
        }
    }

    // Se algum inimigo atinge as bordas, muda a direção do movimento
    if (change_direction) {
        deslocamento_inimigos = -deslocamento_inimigos;
    }

    // Atualiza a posição de todos os inimigos
    for (size_t i = 0; i < enemies.size(); ++i) {
        Enemy& enemy = enemies[i];
        if (enemy.active) {
            enemy.x += deslocamento_inimigos;
        }
    }

    // Renderiza os inimigos
    for (size_t i = 0; i < enemies.size(); ++i) {
        Enemy& enemy = enemies[i];
        if (enemy.active) {
            glPushMatrix();
            glTranslatef(enemy.x, enemy.y, enemy.z);
            glColor3f(0.0, 0.0, 1.0);
            drawModel(enemy.model, render_solid ? GLM_SMOOTH | GLM_MATERIAL : GLM_NONE); // Usa o modelo armazenado no struct
            glPopMatrix();
        }
    }
}


void criarXwing(){
	// Desenha a nave do jogador
    glPushMatrix(); // Salva a matriz atual
    glTranslatef(posx, posy, posz+5); // Aplica a translacao da nave do jogador
    glColor3f(1.0, 0.0, 0.0); // Define a cor do modelo 3D
    drawModel(xwing_model, render_solid ? GLM_SMOOTH | GLM_MATERIAL : GLM_NONE);
    glPopMatrix();
}

void criarXwing_laser() {
    for (size_t i = 0; i < lasers.size(); ++i) {
        Laser& laser = lasers[i];
        if (laser.active) {
            glPushMatrix();
            glTranslatef(laser.x, laser.y, laser.z);
            glScalef(0.025, 0.025, 0.025);
            glColor3f(1.0, 0.0, 0.0);
            drawModel(xwing_laser_model, render_solid ? GLM_SMOOTH | GLM_MATERIAL : GLM_NONE);
            glPopMatrix();
        }
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': case 'A':
            key_a = false;
            break;
        case 'd': case 'D':
            key_d = false;
            break;
        case SPACE:
            key_space = false;
            break;
    }
}
void updateMovement() {
    if (key_a) {
    	if(posx >= -5)posx -= deslocamento;
    	else posx = posx + 0;
    }
    if (key_d) {
        if(posx <= 5)posx += deslocamento;
    	else posx = posx + 0;
    }
}

void updateLasers() {
    for (size_t i = 0; i < lasers.size(); ++i) {
        Laser& laser = lasers[i];
        if (laser.active) {
            laser.z -= 1.0;

            // Verifica colisão com naves inimigas
            for (size_t j = 0; j < enemies.size(); ++j) {
                Enemy& enemy = enemies[j];
                if (enemy.active && abs(laser.x - enemy.x) < enemy.size && abs(laser.y - enemy.y) < enemy.size && abs(laser.z - enemy.z) < enemy.size) {
                    // Colisão detectada
                    laser.active = false;
                    enemy.active = false;
                    playExplosionSound();
                    break;
                }
            }

            // Verifica colisão com o BOSS
            if (boss_initialized && boss.active && abs(laser.x - boss.x) < boss.size+1 && abs(laser.y - boss.y) < boss.size+1 && abs(laser.z - boss.z) < boss.size+1) {
                // Colisão detectada com o BOSS
                laser.active = false;
                bosshealth--;
                playExplosionSound();
                if (bosshealth <= 0){
                    // Reiniciar estado do jogo para nova rodada
                    boss_initialized = false;
                    enemies_initialized = false;
                    waveInProgress = true;
                    bosshealth = 10; // Resetar a saúde do boss para a próxima rodada
                    wave++;
                    
                }
            }

            // Verifica se o laser saiu da tela
            if (laser.z < -100.0) {
                laser.active = false;
            }
        }
    }
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
void playSound(const char* soundFile) {
#ifdef _WIN32
    std::string command = "open \"" + std::string(soundFile) + "\" type waveaudio alias " + std::string(soundFile);
    mciSendString(command.c_str(), NULL, 0, NULL);
    command = "play " + std::string(soundFile) + " from 0";
    mciSendString(command.c_str(), NULL, 0, NULL);
#else
    CFURLRef soundFileURL = CFURLCreateFromFileSystemRepresentation(
        kCFAllocatorDefault,
        reinterpret_cast<const UInt8 *>(soundFile),
        strlen(soundFile),
        false
    );
    
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID(soundFileURL, &soundID);
    AudioServicesPlaySystemSound(soundID);
    CFRelease(soundFileURL);
#endif
}

void onPlayerShoot() {
    playSound("SFX/laser_sf.wav");
}
void playExplosionSound() {
    playSound("SFX/exp_caza.wav");
}

void* playMusicThread(void* arg) {
#ifdef _WIN32
    while (true) {
        while (is_paused) {
            Sleep(100); // Espera um pouco antes de verificar novamente
        }

        // Inicia a primeira música
        mciSendString("open \"SFX/battle_1.mp3\" type mpegvideo alias battle_1", NULL, 0, NULL);
        mciSendString("play battle_1 from 0 wait", NULL, 0, NULL); // Espera até que a música termine
        mciSendString("close battle_1", NULL, 0, NULL); // Fecha a música para liberar recursos

        while (is_paused) {
            Sleep(100); // Espera um pouco antes de verificar novamente
        }

        // Inicia a segunda música
        mciSendString("open \"SFX/battle_4.mp3\" type mpegvideo alias battle_4", NULL, 0, NULL);
        mciSendString("play battle_4 from 0 wait", NULL, 0, NULL); // Espera até que a música termine
        mciSendString("close battle_4", NULL, 0, NULL); // Fecha a música para liberar recursos
    }
#else
    while (true) {
        while (is_paused) {
            usleep(100000); // Espera um pouco antes de verificar novamente
        }

        system("afplay SFX/battle_1.mp3");
        sleep(278); // Tempo de duração da música em segundos

        while (is_paused) {
            usleep(100000); // Espera um pouco antes de verificar novamente
        }

        system("afplay SFX/battle_4.mp3");
        sleep(103); // Tempo de duração da música em segundos
    }
#endif
    return NULL;
}

void playMusic() {
#ifdef _WIN32
    // Cria um thread para tocar a música no Windows
    DWORD threadId;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)playMusicThread, NULL, 0, &threadId);
#else
    // Cria um thread para tocar a música no macOS
    pthread_t thread;
    pthread_create(&thread, NULL, playMusicThread, NULL);
#endif
}
void drawText(const char *text, int length, int x, int y) {
	glColor3f(1.0f, 1.0f, 1.0f); // Garante que a cor seja branca
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
void textosNaTela(){


	int len = quantEnemy();
	std::ostringstream oss;
    oss << "Enemies: " << len;
    std::string text = oss.str();
    drawText(text.c_str(), text.length(), 10, height - 20); 
    
    std::ostringstream oss2;
    oss2 << "Wave: " << wave;
    std::string text2 = oss2.str();
	drawText(text2.c_str(), text2.length(), 10, height - 40); 
	

    float xBarPlayer = 30; 
    float yBarPlayer = 30;

   
    std::string playerName = "Player";
    int playerTextWidth = playerName.length() * 9; 
    int xPlayerText = xBarPlayer; 
    int yPlayerText = yBarPlayer + 20; 
    drawText(playerName.c_str(), playerName.length(), xPlayerText, yPlayerText);
	
	if(boss_initialized){

    float yBar = 30; 

    
    std::string name = "Darth Vader";
    int textWidth = name.length() * 9;
    int xText = width - 30 - textWidth;
    int yText = yBar + 20; 
    drawText(name.c_str(), name.length(), xText, yText);
	}
}

void waves(){
	int inimigos = quantEnemy();
		
	    criarXwing();
	    criarXwing_laser();
  	    criarVariosInimigos();
  	    criarInimigoLaser();
	    drawEnemyLasers();
	    if(boss_initialized){
   		criarBossLaser();
  		drawBossLasers();
		}
		textosNaTela();
		
	    if (inimigos == 0 && !boss_initialized) {
	        if (!waveInProgress) {
	            waveInProgress = true; 
	            glutTimerFunc(1500, timerCallback, 1);
	        }
	    } else {
	        waveInProgress = false; 
	    }
			
}

int quantEnemy(){
		int len = 1;
		for (size_t j = 0; j < enemies.size(); ++j) {
                Enemy& enemy = enemies[j];
                if (enemy.active) {
					len += 1;
                }
		}
		return len-1;
		
}

void afterDelay() {
    enemies.clear();
    enemies_initialized = false;
    
    criarVariosInimigos();
    wave += 1;
	
}

void timerCallback(int value) {
    if (value == 1) {
        afterDelay();
        
    }
}

GLMmodel* sorteiaInimigos(){
	sorteado = std::rand() % 3;
	switch(sorteado)
	{
	case 0:
		return tie_model;
		break;
	case 1:
		return tie_interceptor_model;
		break;
	case 2:
		return NULL;
		break;
	default:
		break;
	}
}
void drawHealthBar() {
    float healthRatio = (float)playerhealth / 10.0f;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(30, 30);
    glVertex2f(30 + 200 * healthRatio, 30); 
    glVertex2f(30 + 200 * healthRatio, 40); 
    glVertex2f(30, 40); 
	glEnd();
	glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void updateEnemyLasers() {
    int current_time = glutGet(GLUT_ELAPSED_TIME);
	
    if (current_time - last_enemy_shot_time >= ENEMY_SHOOT_INTERVAL) {
       
    	size_t i = rand() % enemies.size();
    	Enemy& enemy = enemies[i];
            if (enemy.active) {
                enemyLasers.push_back(EnemyLaser(enemy.x, enemy.y, enemy.z));
            }
        
        last_enemy_shot_time = current_time;
    }

    for (size_t i = 0; i < enemyLasers.size(); ++i) {
        EnemyLaser& laser = enemyLasers[i];
        if (laser.active) {
            laser.z += 1.0;

           
            if (abs(laser.x - posx) < 1.2 && abs(laser.y - posy) < 1.0 && abs(laser.z - posz-4) < 1.0) {
                laser.active = false;
                playerhealth--;
                playSound("SFX/hit.wav");
                if (playerhealth <= 0) {
                 
                    printf("Game Over!\n");
                    exit(0);
                }
            }

            if (laser.z > 100.0) {
                laser.active = false;
            }
        }
    }
}

void criarInimigoLaser() {
    if (enemies.empty()) {
        return;
    }
    
    size_t i = rand() % enemies.size();
    Enemy& enemy = enemies[i];
    if(enemy.active == false){
		return;
	}

    if (enemy.active && rand() % 100 < 5) { 
        enemyLasers.push_back(EnemyLaser(enemy.x, enemy.y, enemy.z));
    	playSound("SFX/tie_laser.wav");
    }
}

void drawEnemyLasers() {
    for (size_t i = 0; i < enemyLasers.size(); ++i) {
        EnemyLaser& laser = enemyLasers[i];
        if (laser.active) {
            glPushMatrix();
            glTranslatef(laser.x, laser.y, laser.z);
            glScalef(0.025, 0.025, 0.025);
            glColor3f(0.0, 1.0, 0.0); 
            drawModel(tie_laser_model, render_solid ? GLM_SMOOTH | GLM_MATERIAL : GLM_NONE);
            glPopMatrix();
        }
    }
}


void criarBoss() {
    if (!boss_initialized) {

        float boss_x = 0.0f;
        float boss_y = posy;
        float boss_z = poszT - 20.0f;

        boss = Enemy(boss_x, boss_y, boss_z, 1.0f, tie_vader_model);
        boss_initialized = true;
    }

    
    if (boss.active) {
       
        boss.x += deslocamento_boss;
        if (boss.x >= 12.0f || boss.x <= -12.0f) {
            deslocamento_boss = -deslocamento_boss;
        }
        glPushMatrix();
        glTranslatef(boss.x, boss.y, boss.z);
        glScalef(boss.size+1, boss.size+1, boss.size+1);
        glColor3f(0.0, 1.0, 0.0); 
        drawModel(boss.model, render_solid ? GLM_SMOOTH | GLM_MATERIAL : GLM_NONE);
        glPopMatrix();
    }
}

void criarBossLaser() {
    if (boss.active && rand() % 100 < 10) { 
        bossLasers.push_back(BossLaser(boss.x, boss.y, boss.z));
        bossLasers.push_back(BossLaser(boss.x, boss.y, boss.z));
    	playSound("SFX/tie_laser.wav");
    }
}
void updateBossLasers() {
    for (size_t i = 0; i < bossLasers.size(); ++i) {
        BossLaser& laser = bossLasers[i];
        if (laser.active) {
            laser.z += 1.0;

            // Verifica colisão com a nave do jogador
            if (abs(laser.x - posx) < 1.2 && abs(laser.y - posy) < 1.0 && abs(laser.z - posz - 4) < 1.0) {
                laser.active = false;
                playerhealth--;
                playSound("SFX/hit.wav");
                if (playerhealth <= 0) {
                    printf("Game Over!\n");
                    exit(0);
                }
            }

            if (laser.z > 100.0) {
                laser.active = false;
            }
        }
    }
}
void drawBossLasers() {
    for (size_t i = 0; i < bossLasers.size(); ++i) {
        BossLaser& laser = bossLasers[i];
        if (laser.active) {
            glPushMatrix();
            glTranslatef(laser.x, laser.y, laser.z);
            glScalef(0.025, 0.025, 0.025);
            glColor3f(0.0, 1.0, 0.0); 
            drawModel(tie_laser_model, render_solid ? GLM_SMOOTH | GLM_MATERIAL : GLM_NONE);
            glPopMatrix();
        }
    }
}
void drawBossHealthBar() {
    float healthRatio = (float)bosshealth / 10.0f;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
	float barWidth = 200 * healthRatio;
    float x = width - 30 - barWidth; 
    float y = 30; 
	glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); 
    glVertex2f(x, y); 
    glVertex2f(x + barWidth, y); 
    glVertex2f(x + barWidth, y + 10);
    glVertex2f(x, y + 10); 
    glEnd();
	glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}