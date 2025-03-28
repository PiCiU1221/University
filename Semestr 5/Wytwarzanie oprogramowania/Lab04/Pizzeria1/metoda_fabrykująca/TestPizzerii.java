package org.example.Pizzeria1.metoda_fabrykująca;

import org.example.Pizzeria1.pizza.Pizza;

public class TestPizzerii {

	public static void main(String[] args) {
		Pizzeria włoskaPizzeria = new WłoskaPizzeria();
		Pizza pizza = włoskaPizzeria.zamówPizza("serowa");
		System.out.println(włoskaPizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza.getClass().getSimpleName() + "\n");

		Pizzeria amerykańskaPizzeria = new AmerykańskaPizzeria();
		pizza = amerykańskaPizzeria.zamówPizza("serowa");
		System.out.println(amerykańskaPizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza.getClass().getSimpleName());
	}
}
