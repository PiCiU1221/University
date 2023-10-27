package menuoptions.operacjearytmetyczne;

import matrixpackage.Matrix;
import matrixpackage.MatrixHolder;

import java.util.Scanner;

import static menuoptions.operacjearytmetyczne.TransponujWejsciowe.transpose;

public class TransponujWynikowa {
    public static void outputTransposition(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        if (matrixHolder.getC() == null) {
            System.out.println("\nMacierz nie zostala utworzona");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        }

        Matrix C = matrixHolder.getC();

        matrixHolder.setC(transpose(C));

        System.out.println("\nPomyslnie transponowano macierz");
        System.out.print("Nacisnij ENTER, by wrocic");

        scanner.nextLine();
    }
}
