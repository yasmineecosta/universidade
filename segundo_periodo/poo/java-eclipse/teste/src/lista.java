package relatorio;

import java.util.Scanner;

public class lista 
{
    private Node inicio = null, fim = null; // Descritor do inicio e fim da lista

    private class Node
    {
        String nome;
        Node prox;
    }

    public static void main(String[] args)
    {
        lista app = new lista();
        Scanner scan = new Scanner(System.in);
        int opcao = -1;
        System.out.println("Bem-vindo!");

        while (opcao != 6)
        {
            System.out.println("");
            app.menu();
            opcao = Integer.parseInt(scan.nextLine());
            
            // Caso escolha a opção 6 finalizar o programa
            if (opcao == 6)
            {
                break;
            }

            System.out.println("");
            String wsnome;

            switch(opcao)
            {
                case 1: // Insere no inicio da lista
                    System.out.print("Nome da pessoa: ");
                    wsnome = scan.nextLine();
                    app.insere_inicio(wsnome);
                    break;

                case 2: // Insere no final da lista
                    System.out.print("Nome da pessoa: ");
                    wsnome = scan.nextLine();
                    app.insere_final(wsnome);
                    break;

                case 3: // Exclui determinada pessoa da lista
                    System.out.print("Nome da pessoa a ser removida: ");
                    wsnome = scan.nextLine();
                    app.remove(wsnome);
                    break;

                case 4: // Lista e mostra a quantidade dos nomes
                    app.listar();
                    break;

                case 5: // Mostra a lista de trás para frente
                    app.lista_inversa();
                    break;
            }

            System.out.print("\nPressione enter para continuar...");
            String tecla = scan.nextLine();
        }

        scan.close();

        System.out.println("Fim do programa! :)");
    }

    private void menu()
    {
        System.out.println("MENU");
        System.out.println("1 - Inserir pessoa no inicio da lista");
        System.out.println("2 - Inserir pessoa no final da lista");
        System.out.println("3 - Excluir determinada pessoa da lista");
        System.out.println("4 - Listar todos os nomes e a quantidade de nomes");
        System.out.println("5 - Mostra os nomes da lista do final para o inicio");
        System.out.println("6 - Sair da aplicacao\n");
        System.out.print("Digite uma opcao: ");
    }

    private boolean busca_nome(String wsnome)
    {
        Node aux = inicio;
        
        // Busca o nome pela lista
        while (aux != null)
        {
            // Caso encontre o nome
            if (aux.nome.equals(wsnome))
            {
                System.out.println("O nome " + wsnome + " ja esta na lista!");
                return true;
            }

            aux = aux.prox;
        }

        // Nome não encontrado
        return false;
    }

    private void insere_inicio(String wsnome)
    {
        // Se encontrar o nome então não inserir
        if (busca_nome(wsnome))
        {
            return;
        }

        Node novo = new Node(); 
        novo.nome = wsnome;
        novo.prox = inicio;
        inicio = novo;

        // Fila vazia então fim = inicio
        if (fim == null)
        {
            fim = inicio;
        }
    }

    private void insere_final(String wsnome)
    {
        // Se encontrar o nome então não inserir
        if (busca_nome(wsnome))
        {
            return;
        }

        Node novo = new Node();
        novo.nome = wsnome;
        novo.prox = null;

        if (fim != null)
        {
            fim.prox = novo;
            fim = novo;
        }
        else
        {
            // Se a fila estiver vazia basta adicionar o novo elemento
            fim = novo;
            inicio = novo;
        }
    }

    private void listar()
    {
        Node aux = inicio;
        int qtd_pessoas = 0, i = 1;

        // Passa por todos da lista e mostra a posição e nome
        System.out.println("LISTA");
        while (aux != null)
        {
            System.out.println(i++ + " - " + aux.nome);
            aux = aux.prox;
            qtd_pessoas++; // Cada pessoa que passa acrescenta um;
        }

        System.out.println("\nQuantidade de pessoas na lista: " + qtd_pessoas);
    }

    private void lista_inversa()
    {
        Node aux = inicio;
        int tam = 0, i = 0;

        // Pega a qtd de pessoas na lista
        while (aux != null)
        {
            aux = aux.prox;
            tam++;
        }

        // Cria o array e atribui os nomes na ordem normal da lista
        aux = inicio;
        String nomes[] = new String[tam];

        while (aux != null)
        {
            nomes[i++] = aux.nome;
            aux = aux.prox;
        }

        // Mostra na tela o array do fim ao início
        System.out.println("LISTA INVERSA");
        for (int j = tam - 1; j >= 0; j--)
        {
            System.out.println(((tam - 1) - j + 1) + " - " + nomes[j]);
        }
    }

    private void remove(String wsnome)
    {
        // Lista vazia
        if (inicio == null)
        {
            System.out.println("Lista vazia!");
            return;
        }

        // Caso esteja no primeiro elemento
        if ((inicio.nome).equals(wsnome))
        {
            inicio = inicio.prox;
            System.out.println(wsnome + " deletado!");
            return;
        }

        Node anterior = inicio, atual = inicio.prox;
        
        // Busca o nome pela lista caso não esteja no primeiro elemento
        while (atual != null)
        {
            // Caso encontre o nome
            if (wsnome.equals(atual.nome))
            {
                anterior.prox = atual.prox;

                // Caso seja o último
                if (atual.prox == null)
                {
                    fim = anterior;
                }
                
                System.out.println(wsnome + " deletado!");
                return;
            }
        }

        System.out.println("Nome não encontrado na lista!");
        return;
    }
}