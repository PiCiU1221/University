package lab09.view.menuOptions;

import lab09.model.PracownicyKlasy.Pracownik;
import lab09.controller.PracownikHolder;
import lab09.Utils.PeselUtils;

import java.util.Scanner;

public class UsunPracownika {
    public static void usunPracownika(PracownikHolder pracownikHolder) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("\n3. Usuń pracownika\n");

        Pracownik pracownikToRemove = null;

        do {
            String pesel;
            do {
                System.out.print("Podaj Identyfikator PESEL  : ");
                pesel = scanner.nextLine();
            } while (!(PeselUtils.werifikacjaPesel(pesel)));

            pracownikToRemove = pracownikHolder.getPracownik(pesel);

            if (pracownikToRemove == null) {
                System.out.println("Pracownik o podanym PESEL nie istnieje. Spróbuj ponownie.");
            }

        } while (pracownikToRemove == null);

        System.out.println("--------------------------------------------------------");

        pracownikToRemove.display();

        System.out.println("--------------------------------------------------------");

        while (true) {
            System.out.println("\n[Enter] - zapisz");
            System.out.println("[Q] - porzuc");

            String confirmation = scanner.nextLine();

            if (confirmation.isEmpty()) {
                pracownikHolder.usunPracownika(pracownikToRemove);

                // Wait for the user to press Enter
                System.out.println("Naciśnij Enter, aby kontynuować...");
                scanner.nextLine();
                break;
            } else if ("Q".equalsIgnoreCase(confirmation)) {
                System.out.println("\nUsunięcie pracownika anulowane.");
                break;
            } else {
                System.out.println("\nNiepoprawny wybór. Spróbuj ponownie.");
            }
        }
    }
}
