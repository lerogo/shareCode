package com.mybank.domain;
public class Account {
	private double balance;
	public Account(double initbalance)
	{
		this.balance=initbalance;
	}
	public  void deposit(double amt)
	{
		this.balance+=amt;
	}
	public void withdraw(double amt)
	{
		if (amt<=balance)
			balance-=amt;
	}
	public double getBalance()
	{
		return this.balance;
	}
	
}
