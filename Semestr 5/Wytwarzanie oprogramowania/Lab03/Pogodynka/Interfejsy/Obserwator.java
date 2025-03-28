package org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy;

public interface Obserwator {
    public void aktualizacja(float temperatura,
                             float wilgotność,
                             float ciśnienie);
}
