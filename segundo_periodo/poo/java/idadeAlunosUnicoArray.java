import java.util.Scanner;

public class idadeAlunosUnicoArray {
	private Node alunos[];
	
	private class Node {
		private String nome;
		private int idade;

		public Node(String nome, int idade) {
			this.nome = nome;
			this.idade = idade;
		}
	}

	public static void main(String[] args) {
		int N; // Qde de alunos
		float soma, idadeMenor, idadeMaior;
		String wsNome;
		int wsIdade;

		idadeAlunosUnicoArray app = new idadeAlunosUnicoArray();
		
		// Definicao do canal para leitura de dados
		Scanner sc = new Scanner(System.in);

		System.out.println("Qual a qde de alunos? ");
		N = sc.nextInt();
		app.alunos = new Node[N];
				
		System.out.println("Digite nome e idade dos alunos?");
		for (int i=0; i<N; i++) {		
			wsNome = sc.next();
			wsIdade = sc.nextInt();
			app.alunos[i] = app.new Node(wsNome, wsIdade);
		}
		
		idadeMenor = app.alunos[0].idade;
		idadeMaior = app.alunos[0].idade;
		soma = app.alunos[0].idade;
		
		for (int i=1; i<N; i++) {
			soma += app.alunos[i].idade;
			if (app.alunos[i].idade < idadeMenor)
				idadeMenor = app.alunos[i].idade;
			if (app.alunos[i].idade > idadeMaior)
				idadeMaior = app.alunos[i].idade;
		}
		
		System.out.println("Media: "+soma/N);
		System.out.println("Alunos mais novos");
		for(int i=0; i<N; i++) {
			if (app.alunos[i].idade==idadeMenor)
				System.out.println("Novo: "+app.alunos[i].nome);
		}
		sc.close();
	}
}
