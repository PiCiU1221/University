package org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator;

public class Kaczka {
    private LatanieInterfejs latanieInterfejs;
    private KwakanieInterfejs kwakanieInterfejs;

    public void pływaj() {
        System.out.println("Pływam jak kaczka.");
    }
    public void wyświetl() {
        System.out.println("Wyglądam jak kaczka.");
    }

    public void wykonajKwacz() {
        kwakanieInterfejs.kwacz();
    }

    public void wykonajLec() {
        latanieInterfejs.lec();
    }

    public void ustawKwaczInt(KwakanieInterfejs kwakanieInterfejs) {
        this.kwakanieInterfejs = kwakanieInterfejs;
    }

    public void ustawLećInt(LatanieInterfejs latanieInterfejs) {
        this.latanieInterfejs = latanieInterfejs;
    }
}
