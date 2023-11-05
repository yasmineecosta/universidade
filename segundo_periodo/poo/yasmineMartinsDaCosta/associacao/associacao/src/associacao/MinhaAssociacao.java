package associacao;

import java.util.ArrayList;

public class MinhaAssociacao implements InterfaceAssociacao{
    public ArrayList<Associacao> associacoes = new ArrayList<Associacao>();
    public ArrayList<Reuniao> reunioes = new ArrayList<Reuniao>();
    public ArrayList<Associado> associados = new ArrayList<Associado>();
    public ArrayList<Taxa> taxas = new ArrayList<Taxa>();

    @Override
    public double calcularFrequencia(int numAssociado, int numAssociacao, long inicio, long fim) throws AssociadoNaoExistente, ReuniaoNaoExistente, AssociacaoNaoExistente {
        Associacao asc = pesquisar(numAssociacao);
        if(asc == null){
            throw new AssociacaoNaoExistente();
        }

        Associado asd = asc.pesquisarAssociado(numAssociado);
        if(asd == null){
            throw new AssociadoNaoExistente();
        }

        double freq = 0;
        int cont = 0;

        for(int i=0; i<asc.reunioes.size(); i++){
            if(asc.reunioes.get(i).ata.isBlank() || asc.reunioes.get(i).ata.isEmpty() || asc.reunioes.get(i).ata == null){
                throw new ReuniaoNaoExistente();
            }
        }

        for(int i=0; i<asc.reunioes.size(); i++){
            if(asc.reunioes.get(i).data >= inicio && asc.reunioes.get(i).data <= fim){
                cont++;
                for(Associado associado : asc.reunioes.get(i).associados){
                    if(numAssociado == associado.num_pos){
                        freq++;
                        break;
                    }
                }
            }
        }
        return freq/cont;
    }

    @Override
    public void registrarFrequencia(int codigoAssociado, int numAssociacao, long dataReuniao) throws AssociadoNaoExistente, ReuniaoNaoExistente, AssociacaoNaoExistente, FrequenciaJaRegistrada, FrequenciaIncompativel {
        Associacao asc = pesquisar(numAssociacao);
        if(asc == null){
            throw new AssociacaoNaoExistente();
        }

        Associado asd = asc.pesquisarAssociado(codigoAssociado);
        if(asd == null){
            throw new AssociadoNaoExistente();
        }

        for(int i=0; i<asc.reunioes.size(); i++){
            if(asc.reunioes.get(i).ata.isBlank() || asc.reunioes.get(i).ata.isEmpty() || asc.reunioes.get(i).ata == null){
                throw new ReuniaoNaoExistente();
            }
        }
        
        if(asd.dataAssociacao < dataReuniao){
            throw new FrequenciaIncompativel();
        }

        boolean flag = false;

        for(Reuniao r : asc.reunioes){
            if(r.data == dataReuniao){
                flag = true;

                for(Integer cod : r.freqParticipantes){
                    if(cod == codigoAssociado){
                        throw new FrequenciaJaRegistrada();
                    }
                }
                r.freqParticipantes.add(codigoAssociado);
            }
        }

        if(!flag){
            throw new FrequenciaIncompativel();
        }
        
        for(int i=0; i<asc.reunioes.size(); i++){
            if(asc.reunioes.get(i).data == dataReuniao && asc.reunioes.get(i).associados.contains(asd)){
                throw new FrequenciaJaRegistrada();
            }
        }
        for(int i=0; i<asc.reunioes.size(); i++){
            if(asc.reunioes.get(i).data == dataReuniao){
                asc.reunioes.get(i).associados.add(asd);
                break;
            }
        }
    }

    @Override
    public void registrarPagamento(int numAssociacao, String taxa, int vigencia, int numAssociado, long data, double valor) throws AssociacaoNaoExistente, AssociadoNaoExistente, AssociadoJaRemido, TaxaNaoExistente, ValorInvalido {
        Associacao asc = pesquisar(numAssociacao);
        if(asc == null){
            throw new AssociacaoNaoExistente();
        }

        Associado asd = asc.pesquisarAssociado(numAssociado);
        if(asd == null){
            throw new AssociadoNaoExistente();
        }

        Taxa t = asc.pesquisarT(taxa, vigencia);

        if(t == null){
            throw new TaxaNaoExistente();
        }
        
        Pagamento pagamento = null;
        for(int i=0; i<asd.pagamentos.size(); i++){
            if((asd.pagamentos.get(i).taxa.nome == taxa) && (asd.pagamentos.get(i).taxa.vigencia == vigencia)){
                pagamento = asd.pagamentos.get(i);
            }
        }

        if(asd instanceof AssociadoRemido && t.adms && ((AssociadoRemido)asd).remissao<=data){
            throw new AssociadoJaRemido();
        }

        double valorParcela = t.valorAno/t.parcelas;
        double valorRestante = t.valorAno - pagamento.valorPago;
        
        if(valor < valorParcela && valorRestante > valorParcela || valor > t.valorAno)
            throw new ValorInvalido();

        pagamento.pagarTaxa(valor);
    
    }

    @Override
    public double somarPagamentoDeAssociado(int numAssociacao, int numAssociado, String nomeTaxa, int vigencia, long inicio, long fim) throws AssociacaoNaoExistente, AssociadoNaoExistente, TaxaNaoExistente {
        
        double pagamento = 0;
        Associacao asc = pesquisar(numAssociacao);
        if(asc == null){
            throw new AssociacaoNaoExistente();
        }
       
        Associado asd = asc.pesquisarAssociado(numAssociado);
        if(asd == null){
            throw new AssociadoNaoExistente();
        }

        Taxa t = asc.pesquisarT(nomeTaxa, vigencia);
        if(t == null){
            throw new TaxaNaoExistente();
        }

        pagamento = asd.getPagamento(t);

        return pagamento;
        
    }

    @Override
    public double calcularTotalDeTaxas(int numAssociacao, int vigencia) throws AssociacaoNaoExistente, TaxaNaoExistente {
        Associacao asc = pesquisar(numAssociacao);
        if(asc == null){
            throw new AssociacaoNaoExistente();
        }
        
        double total = 0;
        for(Taxa t : asc.taxas){
            if(t.vigencia == vigencia){
                total += t.valorAno;
            }
        }

        if(total == 0){
            throw new TaxaNaoExistente();
        }
        return total;
    }

    @Override
    public void adicionar(Associacao a) throws AssociacaoJaExistente, ValorInvalido {
        if(a == null || a.nome == null || a.nome.isBlank() || a.nome.isEmpty() || a.num < 0){
            throw new ValorInvalido();
        }
        
        for(Associacao associacao : associacoes){
            if(associacao.num == a.num){
                throw new AssociacaoJaExistente();
            }
        }
        associacoes.add(a);
        
    }

    @Override
    public void adicionar(int associacao, Associado a) throws AssociacaoNaoExistente, AssociadoJaExistente, ValorInvalido {
        if(associacao < 0 || a == null || a.nome.isBlank() || a.nome.isEmpty() || a.nome == null){
            throw new ValorInvalido();
        }    

        if(a.telefone.isBlank() || a.telefone.isEmpty() || a.telefone == null){
            throw new ValorInvalido();
        }
        
        if(a.num_pos <= 0 || a.nascimento <= 0 || a.dataAssociacao <= 0){
            throw new ValorInvalido();
        }
        
        Associacao asc = pesquisar(associacao);
        
        if(asc==null){
            throw new AssociacaoNaoExistente();
        }

        for(int i=0; i<asc.associados.size(); i++){
            if(asc.associados.get(i).num_pos == a.num_pos){
                throw new AssociadoJaExistente();
            }
        }
        a.setPagamentos(asc.taxas);
        asc.associados.add(a);
    }

    @Override
    public void adicionar(int associacao, Reuniao r) throws AssociacaoNaoExistente, ReuniaoJaExistente, ValorInvalido {
        if(associacao < 0 || r == null || r.ata.isBlank() || r.ata.isEmpty() || r.ata == null){
            throw new ValorInvalido();
        }

        Associacao asc = pesquisar(associacao);
        if(asc == null){
            throw new AssociacaoNaoExistente();
        }

        for(int i=0; i<asc.reunioes.size(); i++){
            if(asc.reunioes.get(i).ata.equals(r.ata)){
                throw new ReuniaoJaExistente();
            }
        }
        asc.reunioes.add(r);
    }

    @Override
    public void adicionar(int associacao, Taxa t) throws AssociacaoNaoExistente, TaxaJaExistente, ValorInvalido {
        if(associacao < 0 || t == null || t.nome.isBlank() || t.nome.isEmpty() || t.nome == null){
            throw new ValorInvalido();
        }

        if(t.parcelas <= 0 || t.vigencia <= 0 || t.valorAno <= 0){
            throw new ValorInvalido();
        }

        Associacao asc = pesquisar(associacao);

        for(int i=0; i<associacoes.size(); i++){
            if(associacoes.get(i).num == associacao){
                asc = associacoes.get(i);
            }
        }

        if(asc == null){
            throw new AssociacaoNaoExistente();
        }

        for(int i=0; i<asc.taxas.size(); i++){
            if(asc.taxas.get(i).nome.equals(t.nome) && asc.taxas.get(i).vigencia == t.vigencia){
                throw new TaxaJaExistente();
            }
        }
        asc.taxas.add(t);

        for(int i=0; i<asc.associados.size(); i++){
            if(asc.associados.get(i).verificaTaxa(t) == false){
                asc.associados.get(i).pagamentos.add(new Pagamento(t));
            }
        }
    }

    public Associacao pesquisar(int cod){
        for(Associacao a : associacoes){
            if(a.num == cod){
                return a;
            }
        }
        return null;
    }
    
    public Taxa pesquisarTaxa(int vigencia){
        for(Taxa t : taxas){
            if(t.vigencia == vigencia){
                return t;
            }
        }
        return null;
    }
}
