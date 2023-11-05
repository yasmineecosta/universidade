package associacao;

import java.util.Date;

public class AssociadoRemido extends Associado{
    public long dataRemissao;

    public AssociadoRemido(int numero, String nome, String telefone, long dataAssociacao, long nascimento, long dataRemissao) {
        super(numero, nome, telefone, nascimento, dataAssociacao);
        this.dataRemissao = dataRemissao;
    }

    public long getDataRemissao() {
        return dataRemissao;
    }
    
}
