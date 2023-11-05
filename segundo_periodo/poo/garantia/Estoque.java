package matheusKaikyBritoSilva.estoqueComProdutoPerecivel;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Estoque implements InterfaceEstoque{
    private Node inicio = null;
    private static class Node {
        private Produto prod;
        private Node next;
    }

    public String printDadosProduto(Produto dados) {
        return ("\nCódigo: " + dados.cod + " | Produto: " + dados.desc + " | Estoque mínimo: " +
                dados.min + " | Porcentagem de lucro: " + dados.lucro*100 + "%\nFornecedor: " + dados.forn.nome +
                " | CNPJ: " + dados.forn.cnpj);
    }

    private String formataDataValidade(Date val) {
            SimpleDateFormat formatar = new SimpleDateFormat("dd/MM/yyyy");
            return formatar.format(val);
    }

    private int quantVencido(Produto temp) {
        Node aux = new Node();
        aux.prod = temp;
        int quant = ((ProdutoPerecivel) aux.prod).quantidadeVencidoPorProduto();
        if (quant != 0) {
            System.out.println(resumoProduto(aux) + "\nQuantidade de produtos vencidos: " + quant);
        }
        return quant;
    }

    public String resumoProduto(Node resumo) {
        return ("\nProduto: " + resumo.prod.desc + " | Código: " + resumo.prod.cod);
    }

    private Node buscaProduto(int cod) {
        Node aux = inicio;
        while (aux != null) {
            if (aux.prod.cod == cod) {
                return aux;
            }
            aux = aux.next;
        }
        return null;
    }

    private boolean validaCompra(Node temp, int quant, double preco, Date val) {
        Date hoje = new Date();
        if (temp.prod instanceof ProdutoPerecivel && val == null) {
            System.out.println("\nNão foi possível comprar o(s) produto(s)!\nProdutos " +
                    "perecíveis devem possuir data de validade válida.");
            return false;
        }
        if (quant < 1 || preco < 0 || (!(temp.prod instanceof ProdutoPerecivel) && val != null) ||
                ((temp.prod instanceof ProdutoPerecivel) && val.compareTo(hoje) < 0)) {
            System.out.println("\nNão foi possível comprar o(s) produto(s)!");
            if (quant < 1) {
                System.out.println("Não é possível comprar produtos com quantidades menores que 1.");
            }
            if (preco < 0) {
                System.out.println("Não é possível comprar produtos com preços negativos.");
            }
            if (!(temp.prod instanceof ProdutoPerecivel) && val != null) {
                System.out.println("Produtos não perecíveis não podem possuir data de validade.");
            }
            if ((temp.prod instanceof ProdutoPerecivel) && val.compareTo(hoje) < 0) {
                System.out.println("Não é possível comprar produtos vencidos.");
            }
            return false;
        }
        return true;
    }

    private boolean validaVenda(Node temp, int quant) {
        if (quant < 1 || (temp.prod.quantTotal - quant) < 0) {
            System.out.println("\nNão foi possível vender o(s) produto(s)!");
            if (quant < 1) {
                System.out.println("Não é possível vender quantidades menores que 1.");
            }
            if ((temp.prod.quantTotal - quant) < 0) {
                System.out.println("Não há estoque suficiente para vender essa quantidade.");
            }
            return false;
        }
        return true;
    }

    private boolean validaInclusao(Produto p) {
        String descTeste = p.desc.trim();
        if (p.cod < 1 || (p.desc == null || descTeste.length() == 0) || p.min < 0 || p.lucro < 0 ||
                p.forn.cnpj < 1 || (p.forn.nome == null || p.forn.nome.equals(""))) {
            System.out.println("Não foi possível incluir o produto!");
            if (p.cod < 1) {
                System.out.println("\nO código não pode ser igual a 0 ou negativo");
            }
            if (p.desc == null || descTeste.length() == 0) {
                System.out.println("A descrição não pode ser vazia.");
            }
            if (p.min < 0) {
                System.out.println("O estoque mínimo não poder ser menor que 0.");
            }
            if (p.lucro < 0) {
                System.out.println("O lucro não pode ser negativo.");
            }
            if (p.forn.nome == null || p.forn.nome.equals("")) {
                System.out.println("O nome do fornecedor não pode estar vázio.");
            }
            if (p.forn.cnpj < 1) {
                System.out.println("O CNPJ não pode ser menor igual a 0 ou negativo.");
            }
            return false;
        }
        return true;
    }

    private void insereNaLista(Produto inputProd) {
        Node newProd = new Node();
        newProd.prod = inputProd;
        newProd.next = null;
        if (inicio == null) {
            inicio = newProd;
        }
        else {
            Node aux = inicio;
            while (aux.next != null) {
                aux = aux.next;
            }
            aux.next = newProd;
        }
    }

    public boolean incluir(Produto p){
        if (p == null) {
            System.out.println("\nNão é possível incluir produtos null");
            return false;
        }
        Node temp = buscaProduto(p.cod);
        if (!validaInclusao(p)) {
            return false;
        }
        if (temp != null) {
            System.out.println("\nNão é possível inlcuir o produto!\nO código informado já está cadastrado.");
            return false;
        }
        insereNaLista(p);
        System.out.println(printDadosProduto(p) + "\nProduto adicionado");
        return true;
    }

    public boolean comprar(int cod, int quant, double preco, Date val) {
        if (cod < 1) {
            System.out.println("Código inválido!\nO código não pode ser igual a 0 ou negativo.");
            return false;
        }
        Node temp = buscaProduto(cod);
        if (temp == null) {
            System.out.println("Não foi possível comprar o(s) produto(s)!" +
                    "\nNão foi encontrado nenhum produto com o código informado");
            return false;
        }
        if (!validaCompra(temp, quant, preco, val)) {
            return false;
        }
        if (!(temp.prod instanceof ProdutoPerecivel)) {
            temp.prod.compra(quant, preco);
        } else {
            ((ProdutoPerecivel) temp.prod).compraPerecivel(quant, preco, val);
        }
        String valid;
        if (temp.prod instanceof ProdutoPerecivel) {
            valid = formataDataValidade(val);
        } else {
            valid = "Produto não perecível";
        }
        System.out.println(resumoProduto(temp) + " | Vencimento: " + valid + "\nComprada(s) " + quant +
                " unidade(s) a R$" + preco + "/cada, totalizando = R$" + quant * preco);
        return true;
    }

    public double vender(int cod, int quant) {
        if (cod < 1) {
            System.out.println("Código inválido!\nO código não pode ser igual a 0 ou negativo.");
            return -1;
        }
        double valorVenda;
        Node temp = buscaProduto(cod);
        if (temp == null) {
            System.out.println("Não foi possível vender o(s) produto(s)!" +
                    "\nNão foi encontrado nenhum produto com o código informado");
            return -1;
        }
        if (!validaVenda(temp, quant)) {
            return -1;
        }
        if (temp.prod instanceof ProdutoPerecivel) {
            valorVenda = ((ProdutoPerecivel) temp.prod).vendaPerecivel(quant);
        } else {
            valorVenda = temp.prod.venda(quant);
        }
        if (valorVenda != -1) {
            System.out.println(resumoProduto(temp) + "\nVendida(s) " + quant + " unidade(s) a R$" +
                    temp.prod.precoFinal + "/cada, totalizando = R$" + valorVenda);
        } else {
            System.out.println("\nNão foi possível vender!\nNão há produtos válidos no estoque.");
        }
        return valorVenda;
    }

    public Produto pesquisar(int cod) {
        Node aux = buscaProduto(cod);
        if (aux == null) {
            System.out.println("\nProduto não encontrado!");
            return null;
        } else {
            System.out.println("\nProduto encontrado!\n" + printDadosProduto(aux.prod));
            return aux.prod;
        }
    }

    public int quantidade(int cod) {
        Node temp = buscaProduto(cod);
        if (temp != null) {
            System.out.println(resumoProduto(temp) + "\nHá " + temp.prod.quantTotal + " unidade(s) no estoque.");
            return temp.prod.quantTotal;
        }
        else {
            System.out.println("\nCódigo não encontrado!");
        }
        return -1;
    }

    public Fornecedor fornecedor(int cod) {
        Node temp = buscaProduto(cod);
        if (temp != null) {
            System.out.println(resumoProduto(temp) + "\nFornecedor: " + temp.prod.forn.nome +
                    " | CNPJ: " + temp.prod.forn.cnpj);
            return temp.prod.forn;
        }
        else {
            System.out.println("\nCódigo não encontrado!");
        }
        return null;
    }

    public ArrayList<Produto> estoqueAbaixoDoMinimo() {
        ArrayList<Produto> abaixo = new ArrayList<>();
        Node aux = inicio;
        while (aux != null) {
            Produto temp = aux.prod;
            if (temp.quantTotal < temp.min){
                abaixo.add(temp);
            }
            aux = aux.next;
        }
        if (abaixo.size() == 0) {
            System.out.println("\nNão há produtos com estoque abaixo do mínimo.");
            return null;
        }
        System.out.println("\nProdutos com estoque abaixo do mínimo:");
        for (int i = 0; i < abaixo.size() ; i++) {
            Node dados = new Node();
            dados.prod = abaixo.get(i);
            System.out.println(resumoProduto(dados) + "\nEstoque mínimo: " + abaixo.get(i).min +
                    " | Estoque atual: " + abaixo.get(i).quantTotal);
        }
        return abaixo;
    }

    public ArrayList<Produto> estoqueVencido() {
        ArrayList<Produto> listaVenc = new ArrayList<>();
        Node aux = inicio;
        while (aux != null) {
            if (aux.prod instanceof ProdutoPerecivel) {
                if (((ProdutoPerecivel) aux.prod).temProdutoVencido()) {
                    listaVenc.add(aux.prod);
                }
            }
            aux = aux.next;
        }
        if (listaVenc.size() == 0) {
            System.out.println("\nNão há produtos vencidos no estoque.");
        } else {
            System.out.println("\nLista de produto(s) com lote(s) vencido(s):");
            for (int i = 0; i < listaVenc.size() ; i++) {
                quantVencido(listaVenc.get(i));
            }
        }
        return listaVenc;
    }

    public int quantidadeVencidos(int cod) throws ProdutoInexistente {
        Node aux = buscaProduto(cod);
        if (aux == null) {
            throw new ProdutoInexistente();
        }
        if (quantVencido(aux.prod) == 0) {
            System.out.println("\nNão há produtos vencidos no estoque.");
            return 0;
        } else {
            System.out.println(resumoProduto(aux));
            return quantVencido(aux.prod);
        }
    }
}

