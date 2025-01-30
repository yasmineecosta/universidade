package banco;

public class Banco {

	private ContaComum contas[] = new ContaComum[50];
	private int pos = 0;
	
	public void inserir(ContaComum c) {
		contas[pos++] = c;
	}
	
	public void deposito(int n, double v) {
		for (int i = 0; i < pos; i++) {
			if (contas[i].getNum() == n) {
				contas[i].credito(v);
				return;
			}
		}
		System.out.println("Conta não encontrada.");	
	}
	
	public void saque(int n, double v) {
		for (int i = 0; i < pos; i++) {
			if (contas[i].getNum() == n) {
				contas[i].debito(v);
				return;
			}
		}
		System.out.println("Conta não encontrada.");		
	}
	
	public double saldo(int n) {
		for (int i = 0; i < pos; i++) {
			if (contas[i].getNum() == n) {
				return contas[i].getSaldo();
			}
		}
		System.out.println("Conta não encontrada.");
		return -9999999;
	}
	
	public String extrato(int n) {
		for (int i = 0; i < pos; i++) {
			if (contas[i].getNum() == n) {
				return contas[i].getExtrato();
			}
		}
		System.out.println("Conta não encontrada.");
		return "";
	}
}
