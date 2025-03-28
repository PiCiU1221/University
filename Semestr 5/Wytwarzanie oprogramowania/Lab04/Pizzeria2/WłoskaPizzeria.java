package org.example.Pizzeria2;

import org.example.Pizzeria2.fabryka.FabrykaSkładnikówPizzy;
import org.example.Pizzeria2.fabryka.WłoskaFabrykaSkładnikówPizzy;
import org.example.Pizzeria2.pizza.*;

public class WłoskaPizzeria extends Pizzeria {
	protected Pizza utwórzPizza(String item) {
		Pizza pizza = null;
		FabrykaSkładnikówPizzy fabrykaSkładników = new WłoskaFabrykaSkładnikówPizzy();
		if (item.equals("serowa")) {
			pizza = new SerowaPizza(fabrykaSkładników);
			pizza.ustawNazwa("Włoska Pizza Serowa");
		} else if (item.equals("wegetariańska")) {
			pizza = new WegetariańskaPizza(fabrykaSkładników);
			pizza.ustawNazwa("Włoska Pizza Wegetariańska");
		} else if (item.equals("owoce morza")) {
			pizza = new OwoceMorzaPizza(fabrykaSkładników);
			pizza.ustawNazwa("Włoska Pizza Owoce Morza");
		} else if (item.equals("pepperoni")) {
			pizza = new PepperoniPizza(fabrykaSkładników);
			pizza.ustawNazwa("Włoska Pizza Pepperoni");
		}
		return pizza;
	}
}