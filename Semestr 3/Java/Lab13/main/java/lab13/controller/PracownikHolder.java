package lab13.controller;

import lab13.model.base.Pracownik;

import java.util.ArrayList;
import java.util.List;

public class PracownikHolder {
    private final List<Pracownik> pracownicy;

    public PracownikHolder() {
        this.pracownicy = new ArrayList<>();
    }

    public void addPracownik(Pracownik pracownik) {
        pracownicy.add(pracownik);
    }

    public void deletePracownik(Pracownik pracownik) {
        if (pracownik != null) {
            pracownicy.remove(pracownik);
            System.out.println("Pracownik usunięty pomyślnie.");
        } else {
            System.out.println("Podany pracownik nie istnieje.");
        }
    }

    public Pracownik getPracownik(String pesel) {
        for (Pracownik pracownik : pracownicy) {
            if (pracownik.getPesel().equals(pesel)) {
                return pracownik;
            }
        }
        return null;
    }

    public int getSize() {
        return pracownicy.size();
    }

    public Pracownik getPracownikAtIndex(int i) {
        if (i >= 0 && i < pracownicy.size()) {
            return pracownicy.get(i);
        } else {
            return null;
        }
    }

    public boolean isPeselInUse(String pesel) {
        for (Pracownik pracownik : pracownicy) {
            if (pracownik.getPesel().equals(pesel)) {
                return true;
            }
        }
        return false;
    }
}