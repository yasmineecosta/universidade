package banco;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.GregorianCalendar;

public class UsoDeDatas {
	
  public static void main(String[] args) throws ParseException, InterruptedException {
	 Date d = new Date();
	 System.out.println(d); 
	 int dia1 = d.getDate();
	 int mes1 = d.getMonth();
	 int ano1 = d.getYear();
	 int hora = d.getHours();
	 int minuto = d.getMinutes();
	 int segundo = d.getSeconds();
	 System.out.println(dia1);
	 System.out.println(mes1);
	 System.out.println(ano1);
	 
	 System.out.println(hora);
	 System.out.println(minuto);
	 System.out.println(segundo);
	 
	 GregorianCalendar gc = new GregorianCalendar();
	 System.out.println(gc);
	 int d1 = gc.get(gc.DAY_OF_MONTH);
	 int m1 = gc.get(gc.MONTH);
	 int a1 = gc.get(gc.YEAR);
 
	 System.out.println("Data via calendario gregoriano");

	 System.out.println(d1 + "/" + m1 + "/" + a1);
  }
}
