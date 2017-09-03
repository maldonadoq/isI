import javax.swing.*;
public class h{

	public static void main(String[] args){
		/*String name = JOptionPane.showInputDialog("ingrese nombre: ");
		String age = JOptionPane.showInputDialog("ingrese edad: ");
		int ag = Integer.parseInt(age);
		System.out.println("hello " + name + ", you are " + (ag+1) + " years old");*/

		/*String d = JOptionPane.showInputDialog("numero: ");
		double a = Double.parseDouble(d);
		System.out.printf("%1.4f\n",Math.sqrt(a));
		String key = "Percy";
		String pass = "";
		while(key.equals(pass)==false){
			System.out.println("incorrect password");
			pass = JOptionPane.showInputDialog("password: ");
		}*/

		/*int t = Integer.parseInt(JOptionPane.showInputDialog("factorial de: "));
		long f=1;
		for (int i=1; i<=t; i++) {
			f *= i;
		}
		System.out.println(f);*/

		int [][] m = {{1,2,3,4},{0,1,2,3},{9,8,7,6}};
		for(int i=0; i<3; i++){
			for(int j=0; j<4; j++)
				System.out.print(m[i][j]+" ");
			System.out.println();
		}
	}
}