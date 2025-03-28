package org.example.StarCafe.składniki;

import org.example.StarCafe.SkładnikDekorator;
import org.example.StarCafe.napoje.Napój;

public class MleczkoSojowe extends SkładnikDekorator {
    Napój napój;

    public MleczkoSojowe(Napój napój) {
        this.napój = napój;
    }

    @Override
    public String pobierzOpis() {
        return napój.pobierzOpis() + " Mleczko sojowe";
    }

    public double koszt() {
        return napój.koszt() + 0.15;
    }
}
