package banco;

import java.util.Date;

public class Extrato {

	private String operacao;
	private double valor;
	private double saldo;
	private Date data; //criei o atributo do tipo Date

	public Extrato(String op, double v, double s, Date data1) { // botei "data" como parametro pro construtor

		operacao = op;
		valor = v;
		saldo = s;
		data = data1; //botei no construtor
	}

	public Date getDate() { // fiz essa
		return getData();
		
	}
	public Date getData() {// fiz essa
		return data;
	}
	public int getDate1() {//fiz essa pra pegar somente o dia em inteiro
		return data.getDate();
	}
	public int getMonth1() {// fiz essa pra pegar somente o mes em intiro
		return data.getMonth();
	}
	public String getLinha() { // alterei aqui a string!
		
		return "Data: " + getData().getDate()+"/" + (getData().getMonth()+1) + "/" + (getData().getYear()+1900) + "\n" + "Horário: " + getData().getHours() + ":" + getData().getMinutes() + "\n" + "operação: " + operacao + ": " + valor + " Saldo: " + saldo + "\n\n"; //adicionei a data 
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
