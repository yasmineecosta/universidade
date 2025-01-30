import java.util.Scanner;

public class ListaNomes {
	private Node ini=null; // Descritor da lista
			
	private class Node {
		private String nome;
		private Node prox;
	}

	public static void main(String[] args) {
		ListaNomes app = new ListaNomes();
		Scanner sc = new Scanner(System.in);
		int opcao=-1;

		while (opcao != 0) {
			System.out.println("Lista de Nomes\n1.Inserir\n2.Listar\n0.Sair");
			opcao = Integer.parseInt(sc.nextLine());
			switch (opcao) {
			case 1: // Inserir
				System.out.println("Digite nome?");
				String wsNome = sc.nextLine();
				app.Inserir(wsNome);
				break;
			case 2: // Listar
				app.listar();
				break;
			}
		}
		System.out.println("end of program");
	}

	private void Inserir(String wsNome) {
		Node novo = new Node();
		novo.nome = wsNome;
		novo.prox = ini;
		ini = novo;
	}

	private void listar() {
		Node aux = ini;
		System.out.print("Lista: ");
		while (aux!=null) {
			System.out.print(aux.nome+" ->");
			aux = aux.prox;
		}
		System.out.println("\n");
	}
}
