package estoqueComProdutoPerecivel;

import java.util.ArrayList;
import java.util.Date;

public class Estoque implements InterfaceEstoque {

	ArrayList<Produto> produtos = new ArrayList<Produto>();
	
	public boolean incluir(Produto p) {
		if(p == null || p.getForn() == null){
			return false;
		}
		
		if((p.getForn().getCnpj() <= 0) || (p.getDesc().isBlank()) || p.getCodigo()<=0)
			return false;

		for(int i=0; i<produtos.size(); i++){
			if(produtos.get(i).getCodigo() == p.getCodigo())
				return false;
		}

		if(p instanceof ProdutoPerecivel){
			ProdutoPerecivel pp = (ProdutoPerecivel) p;
			if(pp.getForn() == null){
				return false;
			}
		}

		if(p.getForn().getNome() == null || p.getForn().getNome().isBlank()){
			return false;
		}

		if(p.getMin() < 0 || p.getLucro() <= 0 || p.getForn().getNome() == null || p.getForn().getNome().isBlank()){
			return false;
		}

		produtos.add(p);
		return true;
		
	}

	public boolean dataMaiorQueDataAtual(Date val) {
		Date dataAtual = new Date();
		if(val.after(dataAtual)) {
			return true;
		}
		return false;
	}

	public boolean comprar(int cod, int quant, double preco, Date val) {
		Date dataAtual = new Date();

		if(pesquisar(cod) == null || quant <= 0 || preco <= 0)
			return false;
		
		if(val == null && pesquisar(cod) instanceof ProdutoPerecivel){
		return false;
		}

		if (val == null) {
			pesquisar(cod).compra(quant, preco);
			return true;
		}
		
		if(val != null && !(pesquisar(cod) instanceof ProdutoPerecivel)) {
				return false;
		}

		if(val!=null && pesquisar(cod) instanceof ProdutoPerecivel){
			ProdutoPerecivel pp = (ProdutoPerecivel) pesquisar(cod);
			if(val.before(dataAtual))
				return false;
			pp.compraPerecivel(quant, preco, val);
		}else{
			pesquisar(cod).compra(quant, preco);
		}

		
		return true;
	}

	@Override
	public double vender(int cod, int quant) {
		Date Atual = new Date();
		Produto produto = pesquisar(cod);
		if(cod <= 0 || quant <= 0 || produto == null)
			return -1;

		if(produto.quant < quant)
			return -1;

		if(produto instanceof ProdutoPerecivel){
			if(produto.quant - quantidadeVencidos(cod) < quant)
				return -1;

			int temporaria = quant;
			ArrayList<Lote> lotes = new ArrayList<Lote>();
			for(Lote lot : ((ProdutoPerecivel) produto).lotes){
				long difference = lot.getValidade().getTime() - Atual.getTime();
				if(difference > 0 && lot.quantidade > 0){
					lotes.add(lot);
				}
			}
			
			if(lotes.size() == 0)
				return -1;

			while(temporaria > 0){
				Lote lts = lotes.get(0);
				long diferenca = 100000000;

				for(Lote lot : lotes){
					long dif = lot.getValidade().getTime() - Atual.getTime();
					if(lot.quantidade > 0 && dif < diferenca){
						diferenca = dif;
						lts = lot;
						
					}
				}

				if(lts.quantidade < temporaria){
					temporaria -= lts.quantidade;

					for(Lote lo : ((ProdutoPerecivel) produto).lotes){
						if(lo.getValidade() == lts.getValidade() && lo.getQuant() == lts.getQuant()){
							lo.quantidade = 0;
							break;
						}
					}
					lts.quantidade = 0;
				}else if(lts.quantidade == temporaria){
					for(Lote lotez : ((ProdutoPerecivel) produto).lotes){
						if(lotez.getValidade() == lts.getValidade() && lotez.getQuant() == lts.getQuant()){
							lotez.quantidade = 0;
							break;
						}
					}

					lts.quantidade = 0;
					break;
				}else{
					for(Lote lotez : ((ProdutoPerecivel) produto).lotes){
						if(lotez.getValidade() == lts.getValidade() && lotez.getQuant() == lts.getQuant()){
							lotez.quantidade -= quant;
							break;
						}
					}
					lts.quantidade -= temporaria;
					break;
				}			
			}
		} 
		produto.quant -= quant;
		return quant * produto.precoDeVenda;

	}

	@Override
	public Produto pesquisar(int cod) {
		for(int i=0; i<produtos.size();i++) {
			if(produtos.get(i).getCodigo() == cod)
				return produtos.get(i);
		}
		return null;
	}


	@Override
	public ArrayList<Produto> estoqueAbaixoDoMinimo() {
		ArrayList<Produto> produtosAbaixoDoMin = new ArrayList<Produto>();

		for (int i = 0; i < produtos.size(); i++) {
			if (produtos.get(i).getQuant() < produtos.get(i).getMin()) {
				produtosAbaixoDoMin.add(produtos.get(i));
			}
		}
		return produtosAbaixoDoMin;
	}

	@Override
	public ArrayList<Produto> estoqueVencido() {
		ArrayList<Produto> produtosVencidos = new ArrayList<Produto>();
		Date dataAtual = new Date();
		for(Produto produto : produtos){
			if(produto instanceof ProdutoPerecivel){
				for(Lote lote : ((ProdutoPerecivel) produto).lotes){
					if(lote.getValidade().before(dataAtual)){
						produtosVencidos.add(produto);
						break;
					}
				}
			}
		}
		return produtosVencidos;
	}	

	@Override
	public int quantidadeVencidos(int cod) {
		
		int quantVencidos = 0;
		Date dataAtual = new Date();

		Produto p = pesquisar(cod);
		if(p == null || !(p instanceof ProdutoPerecivel))
			return 0;
		
		for(Lote lote : ((ProdutoPerecivel) p).lotes){
			if(lote.getValidade().before(dataAtual)){
				quantVencidos += lote.getQuant();
			}
		}
		return quantVencidos;
		// for (int i = 0; i < produtos.size(); i++) {
		// 	if (produtos.get(i) instanceof ProdutoPerecivel) {
		// 		ProdutoPerecivel pp = (ProdutoPerecivel) produtos.get(i);
		// 		if (pp.getLoteVencido()) {
		// 			quantVencidos++;
		// 		}
		// 	}
		// }
		// return quantVencidos;
	}

    public Fornecedor fornecedor(int i) {
		return pesquisar(i).getForn();
	}

}
