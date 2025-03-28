package org.example.fabryka_czekolady;

import org.example.fabryka_czekolady.singleton.klasyczny.CzekoladowyKocioł;

public class FabrykaCzekolady {

	public static void main(String... params) {
		CzekoladowyKocioł kocioł = CzekoladowyKocioł.pobierzInstancję();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
}
