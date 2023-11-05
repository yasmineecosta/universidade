package associacao;

public class AssociadoJaExistente extends Exception{
    public AssociadoJaExistente(){
        super("O associado ja existe!");
    }
}
