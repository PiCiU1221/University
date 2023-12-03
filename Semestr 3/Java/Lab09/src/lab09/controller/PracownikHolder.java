package lab09.controller;

import lab09.model.PracownicyKlasy.Pracownik;
import lab09.Utils.FileUtils;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class PracownikHolder implements Serializable {
    private final List<Pracownik> pracownicy;

    public PracownikHolder() {
        this.pracownicy = new ArrayList<>();
    }

    public void dodajPracownika(Pracownik pracownik) {
        pracownicy.add(pracownik);
    }

    public void wyswietlListePracownikow() {
        System.out.println("Lista pracowników:");
        for (Pracownik pracownik : pracownicy) {
            System.out.println(pracownik);
        }
    }

    public int getSize() {
        return pracownicy.size();
    }

    public Pracownik getPracownikAtPosition(int position) {
        if (position >= 0 && position < pracownicy.size()) {
            return pracownicy.get(position);
        } else {
            throw new IndexOutOfBoundsException("Invalid position");
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

    public void usunPracownika(Pracownik pracownik) {
        if (pracownik != null) {
            pracownicy.remove(pracownik);
            System.out.println("Pracownik usunięty pomyślnie.");
        } else {
            System.out.println("Podany pracownik nie istnieje.");
        }
    }

    public void saveToGZipFile(String fileName) {
        FileUtils.saveToGZipFile(this, fileName);
    }

    public void saveToZipFile(String fileName) {
        FileUtils.saveToZipFile(this, fileName);
    }

    public void readFromFile(String fileName) {
        PracownikHolder loadedData = FileUtils.readFromFile(fileName);
        if (loadedData != null) {
            pracownicy.clear();
            pracownicy.addAll(loadedData.pracownicy);
            System.out.println("Dane wczytane pomyślnie.");
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