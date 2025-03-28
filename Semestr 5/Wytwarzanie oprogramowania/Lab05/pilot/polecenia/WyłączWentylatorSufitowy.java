package org.example.pilot.polecenia;

import org.example.pilot.sterowniki.WentylatorSufitowy;

public class WyłączWentylatorSufitowy implements Polecenie {
    WentylatorSufitowy wentylatorSufitowy;
    int poprzedniaPredkosc;

    public WyłączWentylatorSufitowy(WentylatorSufitowy wentylatorSufitowy) {
        super();
        this.wentylatorSufitowy = wentylatorSufitowy;
    }

    public void wykonaj() {
        poprzedniaPredkosc = wentylatorSufitowy.pobierzSzybkość();
        wentylatorSufitowy.off();
    }

    public void wycofaj() {

        switch (poprzedniaPredkosc) {
            case 0:
                wentylatorSufitowy.off();
            case 1:
                wentylatorSufitowy.wolno();
            case 2:
                wentylatorSufitowy.średnio();
            case 3:
                wentylatorSufitowy.szybko();
        }
    }
}
