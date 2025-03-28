package edu.zut.order;

public class OrderCalculator {

	public static double price(Order order) {
		// Cena ko�cowa = cena bazowa � upust + koszt wysy�ki.
		double cena_bazowa = order.getQuantity() * order.getItemPrice();
		double upust = Math.max(0, order.getQuantity() - 500) * order.getItemPrice() * 0.05;
		double koszt_wysylki = Math.min(order.getQuantity() * order.getItemPrice() * 0.1, 100);

		return cena_bazowa - upust + koszt_wysylki;
	}
}
