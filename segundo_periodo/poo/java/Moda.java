import java.util.ArrayList;

import javax.swing.JOptionPane;

public class Moda {
	public static void main(String[] args) {
		final int MAX = 1000;
		int numeros[] = new int[MAX];
		int wsNum, n=0;
		
		while (true) {
			wsNum = Integer.parseInt(
					JOptionPane.showInputDialog("Digite numero?")
					);
			if (wsNum == -1) break;
			numeros[n] = wsNum;
			n++;
		}
		for (int i=0; i < n; i++) {
			System.out.print(numeros[i]+ " ");
		}
	}
}
