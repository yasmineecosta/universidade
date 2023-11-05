package estoqueComProdutoPerecivel;
import java.util.Date;
import java.util.Objects;

public class Produto {
		private int cod;
		private String descricao;
		protected double precoDeCompra;
		protected double precoDeVenda;
		protected double lucro;
		protected int quant;
		protected int min;
		protected Fornecedor forn;
		
		public Produto(int cod, String descricao, int min, double lucro, Fornecedor forn) {
			this.cod = cod;
			this.descricao = descricao;
			this.precoDeCompra = 0;
			this.precoDeVenda = 0;
			this.quant = 0;
			this.min = min;
			this.lucro = lucro;
			this.forn = forn;
		}
		
		public double getPrecoDeCompra() {
			return precoDeCompra;
		}

		public double getPrecoDeVenda() {
			return precoDeVenda;
		}

		public int getCodigo() {
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
		
		public boolean abaixoDoMinimo(){
			if(this.quant < this.min)
				return true;
			return false;
		}

		public boolean compra(int quant, double val){
			if(quant>0 && val>0 && ((quant+this.quant)>=this.min)) {
				precoDeCompra = ((this.quant * precoDeCompra) + quant * val) / (this.quant + quant);
				this.quant += quant;
				precoDeVenda = (precoDeCompra * (1 + lucro));
				return true;
			}
			return false;
		}
		/*
		public double venda(int quant) {
			if(quant<=this.quant && quant >0){
				this.quant -= quant;
				return (quant*precoDeVenda);
			}
			return -1;
		} 
		*/
}