package com.mybank.domain;

public class CheckingAccount extends Account {

	private double overdraftAmount;

	public CheckingAccount(double initBalance, double overdraftAmount) {
		super(initBalance);
		this.overdraftAmount = overdraftAmount;
	}

	public CheckingAccount(double initBalance) {
		this(initBalance, 0.0);
	}

	public void withdraw(double amount) throws OverdraftException {

		if (balance < amount) {

			// Not enough balance to cover the amount requested to withdraw
			// Check if there is enough in the overdraft protection (if any)
			double overdraftNeeded = amount - balance;
			if (overdraftAmount < overdraftNeeded) {

				// No overdraft protection or not enough to cover the amount needed
				throw new OverdraftException("Insufficient funds for overdraft protection", overdraftNeeded);
			} else {

				// Yes, there is overdraft protection and enough to cover the amount
				balance = 0.0;
				overdraftAmount -= overdraftNeeded;
			}

		} else {

			// Yes, there is enough balance to cover the amount
			// Proceed as usual
			balance -= amount;
		}

	}
}
