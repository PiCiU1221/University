package lab09.view.menuOptions;

import lab09.controller.PracownikHolder;

import java.util.Scanner;

public class KopiaZapasowa {
    public static void kopiaZapasowa(PracownikHolder pracownikHolder) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("\n4. Kopia Zapasowa\n");

        String wyborOpcji;

        while (true) {
            System.out.print("[Z]achowaj/[O]dtwórz   :  ");
            wyborOpcji = scanner.nextLine();

            if ("Z".equalsIgnoreCase(wyborOpcji) || "O".equalsIgnoreCase(wyborOpcji)) {
                break;
            } else {
                System.out.println("\nZły wybór\n");
            }
        }

        System.out.println("--------------------------------------------------------");

        String wyborKompresji = null;

        if ("Z".equalsIgnoreCase(wyborOpcji)) {
            while (true) {
                System.out.print("Kompresja [G]zip/[Z]ip :  ");
                wyborKompresji = scanner.nextLine();

                if ("G".equalsIgnoreCase(wyborKompresji) || "Z".equalsIgnoreCase(wyborKompresji)) {
                    break;
                } else {
                    System.out.println("\nZły wybór\n");
                }
            }
        }

        System.out.print("Nazwa pliku            : ");
        String nazwaPliku = scanner.nextLine();

        System.out.println("--------------------------------------------------------");

        if ("Z".equalsIgnoreCase(wyborOpcji)) {
            while (true) {
                System.out.println("[Enter] - potwierdź");
                System.out.println("[Q] - porzuc");

                String confirmation = scanner.nextLine();

                if (confirmation.isEmpty()) {
                    if ("G".equalsIgnoreCase(wyborKompresji)) {
                        pracownikHolder.saveToGZipFile(nazwaPliku);
                    } else if ("Z".equalsIgnoreCase(wyborKompresji)) {
                        pracownikHolder.saveToZipFile(nazwaPliku);
                    }

                    // Wait for the user to press Enter
                    System.out.print("Naciśnij Enter, aby kontynuować...");
                    scanner.nextLine();
                    break;
                } else if ("Q".equalsIgnoreCase(confirmation)) {
                    System.out.println("\nZachowanie danych anulowane.");
                    break;
                } else {
                    System.out.println("\nNiepoprawny wybór. Spróbuj ponownie.");
                }
            }
        } else {
            while (true) {
                System.out.println("[Enter] - potwierdź");
                System.out.println("[Q] - porzuc");

                String confirmation = scanner.nextLine();

                if (confirmation.isEmpty()) {
                    pracownikHolder.readFromFile(nazwaPliku);

                    // Wait for the user to press Enter
                    System.out.println("Naciśnij Enter, aby kontynuować...");
                    scanner.nextLine();
                    break;
                } else if ("Q".equalsIgnoreCase(confirmation)) {
                    System.out.println("\nOdtwarzanie danych anulowane.");
                    break;
                } else {
                    System.out.println("\nNiepoprawny wybór. Spróbuj ponownie.");
                }
            }
        }
    }
}
