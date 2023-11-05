package associacao;

// import associacao.associacao.conexao;
import associacao.associacao.conexao.Conexao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class ReuniaoDAO {
     public ReuniaoDAO() {
    }

    public void inserir(Reuniao reuniao){
        String sql = "INSERT INTO reuniao (data, numassociacao, ata) VALUES (?, ?, ?)";
        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setLong(1, reuniao.getData());
            ps.setInt(2, reuniao.getNumAssociacao());
            ps.setString(3, reuniao.getAta());
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

        String sql = "DELETE FROM reuniao";
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

    ArrayList<Reuniao> getReunioes(int numAssociacao){

        ArrayList<Reuniao> reunioes = new ArrayList<Reuniao>();
        String sql = "SELECT * FROM reuniao WHERE numAssociacao = ?";
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, numAssociacao);
            rs = ps.executeQuery();
            while (rs.next()) {
                Reuniao reuniao = new Reuniao();
                reuniao.setData(rs.getLong("data"));
                reuniao.setNumAssociacao(rs.getInt("numassociacao"));
                reuniao.setAta(rs.getString("ata"));
                reunioes.add(reuniao);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                rs.close();
                ps.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return reunioes;

    }

    public ArrayList<Associado> getParticipantesDeReuniao(long data, String ata){

        ArrayList<Associado> participantes = new ArrayList<Associado>();
        Reuniao reuniao = new Reuniao(data, ata);
        ParticipantesDAO participantesDao = new ParticipantesDAO();
        participantes = participantesDao.getParticipantes(reuniao);
        
        return participantes;
    }

    ArrayList<Reuniao>getReunioesDeAssociado(int numAssociado){
        //ArrayList<Reuniao> reunioes = new ArrayList<Reuniao>();
        return null;
    }

    public Reuniao pesquisarPorData(long dataReuniao) {
        
        Reuniao reuniao = null;
        String sql = "SELECT * FROM reuniao WHERE data = ?";
        PreparedStatement ps = null;
        ResultSet rs = null;

        try{
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setLong(1, dataReuniao);
            rs = ps.executeQuery();
            if(rs.next()){
                reuniao = new Reuniao();
                reuniao.setData(rs.getLong("data"));
                reuniao.setNumAssociacao(rs.getInt("numassociacao"));
                reuniao.setAta(rs.getString("ata"));
            }
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                rs.close();
                ps.close();
            }catch(Exception e){
                e.printStackTrace();
            }
        }
        return reuniao;
    }
}
