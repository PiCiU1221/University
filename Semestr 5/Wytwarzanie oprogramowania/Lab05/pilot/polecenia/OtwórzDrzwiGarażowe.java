package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.DrzwiGarażu;

public class OtwórzDrzwiGarażowe implements Polecenie {
    DrzwiGarażu drzwiGarażu;

    public OtwórzDrzwiGarażowe(DrzwiGarażu drzwiGarażu) {
        super();
        this.drzwiGarażu = drzwiGarażu;
    }

    public void wykonaj() {
        drzwiGarażu.podnieś();
    }

    public void wycofaj() {
        drzwiGarażu.opuść();
    }
}
