package org.example.StarCafe.napoje;

public abstract class Napój {
	protected String opis;

	public Napój() {
		opis = "Nieznany napój";
	}

	public String pobierzOpis() {
		return opis;
	}

	public abstract double koszt();
}