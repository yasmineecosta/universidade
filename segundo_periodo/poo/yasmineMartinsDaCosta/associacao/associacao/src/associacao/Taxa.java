package associacao;

public class Taxa{
    
    private String nome;
    private int vigencia;
    private double valorAno;
    private int parcelas;
    private boolean admnistrativa;
    private int NumAssociacao;

    public int getNumAssociacao() {
        return NumAssociacao;
    }

    public void setNumAssociacao(int numAssociacao) {
        NumAssociacao = numAssociacao;
    }

    public Taxa(String nome, int vigencia, double valorAno, int parcelas, boolean admnistrativa) {
        this.nome = nome;
        this.vigencia = vigencia;
        this.valorAno = valorAno;
        this.parcelas = parcelas;
        this.admnistrativa = admnistrativa;
    }

    public String getNome() {
        return nome;
    }

    public int getVigencia() {
        return vigencia;
    }

    public double getValorAno() {
        return valorAno;
    }

    public int getParcelas() {
        return parcelas;
    }

    public boolean isAdmnistrativa() {
        return admnistrativa;
    }

    public int getparcelas() {
        return parcelas;
    }

    public void setVigencia(int vigencia2) {
        vigencia = vigencia2;
    }
}

// Calcula o total de taxas previstas para um dado ano, em uma associação.

// Registra o pagamento de uma taxa, em uma associação, dentro uma determinada competência, para um associado. O valor a ser pago não pode ser menor que uma parcela, embora não precise ser exatamente duas parcelas. Uma parcela de R$20,00 por mês aceita um pagamento de R$30,00, sendo uma parcela completa e um pedaço da próxima. Associados remidos não deveriam mais realizar pagamentos de taxas administrativas vigentes em datas antes da sua remissão, gerando exceção de AssociadoJaRemido se houver tentativa de se pagar algo para esse caso. Caso o valor a ser pago seja menor que o mínimo (não sendo o ultimo do ano!) ou gerando pagamento maior que a taxa anual, gerar exceção de ValorInvalido. Lembrar de verificar valores negativos.
