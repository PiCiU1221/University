package org.example.Pizzeria2.pizza;

import org.example.Pizzeria2.składniki.*;

public abstract class Pizza {
	String nazwa;
	Ciasto ciasto;
	Sos sos;
	Warzywa warzywa[];
	Ser ser;
	Pepperoni pepperoni;
	Małże małże;

	public abstract void przygotowanie();

	public void pieczenie() {
		System.out.println("Pieczenie: 25 minut w temperaturze 180 stopni Celsjusza");
	}

	public void krojenie() {
		System.out.println("Krojenie pizzy na 8 kawałków");
	}

	public void pakowanie() {
		System.out.println("Pakowanie pizzy w oficjalne pudełko naszej sieci Pizzerii.");
	}

	public void ustawNazwa(String nazwa) {
		this.nazwa = nazwa;
	}

	public String pobierzNazwa() {
		return nazwa;
	}

	public String toString() {
		// kod wyświetlający informacje o pizzy
		String warz = null;
		if (warzywa != null) 
			for (Warzywa w : warzywa) {
				warz += (warz == null ? "" : ",") + w.getClass().getSimpleName();
			}
		String info = String.format("%s\n"
				+ "ciasto: %s\n"
				+ "sos: %s\n"
				+ "warzywa: %s\n"
				+ "ser: %s\n"
				+ "pepperoni: %s\n"
				+ "małże: %s", 
				nazwa, 
				ciasto == null ? "brak" : ciasto.getClass().getSimpleName(),
				sos == null ? "brak" : sos.getClass().getSimpleName(),
				warz == null ? "brak" : warz, 
				ser == null ? "brak" : ser.getClass().getSimpleName(),
				pepperoni == null ? "brak" : pepperoni.getClass().getSimpleName(),
				małże == null ? "brak" : małże.getClass().getSimpleName()); 
		return info;
	}
}