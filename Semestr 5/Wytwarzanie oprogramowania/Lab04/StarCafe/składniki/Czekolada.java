package org.example.StarCafe.składniki;

import org.example.StarCafe.SkładnikDekorator;
import org.example.StarCafe.napoje.Napój;

public class Czekolada extends SkładnikDekorator {
    Napój napój;

    public Czekolada(Napój napój) {
        this.napój = napój;
    }

    @Override
    public String pobierzOpis() {
        return napój.pobierzOpis() + " Czekolada";
    }

    public double koszt() {
        return napój.koszt() + 0.20;
    }
}
