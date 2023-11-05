package matheusKaikyBritoSilva.estoqueComProdutoPerecivel;

import java.util.Date;

public class Lote {
    public Date validade;
    public double val;
    public int quant;
    public Lote(int quant, Date validade, double val){
        this.quant = quant;
        this.validade = validade;
        this.val = val;
    }
}
