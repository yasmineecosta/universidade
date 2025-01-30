package pedroSantosNeto.banco;

public class Banco {

	private ListaDeContas contas = new ListaDeContas();
	
	public void inserir(ContaComum c) {
		contas.inserir(c);
	}
	
	public void deposito(int n, double v) {
		ContaComum c = contas.pesquisar(n);
		if (c != null) {
		  c.credito(v);
		}
	}
	
	public void saque(int n, double v) {
		ContaComum c = contas.pesquisar(n);	
		if (c != null) {
			c.debito(v);
		}
	}
	
	public void transfere(int de, int para, double val) {
		ContaComum c1 = contas.pesquisar(de);	
		ContaComum c2 = contas.pesquisar(para);	
		if (c1 != null && c2 != null) {
			if (c1.debito(val)) {
				c2.credito(val);				
			}
		}
	}
	
	public double saldo(int n) {
		ContaComum c = contas.pesquisar(n);	
		if (c != null) {
			return c.getSaldo();
		} else {
			return -9999999;
		}
	}
	
	public String extrato(int n) {
		ContaComum c = contas.pesquisar(n);	
		if (c != null) {
			return c.getExtrato();
		} else {
			return "";
		}
	}
	
	public String nomeDoDono(int n) {
		ContaComum c = contas.pesquisar(n);	
		if (c != null) {
			return c.getDono().getNome();
		} else {
			return null;
		}
	}
	
	public int cpfDoDono(int n) {
		ContaComum c = contas.pesquisar(n);	
		if (c != null) {
			return c.getDono().getCpf();
		} else {
			return 0;
		}
	}
}
