package cn.jbit.quicktype;

public class Level {
	private int levelNo;	// 级别号
	private int strLength;	// 字符串长度
	private int strTime;	// 输出字符串次数
	private int timeLimit;	// 时间限制
	private int perScore;	// 增加的分值

	public Level(int new_levelNo, int new_strLength, int new_strTime, int new_timeLimit, int new_perscore) {
		levelNo = new_levelNo;
		strLength = new_strLength;
		strTime = new_strTime;
		timeLimit = new_timeLimit;
		perScore = new_perscore;
	}

	public int getLevelNo() {
		return levelNo;
	}

	public int getStrLength() {
		return strLength;
	}

	public int getStrTime() {
		return strTime;
	}

	public int getTimeLimt() {
		return timeLimit;
	}

	public int getPerScore() {
		return perScore;
	}

}
