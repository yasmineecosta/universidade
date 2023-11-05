package associacao;

public class limpaBanco {
    public static void main(String[] args){

        AssociacaoDAO dao1 = new AssociacaoDAO();
        AssociadoDAO dao2 = new AssociadoDAO();
        PagamentoDAO dao3 = new PagamentoDAO();
        ParticipantesDAO dao4 = new ParticipantesDAO();
        ReuniaoDAO dao5 = new ReuniaoDAO();
        TaxaDAO dao6 = new TaxaDAO();

        dao1.removerTodos();
        dao2.removerTodos();
        dao3.removerTodos();
        dao4.removerTodos();
        dao5.removerTodos();
        dao6.removerTodos();

    }
}
