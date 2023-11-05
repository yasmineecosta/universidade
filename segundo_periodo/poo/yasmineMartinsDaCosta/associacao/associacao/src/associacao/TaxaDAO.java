package associacao;

import associacao.associacao.conexao.Conexao;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class TaxaDAO {
    
    public TaxaDAO() {
    }

    public void inserir(Taxa taxa){

        String sql = "INSERT INTO taxa (nome, numassociacao, vigencia, valorano, parcelas, administrativa) VALUES (?, ?, ?, ?, ?, ?)";
        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, taxa.getNome());
            ps.setInt(2, taxa.getNumAssociacao());
            ps.setLong(3, taxa.getVigencia());
            ps.setDouble(4, taxa.getValorAno());
            ps.setDouble(5, taxa.getParcelas());
            ps.setBoolean(6, taxa.isAdmnistrativa());
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

    public void remover(String nome){

        String sql = "DELETE FROM taxa WHERE nome = ?";
        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, nome);
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

    public void removerTodos(){

        String sql = "DELETE FROM taxa";
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

    public Taxa pesquisarPorNome(String nome){

        String sql = "SELECT * FROM taxa WHERE nome = ?";
        PreparedStatement ps = null;
        Taxa taxa = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, nome);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                String anome = rs.getString("nome");
                int vigencia = rs.getInt("vigencia");
                double valorano = rs.getDouble("valorano");
                int parcelas = rs.getInt("parcelas");
                boolean administrativa = rs.getBoolean("administrativa");
                taxa = new Taxa(anome, vigencia, valorano, parcelas, administrativa);
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            try {
                ps.close();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        return taxa;
    }

    public ArrayList<Taxa> pesquisarTodas(){

        String sql = "SELECT * FROM taxa";
        PreparedStatement ps = null;
        ArrayList<Taxa> taxas = new ArrayList<>();

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                String nome = rs.getString("nome");
                int vigencia = rs.getInt("vigencia");
                double valorano = rs.getDouble("valorano");
                int parcelas = rs.getInt("parcelas");
                boolean administrativa = rs.getBoolean("administrativa");
                taxas.add(new Taxa(nome, vigencia, valorano, parcelas, administrativa));
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            try {
                ps.close();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        return taxas;
    }

    protected ArrayList<Taxa> getTaxasDaAssociacao(int numAssociacao){

        ArrayList<Taxa> taxas = new ArrayList<>();
        String sql = "SELECT * FROM taxa WHERE numassociacao = ?";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, numAssociacao);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                String nome = rs.getString("nome");
                int vigencia = rs.getInt("vigencia");
                double valorano = rs.getDouble("valorano");
                int parcelas = rs.getInt("parcelas");
                boolean administrativa = rs.getBoolean("administrativa");
                taxas.add(new Taxa(nome, vigencia, valorano, parcelas, administrativa));
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            try {
                ps.close();
            }catch (Exception e){
            }
        }
        return taxas;
    }

    public void setPagamentosDeTaxa(Taxa taxa, ArrayList<Associado> associados){

        PagamentoDAO pagamentoDao = new PagamentoDAO();

        for(Associado associado : associados){
            Pagamento p = new Pagamento(taxa);
            p.setNumAssociado(associado.getNumero());
            p.setValorPago(0);
            pagamentoDao.inserir(p);
        }

    }
    
}
