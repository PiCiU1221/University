package org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.wyświetl;

import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy.Obserwator;
import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy.WyświetlElement;

public class WarunkiBieżąceWyświetlanie implements Obserwator, WyświetlElement {

	private float temperatura;
	private float wilgotność;
	private float ciśnienie;

	@Override
	public void aktualizacja(float temperatura, float wilgotność, float ciśnienie) {
		this.temperatura = temperatura;
		this.wilgotność = wilgotność;
		this.ciśnienie = ciśnienie;
		wyświetl();
	}

	@Override
	public void wyświetl() {
		System.out.println("Warunki bieżące " + temperatura + " stopni C oraz " + wilgotność + "% wilgotność");
	}

}