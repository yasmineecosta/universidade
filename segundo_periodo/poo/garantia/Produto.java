package matheusKaikyBritoSilva.estoqueComProdutoPerecivel;

import java.util.Date;

public class Produto {

    int cod; String desc; int min; double lucro; Fornecedor forn;
    public Produto(int cod, String desc, int min, double lucro, Fornecedor forn){
         this.cod = cod;
         this.desc = desc;
         this.min = min;
         this.lucro = lucro;
         this.forn = forn;
    }

    protected int getCodigo() {
        return cod;
    }

    public int quantTotal = 0;
    public double valTotal = 0;
    public double precoFinal;
    public static double custo;
    public void atualizaCusto() {
        custo = (valTotal/quantTotal);
        precoFinal = custo + (custo * lucro);
    }

    public void decrementaQuantidade(int quant) {
        quantTotal -= quant;
        valTotal -= (quant*custo);
        atualizaCusto();
    }

    public void compra(int quant, double val) {
        quantTotal += quant;
        valTotal += (val*quant);
        atualizaCusto();
    }

    public double venda(int quant) {
        double vendaTotal = quant * precoFinal;
        decrementaQuantidade(quant);
        return vendaTotal;
    }
}





















































































































































//@Matheus Kaiky Brito Silva