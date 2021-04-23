package com.mybank.domain;

public class OverdraftException extends Exception {
	private static final long serialVersionUID = 1L;
	private final double deficit;

	public OverdraftException(String msg, double deficit) {
		super(msg);
		this.deficit = deficit;
	}

	public double getDeficit() {
		return deficit;
	}

}