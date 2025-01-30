package pedroSantosNeto.banco;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class BancoTest {

	@Test
	void testarDepositoESaque() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		Pessoa p2 = new Pessoa(2);
		p2.setNome("João");
		ContaComum c2 = new ContaComum(102, p2);
		
		b.inserir(c1);
		b.inserir(c2);
		
		b.deposito(101, 900);
		b.deposito(102, 500);
		
		assertEquals(900, b.saldo(101));
		assertEquals(500, b.saldo(102));
		
		b.saque(101, 90);
		b.saque(102, 50);

		assertEquals(810, b.saldo(101));
		assertEquals(450, b.saldo(102));
		
	}
	
	@Test
	void testarTranferencia() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		Pessoa p2 = new Pessoa(2);
		p2.setNome("João");
		ContaComum c2 = new ContaComum(102, p2);
		
		b.inserir(c1);
		b.inserir(c2);
		
		b.deposito(101, 900);
		b.deposito(102, 500);
		b.transfere(101, 102, 400);
		
		assertEquals(500, b.saldo(101));
		assertEquals(900, b.saldo(102));
	}
	
	@Test
	void testarTranferenciaContaInexistente() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		Pessoa p2 = new Pessoa(2);
		p2.setNome("João");
		ContaComum c2 = new ContaComum(102, p2);
		
		b.inserir(c1);
		b.inserir(c2);
		
		b.deposito(101, 900);
		b.deposito(102, 500);
		b.transfere(101, 103, 400);
		
		assertEquals(900, b.saldo(101));
		assertEquals(500, b.saldo(102));
		
		b.transfere(103, 101, 400);
		
		assertEquals(900, b.saldo(101));
		assertEquals(500, b.saldo(102));
	}
	
	@Test
	void testarTranferenciaContaSaldoInsuficiente() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		Pessoa p2 = new Pessoa(2);
		p2.setNome("João");
		ContaComum c2 = new ContaComum(102, p2);
		
		b.inserir(c1);
		b.inserir(c2);
		
		b.deposito(101, 900);
		b.deposito(102, 500);
		b.transfere(101, 102, 901);
		
		assertEquals(900, b.saldo(101));
		assertEquals(500, b.saldo(102));
	}
	
	
	
	@Test
	void testarDepositoESaqueEmContaInexistente() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		Pessoa p2 = new Pessoa(2);
		p2.setNome("João");
		ContaComum c2 = new ContaComum(102, p2);
		
		b.inserir(c1);
		b.inserir(c2);
		
		b.deposito(103, 900);
		assertEquals(-9999999, b.saldo(103));
		
		b.saque(103, 90);
		assertEquals(-9999999, b.saldo(103));
		
		assertEquals("", b.extrato(103));
	}
	
	@Test
	void testarExtrato() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		b.inserir(c1);
		
		b.deposito(101, 900);		
		b.saque(101, 90);
		String extrato = "Credito: 900.0 Saldo: 900.0\nDebito: 90.0 Saldo: 810.0\n";
		assertEquals(extrato, b.extrato(101));
	}
	
	@Test
	void testarSaqueAcimaDoSaldo() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		b.inserir(c1);
		
		b.deposito(101, 900);		
		b.saque(101, 901);
		assertEquals(900, b.saldo(101));
	}
	
	@Test
	void testarDadosDoDonoDaConta() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		
		b.inserir(c1);
		assertEquals(1, b.cpfDoDono(101));
		assertEquals("Pedro", b.nomeDoDono(101));

		assertEquals(0, b.cpfDoDono(103));
		assertEquals(null, b.nomeDoDono(103));
    }
	
	
	@Test
	void testarInclusaoDeContaJaCadastrada() {
		Banco b = new Banco();
		
		Pessoa p1 = new Pessoa(1);
		p1.setNome("Pedro");
		ContaComum c1 = new ContaComum(101, p1);
		c1.credito(1000);
		System.out.println(c1.getSaldo());
		
		Pessoa p2 = new Pessoa(2);
		p2.setNome("Maria");
		ContaComum c2 = new ContaComum(101, p2);
		c2.credito(11);
		System.out.println(c2.getSaldo());

		b.inserir(c1);
		b.inserir(c2);
		assertEquals(1000, b.saldo(101));
		assertEquals("Pedro", b.nomeDoDono(101));
		assertEquals(1, b.cpfDoDono(101));
    }
}
