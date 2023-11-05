package estoqueComProdutoPerecivelExcecoes;

public class ProdutoInexistente extends Exception{
    public ProdutoInexistente(){
        super("Produto inexistente!");
    }
}
