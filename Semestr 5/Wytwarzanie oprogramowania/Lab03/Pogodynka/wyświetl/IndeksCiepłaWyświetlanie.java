package org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.wyświetl;

import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy.Obserwator;
import org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy.WyświetlElement;

public class IndeksCiepłaWyświetlanie implements Obserwator, WyświetlElement {
    private float temperatura;
    private float wilgotność;
    private float ciśnienie;

    public void aktualizacja(float temperatura, float wilgotność, float ciśnienie) {
        this.temperatura = temperatura;
        this.wilgotność = wilgotność;
        this.ciśnienie = ciśnienie;
        wyświetl();
    }

    public void wyświetl() {
        System.out.println("Indeks ciepła: " + computeHeatIndex(temperatura, wilgotność));
    }

    private float computeHeatIndex(float t, float rh) {
        float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh)
                + (0.00941695 * (t * t)) + (0.00728898 * (rh * rh))
                + (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
                (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
                (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
                (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
                0.000000000843296 * (t * t * rh * rh * rh)) -
                (0.0000000000481975 * (t * t * t * rh * rh * rh)));
        return index;
    }
}
