package matrixpackage;

public class Matrix {
    private final int[][] data;
    private final int rows;
    private final int columns;

    public Matrix(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;
        data = new int[rows][columns];
    }

    public int getRows() {
        return rows;
    }

    public int getColumns() {
        return columns;
    }

    public int getElement(int row, int column) {
        return data[row][column];
    }

    public void setElement(int row, int column, int value) {
        data[row][column] = value;
    }

    public void displayContent() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                System.out.print(data[i][j] + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }
}
