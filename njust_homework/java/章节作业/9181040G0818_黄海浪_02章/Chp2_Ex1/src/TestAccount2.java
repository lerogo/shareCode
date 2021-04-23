public class TestAccount2 {
	public static void main(String[] args) {
		Account acct = new Account(100.0);
		acct.balance += 47.0;
		acct.balance -= 150.0;
		System.out.println("Final account balance is " + acct.balance);
	}
}

//@utf-8 discussion
//因为会自动编译Account.java 生成class文件