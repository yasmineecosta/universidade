package associacao;

import java.util.ArrayList;

public class Associacao{
    private int numero;
    private ArrayList<Associado> associados = new ArrayList<Associado>();
    private ArrayList<Reuniao> reunioes = new ArrayList<Reuniao>();
    private ArrayList<Taxa> taxas = new ArrayList<Taxa>();
    private String nome;
    // private int relacaoAssociados;

    public Associacao(int numero, String nome) {
        this.numero = numero;
        this.nome = nome;
    }

    public Associacao() {
    }

    public int getNumero() {
        return numero;
    }

    public String getNome() {
        return nome;
    }

    public ArrayList<Associado> getAssociados() {
        return associados;
    }

    public ArrayList<Reuniao> getReunioes() {
        return reunioes;
    }

    public ArrayList<Taxa> getTaxas() {
        return taxas;
    }

    public void setNumero(int i) {
        this.numero = i;
    }

    public void setNome(String string) {
        this.nome = string;
    }

    public Associado pesquisaAssociado(int numero) {
        for(Associado associado : associados){
            if(associado.getNumero() == numero){
                return associado;
            }
        }
        return null;
    }

    public Reuniao pesquisarReuniao(long data) {
        for(Reuniao reuniao : reunioes){
            if(reuniao.getData()==(data)){
                return reuniao;
            }
        }
        return null;
    }

    public Taxa pesquisarTaxa(String nome, int vigencia) {
        for(Taxa taxa : taxas){
            if(taxa.getNome().equals(nome) && taxa.getVigencia() == vigencia){
                return taxa;
            }
        }
        return null;
    }

    public ArrayList<Reuniao> getReuniosNoPeriodo(long dataInicio, long dataFim) {
        ArrayList<Reuniao> reunioesNoPeriodo = new ArrayList<Reuniao>();
        for(Reuniao reuniao : reunioes){
            if(reuniao.getData()>=(dataInicio) && reuniao.getData()<=(dataFim)){
                reunioesNoPeriodo.add(reuniao);
            }
        }
        return reunioesNoPeriodo;
    }

    public void setReunioes(ArrayList<Reuniao> reunioes) {
        this.reunioes = reunioes;
    }
}


