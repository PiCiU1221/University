package edu.zut.invoice;

import java.time.LocalDate;

public class InvoiceManager {

	public static void printOwing(Invoice invoice) {
		double outstanding = 0;

		printHeader();

		// Wyliczenie nale�no�ci.
		outstanding = calculateOwing(invoice);

		// Zapisanie daty p�atno�ci.
		setInvoiceDate(invoice);

		// Wy�wietlenie szczeg��w.
		printInvoiceDetails(invoice, outstanding);
	}

	private static void printHeader() {
		System.out.println("************************");
		System.out.println("* Rachunek dla klienta *");
		System.out.println("************************");
	}

	private static double calculateOwing(Invoice invoice) {
		double outstanding = 0;

		for (Order o : invoice.getOrders()) {
			outstanding += o.getAmount();
		}

		return outstanding;
	}

	private static void setInvoiceDate(Invoice invoice) {
		LocalDate today = LocalDate.now();
		invoice.setDueDate(today.plusDays(30));
	}

	private static void printInvoiceDetails(Invoice invoice, double outstanding) {
		System.out.println(String.format("nazwa: %s", invoice.getCustomer()));
		System.out.println(String.format("kwota: %.2f", outstanding));
		System.out.println(String.format("p�atno�� do: %s", invoice.getDueDate()));
	}
}
