package org.example;

import sac.graph.GraphState;
import sac.graph.GraphStateImpl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class SlidingPuzzle extends GraphStateImpl {

    byte[][] board;
    int n;
    int zeroRow, zeroCol;

    public SlidingPuzzle(int n) {
        this.n = n;

        board = new byte[n][n];

        byte k = 0;

        this.zeroRow = 0;
        this.zeroCol = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = k;
                k++;
            }
        }
    }

    public SlidingPuzzle(SlidingPuzzle toCopy) {
        n = toCopy.n;
        zeroRow = toCopy.zeroRow;
        zeroCol = toCopy.zeroCol;

        board = new byte[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = toCopy.board[i][j];
            }
        }
    }

    public int getN() {
        return n;
    }

    public byte[][] getBoard() {
        return board;
    }

    @Override
    public String toString() {
        StringBuilder txt = new StringBuilder();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                txt.append(board[i][j]);
                txt.append(" ");
            }
            txt.append("\n");
        }

        return txt.toString();
    }

    @Override
    public List<GraphState> generateChildren() {
        List<GraphState> children = new ArrayList<GraphState>();

        for (MoveEnum move : MoveEnum.values()) {
            SlidingPuzzle child = new SlidingPuzzle(this);

            if (child.makeMove(move)) {
                child.setMoveName(String.valueOf(move));
                children.add(child);
            }
        }

        return children;
    }

    @Override
    public boolean isSolution() {
        byte k = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != k) {
                    return false;
                }
                k++;
            }
        }

        return true;
    }

    public boolean makeMove(MoveEnum moveEnum) {
        if (moveEnum == MoveEnum.L && zeroRow == 0) {
            return false;
        } else if (moveEnum == MoveEnum.R && zeroRow == n - 1) {
            return false;
        } else if (moveEnum == MoveEnum.U && zeroCol == 0) {
            return false;
        } else if (moveEnum == MoveEnum.D && zeroCol == n - 1) {
            return false;
        }

        if (moveEnum == MoveEnum.L) {
            board[zeroCol][zeroRow] = board[zeroCol][zeroRow - 1];;
            board[zeroCol][zeroRow - 1] = 0;
            zeroRow--;
        } else if (moveEnum == MoveEnum.R) {
            board[zeroCol][zeroRow] = board[zeroCol][zeroRow + 1];
            board[zeroCol][zeroRow + 1] = 0;
            zeroRow++;
        } else if (moveEnum == MoveEnum.U) {
            board[zeroCol][zeroRow] = board[zeroCol - 1][zeroRow];
            board[zeroCol - 1][zeroRow] = 0;
            zeroCol--;
        } else if (moveEnum == MoveEnum.D) {
            board[zeroCol][zeroRow] = board[zeroCol + 1][zeroRow];
            board[zeroCol + 1][zeroRow] = 0;
            zeroCol++;
        }

        return true;
    }

    @Override
    public int hashCode() {
        byte[] flat = new byte[n * n];
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                flat[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flat);
    }

    public void scrambleBoard(int howManyScrambleMoves) {
        int i = 0;

        Random r = new Random();
        int randomizedMove;
        boolean wasLegal = false;

        while (i < howManyScrambleMoves) {
            randomizedMove = r.nextInt(4);

            if (randomizedMove == 0) {
                wasLegal = makeMove(MoveEnum.L);
            } else if (randomizedMove == 1) {
                wasLegal = makeMove(MoveEnum.R);
            } else if (randomizedMove == 2) {
                wasLegal = makeMove(MoveEnum.U);
            } else if (randomizedMove == 3) {
                wasLegal = makeMove(MoveEnum.D);
            }

            if (wasLegal) {
                i++;
            }
        }
    }
}
