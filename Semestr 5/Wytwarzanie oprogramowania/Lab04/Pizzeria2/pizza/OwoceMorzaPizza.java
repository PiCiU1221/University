package org.example.Pizzeria2.pizza;

import org.example.Pizzeria2.fabryka.FabrykaSkładnikówPizzy;

public class OwoceMorzaPizza extends Pizza {
	FabrykaSkładnikówPizzy fabrykaSkładników;

	public OwoceMorzaPizza(FabrykaSkładnikówPizzy fabrykaSkładników) {
		this.fabrykaSkładników = fabrykaSkładników;
	}

	public void przygotowanie() {
		System.out.println("Przygotowywanie: " + nazwa);
		ciasto = fabrykaSkładników.utwórzCiasto();
		sos = fabrykaSkładników.utwórzSos();
		ser = fabrykaSkładników.utwórzSer();
		małże = fabrykaSkładników.utwórzMałże();
	}
}