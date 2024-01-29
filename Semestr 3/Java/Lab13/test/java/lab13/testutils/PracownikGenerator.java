package lab13.testutils;

import lab13.model.Dyrektor;
import lab13.model.Handlowiec;
import lab13.model.base.Pracownik;

import java.util.Random;

public class PracownikGenerator {
    public static Pracownik generateRandomPracownik() {
        String pesel = PeselGenerator.generatePesel();
        String imie = StringGenerator.generateRandomString();
        String nazwisko = StringGenerator.generateRandomString();

        Random random = new Random();
        int profession = random.nextInt(2);

        if (profession == 0) {
            Handlowiec handlowiec = new Handlowiec();
            handlowiec.setPesel(pesel);
            handlowiec.setImie(imie);
            handlowiec.setNazwisko(nazwisko);
            handlowiec.setStanowisko("Handlowiec");
            return handlowiec;
        } else {
            Dyrektor dyrektor = new Dyrektor();
            dyrektor.setPesel(pesel);
            dyrektor.setImie(imie);
            dyrektor.setNazwisko(nazwisko);
            dyrektor.setStanowisko("Dyrektor");
            return dyrektor;
        }
    }
}
