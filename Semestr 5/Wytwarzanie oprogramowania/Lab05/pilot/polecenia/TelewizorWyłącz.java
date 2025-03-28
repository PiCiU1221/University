package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.TV;

public class TelewizorWyłącz implements Polecenie {
    TV tv;

    public TelewizorWyłącz(TV tv) {
        super();
        this.tv = tv;
    }

    public void wykonaj() {
        tv.wyłącz();
    }

    public void wycofaj() {
        tv.włącz();
    }
}