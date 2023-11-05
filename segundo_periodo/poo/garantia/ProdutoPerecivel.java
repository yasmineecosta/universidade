package matheusKaikyBritoSilva.estoqueComProdutoPerecivel;

import java.util.Date;

public class ProdutoPerecivel extends Produto {
    public ProdutoPerecivel(int cod, String desc, int min, double lucro, Fornecedor forn) {
        super(cod, desc, min, lucro, forn);
    }

    protected static class Node {
        public Lote lote;
        public Node prox;
    }
    public Node inicio = null;

    protected Date maisProx;

    public boolean temProdutoVencido() {
        Node aux = inicio;
        Date hoje = new Date();
        while (aux != null) {
            if (aux.lote.validade.compareTo(hoje) < 0) {
                return true;
            }
            aux = aux.prox;
        }
        return false;
    }

    public int quantidadeVencidoPorProduto() {
        int quantVenc = 0;
        Node aux = inicio;
        Date dataAtual = new Date();
        while (aux != null) {
            if (aux.lote.validade.compareTo(dataAtual) < 0) {
                quantVenc += aux.lote.quant;
            }
            aux = aux.prox;
        }
        return quantVenc;
    }

    private void insereNaLista(Lote temp) {
        Node newLote = new Node();
        newLote.lote = temp;
        newLote.prox = null;
        if (inicio == null) {
            inicio = newLote;
            return;
        }
        Node aux = inicio;
        while (aux != null) {
            if (aux.lote.val == temp.val && aux.lote.validade.equals(temp.validade)) {
                aux.lote.quant += temp.quant;
                return;
            }
            if (aux.prox == null) {
                aux.prox = newLote;
                break;
            }
            aux = aux.prox;
        }

    }

    public void atualizaCustoEProxVencimento() {
        Node aux = inicio;
        Date hoje = new Date();
        maisProx = null;
        quantTotal = 0;
        valTotal = 0;
        while (aux != null) {
            if (aux.lote.validade.compareTo(hoje) >= 0) {
                if (maisProx == null) {
                    maisProx = aux.lote.validade;
                } else if (aux.lote.validade.compareTo(maisProx) < 0) {
                    maisProx = aux.lote.validade;
                }
            }
            quantTotal += aux.lote.quant;
            valTotal += (aux.lote.val * aux.lote.quant);
            aux = aux.prox;
        }
        if (maisProx == null) {
            maisProx = new Date(-1);
        }
        custo = valTotal / quantTotal;
        precoFinal = custo + (custo * lucro);
    }

    public void compraPerecivel(int quant, double val, Date venc){
        Lote temp = new Lote(quant, venc, val);
        insereNaLista(temp);
        atualizaCustoEProxVencimento();
    }

    public double vendaPerecivel(int quant) {
        double vendaTotal = 0;
        int i = quant;
        Node aux = inicio;
        Node anterior = null;
        while (aux != null && i != 0) {
            if (maisProx.equals(aux.lote.validade)) {
                if ((aux.lote.quant - i) > 0) { // caso sobrar estoque no lote após a venda
                    vendaTotal += (i * precoFinal);
                    aux.lote.quant -= i;
                    atualizaCustoEProxVencimento();
                    return vendaTotal;
                } else if ((i - aux.lote.quant) >= 0) { // caso o lote zerar ou não ser suficiente pra vender
                    i -= aux.lote.quant;
                    vendaTotal += (aux.lote.quant * precoFinal);
                    if (aux == inicio) { // apaga o lote atual caso esteja no inico da lista
                        aux = aux.prox;
                        inicio = inicio.prox;
                        atualizaCustoEProxVencimento();
                        continue;
                    } else if (aux.prox == null) {
                        anterior.prox = null;
                    } else { // apaga o lote atual nas demais posições
                        anterior.prox = aux.prox;
                    }
                    atualizaCustoEProxVencimento();
                }
            }
            anterior = aux;
            aux = aux.prox;
        }
        if (i == 0) {
            return vendaTotal;
        } else {
            return -1;
        }
    }
}