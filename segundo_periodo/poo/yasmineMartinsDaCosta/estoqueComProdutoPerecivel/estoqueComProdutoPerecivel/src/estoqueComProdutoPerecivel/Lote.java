package estoqueComProdutoPerecivel;

import java.util.Date;

public class Lote {
	int quantidade;
	Date validade;

	public Lote(int quant, Date val) {
		quantidade = quant;
		validade = val;
	}

	public Lote() {
		
	}
	
	public int getQuant() {
		return quantidade;
	}
	
	public Date getValidade() {
		return validade;
	}
	
	public void reduzQuant(int quant) {
		quantidade -= quant;
	}
}
