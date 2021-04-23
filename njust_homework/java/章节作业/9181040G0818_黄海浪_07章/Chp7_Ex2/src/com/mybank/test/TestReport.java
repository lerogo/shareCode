package com.mybank.test;

import com.mybank.domain.*;
import com.mybank.report.*;

public class TestReport {

	public static void main(String[] args) {
		Bank bank = new Bank();
		initializeCustomers(bank);

		// run the customer report
		CustomerReport report = new CustomerReport();
		report.setBank(bank);
		report.generateReport();
	}

	private static void initializeCustomers(Bank bank) {
		Customer customer;

		// Create several customers and their accounts
		bank.addCustomer("Jane", "Simms");
		customer = bank.getCustomer(0);
		customer.addAccount(new SavingsAccount(500.00, 0.05));
		customer.addAccount(new CheckingAccount(200.00, 400.00));

		bank.addCustomer("Owen", "Bryant");
		customer = bank.getCustomer(1);
		customer.addAccount(new CheckingAccount(200.00));

		bank.addCustomer("Tim", "Soley");
		customer = bank.getCustomer(2);
		customer.addAccount(new SavingsAccount(1500.00, 0.05));
		customer.addAccount(new CheckingAccount(200.00));

		bank.addCustomer("Maria", "Soley");
		customer = bank.getCustomer(3);
		// Maria and Tim have a shared checking account
		customer.addAccount(bank.getCustomer(2).getAccount(1));
		customer.addAccount(new SavingsAccount(150.00, 0.05));
	}
}
