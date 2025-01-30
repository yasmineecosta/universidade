package pedroSantosNeto.banco;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class ContaComumTest {

	@Test
	void testarCreditoEDebito() {
		Pessoa p = new Pessoa(1);
		p.setNome("Pedro");
		ContaComum c = new ContaComum(100, p);
		
		c.credito(1000);
		assertEquals(1000, c.getSaldo());
		
		c.debito(10);
		assertEquals(990, c.getSaldo());
	}
	
	@Test
	void testarUsoDeNumerosGrandes() {
		Pessoa p = new Pessoa(1);
		p.setNome("Pedro");
		ContaComum c = new ContaComum(100, p);

		c.setNum(101);
		assertEquals(101, c.getNum());
		
		c.setNum(1001);
		assertEquals(101, c.getNum());
	}
	
	@Test
	void testarExtrato() {
		Pessoa p = new Pessoa(1);
		p.setNome("Pedro");
		ContaComum c = new ContaComum(100, p);

		c.credito(1000);		
		c.debito(10);
		String extrato = "Credito: 1000.0 Saldo: 1000.0\nDebito: 10.0 Saldo: 990.0\n";
		assertEquals(extrato, c.getExtrato());
	}
	
	@Test
	void testarDebitoAcimaDoLimite() {
		Pessoa p = new Pessoa(1);
		p.setNome("Pedro");
		ContaComum c = new ContaComum(100, p);
		
		c.debito(1);
		assertEquals(0, c.getSaldo());
		
		c.credito(1000);
		assertEquals(1000, c.getSaldo());
		
		c.debito(1001);
		assertEquals(1000, c.getSaldo());
	
		c.debito(1000);
		assertEquals(0, c.getSaldo());
	}

}
