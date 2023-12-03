package lab09.model.PracownicyKlasy;

import java.io.Serializable;
import java.math.BigDecimal;

public class Dyrektor extends Pracownik implements Serializable {
    private BigDecimal dodatekSluzbowy;
    private String kartaSluzbowa;
    private int limitKosztow;

    @Override
    public void display() {
        System.out.println("Identyfikator PESEL        : " + getPesel());
        System.out.println("Imię                       : " + getImie());
        System.out.println("Nazwisko                   : " + getNazwisko());
        System.out.println("Stanowisko                 : " + getStanowisko());
        System.out.println("Wynagrodzenie (zł)         : " + getWynagrodzenie());
        System.out.println("Telefon służbowy numer     : " + getTelefon());

        System.out.println("Dodatek Służbowy (zl)      : " + dodatekSluzbowy);
        System.out.println("Karta Służbowa numer       : " + kartaSluzbowa);
        System.out.println("Limit Kosztów (zl)         : " + limitKosztow);
    }

    // Getters
    public BigDecimal getDodatekSluzbowy() {
        return dodatekSluzbowy;
    }

    public String getKartaSluzbowa() {
        return kartaSluzbowa;
    }

    public long getLimitKosztow() {
        return limitKosztow;
    }

    // Setters
    public void setDodatekSluzbowy(BigDecimal dodatekSluzbowy) {
        this.dodatekSluzbowy = dodatekSluzbowy;
    }

    public void setKartaSluzbowa(String kartaSluzbowa) {
        this.kartaSluzbowa = kartaSluzbowa;
    }

    public void setLimitKosztow(int limitKosztow) {
        this.limitKosztow = limitKosztow;
    }
}
