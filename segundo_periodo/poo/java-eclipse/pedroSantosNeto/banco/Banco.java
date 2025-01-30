package pedroSantosNeto.banco;

public class Banco {

	private ContaComum contas[] = new ContaComum[50];
	private int pos = 0;
	
	public void inserir(ContaComum c) {
		ContaComum c1 = pesquisar(c.getNum());
		if (c1 == null) {
		   contas[pos++] = c;
		} else {
			System.out.println("Conta já cadastrada.");
		}
	}
	
	private ContaComum pesquisar(int n) {
		for (int i = 0; i < pos; i++) {
			if (contas[i].getNum() == n) {
				return contas[i];
			}
		}
		System.out.println("Conta não encontrada.");	
		return null;
	}
	
	public void deposito(int n, double v) {
		ContaComum c = pesquisar(n);
		if (c != null) {
		  c.credito(v);
		}
	}
	
	public void saque(int n, double v) {
		ContaComum c = pesquisar(n);	
		if (c != null) {
			c.debito(v);
		}
	}
	
	public double saldo(int n) {
		ContaComum c = pesquisar(n);	
		if (c != null) {
			return c.getSaldo();
		} else {
			return -9999999;
		}
	}
	
	public String extrato(int n) {
		ContaComum c = pesquisar(n);	
		if (c != null) {
			return c.getExtrato();
		} else {
			return "";
		}
	}
	
	public String nomeDoDono(int n) {
		ContaComum c = pesquisar(n);	
		if (c != null) {
			return c.getDono().getNome();
		} else {
			return null;
		}
	}
	
	public int cpfDoDono(int n) {
		ContaComum c = pesquisar(n);	
		if (c != null) {
			return c.getDono().getCpf();
		} else {
			return 0;
		}
	}
}
