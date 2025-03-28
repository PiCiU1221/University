package org.example.StarCafe.składniki;

import org.example.StarCafe.SkładnikDekorator;
import org.example.StarCafe.napoje.Napój;

public class BitaŚmietana extends SkładnikDekorator {
    Napój napój;

    public BitaŚmietana(Napój napój) {
        this.napój = napój;
    }

    @Override
    public String pobierzOpis() {
        return napój.pobierzOpis() + " Bita śmietana";
    }

    public double koszt() {
        return napój.koszt() + 0.10;
    }
}
