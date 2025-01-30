package banco;

public class UsoDeConta {

	public static void main(String[] args) {
		
		Pessoa p = new Pessoa(1);
		p.setNome("Pedro");
		
		Pessoa p1 = new Pessoa(2, "João");
		
		ContaComum c = new ContaComum(1, p);
		ContaComum c1 = new ContaComum(1, p);
		
//		c1.saldo = 10;
//		c1.num = 10;
		c1.setNum(10);
		c1.setNum(10000);

	
		c.credito(100);
		c.debito(40);
		
		System.out.println("Dono: " + c.getDono().getCpf());
		System.out.println("Nome: " + c.getDono().getNome());
		System.out.println(c.getExtrato());

	}

}
