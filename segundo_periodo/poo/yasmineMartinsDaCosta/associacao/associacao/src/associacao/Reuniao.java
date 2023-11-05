package associacao;

import java.util.ArrayList;

public class Reuniao {
    private long data;
    private String ata;
    private ArrayList<Associado> participantes = new ArrayList<Associado>();
    private int numAssociacao;

    public Reuniao(long data, String ata) {
        this.data = data;
        this.ata = ata;
    }

    public Reuniao() {
    }

    public long getData() {
        return data;
    }       

    public String getAta() {
        return ata;
    }

    public ArrayList<Associado> getParticipantes() {
        return participantes;
    }

    public void setNumAssociacao(int numAssociacao) {
        this.numAssociacao = numAssociacao;
    }

    public int getNumAssociacao() {
        return numAssociacao;
    }

    public void setData(long long1) {
        this.data = long1;
    }

    public void setAta(String string) {
        this.ata = string;
    }
}

// Adiciona uma reunião a uma associação. Valida todos os campos para evitar dados não preenchidos.
