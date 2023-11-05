package estoqueComProdutoPerecivelExcecoes;

import java.util.ArrayList;
import java.util.Date;
// import java.time.Clock;
// import java.time.Instant;
// import java.time.ZoneId;
public class Estoque implements InterfaceEstoqueComExcecoes {

	private ArrayList<Produto> produtos = new ArrayList<>();
	private int quant = 0;
	
	public boolean dataMaiorQueDataAtual(Date val) {
		Date dataAtual = new Date();
		if(val.after(dataAtual)) {
			return true;
		}
		return false;
	}

	public void incluir(Produto p) throws ProdutoJaCadastrado, DadosInvalidos {
		if(p == null || p.getForn() == null){
			throw new DadosInvalidos();
		}
		
		if((p.getForn().getCnpj() <= 0) || p.getDesc() == null ||(p.getDesc().isBlank()) || p.getCodigo()<=0)
			throw new DadosInvalidos();

		for(int i=0; i<produtos.size(); i++){
			if(produtos.get(i).getCodigo() == p.getCodigo())
				throw new ProdutoJaCadastrado();
		}

		if(p instanceof ProdutoPerecivel){
			ProdutoPerecivel pp = (ProdutoPerecivel) p;
			if(pp.getForn() == null){
				throw new DadosInvalidos();
			}
		}

		if(p.getForn().getNome() == null || p.getForn().getNome().isBlank()){
			throw new DadosInvalidos();
		}

		if(p.getMin() < 0 || p.getLucro() <= 0 || p.getForn().getNome() == null || p.getForn().getNome().isBlank()){
			throw new DadosInvalidos();
		}

		produtos.add(p);
		return;
		
	}

	public void comprar(int cod, int quant, double preco, Date val) throws ProdutoInexistente, DadosInvalidos, ProdutoNaoPerecivel{
		Date dataAtual = new Date();

		if(pesquisar(cod) == null || quant <= 0 || preco <= 0)
			throw new DadosInvalidos();

		if (val == null && pesquisar(cod) instanceof ProdutoPerecivel) {
			throw new DadosInvalidos();
		}
		
		if(val != null && !(pesquisar(cod) instanceof ProdutoPerecivel)) {
			throw new ProdutoNaoPerecivel();
		}
 	
		if(val!=null && pesquisar(cod) instanceof ProdutoPerecivel){
			ProdutoPerecivel pp = (ProdutoPerecivel) pesquisar(cod);
			if(val.before(dataAtual))
				throw new DadosInvalidos();
			pp.compraPerecivel(quant, preco, val);
		}else{
			pesquisar(cod).compra(quant, preco);
		}

		if(val == null && !(pesquisar(cod) instanceof ProdutoPerecivel)) {
			pesquisar(cod).compra(quant, preco);
			return;
		}

		return;
	}

	@Override
	public double vender(int cod, int quant) throws ProdutoInexistente, ProdutoVencido, DadosInvalidos{
		Date Atual = new Date();
		Produto produto = pesquisar(cod);
		if(cod <= 0 || quant <= 0 || produto == null)
			throw new DadosInvalidos();

		if(produto.quant < quant)
			throw new DadosInvalidos();

		if(produto instanceof ProdutoPerecivel){
			if(produto.quant - quantidadeVencidos(cod) < quant)
			// if(quantidadeDisponivelparaVenda(cod) < quant)
				throw new ProdutoVencido();

			if(quantidadeVencidos(cod) == produto.quant)
				throw new ProdutoVencido();

			int temporaria = quant;
			ArrayList<Lote> lotes = new ArrayList<Lote>();
			for(Lote lot : ((ProdutoPerecivel) produto).lotes){
				long difference = lot.getValidade().getTime() - Atual.getTime();
				if(difference > 0 && lot.quantidade > 0){
					lotes.add(lot);
				}
			}
			
			if(lotes.size() == 0)
				throw new ProdutoVencido();

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
		// return quant * produto.getPrecoDeVenda();

	}

	@Override
	public Produto pesquisar(int cod) throws ProdutoInexistente{
		// for(int i=0; i<quant;i++) {
		for(int i=0; i<produtos.size();i++){
			if(produtos.get(i).getCodigo() == cod)
				return produtos.get(i);
		}
		throw new ProdutoInexistente();
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
	public int quantidadeVencidos(int cod) throws ProdutoInexistente{
		
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

		// for (int i = 0; i < produtos.size(); i++) {
		// 	if (produtos.get(i) instanceof ProdutoPerecivel) {
		// 		ProdutoPerecivel pp = (ProdutoPerecivel) produtos.get(i);
		// 		if (pp.getLoteVencido()) {
		// 			quantVencidos++;
		// 		}
		// 	}else{
		// 		throw new ProdutoInexistente();
		// 	}
		// }
		return quantVencidos;
	}

	public int quant(int cod){
		for(int i=0; i<quant;i++) {
			if(produtos.get(i).getCodigo() == cod)
				return produtos.get(i).getQuant();
		}
		return 0;
	}

    public Fornecedor fornecedor(int cod) {
		for(int i=0; i<quant;i++) {
			if(produtos.get(i).getCodigo() == cod)
				return produtos.get(i).getForn();
		}
		return null;
	}

	// public int quantidadeDisponivelparaVenda(int cod) throws ProdutoInexistente{
	// 	Produto produto = pesquisar(cod);
	// 	if(produto == null)
	// 		throw new ProdutoInexistente();
		
	// 	if(produto instanceof ProdutoPerecivel){
	// 		int quantidadeVencidos = quantidadeVencidos(cod);
	// 		return produto.getQuant() - quantidadeVencidos;
	// 	}else{
	// 		return produto.getQuant();
	// 	}
	// }

}
