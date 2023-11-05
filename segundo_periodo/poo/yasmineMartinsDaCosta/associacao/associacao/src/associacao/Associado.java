package associacao;

import java.util.ArrayList;
import java.util.Date;

public class Associado{
    int numero;
    String nome;
    String telefone;
    long nascimento;
    long dataAssociacao;
    ArrayList<Pagamento> pagamentos = new ArrayList<Pagamento>();
    int numAssociacao;

     public void setNumAssociacao(int numAssociacao) {
        this.numAssociacao = numAssociacao;
     }
    
     public int getNumAssociacao() {
        return numAssociacao;
     }
   
     public Associado(int numero, String nome, String telefone, long nascimento, long dataAssociacao) {
           this.numero = numero;
           this.nome = nome;
           this.telefone = telefone;
           this.nascimento = nascimento;
           this.dataAssociacao = dataAssociacao;
     
     }
   
       public Associado() {
       }
   
       public void setPagamentos(ArrayList<Taxa> taxas){
             for(Taxa taxa : taxas){
                  Pagamento pagamento = new Pagamento(taxa);
                  pagamentos.add(pagamento);
             }
       }
   
   
       public int getNumero() {
            return numero;
       }   
   
       public String getNome() {
            return nome;
       }
   
       public String getTelefone() {
            return telefone;
       }
   
       public long getNascimento() {
            return nascimento;
       }
   
       public long getDataAssociacao() {
            return dataAssociacao;
       }
   
        public ArrayList<Pagamento> getPagamentos() {
             return pagamentos;
        }
   
        public double getPagamento(Taxa taxa){
             for(Pagamento pagamento : pagamentos){
                  if(pagamento.getTaxa().equals(taxa)){
                       return pagamento.getValorPago();
                  }
             }
             return 0;
        }
   
        public boolean verificaTaxa(Taxa taxa){
             for(Pagamento pagamento : pagamentos){
                  if(pagamento.getTaxa().equals(taxa)){
                       System.out.println("Taxa ja registrada");
                       return true;
                  }
             }
             return false;
        }
}
// Calcula o total de pagamentos realizado por um associado, em uma associação, para uma taxa, que possui uma vigência, dentro de um certo período de tempo.

// Registra a frequencia de um associado em uma reunião. não deveria registrar participacao em reunioes acontecidas antes da sua filiacao na associação.

// Calcula a frequência de um associado nas reuniões ocorridas durante um determinado período, retornando um número entre 0 e 1 (ex: 0,6, indicando que o associado participou de 60% das reuniões.
