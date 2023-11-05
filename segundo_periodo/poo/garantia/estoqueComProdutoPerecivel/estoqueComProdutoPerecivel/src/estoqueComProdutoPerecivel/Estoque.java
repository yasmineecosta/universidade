package estoqueComProdutoPerecivel;

import java.util.ArrayList;
import java.util.Date;

public class Estoque implements InterfaceEstoque {

	ListaDeProdutos produtos = new ListaDeProdutos();

	public boolean dataMaiorQueDataAtual(Date val) {
		Date dataAtual = new Date();
		if(val.after(dataAtual)) {
			return true;
		}
		return false;
	}

	public boolean incluir(Produto p) {
		
		if((p == null) || (p.getForn().getCnpj() <= 0) || (p.getDesc().isBlank()) || p.getCodigo()<=0)
			return false;
		
		return produtos.incluir(p);
	}

	public boolean comprar(int cod, int quant, double preco, Date val) {
		Date dataAtual = new Date();

		if(produtos.pesquisar(cod) == null || quant <= 0 || preco <= 0)
			return false;
		
		if (val == null) {
			produtos.pesquisar(cod).compra(quant, preco);
			return true;
		}
		
		if(val != null && !(produtos.pesquisar(cod) instanceof ProdutoPerecivel)) {
				return false;
		}
 	
		if(val!=null && produtos.pesquisar(cod) instanceof ProdutoPerecivel){
			ProdutoPerecivel pp = (ProdutoPerecivel) produtos.pesquisar(cod);
			if(val.before(dataAtual))
				return false;
			pp.compra(quant, preco, val);
		}else{
			produtos.pesquisar(cod).compra(quant, preco);
		}

		return true;
	}

	@Override
	public double vender(int cod, int quant) {
		Date Atual = new Date();
		if (produtos.pesquisar(cod) instanceof ProdutoPerecivel) {// confere se é ou n prodperecivel
			ProdutoPerecivel pp = (ProdutoPerecivel) produtos.pesquisar(cod);
			if (pp.getLoteVencido()) {// confere se o lote está vencido
				return -1;
			}
			return pp.venda(quant);
		}

		if(quant <= 0 || produtos.pesquisar(cod) == null || produtos.pesquisar(cod) instanceof ProdutoPerecivel){
			return -1;
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
		Node aux = inicio;
		while(aux != null) {
			if(aux.prod instanceof ProdutoPerecivel) {
				if (((ProdutoPerecivel) aux.prod).produtoVencido()) {
                    produtosVencidos.add(aux.prod);
                }
            }
            aux = aux.prox;
		}
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

    public Fornecedor fornecedor(int i) {
		return produtos.pesquisar(i).getForn();
	}

}
