package associacao.associacao.conexao;

import java.sql.Connection;

public class Conexao {
    private static final String url = "jdbc:mysql://localhost:3306/associacao";
    private static final String user = "root";
    private static final String password = "Biazinha10.Maino!";

    private static Connection con;

    public static Connection getConexao() {
        if (con == null) {
            try {
                Class.forName("com.mysql.jdbc.Driver");
                con = java.sql.DriverManager.getConnection(url, user, password);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return con;
    }
}
