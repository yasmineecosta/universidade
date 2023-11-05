package associacao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import associacao.associacao.conexao.Conexao;


public class AssociadoDAO {
    public AssociadoDAO() {
    }

    public void inserir(Associacao associado) {
		Connection con;
        String sql = "INSERT INTO associado (numero, numassociacao, nome, telefone, nascimento, dataassociacao, remido, dataremissao) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
		PreparedStatement ps = null;
        
		try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, associado.getNumero());
            ps.setInt(2, associado.getNumAssociacao());
            ps.setString(3, associado.getNome());
            ps.setString(4, associado.getTelefone());
            ps.setLong(5, associado.getNascimento());
            ps.setLong(6, associado.getDataAssociacao());
            if(associado instanceof AssociadoRemido){
                ps.setInt(7, 1);
                ps.setLong(8, ((AssociadoRemido)associado).getDataRemissao());    
            }else{
                ps.setInt(7, 0);
                ps.setLong(8, 0);
            }
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

    
    public void remover(int num) {
        
        String sql = "DELETE FROM associacao WHERE numero = ?";
        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
			ps.setInt(1, num);
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

        String sql = "DELETE FROM associado";
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
	
    public Associacao pesquisarPorNumero(int num) {

        Associacao associacao = null;
        String sql = "SELECT * FROM associacao WHERE numero = ?";
        PreparedStatement ps = null;

		try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, num);
            ResultSet rs = ps.executeQuery();
            if(rs.next()){
                if(rs.getInt("remido") == 1){
                    associado = new AssociadoRemido(rs.getInt("numero"), rs.getString("nome"), rs.getString("telefone"), rs.getLong("nascimento"), rs.getLong("dataassociacao"), rs.getLong("dataremissao"));
                }else{
                    associado = new Associado(rs.getInt("numero"), rs.getString("nome"), rs.getString("telefone"), rs.getLong("nascimento"), rs.getLong("dataassociacao"));
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                ps.close();
            }catch(Exception e){
                e.printStackTrace();
            }
        }

        return associado; 
    }

    protected ArrayList<Associado> getAssociadosDaAssociacao(int numAssociacao){
        
        ArrayList<Associado> associados = new ArrayList<Associado>();
        String sql = "SELECT * FROM associado WHERE numassociacao = ?";
        PreparedStatement ps = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, numAssociacao);
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                if(rs.getInt("remido") == 1){
                    associados.add(new AssociadoRemido(rs.getInt("numero"), rs.getString("nome"), rs.getString("telefone"), rs.getLong("nascimento"), rs.getLong("dataassociacao"), rs.getLong("dataremissao")));
                }else{
                    associados.add(new Associado(rs.getInt("numero"), rs.getString("nome"), rs.getString("telefone"), rs.getLong("nascimento"), rs.getLong("dataassociacao")));
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                ps.close();
            }catch(Exception e){
                e.printStackTrace();
            }
        }

        return associados;
    }

    public ArrayList<Pagamento> getPagamentosDeAssociado(int numAssociado){

        ArrayList<Pagamento> pagamentos = new PagamentoDAO().getPagamentos(numAssociado);

        return pagamentos;
    }
    
}
