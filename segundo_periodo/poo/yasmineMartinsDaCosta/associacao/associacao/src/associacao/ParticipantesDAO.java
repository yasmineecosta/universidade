package associacao;

import associacao.associacao.conexao.Conexao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class ParticipantesDAO {
    
    public ParticipantesDAO() {
    }

    public void inserir(Reuniao reuniao, Associado associado){

        String sql = "INSERT INTO participantes (ata, datareuniao, numassociado) VALUES (?, ?, ?)";
        PreparedStatement ps = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setString(1, reuniao.getAta());
            ps.setLong(2, reuniao.getData());
            ps.setInt(3, associado.getNumero());
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

        String sql = "DELETE FROM participantes";
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

    ArrayList<Associado> getParticipantes(Reuniao reuniao){

        ArrayList<Associado> participantes = new ArrayList<Associado>();
        String sql = "SELECT * FROM participantes WHERE datareuniao = ?";
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setLong(1, reuniao.getData());
            rs = ps.executeQuery();
            while (rs.next()) {
                Associado associado = new AssociadoDAO().pesquisarPorNumero(rs.getInt("numassociado"));
                participantes.add(associado);
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
        return participantes;

    }

    ArrayList<Reuniao> getReunioesDeAssociado(Associado associado){

        ArrayList<Reuniao> reunioes = new ArrayList<Reuniao>();
        String sql = "SELECT * FROM participantes WHERE numassociado = ?";
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            ps = Conexao.getConexao().prepareStatement(sql);
            ps.setInt(1, associado.getNumero());
            rs = ps.executeQuery();
            while (rs.next()) {
                Reuniao reuniao = new Reuniao();
                reunioes.add(reuniao);
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
        return reunioes;
    }
}
