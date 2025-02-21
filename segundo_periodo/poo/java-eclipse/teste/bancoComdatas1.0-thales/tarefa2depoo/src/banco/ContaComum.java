package banco;

import java.util.Date;

public class ContaComum {

	private int num;
	private double saldo;
	private Extrato[] extrato = new Extrato[100];
	private int pos = 0;
	private Pessoa dono;
	private Date data1 = new Date(); // criei a data aqui

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
		extrato[pos++] = new Extrato("Credito", val, saldo, data1); // adicionei mais um parametro, o data1, do tipo
																	// Date

	}

	public void debito(double val) {
		if (val <= saldo) {
			saldo = saldo - val;
			extrato[pos++] = new Extrato("Debito", val, saldo, data1);// adicionei mais um parametro, o data1, do tipo
																		// Date
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
		int flag = 0;
		String ext = "Peridoinicio: "+ini.getDate()+"/"+ini.getMonth()+" "+"Peridofim: "+fim.getDate()+"/"+fim.getMonth()+"\n";
		for (int i = 0; i < pos; i++) {
			    // nesa parte do if, analisa o dia                                            //    // nessa parte analisa o mes                                                                //
			if (ini.getDate() <= extrato[i].getDate1() && fim.getDate() >= extrato[i].getDate1() && ini.getMonth() <= (extrato[i].getMonth1()+1) && fim.getMonth() >= (extrato[i].getMonth1()+1)) {

				ext = ext + extrato[i].getLinha();
				flag = 1;
			}

		}
			if(flag==0){
				ext = ext + "nao existe extratos no periodo informado!";
			}

		return ext;

	}

	public Pessoa getDono() {
		return dono;
	}

}
