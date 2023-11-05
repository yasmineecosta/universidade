package estoqueComProdutoPerecivelExcecoes;

import java.util.ArrayList;
import java.time.Clock;
import java.time.Instant;
import java.time.ZoneId;
import java.util.Collections;
import java.util.Date;
public class ProdutoPerecivel extends Produto{

	ArrayList<Lote> lotes = new ArrayList<Lote>();
	int quantLotes = 0;
	public ProdutoPerecivel(int cod, String desc, int min, double lucro, Fornecedor forn) {
		super(cod, desc, min, lucro, forn);
	}

	public void compraPerecivel(int quant, double val, Date val2) {
		//compraProdutoPerecivelComValidadeMenorQueDataAtual
		Lote lt = new Lote(quant, val2);
		precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
		this.quant += quant;
		precoDeVenda = (precoDeCompra * (1 + lucro));
		quantLotes++;
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

}
