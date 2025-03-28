package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.TV;
import org.example.pilot.sterowniki.WieżaStereo;

public class PrzełączZestawNaDVD implements Polecenie {
    WieżaStereo wieżaStereo;
    TV tv;

    public PrzełączZestawNaDVD(WieżaStereo wieżaStereo, TV tv) {
        super();
        this.wieżaStereo = wieżaStereo;
        this.tv = tv;
    }

    public void wykonaj() {
        wieżaStereo.ustawDVD();
        tv.ustawDVD();
    }

    public void wycofaj() {
        wieżaStereo.wyłącz();
        tv.wyłącz();
    }
}