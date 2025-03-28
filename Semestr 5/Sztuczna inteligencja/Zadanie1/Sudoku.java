package org.example;

import sac.graph.GraphState;
import sac.graph.GraphStateImpl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Sudoku extends GraphStateImpl {
    private int n;
    private int n2;
    private byte[][] board = null;
    public int zeros;

    public Sudoku(int n) {
        this.n = n;
        this.n2 = n * n;
        this.zeros = n2 * n2;

        board = new byte[n2][n2];

        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                board[i][j] = 0;
            }
        }
    }

    public Sudoku(Sudoku toCopy) {
        n = toCopy.n;
        n2 = toCopy.n2;
        zeros = toCopy.zeros;

        board = new byte[n2][n2];

        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                board[i][j] = toCopy.board[i][j];
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder txt = new StringBuilder();

        for (int i = 0; i < n2; i++) {
            if (i % n == 0 && i != 0) {
                for (int j = 0; j < n2 * 2 + (n - 1) * 2 - 1; j++) {
                    if (j % (n * 2) == 0 && j <= n * 2 && j != 0) {
                        txt.append("|");
                    } else if ((j - n * 2) % (n * 2 + 2) == 0 && j > n * 2 + 1) {
                        txt.append("|");
                    }
                    else {
                        txt.append("-");
                    }
                }
                txt.append("\n");
            }
            for (int j = 0; j < n2; j++) {
                if (j % n == 0 && j != 0) {
                    txt.append("| ");
                }

                txt.append(board[i][j]);

                if (j != n2 - 1) {
                    txt.append(" ");
                }
            }
            txt.append("\n");
        }

        return txt.toString();
    }

    public void fromString(String txt) {
        int k = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                board[i][j] = Byte.valueOf(txt.substring(k, k + 1));
                k++;
            }
        }

        refreshZeros();
    }

    private boolean isGroupLegal(byte[] group) {
        boolean[] visited = new boolean[n2 + 1];

        for (int i = 1; i < n2 + 1; i++)
            visited[i] = false;

        for (int i = 0; i < n2; i++) {
            if (group[i] == 0)
                continue;

            if (visited[group[i]])
                return false;

            visited[group[i]] = true;
        }

        return true;
    }

    public boolean isLegal() {
        byte[] group = new byte[n2];

        //wiersze
        for (int i = 0; i < n2; i++) {
            if (!isGroupLegal(board[i]))
                return false;
        }

        //kolumny
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++)
                group[j] = board[j][i];

            if (!isGroupLegal(group))
                return false;
        }

        //podkwadraty
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++)
                    for (int l = 0; l < n; l++)
                        group[k * n + l] = board[i * n + k][j * n + l];

                if (!isGroupLegal(group))
                    return false;
            }
        }

        return true;
    }

    private void refreshZeros() {
        zeros = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                if (board[i][j] == 0) {
                    zeros++;
                }
            }
        }
    }

    @Override
    public List<GraphState> generateChildren() {
        List<GraphState> children = new ArrayList<GraphState>();
        int i = 0, j = 0;

        zeroFinder:
        for (i = 0; i < n2; i++)
            for (j = 0; j < n2; j++)
                if (board[i][j] == 0)
                    break zeroFinder;

        if (i == n2)
            return children;

        for (int k = 1; k <= n2; k++) {
            Sudoku child = new Sudoku(this);
            child.board[i][j] = (byte) k;

            if (child.isLegal()) {
                children.add(child);
                child.zeros--;
            }
        }

        return children;
    }

    @Override
    public boolean isSolution() {
        return ((zeros == 0) && (isLegal()));
    }

    @Override
    public int hashCode() {
        //return toString().hashCode();

        byte[] flat = new byte[n2 * n2];
        int k = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                flat[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flat);

        //return Arrays.deepHashCode(board);
    }

    public int getZeros() {
        return zeros;
    }
}
