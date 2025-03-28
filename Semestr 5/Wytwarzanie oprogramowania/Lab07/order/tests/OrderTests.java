package edu.zut.order.tests;

import static org.junit.Assert.assertEquals;

import edu.zut.order.Order;
import edu.zut.order.OrderCalculator;
import org.junit.Test;

public class OrderTests {

	@Test
	public void testPrice() {
		Order order = new Order(10, 100);
		assertEquals("Price should be 1100.00", OrderCalculator.price(order), 1100, 0);
	}

}
