package com.mybank.domain;

public class Account {

	protected double balance;

	public Account(double initBalance) {
		balance = initBalance;
	}

	public boolean deposit(double amt) {
		balance += amt;
		return true;
	}

	public boolean withdraw(double amt) {
		boolean result = false;
		if (amt <= balance) {
			balance -= amt;
			result = true;
		}
		return result;
	}

	public double getBalance() {
		return balance;
	}
}
