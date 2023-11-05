package associacao;

// import associacao.associacao.conexao;
import associacao.associacao.conexao.Conexao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class PagamentoDAO {
    public PagamentoDAO(){
    }

    public void inserir(Pagamento pagamento){

        String sql = "INSERT INTO pagamento (nometaxa, numassociado, valorpago, codpagamento) VALUES (?, ?, ?, ?)";

        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, pagamento.getTaxa().getNome());
            ps.setInt(2, pagamento.getNumAssociado());
            ps.setDouble(3, pagamento.getValorPago());
            ps.setString(4, pagamento.getTaxa().getNome()+"-"+pagamento.getNumAssociado()+"-"+pagamento.getTaxa().getVigencia());
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

        String sql = "DELETE FROM pagamento";
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

    ArrayList<Pagamento> getPagamentos(int numAssociado){

        String sql = "SELECT * FROM pagamento WHERE numassociado = ?";
        PreparedStatement ps = null;
        ResultSet rs = null;
        ArrayList<Pagamento> pagamentos = new ArrayList<Pagamento>();

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, numAssociado);
            rs = ps.executeQuery();
            while(rs.next()){
                String nomeTaxa = rs.getString("nometaxa");
                double valorPago = rs.getDouble("valorpago");
                TaxaDAO taxaDao = new TaxaDAO();
                Taxa taxa = taxaDao.pesquisarPorNome(nomeTaxa);
                Pagamento pagamento = new Pagamento(taxa);
                pagamento.setNumAssociado(numAssociado);
                pagamento.setValorPago(valorPago);
                pagamentos.add(pagamento);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                ps.close();
                rs.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return pagamentos;
    }

    public Pagamento pesquisaPorCodpagamento(String cod){

        Pagamento pagamento = null;
        String sql = "SELECT * FROM pagamento WHERE codpagamento = ?";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, cod);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                String nomeTaxa = rs.getString("nometaxa");
                int numAssociado = rs.getInt("numassociado");
                double valorPago = rs.getDouble("valorpago");
                TaxaDAO taxaDao = new TaxaDAO();
                Taxa taxa = taxaDao.pesquisarPorNome(nomeTaxa);
                pagamento = new Pagamento(taxa);
                pagamento.setNumAssociado(numAssociado);
                pagamento.setValorPago(valorPago);
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
        return pagamento;
    }

    public void atualizar(Pagamento pagamento){

        String sql = "UPDATE pagamento SET valorpago = ? WHERE codpagamento = ?";

        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setDouble(1, pagamento.getValorPago());
            ps.setString(2, pagamento.getTaxa().getNome()+"-"+pagamento.getNumAssociado()+"-"+pagamento.getTaxa().getVigencia());
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
}
