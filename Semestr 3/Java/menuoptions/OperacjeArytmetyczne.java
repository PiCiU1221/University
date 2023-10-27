package menuoptions;

import matrixpackage.MatrixHolder;
import menuoptions.operacjearytmetyczne.PomnozMacierze;
import menuoptions.operacjearytmetyczne.TransponujWejsciowe;
import menuoptions.operacjearytmetyczne.TransponujWynikowa;

import java.util.Scanner;

public class OperacjeArytmetyczne {
    public void displayMenu(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n\n 2.0 Operacje arytmetyczne");
            System.out.println("[1] Transponuj wejsciowe");
            System.out.println("[2] Pomnoz macierze");
            System.out.println("[3] Transponuj wynikowa");
            System.out.println("\n[0] Powrot\n");

            System.out.print("Wybor: ");

            int menuChoice = scanner.nextInt();

            switch (menuChoice) {
                case 0:
                    return;
                case 1:
                    TransponujWejsciowe.inputTransposition(matrixHolder);
                    break;
                case 2:
                    PomnozMacierze.multiplyMatrices(matrixHolder);
                    break;
                case 3:
                    TransponujWynikowa.outputTransposition(matrixHolder);
                    break;
                default:
                    System.out.println("\n\nNiepoprawny wybor.\n");
            }
        }
    }
}
