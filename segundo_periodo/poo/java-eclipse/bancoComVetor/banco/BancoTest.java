package banco;

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

}
