package EstoqueComProdutoPerecivel;

import java.util.ArrayList;
import java.util.Date;

public class Estoque implements InterfaceEstoque {

	ListaDeProdutos produtos = new ListaDeProdutos();

	public boolean incluir(Produto p) {

		if((p.getForn().getCnpj() <= 0) || (p.getDesc().isBlank()))
			return false;
		
		if(p==null || p.getCodigo() < 0) {
			return false;
		}
		
		if (produtos.incluir(p))
			return true;

		return false;
	}

	public boolean comprar(int cod, int quant, double preco, Date val) {
		Date dataAtual = new Date();
		
		if(val!=null && dataAtual.after(val))
			return false;
		
		if(produtos.pesquisar(cod) == null)
			return false;
		
		if (val == null) {
			produtos.pesquisar(cod).compra(quant, preco, val);
			return true;
		}
		
		if(val != null && !(produtos.pesquisar(cod) instanceof ProdutoPerecivel)) {
			return false;
		}
		ProdutoPerecivel pp = (ProdutoPerecivel) produtos.pesquisar(cod);
		pp.compra(quant, preco, val);
		return true;
	}

	@Override
	public double vender(int cod, int quant) {
		if (produtos.pesquisar(cod) instanceof ProdutoPerecivel) {// confere se é ou n prodperecivel
			ProdutoPerecivel pp = (ProdutoPerecivel) produtos.pesquisar(cod);
			return pp.venda(quant);
		}

		return produtos.pesquisar(cod).venda(quant);
	}

	@Override
	public Produto pesquisar(int cod) {
		return produtos.pesquisar(cod);
	}

	@Override
	public ArrayList<Produto> estoqueAbaixoDoMinimo() {
		ArrayList<Produto> produtosAbaixoDoMin = new ArrayList<Produto>();

		for (int i = 0; i < produtos.getTamanho(); i++) {
			if (produtos.produtos.get(i).getQuant() < produtos.produtos.get(i).getMin()) {
				produtosAbaixoDoMin.add(produtos.produtos.get(i));
			}
		}
		return produtosAbaixoDoMin;
	}

	@Override
	public ArrayList<Produto> estoqueVencido() {
		ArrayList<Produto> produtosVencidos = new ArrayList<Produto>();

		for (int i = 0; i < produtos.getTamanho(); i++) {
			if (produtos.produtos.get(i) instanceof ProdutoPerecivel) {
				ProdutoPerecivel pp = (ProdutoPerecivel) produtos.produtos.get(i);
				if (pp.getLoteVencido()) {
					produtosVencidos.add(pp);
				}
			}
		}

		return produtosVencidos;
	}

	@Override
	public int quantidadeVencidos(int cod) {
		
		int quantVencidos = 0;
		
		for (int i = 0; i < produtos.getTamanho(); i++) {
			if (produtos.produtos.get(i) instanceof ProdutoPerecivel) {
				ProdutoPerecivel pp = (ProdutoPerecivel) produtos.produtos.get(i);
				if (pp.getLoteVencido()) {
					quantVencidos++;
				}
			}
		}

		return quantVencidos;
	}

}
