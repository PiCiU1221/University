package org.example.Pizzeria1;

import org.example.Pizzeria1.pizza.*;

public class ProstaPizzeria {
	Pizza zamówPizza(String type) {
		Pizza pizza = null;
		if (type.equals("serowa")) {
			pizza = new SerowaPizza();
		} else if (type.equals("grecka")) {
			pizza = new GreckaPizza();
		} else if (type.equals("pepperoni")) {
			pizza = new PepperoniPizza();
		} else if (type.equals("owocemorza")) {
			pizza = new OwoceMorzaPizza();
		} else if (type.equals("wegetariańska")) {
			pizza = new WegetariańskaPizza();
		}
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}

}
