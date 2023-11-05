package estoqueComProdutoPerecivel;
import java.util.ArrayList;
import java.util.Date;
public class ProdutoPerecivel extends Produto{

	ArrayList<Lote> lotes = new ArrayList<Lote>();
	protected static class Node{
		public Lote lote;
		public Node prox;
	}
	public Node inicio = null;

	public ProdutoPerecivel(int cod, String desc, int min, double lucro, Fornecedor forn) {
		super(cod, desc, min, lucro, forn);
	}

	public void compraPerecivel(int quant, double val, Date val2) {
		//compraProdutoPerecivelComValidadeMenorQueDataAtual
		
		precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
		this.quant += quant;
		precoDeVenda = (precoDeCompra * (1 + lucro));
		
		Lote lt = new Lote(quant, val2, val);
		
		lotes.add(lt);
	}
	
	public double vendaPerecivel(int quant) {
		
		Date d = new Date(1,1,1);
		Date dataAtual = new Date();
		Lote loteMaisProximoDeVencer = new Lote();
	
		for(int i=0; i<lotes.size(); i++) {
			if(lotes.get(i).getValidade().after(d) && lotes.get(i).getValidade().before(dataAtual)) {
				loteMaisProximoDeVencer = lotes.get(i);
			}
		}
		
		if(quant < loteMaisProximoDeVencer.getQuant()) {
			int quantRemovida = loteMaisProximoDeVencer.getQuant() - quant;
			loteMaisProximoDeVencer.reduzQuant(quantRemovida);
		}
		if(quant == loteMaisProximoDeVencer.getQuant()) {
			lotes.remove(loteMaisProximoDeVencer);
		}
		if(quant > loteMaisProximoDeVencer.getQuant()) {
			quant -= loteMaisProximoDeVencer.getQuant();
			lotes.remove(loteMaisProximoDeVencer);
			return vendaPerecivel(quant);
		}
		
		if(quant <= this.quant) {
			double valor = quant*precoDeVenda;
			this.quant -= quant;
			return valor;
		}else {
			return -1;
		}
	}

	public boolean compra(int quant, double val, Date val2) {
		if(quant>0 && val>0 && ((quant+this.quant)>=this.min) && val2.after(new Date())) {
			precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
			this.quant += quant;
			precoDeVenda = (precoDeCompra * (1 + lucro));
			return true;
		}
		return false;
	}
	
	public boolean getLoteVencido() {
		Date dataAtual = new Date();

		for(int i=0;i<lotes.size();i++) {
			if(lotes.get(i).getValidade().before(dataAtual)) {
				return true;
			}
		}
		return false;
	}

	public boolean produtoVencido() {
		Node aux = inicio;
		Date dataAtual = new Date();
		while(aux != null){
			if(aux.lote.getValidade().before(dataAtual)) {
				return true;
			}
			aux = aux.prox;
		}
		//if(val.before(dataAtual)) {
		//	return true;
		//}
		return false;
	}

}
