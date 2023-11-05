package estoque;

public class Produto {
	private int cod;
	private String descricao;
	private double precoDeCompra;
	private double precoDeVenda;
	private double lucro;
	private int quant;
	private int min;
	private Fornecedor forn;
	
	public Produto(int cod, String descricao, int min, double lucro, Fornecedor forn) {
		this.cod = cod;
		this.descricao = descricao;
		this.min = min;
		this.lucro = lucro;
		this.forn = forn;
	}
	
	public int getCod() {
		if(cod <= 0){
			return 0;
		}
		return cod;
	}
	
	public String getDesc() {
		return descricao;
	}
	
	public double getLucro() {
		return lucro;
	}
	
	public int getQuant() {
		return this.quant;
	}
	
	public int getMin() {
		return min;
	}
	
	public Fornecedor getForn() {
		return forn;
	}
	
	public void compra(int quant, double val) {
			precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
			this.quant += quant;
			precoDeVenda = (precoDeCompra * (1 + lucro));
	}
	
	public double venda(int quant) {
		if (quant > 0) {
			if (quant <= this.quant) {
				this.quant = this.quant - quant;
				return (quant * precoDeVenda);
			} else {
			return -1;
			}
		}
		return (quant*precoDeVenda);
	}
}