package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.Jacuzzi;

public class WyłączJacuzzi implements Polecenie {
    Jacuzzi jacuzzi;

    public WyłączJacuzzi(Jacuzzi jacuzzi) {
        super();
        this.jacuzzi = jacuzzi;
    }

    public void wykonaj() {
        jacuzzi.wyłącz();
    }

    public void wycofaj() {
        jacuzzi.włącz();
    }
}