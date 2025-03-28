package org.example.Pizzeria1.metoda_fabrykująca;

import org.example.Pizzeria1.pizza.Pizza;

public abstract class Pizzeria {

	abstract Pizza utwórzPizza(String typ);

	public Pizza zamówPizza(String typ) {
		Pizza pizza = utwórzPizza(typ);
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}
}
