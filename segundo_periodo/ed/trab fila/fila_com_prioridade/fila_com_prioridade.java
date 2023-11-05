import java.util.Scanner;

public class fila_com_prioridade<Item>
{
    Scanner scan = new Scanner(System.in);  // scan

    private int tam_fila_normal;            // tamanho da fila normal
    private int tam_fila_prioridade;        // tamanho da fila com prioridade

    private int pessoas_totais = 0;         // pessoas atendidas no total do dia
    private int pessoas_normal = 0;         // pessoas antedidas na normal
    private int pessoas_prioridade = 0;     // pessoas atendidas na prioridade


    private Node<Item> inicio_normal;       // inicializador da fila normal
    private Node<Item> final_normal;        // final da fila normal
    
    private Node<Item> inicio_prioridade;   // inicializador da fila com prioridade
    private Node<Item> final_prioridade;    // final da fila com prioridade

    private static class Node<Item> 
    {
        private Item pessoa;
        private int idade;
        private Node<Item> prox;
    }


    // Construtor das duas filas
    public fila_com_prioridade()
    {
        inicio_normal = final_normal = inicio_prioridade = final_prioridade = null;
        tam_fila_normal = tam_fila_prioridade = 0;
    }

    // Se a fila com prioridade ta vazia
    public boolean pq_is_empty() 
    {
        return (tam_fila_prioridade) == 0;
    }

    // Se a fila normal ta vazia
    public boolean queue_is_empty() 
    {
        return (tam_fila_normal) == 0;
    }

    // Enfileirar na Fila normal
    public void push_back(Item item) {
        Node<Item> antigo_final = final_normal;
        final_normal = new Node<Item>();
        final_normal.pessoa = item;
        final_normal.prox = null;

        if (queue_is_empty())
        { 
            inicio_normal = final_normal;
        }
        else 
        {
            antigo_final.prox = final_normal;
        }

        tam_fila_normal++;
    }

    // Enfileirar na Fila com Prioridade
    public void push(Item item) 
    {
        Node<Item> novo = new Node<Item>();
        System.out.print("Digite a idade da pessoa: ");
        novo.idade = Integer.parseInt(scan.nextLine());
        novo.pessoa = item;

        if (pq_is_empty())
        {
            novo.prox = null; 
            inicio_prioridade = final_prioridade = novo;
        }
        else
        {
            Node<Item> ant, atual = inicio_prioridade;

            // Se tiver em primeiro
            if (novo.idade > atual.idade)
            {
                inicio_prioridade = novo;
                novo.prox = atual;
            }
            else
            {
                ant = atual;
                atual = atual.prox;

                while(atual != null)
                {
                    // Encontrou um mais novo
                    if (novo.idade > atual.idade)
                    {
                        break;
                    }
                    
                    ant = atual;
                    atual = atual.prox;
                }

                // Se for colocada em ultima
                if (atual == null)
                {
                    final_prioridade.prox = novo;
                    novo.prox = null;
                    final_prioridade = novo;
                }
                else
                {
                    ant.prox = novo;
                    novo.prox = atual;
                }
            }
        }
        tam_fila_prioridade++;
    }

    // Desenfileirar da fila normal
    public Item pop_back() 
    {
        Item pessoa = inicio_normal.pessoa;
        inicio_normal = inicio_normal.prox;
        tam_fila_normal--;

        if (queue_is_empty())
        {
            final_normal = null;
        }

        pessoas_normal++;
        pessoas_totais++;
        return pessoa;
    }

    // Desenfileirar da fila com prioridade
    public Item pop() 
    {
        Item pessoa = inicio_prioridade.pessoa;
        inicio_prioridade = inicio_prioridade.prox;
        tam_fila_prioridade--;

        if (pq_is_empty())
        {
            final_prioridade = null;
        }

        pessoas_totais++;
        pessoas_prioridade++;
        return pessoa;
    }

    // Listar pessoas
    public void Listar()
    {
        System.out.println();
        // Verificar se a fila com prioridade nao ta vazia antes de listar
        if (!pq_is_empty())
        {
            System.out.println("FILA COM PRIORIDADE");
            Node<Item> aux = inicio_prioridade;
            int cont = 1;

            while(aux != null)
            {
                System.out.println(cont + " - " + aux.pessoa);
                aux = aux.prox;
                cont++;
            }
        }
        else
        {
            System.out.println("Ninguém na fila com prioridade");
        }

        System.out.println();


        // Verificar se a fila normal nao ta vazia antes de listar
        if (!queue_is_empty())
        {
            System.out.println("FILA NORMAL");
            Node<Item> aux = inicio_normal;
            int cont = 1;

            while(aux != null)
            {
                System.out.println(cont + " - " + aux.pessoa);
                aux = aux.prox;
                cont++;
            }
        }
        else
        {
            System.out.println("Ninguém na fila normal");
        }

        System.out.println();
    }

    public void gerar_estatistica()
    {
        System.out.println("\nESTATISTICAS");
        System.out.println("Atendidas na fila com prioridade: " + pessoas_prioridade * 1.0 / pessoas_totais * 100 + "%");
        System.out.println("Atendidas na fila normal: " + pessoas_normal * 1.0 / pessoas_totais * 100 + "%\n");
        System.out.println("TAMANHO DAS FILAS ATUALMENTE");
        System.out.println("Fila com prioridade: " + tam_fila_prioridade + " pessoa(s)");
        System.out.println("Fila normal: " + tam_fila_normal + " pessoa(s)\n");
    }

    // MENU
    public void menu()
    {
        System.out.println("MENU");
        System.out.println("1 - Chegada de pessoa para atendimento normal");
        System.out.println("2 - Chegada de pessoa para atendimento prioritario");
        System.out.println("3 - Atendimento de uma pessoa");
        System.out.println("4 - Listar todas as pessoas da fila");
        System.out.println("5 - Gerar estatisticas parciais sobre o atendimento em um determinado periodo de execucao da aplicacao e mostrar o tamanho da fila");
        System.out.println("6 - Encerrar o programa");
    }

    public static void main(String[] args)
    {
        fila_com_prioridade<String> fila = new fila_com_prioridade<String>();

        System.out.println("Bem-vindo ao programa!\n");
        
        while (true)
        {
            fila.menu();
            System.out.print("\nDigite uma opcao: ");
            int opcao = Integer.parseInt(fila.scan.nextLine());

            if (opcao == 1) // nova pessoa na fila normal
            {
                System.out.print("Nome da pessoa a ser inserida: ");
                String nome = fila.scan.nextLine();
                fila.push_back(nome);
            }
            else if (opcao == 2) // nova pessoa na fila com prioridade
            {
                System.out.print("Nome da pessoa a ser inserida: ");
                String nome = fila.scan.nextLine();
                fila.push(nome);
            }
            else if (opcao == 3) // Atendimento de uma pessoa
            {
                // Verificar se a fila com prioridade ta vazia
                String pessoa;
                if (!fila.pq_is_empty())
                {
                    pessoa = fila.pop();
                    System.out.println(pessoa + " foi atendido(a) na fila com prioridade\n");
                }
                else // Tirando uma pessoa da fila normal caso a fila com prioridade esteja vazia
                {
                    // Verificando se a fila normal nao ta vazia
                    if (fila.queue_is_empty())
                    {
                        System.out.println("Fila com prioridade e normal estão vazias\n");
                    }
                    else
                    {
                        pessoa = fila.pop_back();
                        System.out.println(pessoa + " foi atendido(a) na fila normal\n");
                    }
                }
            }
            else if (opcao == 4) // listar pessoas nas duas filas
            {
                fila.Listar();
            }
            else if (opcao == 5) // gerar estatísticas 
            {
                if (fila.pessoas_totais != 0)
                {
                    fila.gerar_estatistica();
                }
                else
                {
                    System.out.println("\nNinguem foi atendido ainda\n");
                }
            }
            else if (opcao == 6) // encerra o programa
            {
                // Se a fila nao tiver vazia nao permitir encerrar o programa
                if (fila.queue_is_empty() && fila.pq_is_empty())
                {
                    System.out.println("\nQuantidade de pessoas atendida na fila com prioridade ao final da execucao : " + fila.pessoas_prioridade);
                    System.out.println("Quantidade de pessoas atendida na fila normal ao final da execucao : " + fila.pessoas_normal + "\n");

                    System.out.println("ESTATISTICAS FINAIS");
                    if (fila.pessoas_totais == 0)
                    {
                        System.out.println("Fila com prioridade: 0.0%");
                        System.out.println("Fila normal: 0.0%\n");
                    }
                    else
                    {
                        System.out.println("Fila com prioridade: " + fila.pessoas_prioridade * 1.0 / fila.pessoas_totais * 100 + "%");
                        System.out.println("Fila normal: " + fila.pessoas_normal * 1.0 / fila.pessoas_totais * 100 + "%\n");
                    }

                    System.out.println("Fim do programa");
                    break;
                }
                else
                {
                    if (!fila.queue_is_empty())
                    {
                        System.out.println("Fila normal ainda com " + fila.tam_fila_normal + " pessoa(s)");
                    }

                    if (!fila.pq_is_empty())
                    {
                        System.out.println("Fila com prioridade ainda com " + fila.tam_fila_prioridade + " pessoa(s)");
                    }
                }
            }
            else
            {
                System.out.println("Opcao invalida");
            }
        }
        fila.scan.close();
    }
}