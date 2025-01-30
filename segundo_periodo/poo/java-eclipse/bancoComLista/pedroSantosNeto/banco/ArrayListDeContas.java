package pedroSantosNeto.banco;

import java.util.ArrayList;

public class ArrayListDeContas {
	
	private ArrayList<ContaComum> array = new ArrayList<ContaComum>();

	public void inserir(ContaComum c) {
		ContaComum c1 = pesquisar(c.getNum());
		if (c1 == null) {
			array.add(c);
		}
	
	}
	
	public ContaComum pesquisar(int n) {
		for (ContaComum contaComum : array) {
			if (contaComum.getNum() == n)
				return contaComum;
		}
		System.out.println("Conta não encontrada.");	
		return null;
	}
}
