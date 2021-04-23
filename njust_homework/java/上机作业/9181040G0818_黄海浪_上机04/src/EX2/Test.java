package EX2;

public class Test {
    public static void main(String[] args){
        TicketOffice t=new TicketOffice();
        Thread one = new Thread(t);
        Thread two = new Thread(t);
        Thread three = new Thread(t);
        one.setName("张三");
        two.setName("李四");
        three.setName("票贩子");
        
        one.start();
        two.start();
        three.start();
        
    }
}
