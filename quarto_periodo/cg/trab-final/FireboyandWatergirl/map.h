#include <cstdio>
#include "montagem.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

// Defina as constantes para o tamanho do mapa
#define TAM_X 19
#define TAM_Y 21

// 4 verde
// 3 agua
// 2 chao/parede
// 1 lava
// 0 nada

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
		}
	}
}

// 4 verde
// 3 agua
// 2 chao/parede
// 1 lava
// 0 fundo