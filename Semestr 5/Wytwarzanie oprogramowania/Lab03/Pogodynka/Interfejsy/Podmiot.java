package org.example.Pogodynka.src.pl.edu.zut.wo.wzorce.pogodynka.Interfejsy;

public interface Podmiot {
    public void zarejestrujObserwatora(Obserwator o);
    public void usuńObserwatora(Obserwator o);
    public void powiadomObserwatorów();
}
