
// MyThread.java

public class MyThread extends Thread {	//1.  상속 기반의 스레드

	public void run() {
		System.out.println("extends thread");
	}

	public static void main(String[] args) {
		// 자바의 경우, 메인 스레드가 종료되어도 워커 스레드가 구동된다면
		// 프로세스는 종료되지 않습니다.
		Thread t1 = new MyThread();	// upcasting
		t1.start();

		// 2. 인터페이스 기반으로 구현
		Thread t2 = new Thread(new Runnable() {
				public void run() {
					System.out.println("implement Runnable");
				}
			}
		);
		t2.start();

		// 만약 스레드를 한 번만 사용하고 버릴 경우, 아래와 같이
		// 사용 가능합니다.
		new Thread(new Runnable() {
				public void run() {
					System.out.println("implement Runnable");
				}
			}
		).start();

	}
};
