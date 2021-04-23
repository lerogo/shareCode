package cn.jbit.quicktype;

import java.util.Scanner;

public class Player {
	private int levelNo;// 级别
	private int curScore;// 当前积分
	private long startTime = 0;// 各级别开始时间
	private int elapsedTime;// 各级别已用时间

	public long getStartTime() {
		return startTime;
	}

	public void setStartTime(long startTime) {
		this.startTime = startTime;
	}

	public int getLevelNo() {
		return levelNo;
	}

	public void setLevelNo(int levelNo) {
		this.levelNo = levelNo;
	}

	public int getCurScore() {
		return curScore;
	}

	public void setCurScore(int curScore) {
		this.curScore = curScore;
	}

	public int getElapsedTime() {
		return elapsedTime;
	}

	public void setElapsedTime(int elapsedTime) {
		this.elapsedTime = elapsedTime;
	}

	public void play() {
		Game game = new Game(this);
		@SuppressWarnings("resource")
		Scanner input = new Scanner(System.in);
		// 外层循环，循环一次级别晋一级
		for (int i = 0; i < LevelParam.levels.length; i++) {
			// 晋级
			this.levelNo += 1;
			// 积分清零
			this.startTime = System.currentTimeMillis();
			this.curScore = 0;
			// 输出，输入，比较
			for (int j = 0; j < LevelParam.levels[this.levelNo].getStrLength(); j++) {
				// 输出
				String outStr = game.printStr();
				// 输入
				String inStr = input.next();
				// 判断
				game.printResult(outStr, inStr);
			}
		}
	}

}
