package bancos;

public class Extrato {
	int num;
	double saldo;
	String transacoes;
	
	public void credito(double value){
		this.saldo = saldo + value;
	}
	
	public void debito(double value){
		this.saldo = saldo - value;
	}
	
	public double valor(double value) {
		return value;
	}
	
	public double SaldoFinal() {
		return saldo;
	}
	
	public double Account(double value) {
		return (this.saldo = value);
	
	}
}
