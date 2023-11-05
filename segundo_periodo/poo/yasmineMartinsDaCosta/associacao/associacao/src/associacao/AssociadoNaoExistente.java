package associacao;

public class AssociadoNaoExistente extends Exception{
    public AssociadoNaoExistente(){
        super("O associado nao existe!");
    }
}
