import java.util.*;

public class ThreadTest {
	public static void main(String[] args) {
		ThreadDemo _1 = new ThreadDemo("Thread-1");
		ThreadDemo _2 = new ThreadDemo("Thread-2");
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			int choice = in.nextInt();
			if (choice == 1) _1.start();
			else if (choice == 2) _2.start();
			else break;
		}
		System.out.println("Main thread finished.");
	}
}

class ThreadDemo extends Thread {
	private Thread t;
	private String threadName;
	ThreadDemo(String _name) {
		threadName = _name;
		System.out.println("Creating " + threadName);
	}

	public void run() {
		System.out.println("Now running: " + threadName);
		try {
			for (int i = 1; i <= 5; i++) {
				System.out.println(threadName + " is running...");
				Thread.sleep(3000);
			}
		}
		catch (InterruptedException e) {
			System.out.println(threadName + " is interrupted.");
		}
		System.out.println(threadName + " exits.");
	}

	public void start() {
		System.out.println("Now starting: " + threadName);
		t = new Thread(this, threadName);
		t.start();
	}
}