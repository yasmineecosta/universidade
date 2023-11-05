package associacao;

public class ReuniaoNaoExistente extends Exception {
    public ReuniaoNaoExistente(){
        super("A reuniao nao existe!");
    }
}
