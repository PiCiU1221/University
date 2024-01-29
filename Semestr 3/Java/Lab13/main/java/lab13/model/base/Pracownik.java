package lab13.model.base;

import java.io.Serializable;

public abstract class Pracownik implements Serializable {
    private String pesel;
    private String imie;
    private String nazwisko;
    private String stanowisko;
    private int wynagrodzenie;
    private int telefon;

    // Abstract display method
    public abstract void display();

    // Getters
    public String getPesel() {
        return pesel;
    }

    public String getImie() {
        return imie;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public String getStanowisko() {
        return stanowisko;
    }

    public int getWynagrodzenie() {
        return wynagrodzenie;
    }

    public int getTelefon() {
        return telefon;
    }

    // Setters
    public void setPesel(String pesel) {
        this.pesel = pesel;
    }

    public void setImie(String imie) {
        this.imie = imie;
    }

    public void setNazwisko(String nazwisko) {
        this.nazwisko = nazwisko;
    }

    public void setStanowisko(String stanowisko) {
        this.stanowisko = stanowisko;
    }

    public void setWynagrodzenie(int wynagrodzenie) {
        this.wynagrodzenie = wynagrodzenie;
    }

    public void setTelefon(int telefon) {
        this.telefon = telefon;
    }
}
