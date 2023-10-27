package menuoptions;

import matrixpackage.MatrixHolder;
import menuoptions.wprowadzmacierze.UtworzMacierze;
import menuoptions.wprowadzmacierze.WprowadzDane;
import menuoptions.wprowadzmacierze.WprowadzWymiary;

import java.util.Scanner;

public class WprowadzMacierze {
    private final WprowadzWymiary wprowadzWymiary;
    private final UtworzMacierze utworzMacierze;
    private final WprowadzDane wprowadzDane;

    public WprowadzMacierze() {
        wprowadzWymiary = new WprowadzWymiary();
        utworzMacierze = new UtworzMacierze();
        wprowadzDane = new WprowadzDane();
    }

    public void displayMenu(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n\n 1.0 Wprowadz macierze");
            System.out.println("[1] Wprowadz wymiary macierzy");
            System.out.println("[2] Utworz macierze A i B");
            System.out.println("[3] Wprowadz dane do macierzy");
            System.out.println("\n[0] Powrot\n");

            System.out.print("Wybor: ");

            int menuChoice = scanner.nextInt();

            switch (menuChoice) {
                case 0:
                    return;
                case 1:
                    wprowadzWymiary.enterDimensions(utworzMacierze);
                    break;
                case 2:
                    utworzMacierze.createMatrices(matrixHolder);
                    break;
                case 3:
                    wprowadzDane.enterData(matrixHolder);
                    break;
                default:
                    System.out.println("\n\nNiepoprawny wybor.\n");
            }
        }
    }
}
