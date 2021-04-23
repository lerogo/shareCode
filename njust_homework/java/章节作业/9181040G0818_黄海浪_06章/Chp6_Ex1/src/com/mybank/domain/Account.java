package com.mybank.domain;

public class Account {

	private double balance;

	public Account(double initBalance) {
		balance = initBalance;
	}

	public double getBalance() {
		return balance;
	}

	public void deposit(double amt) {
		balance += amt;
	}

	public void withdraw(double amt) {
		if (amt <= balance) {
			balance -= amt;
		}
	}
}
