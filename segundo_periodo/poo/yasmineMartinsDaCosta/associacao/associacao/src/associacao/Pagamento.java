package associacao;

public class Pagamento {
    Taxa taxa;
    private double valorPago;
    private int numAssociado;

    public Pagamento(Taxa taxa) {
        this.taxa = taxa;
        valorPago = 0;
    }

    public void pagarTaxa(double valor) {
        valorPago += valor;
    }

    public double getValorPago() {
        return valorPago;
    }

    public Taxa getTaxa() {
        return taxa;
    }

    public int getNumAssociado() {
        return numAssociado;
    }

    public void setNumAssociado(int numAssociado) {
        this.numAssociado = numAssociado;
    }

    public void setValorPago(double valorPago) {
        this.valorPago = valorPago;
    }
}
