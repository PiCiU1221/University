package org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.Kwakanie;

import org.example.SymulatorKaczki.src.pl.edu.zut.wo.wzorce.symulator.KwakanieInterfejs;

public class NieKwacz implements KwakanieInterfejs {
    @Override
    public void kwacz() {
        System.out.println("Nie kwaczę.");
    }
}
