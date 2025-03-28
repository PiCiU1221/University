package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.DrzwiGarażu;

public class ZamknijDrzwiGarażowe implements Polecenie {
    DrzwiGarażu drzwiGarażu;

    public ZamknijDrzwiGarażowe(DrzwiGarażu drzwiGarażu) {
        super();
        this.drzwiGarażu = drzwiGarażu;
    }

    public void wykonaj() {
        drzwiGarażu.opuść();
    }

    public void wycofaj() {
        drzwiGarażu.podnieś();
    }
}
