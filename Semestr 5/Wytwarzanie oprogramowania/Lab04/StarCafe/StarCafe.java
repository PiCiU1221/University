package org.example.StarCafe;

import org.example.StarCafe.napoje.MocnoPalona;
import org.example.StarCafe.napoje.Napój;
import org.example.StarCafe.składniki.BitaŚmietana;
import org.example.StarCafe.składniki.Czekolada;

public class StarCafe {
	public static void main(String... params) {
		Napój napój = new MocnoPalona();
		napój = new Czekolada(napój);
		napój = new BitaŚmietana(napój);
		System.out.println(napój.pobierzOpis() + " " + napój.koszt() + "zł");
	}
}
