package EstoqueComProdutoPerecivel;

import java.util.ArrayList;

public class ListaDeProdutos {

	ArrayList<Produto> produtos = new ArrayList<Produto>();

	public boolean incluir(Produto p) {
		for(int i=0; i<produtos.size(); i++){
			if(produtos.get(i).getCodigo() == p.getCodigo())
				return false;
		}
		produtos.add(p);
		return true;
		
	}
	
	public Produto pesquisar(int cod) {
		for(int i=0; i<produtos.size();i++) {
			if(produtos.get(i).getCodigo() == cod)
				return produtos.get(i);
		}
		
		return null;
	}

	public int getTamanho() {
		return produtos.size();
	}
}
