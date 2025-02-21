package teste;
import java.util.Date;

public class ContaComum {
	
	private int num;
	private double saldo;
	private Extrato[] extrato = new Extrato[100];
	private int pos = 0;
	private Pessoa dono;
	private Date dInicial = new Date();

	public ContaComum(int n, Pessoa p) {
		num = n;
		if (p.getConta() == null) {
			dono = p;
			p.setConta(this);
		} else {
			System.out.println("Essa pessoa já possui uma conta");
			return;
		}
	}
	
	public void credito(double val) {
		saldo = saldo + val;
		extrato[pos++] = new Extrato("Credito: ", val, saldo, dInicial);
	}
	
	public void debito(double val) {
		if(val <= saldo) {
		saldo = saldo - val;
		extrato[pos++] = new Extrato("Debito", val, saldo, dInicial);
		} else {
		System.out.println("Saldo insuficiente.");
		}
	}

	public int getNum() {
		return num;
	}

	public void setNum(int n) {
		if (n < 1000) {
			num = n;
		} else {
			System.out.println("Não é permitido usar numeros maiores que 1000");
		}
	}

	public double getSaldo() {
		return saldo;
	}

	public String getExtrato(Date ini, Date fim) {
		int time = 0;
		String ext = "Perido inicial: "+ini.getDate()+"/"+ini.getMonth()+" "+"Perido final: "+fim.getDate()+"/"+fim.getMonth()+"\n";
		for (int i = 0; i < pos; i++) {
			if (ini.getDate() <= extrato[i].getDateIni() && fim.getDate() >= extrato[i].getDateIni() && ini.getMonth() <= (extrato[i].getMonthIni()+1) && fim.getMonth() >= (extrato[i].getMonthIni()+1)) {
				ext = ext + extrato[i].getLinha();
				time = 1;
			}

		}
			if(time==0){
				ext = ext + "nao existe extratos nas datas informadas!";
			}

		return ext;

	}

	public Pessoa getDono() {
		return dono;
	}
	
}



