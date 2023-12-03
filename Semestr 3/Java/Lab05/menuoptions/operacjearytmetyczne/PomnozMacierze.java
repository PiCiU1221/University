package menuoptions.operacjearytmetyczne;

import matrixpackage.Matrix;
import matrixpackage.MatrixHolder;

import java.util.Scanner;

public class PomnozMacierze {
    public static void multiplyMatrices(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        if (matrixHolder.getA() == null || matrixHolder.getB() == null) {
            System.out.println("\nMacierze nie zostaly utworzone");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        } else if (matrixHolder.getRowsA() != matrixHolder.getColumnsB()) {
            System.out.println("\nMacierze maja niepoprawne wymiary");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        }

        Matrix A = matrixHolder.getA();
        Matrix B = matrixHolder.getB();

        matrixHolder.setC(multiply(A, B));

        System.out.println("\nPomyslnie wymnozono macierze");
        System.out.print("Nacisnij ENTER, by wrocic");

        scanner.nextLine();
    }

    private static Matrix multiply(Matrix A, Matrix B) {
        int aRows = A.getRows();
        int aColumns = A.getColumns();
        int bRows = B.getRows();
        int bColumns = B.getColumns();

        if (aColumns != bRows) {
            throw new IllegalArgumentException("Wrong matrix dimensions.");
        }

        Matrix resultMatrix = new Matrix(aRows, bColumns);

        for (int i = 0; i < aRows; i++) {
            for (int j = 0; j < bColumns; j++) {
                int sum = 0;
                for (int k = 0; k < aColumns; k++) {
                    sum += A.getElement(i, k) * B.getElement(k, j);
                }
                resultMatrix.setElement(i, j, sum);
            }
        }

        return resultMatrix;
    }
}
