package associacao;

import associacao.associacao.conexao.Conexao;

import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;


public class AssociacaoDAO {
    public AssociacaoDAO(){ 
    }

    public void inserir(Associacao associacao) {
        
        String sql = "INSERT INTO associacao (numero, nome) VALUES (?, ?)";
        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, associacao.getNumero());
            ps.setString(2, associacao.getNome());
            ps.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }

    public void removerTodos() {
        
        String sql = "DELETE FROM associacao";
        PreparedStatement ps = null;
        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }

    public Associacao pesquisarPorNumero(int numero) {

        Associacao associacao = null;
        String sql = "SELECT * FROM associacao WHERE numero = ?";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, numero);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                int anumero = rs.getInt("numero");
                String nome = rs.getString("nome");
                associacao = new Associacao(anumero, nome);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return associacao;

    }

    public Associacao pesquisarPorNome(String nome) {

        Associacao associacao = null;
        String sql = "SELECT * FROM associacao WHERE nome = ?";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, nome);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                int numero = rs.getInt("numero");
                String anome = rs.getString("nome");
                associacao = new Associacao(numero, anome);
            }
        }catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return associacao;

    }

    public ArrayList<Associacao> pesquisarTodas(){

        ArrayList<Associacao> associacoes = new ArrayList<Associacao>();
        String sql = "SELECT * FROM associacao";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                int numero = rs.getInt("numero");
                String nome = rs.getString("nome");
                Associacao associacao = new Associacao(numero, nome);
                associacoes.add(associacao);
            }
        }catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return associacoes;

    }

    public void remover(int i) {
            
            String sql = "DELETE FROM associacao WHERE num = ?";
            PreparedStatement ps = null;
    
            try {
                ps = Conexao.getConexao().prepareStatement(sql);
                ps.setInt(1, i);
                ps.executeUpdate();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    ps.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
    }

    public ArrayList<Associado> getAssociadosDaAssociacao(int numAssociacao){
        AssociadoDAO dao = new AssociadoDAO();
        ArrayList<Associado> associados = dao.getAssociadosDaAssociacao(numAssociacao);
        return associados;
    }

    public ArrayList<Taxa> getTaxasDaAssociacao(int numAssociacao){
        TaxaDAO dao = new TaxaDAO();
        ArrayList<Taxa> taxas = dao.getTaxasDaAssociacao(numAssociacao);
        return taxas;
    }

    public ArrayList<Reuniao> getReunioesDaAssociacao(int numAssociacao){
        ReuniaoDAO dao = new ReuniaoDAO();
        ArrayList<Reuniao> reunioes = dao.getReunioes(numAssociacao);
        return reunioes;
    }

    public ArrayList<Associacao> getAssociacoes() {

        ArrayList<Associacao> associacoes = new ArrayList<Associacao>();
        String sql = "SELECT * FROM associacao";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                int numero = rs.getInt("numero");
                String nome = rs.getString("nome");
                Associacao associacao = new Associacao(numero, nome);
                associacoes.add(associacao);
            }
        }catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return associacoes;
    }
 
}
