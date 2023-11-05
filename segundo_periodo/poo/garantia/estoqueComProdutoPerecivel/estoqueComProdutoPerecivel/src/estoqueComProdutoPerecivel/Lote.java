package estoqueComProdutoPerecivel;

import java.util.Date;

public class Lote {
	int quantidade;
	Date validade;
	double value;

	public Lote(int quant, Date val, double valor) {
		quantidade = quant;
		validade = val;
		value = valor;
	}

	public Lote() {
		
	}
	
	public int getQuant() {
		return quantidade;
	}
	
	public Date getValidade() {
		return validade;
	}

	public double getValue() {
		return value;
	}
	
	public void reduzQuant(int quant) {
		quantidade -= quant;
	}
}
