package cn.jbit.quicktype;

import java.util.Random;

public class Game {
	private Player player;

	public Game(Player p) {
		player = p;
	}

	public String printStr() {
		int strLength = LevelParam.levels[player.getLevelNo() - 1].getStrLength();
		StringBuffer buffer = new StringBuffer();
		Random random = new Random();

		for (int i = 0; i < strLength; i++) {
			// 产生随机数
			int rand = random.nextInt(strLength);
			// 拼接字符串
			switch (rand) {
			case 0:
				buffer.append(">");
				break;
			case 1:
				buffer.append("<");
				break;
			case 2:
				buffer.append("*");
				break;
			case 3:
				buffer.append("&");
				break;
			case 4:
				buffer.append("%");
				break;
			case 5:
				buffer.append("#");
				break;
			case 6:
				buffer.append("$");
				break;
			}
		}
		// 输入
		System.out.println(buffer);
		// 比较
		return buffer.toString();
	}

	public void printResult(String out, String in) {
		boolean flag;
		if (out.equals(in)) {
			flag = true;
		} else {
			flag = false;
		}
		// 正确与否
		if (flag) {
			long currentTime = System.currentTimeMillis();
			// 超时
			if ((currentTime - player.getStartTime()) / 1000 > LevelParam.levels[player.getLevelNo() - 1]
					.getTimeLimt()) {
				System.out.println("你输入太慢了，已经超时，退出！");
				System.exit(1);
				// 没有超时
			} else {
				// 计算当前积分
				player.setCurScore(player.getCurScore() + LevelParam.levels[player.getLevelNo() - 1].getPerScore());
				// 计算已用时间
				player.setElapsedTime((int) ((currentTime - player.getStartTime()) / 1000));
				// 输出积分，级别，已用时间
				System.out.println("输入正确，您的级别" + player.getLevelNo() + "，您的积分" + player.getCurScore() + ",已用时间"
						+ player.getElapsedTime() + "秒。");
				// 判断最后一关
				if (player.getLevelNo() == 6) {
					int score = LevelParam.levels[player.getLevelNo() - 1].getPerScore()
							* LevelParam.levels[player.getLevelNo() - 1].getStrTime();
					if (player.getCurScore() == score) {
						System.out.println("你已闯关成功，成为绝世高手，恭喜你！！！");
						System.exit(0);
					}
				}
			}
			// 输入错误
		} else {
			System.out.println("输入错误，退出！");
			System.exit(1);
		}
	}
}
