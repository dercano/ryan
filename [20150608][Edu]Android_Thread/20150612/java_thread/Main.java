
// Main.java

public class Main {
	void method() {
		for(int i = 0; i < 10; i++) {
			System.out.println("\tmethod");
			try {
				Thread.sleep(1000);
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		new Main().method();		
		while(true) {
			System.out.println("main");
			try {
				Thread.sleep(1000);
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
}







