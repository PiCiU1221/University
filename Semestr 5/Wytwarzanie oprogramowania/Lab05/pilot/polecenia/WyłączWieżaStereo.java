package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.WieżaStereo;

public class WyłączWieżaStereo implements Polecenie {
    WieżaStereo wieżaStereo;

    public WyłączWieżaStereo(WieżaStereo wieżaStereo) {
        super();
        this.wieżaStereo = wieżaStereo;
    }

    public void wykonaj() {
        wieżaStereo.wyłącz();
    }

    public void wycofaj() {
        wieżaStereo.włącz();
    }
}
