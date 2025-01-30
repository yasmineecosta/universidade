package Operacao;

public class Extrato {
	private String tipoOperacao;
	private double value;
	private Date data;

    public Extrato(String tipoOperacao, double valor, Date data) {
        this.tipoOperacao = tipoOperacao;
        this.valor = valor;
        this.data = data;
    }

    public String getTipoOperacao() {
        return tipoOperacao;
    }

    public double getValor() {
        return valor;
    }

    public Date getData() {
        return data;
    }
}
