
// RaceCondition.java
import java.util.Scanner;

public class RaceCondition extends Thread {
	public static int shared = 0;	// shared object

	public void run() {
		for(int i = 0; i < 50000000; i++) {
			//---------------------------------
			synchronized(RaceCondition.class) {
				++shared;
			}
			//---------------------------------
		}
	}
	
	public static void main(String[] arg) {
		RaceCondition r1 = new RaceCondition();
		RaceCondition r2 = new RaceCondition();

		r1.start();
		r2.start();

		try {
			r1.join();
			r2.join();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.out.println("shared = " + shared);
	}
}

