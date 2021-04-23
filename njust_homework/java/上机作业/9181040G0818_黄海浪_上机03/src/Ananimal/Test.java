package Ananimal;

public class Test {
	public static void main(String[] args) {
		Animal a[] = new Animal[3];
		a[0] = new Cat("一只猫", 4);
		a[1] = new Duck("一只鸭", 2);
		a[2] = new Dolphin("一条豚");
		System.out.println("动物名字       " + "腿的条数      " + "动物叫");
		for (int i = 0; i <= 2; i++) {
			if (!(a[i] instanceof Terrestrial)) {
				a[i].legNum = 0;
			}
			System.out.println(a[i].name + "         " + a[i].legNum + "             " + "" + a[i].shout());
		}
	}
}
