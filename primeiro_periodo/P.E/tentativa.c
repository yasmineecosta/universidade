#include <stdio.h>
#define qtd_produtos 4
#define qtd_armazens 3

typedef struct
{
    float custo;
    int armazem[qtd_armazens];
}
tproduto;

int opcao(void);
void ler_estoque(tproduto produto[]);
void ler_custo(tproduto produto[]);
void exibe_estoque_produto(tproduto produto[]);
void exibe_estoque_armazem(tproduto produto[]);
void exibe_total_armazem (tproduto produto[]);
void exibe_estoque_total_produto(tproduto produto[]);
void exibe_custo_armazem(tproduto produto[]);
void exibe_custo_produto(tproduto produto[]);
void altera_estoque_produto(tproduto produto[]);
void altera_custo_produto(tproduto produto[]);


int main()
{

    tproduto produto[qtd_produtos];
    ler_estoque(produto);
    ler_custo(produto);
    int menu = -1;
    while (menu != 0)
    {
        menu = opcao();
        switch (menu)
        {
            case 0:
                break;
            case 1:
                exibe_estoque_produto(produto);
                break;
            case 2:
                exibe_estoque_armazem(produto);
                break;
            case 3:
                exibe_total_armazem(produto);
                break;
            case 4:
                exibe_estoque_total_produto(produto);
                break;
            case 5:
                exibe_custo_armazem(produto);
                break;
            case 6:
                exibe_custo_produto(produto);
                break;
            case 7:
                altera_estoque_produto(produto);
                break;
            case 8:
                altera_custo_produto(produto);
                break;
            default:
                break;
        }
    }
    return 0;
}
