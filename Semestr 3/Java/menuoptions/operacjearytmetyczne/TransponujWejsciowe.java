package menuoptions.operacjearytmetyczne;

import matrixpackage.Matrix;
import matrixpackage.MatrixHolder;

import java.util.Scanner;

public class TransponujWejsciowe {
    public static void inputTransposition(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        if (matrixHolder.getA() == null || matrixHolder.getB() == null) {
            System.out.println("\nMacierze nie zostaly utworzone");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        }

        Matrix A = matrixHolder.getA();
        Matrix B = matrixHolder.getB();

        matrixHolder.setA(transpose(A));
        matrixHolder.setB(transpose(B));

        System.out.println("\nPomyslnie transponowano macierze");
        System.out.print("Nacisnij ENTER, by wrocic");

        scanner.nextLine();
    }

    public static Matrix transpose(Matrix matrix) {
        int rows = matrix.getRows();
        int columns = matrix.getColumns();

        Matrix transposedMatrix = new Matrix(columns, rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                int value = matrix.getElement(i, j);
                transposedMatrix.setElement(j, i, value);
            }
        }

        return transposedMatrix;
    }
}
