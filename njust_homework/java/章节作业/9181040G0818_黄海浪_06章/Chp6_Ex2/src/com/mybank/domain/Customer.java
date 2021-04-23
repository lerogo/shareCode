package com.mybank.domain;

public class Customer {
	public String firstname;
	public String lastname;
	private Account account;

	public Customer(String s, String l) {
		firstname = s;
		lastname = l;
	}

	public Account getAccount() {
		return account;
	}

	public void setAccount(Account acc) {
		account = acc;
	}

	public String getLastName() {
		return lastname;
	}

	public String getFirstName() {
		return firstname;
	}
}
