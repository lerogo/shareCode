package com.mybank.domain;

public class Bank {

	private Customer[] customers;
	private int numberOfCustomers;

	public Bank() {
		customers = new Customer[10];
		numberOfCustomers = 0;
	}

	public void addCustomer(String f, String l) {
		customers[numberOfCustomers++] = new Customer(f, l);
	}

	public int getNumOfCustomers() {
		return numberOfCustomers;
	}

	public Customer getCustomer(int customer_index) {
		return customers[customer_index];
	}
}
