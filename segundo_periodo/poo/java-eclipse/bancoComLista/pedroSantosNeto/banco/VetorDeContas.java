package pedroSantosNeto.banco;

public class VetorDeContas {

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
	
	public ContaComum pesquisar(int n) {
		for (int i = 0; i < pos; i++) {
			if (contas[i].getNum() == n) {
				return contas[i];
			}
		}
		System.out.println("Conta não encontrada.");	
		return null;
	}
}
