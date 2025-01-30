package pedroSantosNeto.banco;

public class ContaComum {
	
	private int num;
	private double saldo;
	private Extrato[] extrato = new Extrato[100];
	private int pos = 0;
	private Pessoa dono;

	
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
		extrato[pos++] = new Extrato("Credito", val, saldo);
	}
	
	public boolean debito(double val) {
		if (val <= saldo) { 
		    saldo = saldo - val;
		    extrato[pos++] = new Extrato("Debito", val, saldo);
		    return true;
		} else {
			System.out.println("Saldo insuficiente.");
			return false;
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

	public String getExtrato() {
		String ext = "";
		for (int i = 0; i < pos; i++) {
			ext = ext + extrato[i].getLinha();
		}
		return ext;
	}
	
	public Pessoa getDono() {
		return dono;
	}
	
}
