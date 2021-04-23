package Ananimal;

public class Animal {
	protected String name;
	protected int legNum;

	public String getName(String n) {
		n = this.name;
		return n;
	}

	public String shout() {
		return "";
	}
}

interface Terrestrial {
	public int getLegNum();
}

class Cat extends Animal implements Terrestrial {
	public Cat(String name, int legNum) {
		this.name = name;
		this.legNum = legNum;
	}

	public String shout() {
		return "喵喵喵......";
	}

	public int getLegNum() {
		return legNum;
	}
}

class Duck extends Animal implements Terrestrial {
	public Duck(String name, int legNum) {
		this.name = name;
		this.legNum = legNum;
	}

	public String shout() {
		return "嘎嘎嘎......";
	}

	public int getLegNum() {
		return legNum;
	}
}

class Dolphin extends Animal {
	public Dolphin(String name) {
		this.name = name;
	}

	public String shout() {
		return "海豚音......";
	}
}
