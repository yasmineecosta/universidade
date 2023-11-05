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

int opcao(void)
{
    int menu;
    printf("MENU\n");
    printf("1- Estoque por produto\n");
    printf("2- Estoque por armazém\n");
    printf("3- Total em cada armazém\n");
    printf("4 - Total de cada produto\n");
    printf("5- Custo total por armazém\n");
    printf("6- Custo total por produto\n");
    printf("7- Alterar quantidade de um produto\n");
    printf("8- Alterar custo de um produto\n");
    printf("0- Sair\n");

    printf("Digite uma das opções: ");
    while (1)
    {
        scanf("%d", &menu);
        if ((menu < 0) || (menu > 8))
            printf("Opção inválida, digite novamente: ");
        else
            break;
    }
    return menu;
}

void ler_estoque(tproduto produto[])
{
    int i, j;
    printf("DIGITE O ESTOQUE:\n");
    for (i = 0; i < qtd_armazens; i++)
    {
        printf("Armazém %d:\n", i + 1);
        for (j = 0; j < qtd_produtos; j++)
        {
            printf("Produto %d: ", j + 1);
            scanf("%d", &produto[j].armazem[i]);
        }
    }
}

void ler_custo(tproduto produto[])
{
    int i;
    for (i = 0; i < qtd_produtos; i++)
    {
        printf("Valor do produto %d:R$ ", i + 1);
        scanf("%f", &produto[i].custo);
    }
}

void exibe_estoque_produto(tproduto produto[])
{
    int i, j;
    printf("\nESTOQUE POR PRODUTO\n");
    for (i = 0; i < qtd_produtos; i++)
    {
        printf("Produto %d:\n", i + 1);
        for (j = 0; j < qtd_armazens; j++)
        {
        printf("- Armazém %d: %d\n", j + 1, produto[i].armazem[j]);
        }
    }
}

void exibe_estoque_armazem(tproduto produto[])
{
    int i, j;
    printf("Opção 2 do menu:\n");
    printf("Estoque por armazém:\n");
    for (i = 0; i < qtd_armazens; i++)
    {
        printf("Armazém %d:\n", i + 1);
        for (j = 0; j < qtd_produtos; j++)
        {
        printf("- Produto %d: %d\n", j + 1,                    produto[j].armazem[i]);
        }
    }
}

void exibe_total_armazem(tproduto produto[])
{
    int i, j;
    printf("Total de produtos no armazém:\n");
    for (i = 0; i < qtd_armazens; i++)
    {
        int total = 0;
        for (j = 0; j < qtd_produtos; j++)
            total += produto[j].armazem[i];
        printf("Armazém %d: %d\n", i + 1, total);
    }
}

void exibe_estoque_total_produto(tproduto produto[])
{
    int i, j;
    printf("Total de cada produto:\n");
    for (i = 0; i < qtd_produtos; i++)
    {
        int total = 0;
        for (j = 0; j < qtd_armazens; j++)
        total += produto[i].armazem[j];
        printf("Produto %d: %d\n", i + 1, total);
    }
}

void exibe_custo_armazem(tproduto produto[])
{
    int i, j;
    printf("Custo total por armazém:\n");
    for (i = 0; i < qtd_armazens; i++)
    {
        float total = 0;
        for (j = 0; j < qtd_produtos; j++)
            total += produto[j].armazem[i] * produto[j].custo;
        printf("Armazém %d: R$ %.2f\n", i + 1, total);
    }
}

void exibe_custo_produto(tproduto produto[])
{
    int i, j;
    printf("Custo total por produto:\n");
    for (i = 0; i < qtd_produtos; i++)
    {
        float total = 0;
        for (j = 0; j < qtd_armazens; j++)
            total += produto[i].armazem[j] * produto[i].custo;
        printf("Produto %d: R$ %.2f\n", i + 1, total);
    }
}

void altera_estoque_produto(tproduto produto[])
{
    int id_prod, id_armz;
    do
    {
        printf("Número do produto: ");
        scanf("%d", &id_prod);
    }
    while ((id_prod < 1) || (id_prod > 4));

    do
    {
        printf("Número do armazém: ");
        scanf("%d", &id_armz);
    }
    while ((id_armz < 1) || (id_armz > 3));

    // informar quantidade atual do produto
    printf("Quantidade atual do produto: %d\n",
produto[id_prod - 1].armazem[id_armz - 1]);

    printf("Deseja alterar a quantidade do produto?");
    char resp[4];
    scanf("%s", resp);

    if (resp[0] == 's' || resp[0] == 'S')
    {
        int novo_valor;
        do
        {
            printf("Novo valor: ");
            scanf("%d", &novo_valor);
        }
        while (novo_valor < 0);

        produto[id_prod - 1].armazem[id_armz - 1] = novo_valor;
    }
}

void altera_custo_produto(tproduto produto[])
{
    int id_prod;
    do
    {
        printf("Número do produto: ");
        scanf("%d", &id_prod);
    }
    while ((id_prod < 1) || (id_prod > 4));

    printf("Valor atual do produto: %.2f\n", produto[id_prod - 1].custo);

    printf("Deseja alterar o custo do produto?");
    char resp[4];
    scanf("%s", resp);

    if (resp[0] == 's' || resp[0] == 'S')
    {
        float novo_valor;
        do
        {
            printf("Novo valor: ");
            scanf("%f", &novo_valor);
        }
        while (novo_valor < 0);

    produto[id_prod - 1].custo = novo_valor;
    }
}
