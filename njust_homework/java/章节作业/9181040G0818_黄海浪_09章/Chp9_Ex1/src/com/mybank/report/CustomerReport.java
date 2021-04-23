package com.mybank.report;

import com.mybank.domain.*;

public class CustomerReport {

	public CustomerReport() {
	}

	public void generateReport() {

		// Print report header
		System.out.println("\t\t\tCUSTOMERS REPORT");
		System.out.println("\t\t\t================");

		// For each customer...
		for (int cust_idx = 0; cust_idx < Bank.getNumOfCustomers(); cust_idx++) {
			Customer customer = Bank.getCustomer(cust_idx);

			// Print the customer's name
			System.out.println();
			System.out.println("Customer: " + customer.getLastName() + ", " + customer.getFirstName());

			// For each account for this customer...
			for (int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++) {
				Account account = customer.getAccount(acct_idx);
				String account_type = "";

				// Determine the account type
				if (account instanceof SavingsAccount) {
					account_type = "Savings Account";
				} else if (account instanceof CheckingAccount) {
					account_type = "Checking Account";
				} else {
					account_type = "Unknown Account Type";
				}

				// Print the current balance of the account
				System.out.println("    " + account_type + ": current balance is " + account.getBalance());
			}
		}
	}
}
