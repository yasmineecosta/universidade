package teste;
import java.util.Date;
public class UsoDeConta {

	public static void main(String[] args) {
		/*
		/Scanner sc = new Scanner(System.in);
		int quant, i, ident, resp;
		double value;
		String usuario;
		ContaComum c = new ContaComum();
		//lendo info:
		System.out.println("CPF e nome: ");
		ident = sc.nextInt();
		usuario = sc.next();
		*/
		//set das datas
		Pessoa p = new Pessoa(1);
		p.setNome("Pedro");
		Date dInicial = new Date();
		Date dFinal = new Date();
		dInicial.setDate(25); 
		dInicial.setMonth(2); 
		dFinal.setDate(27); 
		dFinal.setMonth(8); 

		
		/*
		//quantidade de operacoes
		System.out.println("Quantas operacoes voce quer realizar? \n");
		quant = sc.nextInt();
		String[] transacoes = new String[quant];
		
		for(i = 0; i<quant; i++) {
			System.out.println("Operação de crédito ou débito?[1-crédito][2-débito]: ");
			resp = sc.nextInt();
        	if(resp == 1) {
        		value = sc.nextDouble();
        		c.credito(value);
        		transacoes[i] = Account(value);
        	}
        	if(resp == 2) {
        		value = sc.nextDouble();
        		c.debito(value);
        		transacoes[i] = Account(value);
        	}
		}
		//System.out.println(c.saldo);
		*/
		

		Pessoa p1 = new Pessoa(2, "João");
		
		ContaComum c = new ContaComum(1, p);
		ContaComum c1 = new ContaComum(1, p);
		
		//c1.saldo = 10;
		//c1.num = 10;
		c1.setNum(10);
		c1.setNum(10000);
		
		
		c.credito(100);
		c.debito(40);
		
		System.out.println("Dono: " + c.getDono().getCpf());
		System.out.println("Nome: " + c.getDono().getNome());
		System.out.println(c.getExtrato(dInicial,dFinal ));
				
	}

}


