package yasmineMartinsDaCostaESilva.estoque;
import java.util.ArrayList;

public class Estoque {
	Produto[] produtos = new Produto[50];
	int pos = 0;
	
	public void incluir(Produto prod) {
		produtos[pos] = new Produto(prod.getCod(), prod.getDesc(), prod.getMin(), prod.getLucro(), prod.getForn());
		produtos[pos++] = prod;
	}
	
	public void comprar(int cod, int quant, double preco) {
		for(int i=0; i<pos; i++) {
			
		}
	}
	
	public double vender(int cod, int quant) {
		for (int i = 0; i < pos; i++) {
			if (produtos[i].getCod() == cod) {
				return produtos[i].venda(quant);
			}
		}
		return -1;
	}
	
	public int quantidade(int cod) {
		for(int i = 0; i < pos ; i++) {
			if(produtos[i].getCod() == cod) {
				return produtos[i].getQuant();
			}
		}
		return -1;			
	}
	
	public Fornecedor fornecedor(int cod) {
		for(int i=0; i<pos; i++) {
			if(produtos[i].getCod() == cod) {
				return produtos[i].getForn();
			}
		}
		return null;
	}
	
	public Produto[] estoqueAbaixoDoMinimo() {
		ArrayList<Produto> estMin = new ArrayList<>();
		int min = 0;
		
		for(int i=0; i<pos; i++) {
			if(produtos[i].getMin() > produtos[i].getQuant()) {
				estMin.add(produtos[i]);
				min = 1;
			}
		}
		
		Produto[] sizeV = new Produto[estMin.size()];
			for(int i=0; i<estMin.size(); i++) {
				sizeV[i] = estMin.get(i);
			}
			if(min==1) {
				return sizeV;
			}else {
				return null;
			}
	}
}
