/**
 * Program do mnozenia transponowanych macierzy
 *
 * @author Piotr Pietrusewicz 53828
 * @version 1.0
 * @since 2023-10-27
 */

import java.util.Scanner;

import matrixpackage.MatrixHolder;
import menuoptions.WprowadzMacierze;
import menuoptions.OperacjeArytmetyczne;
import menuoptions.WyswietlMacierze;

public class Menu {
    private final MatrixHolder matrixHolder;
    private final WprowadzMacierze wprowadzMacierze;
    private final OperacjeArytmetyczne operacjeArytmetyczne;
    private final WyswietlMacierze wyswietlMacierze;

    public Menu() {
        matrixHolder = new MatrixHolder();
        wprowadzMacierze = new WprowadzMacierze();
        operacjeArytmetyczne = new OperacjeArytmetyczne();
        wyswietlMacierze = new WyswietlMacierze();
    }

    public void displayMainMenu() {
        Scanner scanner = new Scanner(System.in);

        while(true) {
            System.out.println("\n\n Glowne menu");
            System.out.println("[1] Wprowadz macierze wejsciowe");
            System.out.println("[2] Operacje artymetyczne");
            System.out.println("[3] Wyswietl macierze");
            System.out.println("\n[0] Wyjdz\n");

            System.out.print("Wybor: ");

            int menuChoice = scanner.nextInt();

            switch (menuChoice) {
                case 0:
                    scanner.close();
                    System.exit(0);
                case 1:
                    wprowadzMacierze.displayMenu(matrixHolder);
                    break;
                case 2:
                    operacjeArytmetyczne.displayMenu(matrixHolder);
                    break;
                case 3:
                    wyswietlMacierze.displayMenu(matrixHolder);
                    break;
                default:
                    System.out.println("\n\nNiepoprawny wybor.\n");
            }
        }
    }
}
