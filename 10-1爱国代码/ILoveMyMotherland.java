import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.geom.GeneralPath;
import java.net.MalformedURLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.atomic.AtomicLong;

/**
 * 方便下载交流
 *github:https://github.com/lerogo/shareCode
 */
public class ILoveMyMotherland {
    public static void main(String[] args) throws ParseException {
        Counter.run();
        TheFiveStarRedFlag.run();
    }
}

class Counter {

    static void run() throws ParseException {
        new Counter().getTime();
    }

    private JFrame frame;
    private JLabel alabel;

    /**
     * TODO:窗体以及label初始化等
     */
    private Counter() {
        //一个窗口，一个label（显示文字）
        frame = new JFrame("我爱祖国！");
        alabel = new JLabel();
        alabel.setFont(new Font("Serif", Font.BOLD, 50));//设置文字大小
        JPanel jp = new JPanel();
        jp.add(alabel);
        frame.add(jp);

        //设置大小并自适应
        frame.setPreferredSize(new Dimension(1000, 120));
        frame.pack();
        frame.setLocationRelativeTo(null);//居中
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//点×按钮事件
        frame.setVisible(true);//设置可见
    }

    /**
     * TODO:时间计算，每秒更新label
     */
    private void getTime() throws ParseException {
        Date end = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").parse("2019-10-01 00:00:00");//获取时间
        AtomicLong time = new AtomicLong((end.getTime() - 1 - new Date().getTime()) / 1000); // 自定义倒计时时间
        AtomicLong hour = new AtomicLong();
        AtomicLong minute = new AtomicLong();
        AtomicLong seconds = new AtomicLong();

        while (time.get() >= 0) {
            //计算时间
            hour.set(time.get() / 3600);
            minute.set((time.get() - hour.get() * 3600) / 60);
            seconds.set(time.get() - hour.get() * 3600 - minute.get() * 60);

            String stringBuilder = "距离祖国70岁生日还有：" + hour.get() + "时 " + minute.get() + "分 " + seconds.get() + "秒 ";

            //label设置时间
            alabel.setText(stringBuilder);

            //间隔1s
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            time.getAndDecrement();
        }
        //结束后设置此窗口不可见 为显示国旗做准备
        frame.setVisible(false);
    }
}


class TheFiveStarRedFlag extends JPanel {

    private int width;
    private int height;

    static void run() {
        //创建窗口并显示国旗
        JFrame myFrame = new JFrame("祝祖国70岁生日快乐！");         //标题名字

        //获取屏幕分辨率
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension scrnsize = toolkit.getScreenSize();
        /*
         * TODO:窗口中添加国旗，大小为屏幕宽度的0.8倍
         * 添加一个panel覆盖rootPane
         */
        myFrame.getContentPane().add(new TheFiveStarRedFlag((int) (scrnsize.width*0.80)));

        myFrame.pack();                                                 //让容器适应内部控件大小
        myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);         //设置关闭事件->退出
        myFrame.setLocationRelativeTo(null);                            //设置居中显示
        myFrame.setVisible(true);                                       //显示
    }

    /*
     * TODO:创建一个宽度为width的国旗
     */
    private TheFiveStarRedFlag(int _width) {
        //宽:高 = 3:2
        width = _width / 3 * 3;
        height = _width / 3 * 2;
        setPreferredSize(new Dimension(width, height));//适应大小
    }

    /*
     * TODO:重写paint方法实现画图
     * 会删除原本的所有组件，因为仅显示国旗
     */
    @Override
    public void paint(Graphics g) {
        Graphics2D graphics2D = (Graphics2D) g;

        //画旗面
        g.setColor(Color.RED);
        g.fillRect(0, 0, width, height);

        //画大星
        graphics2D.setColor(Color.YELLOW);
        double ox = height * 0.25, oy = height * 0.25;
        graphics2D.fill(createPentacle(ox, oy, height * 0.15, -Math.PI / 2));

        //画小星
        for (int i = 0; i < 4; i++) {
            double[] minX = {0.50, 0.60, 0.60, 0.50};
            double[] minY = {0.10, 0.20, 0.35, 0.45};
            double sx = minX[i] * height, sy = minY[i] * height;
            double theta = Math.atan2(oy - sy, ox - sx);
            graphics2D.fill(createPentacle(sx, sy, height * 0.05, theta));
        }
    }

    /*
     * TODO:创建一个五角星形状.
     * 该五角星的中心坐标为(sx,sy),中心到顶点的距离为radius,其中某个顶点与中心的连线的偏移角度为theta(弧度)
     */
    private static Shape createPentacle(double sx, double sy, double radius, double theta) {
        final double arc = Math.PI / 5;
        final double rad = Math.sin(Math.PI / 10) / Math.sin(3 * Math.PI / 10);
        GeneralPath path = new GeneralPath();
        path.moveTo(1, 0);
        for (int i = 0; i < 5; i++) {
            path.lineTo(rad * Math.cos((1 + 2 * i) * arc), rad * Math.sin((1 + 2 * i) * arc));
            path.lineTo(Math.cos(2 * (i + 1) * arc), Math.sin(2 * (i + 1) * arc));
        }
        path.closePath();
        AffineTransform atf = AffineTransform.getScaleInstance(radius, radius);
        atf.translate(sx / radius, sy / radius);
        atf.rotate(theta);
        //返回一个Shape, graphics2D可以直接画出
        return atf.createTransformedShape(path);
    }
}

/*
 *参考文献：
 * 用Java画五星红旗：https://blog.csdn.net/huang_qiang123/article/details/82941322
 * 五星红旗-百度百科：https://baike.baidu.com/item/%E4%B8%AD%E5%8D%8E%E4%BA%BA%E6%B0%91%E5%85%B1%E5%92%8C%E5%9B%BD%E5%9B%BD%E6%97%97/240342?fromtitle=%E4%BA%94%E6%98%9F%E7%BA%A2%E6%97%97&fromid=21897&fr=aladdin
 */