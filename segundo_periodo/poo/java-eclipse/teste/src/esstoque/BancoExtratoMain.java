package esstoque;
//criar extrato estruturado
import java.util.Scanner;

import teste.ContaComum;

public class BancoExtratoMain {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int quant, i, ident, resp;
		double value;
		Extrato e = new Extrato();
		String nome;
		
        // Lendo informacoes...
		System.out.println("CPF e nome: ");
		ident = sc.nextInt();
		nome = sc.next();
		//quantidade de operacoes
		System.out.println("Quantas operacoes voce quer realizar? \n");
		quant = sc.nextInt();
		String[] transacoes = new String[quant];
		
		for(i = 0; i<quant; i++) {
			System.out.println("Operação de crédito ou débito?[1-crédito][2-débito]: ");
			resp = sc.nextInt();
        	if(resp == 1) {
        		value = sc.nextDouble();
        		e.credito(value);
        		transacoes[i] = Account(value);
        	}
        	if(resp == 2) {
        		value = sc.nextDouble();
        		e.debito(value);
        		transacoes[i] = Account(value);
        	}
		}
		
		System.out.println(e.saldo);
	}

	private static String Account(double value) {
		// TODO Auto-generated method stub
		return null;
	}
	

}
//Hoje em nossa aula criamos um extrato que basicamente é uma string 
//com uma linha para cada operação realizada em uma conta comum.
//Nesta tarefa vc tem o objetivo de criar uma classe extrato que 
//possui a operação (credito ou debito), o valor, e o saldo final 
//após a operação realizada. A classe conta deve conter um vetor 
//de operações realizadas e não uma String extrato. Mas o 
//método getExtrato deve continuar da mesma forma: gerando uma string. 
//Apenas internamente a obtenção do extrato será feito de forma diferente. 

