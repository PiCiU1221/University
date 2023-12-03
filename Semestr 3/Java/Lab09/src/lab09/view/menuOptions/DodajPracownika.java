package lab09.view.menuOptions;

import lab09.model.PracownicyKlasy.Dyrektor;
import lab09.model.PracownicyKlasy.Handlowiec;
import lab09.model.PracownicyKlasy.Pracownik;
import lab09.controller.PracownikHolder;
import lab09.Utils.StringUtils;
import lab09.Utils.PeselUtils;

import java.math.BigDecimal;
import java.util.Scanner;

public class DodajPracownika {
    public static void dodajPracownika(PracownikHolder pracownikHolder) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("\n2. Dodaj pracownika\n");

        String stanowisko;

        while (true) {
            System.out.print("[D]yrektor/[H]andlowiec    : ");
            stanowisko = scanner.nextLine();

            if ("D".equalsIgnoreCase(stanowisko) || "H".equalsIgnoreCase(stanowisko)) {
                break;
            } else {
                System.out.println("\nZły wybór\n");
            }
        }

        System.out.println("--------------------------------------------------------");

        // Deklarujemy zmienna wczesniej by uniknac bledow
        String pesel;

        do {
            System.out.print("Identyfikator PESEL        : ");
            pesel = scanner.nextLine();

            if (pracownikHolder.isPeselInUse(pesel)) {
                System.out.println("\nPodany PESEL już istnieje.\n");
            }
        } while (!(PeselUtils.werifikacjaPesel(pesel) && !pracownikHolder.isPeselInUse(pesel)));

        System.out.print("Imię                       : ");
        String imie = scanner.nextLine();
        imie = StringUtils.capitalizeFirstLetter(imie);

        System.out.print("Nazwisko                   : ");
        String nazwisko = scanner.nextLine();
        nazwisko = StringUtils.capitalizeFirstLetter(nazwisko);

        System.out.print("Wynagrodzenie              : ");
        int wynagrodzenie = scanner.nextInt();

        System.out.print("Telefon sluzbowy numer     : ");
        int telefon = scanner.nextInt();

        Pracownik nowyPracownik = null;

        if ("D".equalsIgnoreCase(stanowisko)) {
            nowyPracownik = dodajDyrektora(pesel, imie, nazwisko, wynagrodzenie, telefon);
        } else if ("H".equalsIgnoreCase(stanowisko)) {
            nowyPracownik = dodajHandlowca(pesel, imie, nazwisko, wynagrodzenie, telefon);
        }

        // Consume the newline character left in the input buffer
        scanner.nextLine();

        while (true) {
            System.out.println("\n[Enter] - zapisz");
            System.out.println("[Q] - porzuc");

            String confirmation = scanner.nextLine();

            if (confirmation.isEmpty()) {
                System.out.println("Pracownik dodany pomyślnie.");
                pracownikHolder.dodajPracownika(nowyPracownik);

                // Wait for the user to press Enter
                System.out.println("Naciśnij Enter, aby kontynuować...");
                scanner.nextLine();
                break;
            } else if ("Q".equalsIgnoreCase(confirmation)) {
                System.out.println("\nDodawanie pracownika anulowane.");
                break;
            } else {
                System.out.println("\nNiepoprawny wybór. Spróbuj ponownie.");
            }
        }
    }

    private static Dyrektor dodajDyrektora(String pesel, String imie, String nazwisko, int wynagrodzenie, int telefon) {
        Scanner scanner = new Scanner(System.in);

        // Additional details specific to Dyrektor
        System.out.print("Dodatek Służbowy           : ");
        BigDecimal dodatekSluzbowy = scanner.nextBigDecimal();

        // Consume the newline character left in the input buffer
        scanner.nextLine();

        System.out.print("Karta Służbowa             : ");
        String kartaSluzbowa = scanner.nextLine();

        System.out.print("Limit Kosztów              : ");
        int limitKosztow = scanner.nextInt();

        System.out.println("--------------------------------------------------------");

        Dyrektor dyrektor = new Dyrektor();

        dyrektor.setPesel(pesel);
        dyrektor.setImie(imie);
        dyrektor.setNazwisko(nazwisko);
        dyrektor.setStanowisko("Dyrektor");
        dyrektor.setWynagrodzenie(wynagrodzenie);
        dyrektor.setTelefon(telefon);
        dyrektor.setDodatekSluzbowy(dodatekSluzbowy);
        dyrektor.setKartaSluzbowa(kartaSluzbowa);
        dyrektor.setLimitKosztow(limitKosztow);

        return dyrektor;
    }

    private static Handlowiec dodajHandlowca(String pesel, String imie, String nazwisko, int wynagrodzenie, int telefon) {
        Scanner scanner = new Scanner(System.in);

        // Additional details specific to Handlowiec
        System.out.print("Prowizja (%)               : ");
        int prowizja = scanner.nextInt();

        System.out.print("Limit Prowizji             : ");

        int limitProwizji = scanner.nextInt();

        Handlowiec handlowiec = new Handlowiec();

        handlowiec.setPesel(pesel);
        handlowiec.setImie(imie);
        handlowiec.setNazwisko(nazwisko);
        handlowiec.setStanowisko("Handlowiec");
        handlowiec.setWynagrodzenie(wynagrodzenie);
        handlowiec.setTelefon(telefon);
        handlowiec.setProwizja(prowizja);
        handlowiec.setLimitProwizji(limitProwizji);

        return handlowiec;
    }
}