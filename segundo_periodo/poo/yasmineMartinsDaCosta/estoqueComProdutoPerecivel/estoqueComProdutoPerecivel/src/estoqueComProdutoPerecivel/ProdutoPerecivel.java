package estoqueComProdutoPerecivel;
import java.util.ArrayList;
import java.util.Date;
public class ProdutoPerecivel extends Produto{
	
	ArrayList<Lote> lotes = new ArrayList<Lote>();
	
	public ProdutoPerecivel(int cod, String desc, int min, int lucro, Fornecedor forn) {
		super(cod, desc, min, lucro, forn);
	}

	public void compraPerecivel(int quant, double val, Date val2) {
		//compraProdutoPerecivelComValidadeMenorQueDataAtual
		Lote lt = new Lote(quant, val2);
		precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
		this.quant += quant;
		precoDeVenda = (precoDeCompra * (1 + lucro));
		
		lotes.add(lt);
	}
	
	public boolean getLoteVencido() {
		Date dataAtual = new Date();
		int quantidadeVencido = 0;
		for(Lote lote : lotes) {
			if(lote.getValidade().before(dataAtual)) {
				quantidadeVencido += lote.getQuant();
				return true;
			}
		}
		return false;
	}

/*
	public boolean produtoVencido() {
		//Node aux = inicio;
		Date dataAtual = new Date();
		for(int i=0; i<lotes.size(); i++) {
			if(lotes.get(i).getValidade().before(dataAtual)) {
				return true;
			}
		}
		
		while(aux != null){
			if(aux.lote.getValidade().before(dataAtual)) {
				return true;
			}
			aux = aux.prox;
		}

		if(val.before(dataAtual)) {
			return true;
		}
		return false;
	}*/

}
