interface A{
	public void a();
}

interface B extends A{
	public void b();
}

interface C extends A{
	public void c();
}

class D implements B,C{
	public void a(){
		System.out.println("A");
	}
	public void b(){
		System.out.println("B");
	}
	public void c(){
		System.out.println("C");
	}
}


public class Main{
	public static void main(String[] args){	
		System.out.println("Percy");
		D z = new D();
		z.a();
		z.b();
		z.c();
	}
}