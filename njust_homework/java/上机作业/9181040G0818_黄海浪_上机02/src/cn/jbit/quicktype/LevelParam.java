package cn.jbit.quicktype;

public class LevelParam {
    public final static Level levels[] = new Level[6];
    // 六个级别
    static {
        levels[0] = new Level(1, 2, 3, 15, 1);
        levels[1] = new Level(2, 3, 3, 15, 2);
        levels[2] = new Level(3, 4, 2, 15, 5);
        levels[3] = new Level(4, 5, 2, 15, 8);
        levels[4] = new Level(5, 6, 1, 15, 10);
        levels[5] = new Level(6, 7, 1, 12, 15);
    }
}
