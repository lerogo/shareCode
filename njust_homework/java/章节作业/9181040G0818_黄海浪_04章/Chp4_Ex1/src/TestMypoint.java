public class TestMypoint {
	public static void main(String[] args) {
		MyPoint Start = new MyPoint();
		MyPoint End = new MyPoint();
		Start.x = 10;
		Start.y = 10;
		End.x = 20;
		End.y = 30;
		System.out.println("Start point is " + Start);
		System.out.println("End point is " + End + "\n");
		MyPoint Stray = End;
		System.out.println("Stray point is " + Start);
		System.out.println("End point is " + End + "\n");
		Stray.x = 47;
		Stray.y = 50;
		System.out.println("Stray point is " + Stray);
		System.out.println("End point is " + End);
		System.out.println("Start point is " + Start);
	}
}