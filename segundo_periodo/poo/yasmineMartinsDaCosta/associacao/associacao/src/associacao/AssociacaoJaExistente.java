package associacao;

public class AssociacaoJaExistente extends Exception{
    public AssociacaoJaExistente(){
        super("A associacao ja existe!");
    }
}
