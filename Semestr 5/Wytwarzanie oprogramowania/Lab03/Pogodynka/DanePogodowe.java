package org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka;

import java.util.ArrayList;

import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy.Obserwator;
import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy.Podmiot;

public class DanePogodowe implements Podmiot {
	private float temperatura;
	private float wilgotność;
	private float ciśnienie;
	
	private ArrayList<Obserwator> obserwatorzy = new ArrayList<>();

	public void odczytyZmiana(){
		float temp = pobierzTemperaturę();
		float wilgotność = pobierzWilgotność();
		float ciśnienie = pobierzCiśnienie();
	}

	private float pobierzTemperaturę(){
		return temperatura;
	}

	private float pobierzWilgotność(){
		return wilgotność;
	}

	private float pobierzCiśnienie(){
		return ciśnienie;
	}
	
	public void ustawOdczyty(float temperatura, float wilgotność, float ciśnienie) {
		this.temperatura = temperatura;
		this.wilgotność = wilgotność;
		this.ciśnienie = ciśnienie;
		odczytyZmiana();
	}

	@Override
	public void zarejestrujObserwatora(Obserwator o) {
		obserwatorzy.add(o);
	}

	@Override
	public void usuńObserwatora(Obserwator o) {
		obserwatorzy.remove(o);
	}

	@Override
	public void powiadomObserwatorów() {
		for (Obserwator o : obserwatorzy) {
			o.aktualizacja(temperatura, wilgotność, ciśnienie);
		}
	}
}
