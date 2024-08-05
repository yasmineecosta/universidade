#include <cstdio>
#include "brick.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

// Defina as constantes para o tamanho do mapa
#define TAM_X 19
#define TAM_Y 18

float tam_tank = 0.8;

/*
 * Claro: 0
 * Escuro: 1
 * Borda: 2
*/

// 4 verde
// 3 agua
// 2 chao/parede
// 1 lava
// 0 nada

int mapa[TAM_X][TAM_Y] =
{
	/*
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 2, 2, 2, 4, 4, 4, 2, 2, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
	{2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2},
	*/
	{2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 2, 2, 2, 4, 4, 4, 2, 2, 0, 0, 0, 2},
	{2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2},
	{2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2},
	{2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 6, 2, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
		
};

/*
void desenhaTank(float i, float j, int direcao, int R, int G, int B)
{
	//Corpo do tank.
	glPushMatrix();	
	glColor3f(R, G, B);
	glTranslatef (j * 1, i * 1, 0.5);
	glScalef (tam_tank, tam_tank, tam_tank);
	draw_object_smooth();
	glRotatef(direcao, 0.0 , 0.0 , 1.0);

	
	//Esteira direita.
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(0.55, 0, 0);
	glScalef (0.3, 1.3, 0.6);
	draw_object_smooth();
	glPopMatrix();
	
	//Esteira esquerda.
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-0.55, 0, 0);
	glScalef (0.3, 1.3, 0.6);
	draw_object_smooth();
	glPopMatrix();
	

	//Cano do tank.
	glPushMatrix();
	glTranslatef(0, 0.5, 0.3);
	glScalef (0.3, 1.2, 0.3);
	draw_object_smooth();
	glPopMatrix();
	glPopMatrix();
}
*/
void criaMapa()
{
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0;
	for (int i = 0; i < TAM_X; i++)
	{
		for (int j = 0; j < TAM_Y; j++)
		{
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
				portalV(i, j, x, y, h, w);
			}
			else if (mapa[i][j] == 6)
			{
				portalA(i, j, x, y, h, w);
			}
		}
	}
}


// 4 verde
// 3 agua
// 2 chao/parede
// 1 lava
// 0 fundo