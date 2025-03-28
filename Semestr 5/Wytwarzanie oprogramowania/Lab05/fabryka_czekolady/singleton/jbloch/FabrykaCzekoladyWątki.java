package org.example.fabryka_czekolady.singleton.jbloch;

public class FabrykaCzekoladyWątki {

	public static void main(String... params) {
		Thread wątek1 = new Thread("Wątek 1") {
			public void run() {
				System.out.println("Uruchomione przez: " + getName());
				CzekoladowyKocioł kocioł = CzekoladowyKocioł.INSTANCE;
				kocioł.napełniaj();
				kocioł.gotuj();
				kocioł.opróżniaj();
			}
		};
		Thread wątek2 = new Thread("Wątek 2") {
			public void run() {
				System.out.println("Uruchomione przez: " + getName());
				CzekoladowyKocioł kocioł = CzekoladowyKocioł.INSTANCE;
				kocioł.napełniaj();
				kocioł.gotuj();
				kocioł.opróżniaj();
			}
		};
		wątek1.start();
		wątek2.start();
	}
}
