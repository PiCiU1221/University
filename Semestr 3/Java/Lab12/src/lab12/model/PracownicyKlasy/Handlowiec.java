package lab12.model.PracownicyKlasy;

import java.io.Serializable;

public class Handlowiec extends Pracownik implements Serializable {
    private int prowizja;
    private long limitProwizji;

    @Override
    public void display() {
        System.out.println("Identyfikator PESEL        : " + getPesel());
        System.out.println("Imię                       : " + getImie());
        System.out.println("Nazwisko                   : " + getNazwisko());
        System.out.println("Stanowisko                 : " + getStanowisko());
        System.out.println("Wynagrodzenie (zł)         : " + getWynagrodzenie());
        System.out.println("Telefon służbowy numer     : " + getTelefon());

        System.out.println("Prowizja (%)               : " + prowizja);
        System.out.println("Limit Prowizji             : " + limitProwizji);
    }

    // Getters
    public int getProwizja() {
        return prowizja;
    }

    public long getLimitProwizji() {
        return limitProwizji;
    }

    // Setters
    public void setProwizja(int prowizja) {
        this.prowizja = prowizja;
    }

    public void setLimitProwizji(long limitProwizji) {
        this.limitProwizji = limitProwizji;
    }
}
