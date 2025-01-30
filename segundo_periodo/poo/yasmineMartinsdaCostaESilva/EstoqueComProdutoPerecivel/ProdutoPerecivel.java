package EstoqueComProdutoPerecivel;
import java.util.ArrayList;
import java.util.Date;
public class ProdutoPerecivel extends Produto{

	ArrayList<Lote> lotes = new ArrayList<Lote>();
	
	public ProdutoPerecivel(int cod, String desc, int min, double lucro, Fornecedor forn) {
		super(cod, desc, min, lucro, forn);
	}
	
	public void compra(int quant, double val, Date val2) {
		precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
		this.quant += quant;
		precoDeVenda = (precoDeCompra * (1 + lucro));
		
		Lote lt = new Lote(quant, val2);
		
		lotes.add(lt);
	}
	
	public double venda(int quant) {
		
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
			lotes.remove(loteMaisProximoDeVencer);
			int quantRemovida2 = quant - loteMaisProximoDeVencer.getQuant();
			for(int i=0; i<lotes.size(); i++) {
				if(lotes.get(i).getValidade().after(d) && lotes.get(i).getValidade().before(dataAtual)) {
					loteMaisProximoDeVencer = lotes.get(i);
				}
			}
			for(int i=0; i<lotes.size(); i++) {
				if(lotes.get(i).getValidade().after(d) && lotes.get(i).getValidade().before(dataAtual)) {
					loteMaisProximoDeVencer = lotes.get(i);
				}
			}
			
			if(quant < loteMaisProximoDeVencer.getQuant()) {
				int quantRemovida3 = loteMaisProximoDeVencer.getQuant() - quant;
				loteMaisProximoDeVencer.reduzQuant(quantRemovida3);
			}
			if(quant == loteMaisProximoDeVencer.getQuant()) {
				lotes.remove(loteMaisProximoDeVencer);
			}
			if(quant > loteMaisProximoDeVencer.getQuant()) {
				lotes.remove(loteMaisProximoDeVencer);
			}
		}
		
		if(quant <= this.quant) {
			double valor = quant*precoDeVenda;
			this.quant -= quant;
			return valor;
		}else {
			return -1;
		}
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
}
