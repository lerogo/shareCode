package com.mybank.test;

import com.mybank.domain.*;

public class TestBanking {

	public static void main(String[] args) {
		Customer customer;
		Account account;
		boolean operationResult;

		System.out.println("Creating the customer Jane Smith.");
		customer = new Customer("Jane", "Smith");
		System.out.println("Creating her account with a 500.00 balance.");
		customer.setAccount(new Account(500.00));
		account = customer.getAccount();

		operationResult = account.withdraw(150.00);
		System.out.println("Withdraw 150.00: " + operationResult);

		operationResult = account.deposit(22.50);
		System.out.println("Deposit 22.50: " + operationResult);

		operationResult = account.withdraw(47.62);
		System.out.println("Withdraw 47.62: " + operationResult);

		operationResult = account.withdraw(400.00);
		System.out.println("Withdraw 400.00: " + operationResult);

		System.out.println("Customer [" + customer.getLastName() + ", " + customer.getFirstName()
				+ "] has a balance of " + account.getBalance());
	}
}
