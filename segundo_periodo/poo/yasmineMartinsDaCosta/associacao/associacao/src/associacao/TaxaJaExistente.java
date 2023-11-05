package associacao;

public class TaxaJaExistente extends Exception {
    public TaxaJaExistente(){
        super("A taxa ja existe!");
    }
}
