import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;
import javax.swing.*;

interface strat{
	int operacion(int a, int b);
}

class suma implements strat{
	public int operacion(int a, int b){
		return a+b;
	}
}

class resta implements strat{
	public int operacion(int a, int b){
		return a-b;
	}
}

class producto implements strat{
	public int operacion(int a, int b){
		return a*b;
	}
}

class division implements strat{
	public int operacion(int a, int b){
		return a/b;
	}
}

class mcd implements strat{
	public int modulo(int a, int n){
	    int q = a/n;
	    int r = a-(n*q);
	    if(r<0) return r+n;
	    return r;
	}

	public int euc(int x, int y){
	    int may ,men,r;
	    if(x>=y){   may = x;    men = y;    }
	    else{   may = y;    men = x;    }

	    while(men!=0){
	        r = modulo(may,men);
	        may = men;
	        men = r;
	    }
	    return may;
	}

	public int operacion(int a, int b){
		return euc(a,b);
	}
}

class fn implements strat{
	// la verdad que no me convence! no sé si esta bien
	private strat A = new suma();
	private strat B = new resta();
	private strat C = new producto();
	private strat D = new division();
	public int operacion(int a, int b){
		return D.operacion(B.operacion(C.operacion(2,a),b),A.operacion(a,3));
	}
}

class ope{
	private Map<String,strat> operations = new HashMap<>();
	public ope(){	}
	public void set(String op, strat SO){
		operations.put(op,SO);
	}

	public int execute(String op, int a, int b){
		strat O = operations.get(op);
		return O.operacion(a,b);
	}
}

public class strategy{
	public static void main(String[] args){	
		Scanner sc = new Scanner(System.in);
		ope CO = new ope();
		CO.set("+",new suma());
		CO.set("-",new resta());
		CO.set("*",new producto());
		CO.set("/",new division());
		CO.set("#",new mcd());
		CO.set("%",new fn());

		String da, op, db;
		int a,b;
		
		while(true){
			da = JOptionPane.showInputDialog("numero: ");
			op = JOptionPane.showInputDialog("operator: ");
			db = JOptionPane.showInputDialog("numero: ");
			
			a = Integer.parseInt(da);
			b = Integer.parseInt(db);
			System.out.println(CO.execute(op,a,b));
		}
	}
}