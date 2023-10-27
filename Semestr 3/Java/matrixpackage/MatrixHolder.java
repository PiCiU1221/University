package matrixpackage;

public class MatrixHolder {
    private Matrix A, B, C;

    public int getRowsA() { return A.getRows(); }
    public int getColumnsA() { return A.getColumns(); }

    public int getRowsB() { return B.getRows(); }
    public int getColumnsB() { return B.getColumns(); }

    public void displayA() {
        System.out.println("\n Macierz A:\n");
        A.displayContent();
    }

    public void displayB() {
        System.out.println("\n Macierz B:\n");
        B.displayContent();
    }

    public void displayC() {
        System.out.println("\n Macierz C:\n");
        C.displayContent();
    }

    public void setElementA(int row, int column, int value) { A.setElement(row, column, value); }

    public void setElementB(int row, int column, int value) {
        B.setElement(row, column, value);
    }


    public Matrix getA() {
        return A;
    }

    public Matrix getB() {
        return B;
    }

    public Matrix getC() {
        return C;
    }

    public void setA(Matrix A) {
        this.A = A;
    }

    public void setB(Matrix B) { this.B = B; }

    public void setC(Matrix C) { this.C = C; }
}
