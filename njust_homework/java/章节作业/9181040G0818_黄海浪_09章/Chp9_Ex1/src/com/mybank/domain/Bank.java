package com.mybank.domain;

public class Bank {
	private static Customer[] customers;
	private static int numberOfCustomers;

	static {
		customers = new Customer[10];
		numberOfCustomers = 0;
	}

	private Bank() {
		// this constructor should never be called
	}

	public static void addCustomer(String f, String l) {
		customers[numberOfCustomers++] = new Customer(f, l);
	}

	public static int getNumOfCustomers() {
		return numberOfCustomers;
	}

	public static Customer getCustomer(int customer_index) {
		return customers[customer_index];
	}
}
