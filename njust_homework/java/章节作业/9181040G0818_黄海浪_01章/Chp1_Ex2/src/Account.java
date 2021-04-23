public class Account
{
  private double balance;

  public Account(double initBalance)
  {
    this.balance = initBalance;
  }

  public double getBalance() {
    return this.balance;
  }

  public void deposit(double amt) {
    this.balance += amt;
  }

  public void withdraw(double amt) {
      this.balance -= amt;
  }
}