import java.util.Scanner;

public class GuessingGame {
	static public void main(String[] args) {
		@SuppressWarnings("resource")
		Scanner cin = new Scanner(System.in);
		boolean flag = true;
		System.out.println("我们来玩一个猜数游戏！");
		while (flag) {
			boolean validinput;
			int number, guess;
			String ans;
			number = (int) (Math.random() * 10) + 1;
			System.out.println("我正在想一个介于1到10的整数\n您能猜猜到我想的整数是多少？\n");
			do {
				guess = cin.nextInt();
				validinput = true;
				if (guess < 1 || guess > 10) {
					System.out.print("输入的数字必须介于1至10，请重新输入：");
					validinput = false;
				}
			} while (!validinput);
			if (guess == number) {
				System.out.println("您猜对了！");
			} else {
				System.out.println("您猜错了，我想的数是 " + number);
			}
			do {
				System.out.println("\n继续玩？（Y or N）");
				ans = cin.next();
				validinput = true;
				if (ans.equalsIgnoreCase("Y")) {
					flag = true;
				} else if (ans.equalsIgnoreCase("N")) {
					flag = false;
				} else {
					validinput = false;
				}
			} while (!validinput);
		}
		System.out.println("\n感谢您玩猜数字游戏！");
	}
}