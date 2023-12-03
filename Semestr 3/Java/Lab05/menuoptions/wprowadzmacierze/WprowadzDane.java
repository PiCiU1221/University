package menuoptions.wprowadzmacierze;

import matrixpackage.MatrixHolder;

import java.util.Scanner;

public class WprowadzDane {
    public void enterData(MatrixHolder matrixHolder) {
        System.out.println("\n1.3 Uzupelnienie wartosci macierzy");

        Scanner scanner = new Scanner(System.in);

        if (matrixHolder.getA() == null || matrixHolder.getB() == null) {
            System.out.println("\nMacierze nie zostaly utworzone");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        }

        matrixHolder.displayA();

        for (int i = 0; i < matrixHolder.getRowsA(); i++) {
            for (int j = 0; j < matrixHolder.getColumnsA(); j++) {
                System.out.print("Wprowadz wartosc dla: [" + i + "][" + j + "]:");
                matrixHolder.setElementA(i, j, scanner.nextInt());

                matrixHolder.displayA();
            }
        }

        matrixHolder.displayB();

        for (int i = 0; i < matrixHolder.getRowsB(); i++) {
            for (int j = 0; j < matrixHolder.getColumnsB(); j++) {
                System.out.print("Wprowadz wartosc dla: [" + i + "][" + j + "]:");
                matrixHolder.setElementB(i, j, scanner.nextInt());

                matrixHolder.displayB();
            }
        }

        System.out.println("\nPomyslnie wprowadzono dane");
        System.out.print("Nacisnij ENTER, by wrocic");

        scanner.nextLine();
    }
}
