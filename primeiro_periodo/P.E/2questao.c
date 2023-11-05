#include <stdio.h>

typedef struct
{
	int num;
	int den;
}tFracao;

tFracao somar(tFracao fra1, tFracao fra2)
{
    int denominador, numerador;
    tFracao fra3;
	if(fra1.den%fra2.den == 0 || fra2.den%fra1.den == 0)
	{
		if(fra1.den > fra2.den)
		{
			denominador = fra1.den;
		}else
		{
			denominador = fra2.den;
		}
		numerador = (denominador/fra1.den)*fra1.num + (denominador/fra2.den)*fra2.num;
		fra3.num = numerador;
		fra3.den = denominador;
		return fra3;
	}else
	{
		denominador = fra1.den*fra2.den;
		numerador = (denominador/fra1.den)*fra1.num + (denominador/fra2.den)*fra2.num;
		fra3.num = numerador;
		fra3.den = denominador;
		return fra3;		
	}
	
}

tFracao subtrair(tFracao fra1, tFracao fra2)
{
    int denominador, numerador;
    tFracao fra3;
	if(fra1.den%fra2.den == 0 || fra2.den%fra1.den == 0)
	{
		if(fra1.den > fra2.den)
		{
			denominador = fra1.den;
		}else
		{
			denominador = fra2.den;
		}
		numerador = (denominador/fra1.den)*fra1.num - (denominador/fra2.den)*fra2.num;
		fra3.num = numerador;
		fra3.den = denominador;
		return fra3;
	}else
	{
		denominador = fra1.den*fra2.den;
		numerador = (denominador/fra1.den)*fra1.num - (denominador/fra2.den)*fra2.num;
		fra3.num = numerador;
		fra3.den = denominador;
		return fra3;		
	}
		
}

tFracao multiplicar(tFracao fra1, tFracao fra2)
{
	tFracao fra3;
	fra3.num = fra1.num*fra2.num;
	fra3.den = fra1.den*fra2.den;
	return fra3;
}

tFracao dividir(tFracao fra1, tFracao fra2)
{
	tFracao fra3;
	fra3.num = fra1.num*fra2.den;
	fra3.den = fra1.den*fra2.num;
	return fra3;	
}

tFracao simplificar(tFracao fra3)
{
	int i, menor, maior, mdc;
	int numerador, denominador;
	if(fra3.num < fra3.den)
	{
		menor = fra3.num;
		maior = fra3.den;
	}else
	{
		menor = fra3.den;
		maior = fra3.num;
	}
	for( i = 1 ; i <= menor ; i++ )
	{
		if(menor%i == 0 && maior%i == 0)
		{
			mdc = i;
		}
	}
	numerador = fra3.num/mdc;
	denominador = fra3.den/mdc;
	fra3.num = numerador;
	fra3.den = denominador;
	return fra3;
}

int main()
{
	tFracao fra1, fra2, fra3;
	char op;
	printf("Digite o numerador e o denominador da fracao 1:");
	scanf("%d %d", &fra1.num, &fra1.den);
	printf("Digite o numerador e o denominador da fracao 2:");
	scanf("%d %d", &fra2.num, &fra2.den);
	printf("Escolha a operacao '+', '-', '/', 'x':");
	scanf(" %c", &op);
	if(op == '+')
	{
		fra3 = somar(fra1, fra2);
	}
	if(op == '-')
	{
		fra3 = subtrair(fra1, fra2);
	}
	if(op == 'x')
	{
		fra3 = multiplicar(fra1, fra2);
	}
	if(op == '/')
	{
		fra3 =dividir(fra1, fra2);
	}
	fra3 = simplificar(fra3);
	printf("%d/%d\n", fra3.num, fra3.den);

	return 0;
}