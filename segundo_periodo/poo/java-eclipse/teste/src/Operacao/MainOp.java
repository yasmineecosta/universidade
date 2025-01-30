package Operacao;
import java.util.Scanner;
public class MainOp {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

        System.out.print("Digite o nome do usuário: ");
        String nomeUsuario = sc.nextLine();

        Usuario usuario = new Usuario(nomeUsuario);

        while (true) {
            System.out.println("\n--- Menu ---");
            System.out.println("1. Crédito");
            System.out.println("2. Débito");
            System.out.println("3. Mostrar as operações feitas");

            System.out.print("Escolha uma opção: ");
            int opcao = sc.nextInt();
            sc.nextLine(); // Limpar o buffer do scanner

            if (opcao == 1) {
                System.out.print("Digite o tipo de operação: ");
                String tipoOperacao = sc.nextLine();

                System.out.print("Digite o valor da operação: ");
                double valorOperacao = sc.nextDouble();
                sc.nextLine(); // Limpar o buffer do scanner

                Date dataOperacao = new Date();

                usuario.adicionarOperacao(tipoOperacao, valorOperacao, dataOperacao);
                System.out.println("Operação adicionada com sucesso!");
            } else if (opcao == 2) {
                List<Extrato> operacoes = usuario.getOperacoes();

                if (operacoes.isEmpty()) {
                    System.out.println("Nenhuma operação realizada.");
                } else {
                    System.out.println("--- Operações realizadas ---");
                    for (Extrato operacao : operacoes) {
                        System.out.println("Tipo: " + operacao.getTipoOperacao());
                        System.out.println("Valor: " + operacao.getValor());
                        System.out.println("Data: " + operacao.getData());
                        System.out.println("-----------------------------");
                    }
                }
            } else if (opcao == 3) {
                System.out.println("Programa encerrado.");
                break;
            } else {
                System.out.println("Opção inválida. Tente novamente.");
            }
        }

        scanner.close();
	}

}
