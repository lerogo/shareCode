package com.mybank.batch;

import com.mybank.domain.*;

public class AccumulateSavingsBatch {

	public AccumulateSavingsBatch() {
	}

	public void doBatch() {

		// For each customer...
		for (int cust_idx = 0; cust_idx < Bank.getNumOfCustomers(); cust_idx++) {
			Customer customer = Bank.getCustomer(cust_idx);

			// For each account for this customer...
			for (int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++) {
				Account account = customer.getAccount(acct_idx);

				// Determine the account type
				if (account instanceof SavingsAccount) {
					SavingsAccount savings = (SavingsAccount) account;
					savings.accumulateInterest();
				} else {
					// ignore all other account types
				}
			}
		}
	}
}
