package com.mybank.test;

import com.mybank.domain.*;
import com.mybank.report.*;
import com.mybank.batch.*;

public class TestBatch {

  public static void main(String[] args) {
    Bank bank = new Bank();
    initializeCustomers(bank);

    // run the customer report
    CustomerReport report = new CustomerReport();
    report.setBank(bank);
    report.generateReport();

    // run savings accumulation batch job
    AccumulateSavingsBatch job = new AccumulateSavingsBatch();
    job.setBank(bank);
    job.doBatch();
    System.out.println();
    System.out.println("ACCUMULATE SAVINGS BATCH EXECUTED");
    System.out.println();

    // run the customer report again
    report.generateReport();
  }

  private static void initializeCustomers(Bank bank) {
    Customer customer;

    // Create several customers and their accounts
    Bank.addCustomer("Jane", "Simms");
    customer = Bank.getCustomer(0);
    customer.addAccount(new SavingsAccount(500.00, 0.03));
    customer.addAccount(new CheckingAccount(200.00, 400.00));

    Bank.addCustomer("Owen", "Bryant");
    customer = Bank.getCustomer(1);
    customer.addAccount(new CheckingAccount(200.00));

    Bank.addCustomer("Tim", "Soley");
    customer = Bank.getCustomer(2);
    customer.addAccount(new SavingsAccount(1500.00, 0.075));
    customer.addAccount(new CheckingAccount(200.00));

    Bank.addCustomer("Maria", "Soley");
    customer = Bank.getCustomer(3);
    // Maria and Tim have a shared checking account
    customer.addAccount(Bank.getCustomer(2).getAccount(1));
    customer.addAccount(new SavingsAccount(150.00, 0.05));
  }
}
