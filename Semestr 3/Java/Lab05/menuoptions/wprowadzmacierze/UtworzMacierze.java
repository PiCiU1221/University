package menuoptions.wprowadzmacierze;

import matrixpackage.Matrix;
import matrixpackage.MatrixHolder;

import java.util.Scanner;

public class UtworzMacierze {
    private int aRows, aColumns, bRows, bColumns;

    public void setDimensions(int aRows, int aColumns, int bRows, int bColumns) {
        this.aRows = aRows;
        this.aColumns = aColumns;
        this.bRows = bRows;
        this.bColumns = bColumns;
    }

    public void createMatrices(MatrixHolder matrixHolder) {
        System.out.println("\n1.2 Utworz macierze");

        Scanner scanner = new Scanner(System.in);

        if (aRows > 0 && aColumns > 0 && bRows > 0 && bColumns > 0) {
            Matrix A = new Matrix(aRows, aColumns);
            Matrix B = new Matrix(bRows, bColumns);

            matrixHolder.setA(A);
            matrixHolder.setB(B);

            System.out.println("\nPomyslnie utworzono macierze");
        } else {
            System.out.println("\nBledne wymiary macierzy");            
        }

        System.out.print("Nacisnij ENTER, by wrocic");

        scanner.nextLine();
    }
}
