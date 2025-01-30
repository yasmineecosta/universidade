package pedroSantosNeto.banco;

public class Extrato {

	private String operacao;
	private double valor;
	private double saldo;
	
	public Extrato(String op, double v, double s) {
		operacao = op;
		valor = v;
		saldo = s;
	}
	
	public String getLinha() {
		return operacao + ": " + valor + " Saldo: " + saldo + "\n";
	}

	public String getOperacao() {
		return operacao;
	}

	public void setOperacao(String operacao) {
		this.operacao = operacao;
	}

	public double getValor() {
		return valor;
	}

	public void setValor(double valor) {
		this.valor = valor;
	}

	public double getSaldo() {
		return saldo;
	}

	public void setSaldo(double saldo) {
		this.saldo = saldo;
	}
}
