package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.Jacuzzi;

public class PrzygotujJacuzzi implements Polecenie {
    Jacuzzi jacuzzi;

    public PrzygotujJacuzzi(Jacuzzi jacuzzi) {
        super();
        this.jacuzzi = jacuzzi;
    }

    public void wykonaj() {
        jacuzzi.włącz();
        jacuzzi.cyrkulacja();
        jacuzzi.włączDysze();
        jacuzzi.ustawTemperaturę(35);
    }

    public void wycofaj() {
        jacuzzi.wyłącz();
    }
}