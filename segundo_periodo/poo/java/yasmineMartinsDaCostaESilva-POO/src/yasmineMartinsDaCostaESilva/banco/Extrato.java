package yasmineMartinsDaCostaESilva.banco;
import java.util.Date;

public class Extrato {
	private String operacao;
	private double valor;
	private double saldo;
			Date data;
	//private Date d = new Date();
	
	public Extrato(String op, double v, double s, Date dataIni) {
		operacao = op;
		valor = v;
		saldo = s;
		data = dataIni;
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

	public Date getDate() {
		return getData();
	}
	
	public Date getData() {
		return data;
	}
	
	public int getDateIni() {
		return data.getDate();
	}
	
	public int getMonthIni() {
		return data.getMonth();
	}
	public String getLinha() {
		return "Data: " + getData().getDate()+"/" + (getData().getMonth()+1) + "/" + (getData().getYear()+1900) + "\n" + "Horário: " + getData().getHours() + ":" + getData().getMinutes() + "\n" + "operação: " + operacao + ": " + valor + " Saldo: " + saldo + "\n\n"; 
	}
}
