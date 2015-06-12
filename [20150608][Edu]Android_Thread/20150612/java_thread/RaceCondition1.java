
// RaceCondition1.java
import java.util.concurrent.locks.ReentrantLock;

public class RaceCondition1 extends Thread {
	public static ReentrantLock mLock = new ReentrantLock();
	public static int shared = 0;	// shared object

	public void run() {
		for(int i = 0; i < 50000000; i++) {
			mLock.lock();
			//---------------------------------
			++shared;
			//---------------------------------
			mLock.unlock();
		}
	}
	
	public static void main(String[] arg) {
		RaceCondition1 r1 = new RaceCondition1();
		RaceCondition1 r2 = new RaceCondition1();

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

