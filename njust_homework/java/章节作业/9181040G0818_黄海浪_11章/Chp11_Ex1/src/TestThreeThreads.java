public class TestThreeThreads {
	public static void main(String[] args) {
		Runnable prog = new PrintMe();
		Thread t1 = new Thread(prog);
		Thread t2 = new Thread(prog);
		Thread t3 = new Thread(prog);

		t1.setName("T1-Larry");
		t2.setName("T2-Curly");
		t3.setName("T3-Moe");

		t1.start();
		t2.start();
		t3.start();
	}
}
