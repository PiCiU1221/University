package lab09.view.menuOptions;

import lab09.model.PracownicyKlasy.Pracownik;
import lab09.controller.PracownikHolder;

import java.util.Scanner;

public class ListaPracownikow {
    public static void wyswietlPracownikow(PracownikHolder pracownikHolder) {
        Scanner scanner = new Scanner(System.in);
        int currentPosition = 0;
        int totalEmployees = pracownikHolder.getSize();

        System.out.println("\n1. Lista pracownikow\n");

        boolean finishFlag = false;

        while (!finishFlag) {
            if (totalEmployees == 0) {
                System.out.println("Brak pracowników do wyświetlenia.");

                // Wait for the user to press Enter
                System.out.print("Naciśnij Enter, aby kontynuować...");
                scanner.nextLine();
                break;
            }

            Pracownik currentEmployee;

            boolean errorFlag = false;

            while (true) {
                if (!errorFlag) {
                    currentEmployee = pracownikHolder.getPracownikAtPosition(currentPosition);
                    currentEmployee.display();
                }

                System.out.println("\n                              [Pozycja: " + (currentPosition + 1) + "/" + totalEmployees + "]");
                System.out.println("[Enter] – następny");
                System.out.println("[Q] – powrót");

                String choice = scanner.nextLine();

                if ("".equals(choice)) {
                    currentPosition = (currentPosition + 1) % totalEmployees;
                    errorFlag = false;
                } else if ("Q".equalsIgnoreCase(choice)) {
                    finishFlag = true;
                    break;
                } else {
                    System.out.println("Nieznane polecenie. Spróbuj ponownie.");
                    errorFlag = true;
                }
            }
        }
    }
}
