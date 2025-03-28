package org.example.StarCafe.składniki;

import org.example.StarCafe.SkładnikDekorator;
import org.example.StarCafe.napoje.Napój;

public class Mleko extends SkładnikDekorator {
    Napój napój;

    public Mleko(Napój napój) {
        this.napój = napój;
    }

    @Override
    public String pobierzOpis() {
        return napój.pobierzOpis() + " Mleko";
    }

    public double koszt() {
        return napój.koszt() + 0.10;
    }
}
