package Operacao;

public class Usuario {
	private String nome;
    private List<Extrato> operacoes;

    public Usuario(String nome) {
        this.nome = nome;
        this.operacoes = new ArrayList<>();
    }

    public String getNome() {
        return nome;
    }

    public void adicionarOperacao(String tipoOperacao, double valor, Date data) {
        Extrato operacao = new Extrato(tipoOperacao, valor, data);
        operacoes.add(operacao);
    }

    public List<Extrato> getOperacoes() {
        return operacoes;
    }
}
