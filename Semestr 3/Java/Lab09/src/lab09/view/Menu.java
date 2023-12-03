package lab09.view;

import lab09.controller.PracownikHolder;
import lab09.view.menuOptions.DodajPracownika;
import lab09.view.menuOptions.KopiaZapasowa;
import lab09.view.menuOptions.ListaPracownikow;
import lab09.view.menuOptions.UsunPracownika;

public class Menu {
    private static final PracownikHolder pracownikHolder = new PracownikHolder();

    public static void displayMenu() {
        System.out.println("\nMENU");
        System.out.println("  1. Lista pracowników");
        System.out.println("  2. Dodaj pracownika");
        System.out.println("  3. Usuń pracownika");
        System.out.println("  4. Kopia zapasowa\n");
        System.out.print("Wybór> ");
    }

    public static void handleChoice(int choice) {
        switch (choice) {
            case 1:
                ListaPracownikow.wyswietlPracownikow(pracownikHolder);
                break;
            case 2:
                DodajPracownika.dodajPracownika(pracownikHolder);
                break;
            case 3:
                UsunPracownika.usunPracownika(pracownikHolder);
                break;
            case 4:
                KopiaZapasowa.kopiaZapasowa(pracownikHolder);
                break;
            default:
                System.out.println("\nZły wybór. Spróbuj jeszcze raz");
        }
    }
}
