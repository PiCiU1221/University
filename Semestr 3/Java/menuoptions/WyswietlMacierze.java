package menuoptions;

import matrixpackage.MatrixHolder;
import menuoptions.wyswietlmacierze.WyswietlWejsciowe;
import menuoptions.wyswietlmacierze.WyswietlWyjsciowe;

import java.util.Scanner;

public class WyswietlMacierze {
    private final WyswietlWejsciowe wyswietlWejsciowe;
    private final WyswietlWyjsciowe wyswietlWyjsciowe;

    public WyswietlMacierze() {
        wyswietlWejsciowe = new WyswietlWejsciowe();
        wyswietlWyjsciowe = new WyswietlWyjsciowe();
    }

    public void displayMenu(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n\n 3.0 Wyswietl macierze");
            System.out.println("[1] Wyswietl wejsciowe");
            System.out.println("[2] Wyswietl wynikowa");
            System.out.println("\n[0] Powrot\n");

            System.out.print("Wybor: ");

            int menuChoice = scanner.nextInt();

            switch (menuChoice) {
                case 0:
                    return;
                case 1:
                    wyswietlWejsciowe.displayInput(matrixHolder);
                    break;
                case 2:
                    wyswietlWyjsciowe.displayOutput(matrixHolder);
                    break;
                default:
                    System.out.println("\n\nNiepoprawny wybor.\n");
            }
        }
    }
}
