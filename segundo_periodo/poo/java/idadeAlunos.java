import java.util.Scanner;

public class idadeAlunos {

	public static void main(String[] args) {
		int N; // Qde de alunos
		int idades[];
		String nomes[];
		float soma, idadeMenor, idadeMaior;

		// Definicao do canal para leitura de dados
		Scanner sc = new Scanner(System.in);

		System.out.println("Qual a qde de alunos? ");
		N = sc.nextInt();
		nomes = new String[N];
		idades = new int[N];
				
		System.out.println("Digite nome e idade dos alunos?");
		for (int i=0; i<N; i++) {			
			nomes[i] = sc.next();
			idades[i] = sc.nextInt();
		}
		
		idadeMenor = idades[0];
		idadeMaior = idades[0];
		soma = idades[0];
		
		for (int i=1; i<N; i++) {
			soma += idades[i];
			if (idades[i] < idadeMenor)
				idadeMenor = idades[i];
			if (idades[i] > idadeMaior)
				idadeMaior = idades[i];
		}
		
		System.out.println("Media: "+soma/N);
		System.out.println("Alunos mais novos");
		for(int i=0; i<N; i++) {
			if (idades[i]==idadeMenor)
				System.out.println("Novo: "+nomes[i]);
		}
		sc.close();
	}
}
