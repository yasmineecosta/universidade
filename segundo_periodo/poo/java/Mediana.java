import java.util.Arrays;
import java.util.Scanner;

public class Mediana {
	public static void main(String[] args) {
		int n;
		float numeros[];
		float me;
		
		Scanner scan = new Scanner(System.in); 
		System.out.println("Digite Qde de numeros?");
		n = scan.nextInt();
		numeros = new float[n];
		
		System.out.println("Digite os numeros");
		for (int i=0; i<n; i++) {
			numeros[i] = scan.nextFloat();
		}
		
		Arrays.sort(numeros);
		System.out.println("Numeros ordenados");
		for (float el : numeros)
			System.out.print(el+" ");
		
		if (n % 2 == 0) { // par
			me = (numeros[n/2-1] + numeros[n/2])/2;
		} else { // impar
			me = (numeros[n/2]);
		}
		System.out.println("\nMediana: "+me);

		scan.close();
	}
}