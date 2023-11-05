package associacao;

public class TaxaNaoExistente extends Exception {
    public TaxaNaoExistente(){
        super("A taxa nao existe!");
    }
}
