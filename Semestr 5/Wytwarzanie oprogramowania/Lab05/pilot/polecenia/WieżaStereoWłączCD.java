package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.WieżaStereo;

public class WieżaStereoWłączCD implements Polecenie {
    WieżaStereo wieżaStereo;

    public WieżaStereoWłączCD(WieżaStereo wieżaStereo) {
        super();
        this.wieżaStereo = wieżaStereo;
    }

    public void wykonaj() {
        wieżaStereo.włącz();
    }

    public void wycofaj() {
        wieżaStereo.wyłącz();
    }
}
