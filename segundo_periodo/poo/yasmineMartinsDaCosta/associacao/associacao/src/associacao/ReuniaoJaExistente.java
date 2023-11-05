package associacao;

public class ReuniaoJaExistente extends Exception{
    public ReuniaoJaExistente(){
        super("A reuniao ja existe!");
    }
}
