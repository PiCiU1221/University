package org.example.Pizzeria2;

import org.example.Pizzeria2.pizza.Pizza;

public class TestPizzerii2 {

	public static void main(String[] args) {
		WłoskaPizzeria włoskaPizzeria = new WłoskaPizzeria();
		AmerykańskaPizzeria amerykańskaPizzeria = new AmerykańskaPizzeria();

//		Pizza pizza1 = włoskaPizzeria.zamówPizza("owoce morza");
//		System.out.println(pizza1 + "\n");

		Pizza serowaAmerykańska = amerykańskaPizzeria.zamówPizza("serowa");
		System.out.println(serowaAmerykańska + "\n");
		Pizza wegetariańskaAmerykańska = amerykańskaPizzeria.zamówPizza("wegetariańska");
		System.out.println(wegetariańskaAmerykańska + "\n");
		Pizza owoceMorzaAmerykańska = amerykańskaPizzeria.zamówPizza("owoce morza");
		System.out.println(owoceMorzaAmerykańska + "\n");
		Pizza pepperoniAmerykańska = amerykańskaPizzeria.zamówPizza("pepperoni");
		System.out.println(pepperoniAmerykańska + "\n");
	}
}
