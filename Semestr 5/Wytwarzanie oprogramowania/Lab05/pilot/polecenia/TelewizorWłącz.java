package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.TV;

public class TelewizorWłącz implements Polecenie {
    TV tv;

    public TelewizorWłącz(TV tv) {
        super();
        this.tv = tv;
    }

    public void wykonaj() {
        tv.włącz();
    }

    public void wycofaj() {
        tv.wyłącz();
    }
}