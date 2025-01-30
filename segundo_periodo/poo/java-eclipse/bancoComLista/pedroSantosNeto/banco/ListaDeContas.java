package pedroSantosNeto.banco;

public class ListaDeContas {

	private ContaComum conta = null;
	private ListaDeContas prox = null;
	
	public void inserir(ContaComum c) {
		if (conta != null) {
			prox.inserir(c);
		} else {
			conta = c;
			prox = new ListaDeContas();
		}
		
	}
	
	public ContaComum pesquisar(int n) {
		if (prox == null) {
			return null;
		}
		if (conta.getNum() == n) {
			return conta;
		} else {
			return prox.pesquisar(n);
		}
	} 
}
