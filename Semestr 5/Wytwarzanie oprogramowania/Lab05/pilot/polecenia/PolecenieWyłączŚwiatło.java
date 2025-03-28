package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.Światło;

public class PolecenieWyłączŚwiatło implements Polecenie {
    Światło światło;

    public PolecenieWyłączŚwiatło(Światło światło) {
        super();
        this.światło = światło;
    }

    public void wykonaj() {
        światło.włącz();
    }

    public void wycofaj() {
        światło.wyłącz();
    }
}
