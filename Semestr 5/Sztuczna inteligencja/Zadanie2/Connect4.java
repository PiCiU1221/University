package org.example;

import sac.game.GameState;
import sac.game.GameStateImpl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Connect4 extends GameStateImpl {

    public static final boolean IS_MAX_PLAYER_AI = false;
    public static final boolean IS_MIN_PLAYER_AI = true;

    public static final int m = 6;
    public static final int n = 7;
    public static final byte O = 1; // MAX PLAYER
    public static final byte EMPTY = 0;
    public static final byte X = -1; // MIN PLAYER
    private static final String[] SYMBOLS = new String[] {"X", ".", "O"};

    private byte[][] board;
    private int iLast = -1;
    private int jLast = -1;

    public byte[][] getBoard() {
        return board;
    }

    public int getILast() {
        return iLast;
    }

    public int getJLast() {
        return jLast;
    }

    public Connect4() {
        board = new byte[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = EMPTY;
            }
        }
    }

    public Connect4(Connect4 parent) {
        board = new byte[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = parent.board[i][j];
            }
        }

        setMaximizingTurnNow(parent.isMaximizingTurnNow());
    }

    @Override
    public String toString() {
        StringBuilder txt = new StringBuilder();

        for (int j = 0; j < n; j++) {
            txt.append(" ");
            txt.append(j);
        }

        txt.append("\n");

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                txt.append("|");
                txt.append(SYMBOLS[board[i][j] + 1]);
            }
            txt.append("|\n");
        }

        for (int j = 0; j < n; j++) {
            txt.append(" ");
            txt.append(j);
        }

        return txt.toString();
    }

    public boolean move(int j) {
        int i = m - 1;
        for (; i >= 0; i--) {
            if (board[i][j] == EMPTY) {
                break;
            }
        }

        if (i < 0)
            return false;

        board[i][j] = (isMaximizingTurnNow()) ? O : X;
        setMaximizingTurnNow(!isMaximizingTurnNow());

        iLast = i;
        jLast = j;

        setMoveName(Integer.toString(j));

        return true;
    }

    @Override
    public List<GameState> generateChildren() {
        List<GameState> children = new ArrayList<>();

        for (int j = 0; j < n; j++) {
            Connect4 child = new Connect4(this);
            if (child.move(j)) {
                children.add(child);
                child.setMoveName(Integer.toString(j));
            }
        }

        return children;
    }

    public boolean isWin() {
        if ((iLast < 0) || (jLast < 0)) {
            return false;
        }

        byte symbol = board[iLast][jLast];

        // right-left
        int counter = 0;
        for (int k = 1; k < 4; k++) {
            if ((jLast + k >= n) || (board[iLast][jLast + k] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k < 4; k++) {
            if ((jLast - k < 0) || (board[iLast][jLast - k] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        // down-up
        counter = 0;

        for (int k = 1; k < 4; k++) {
            if ((iLast + k >= m) || (board[iLast + k][jLast] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k < 4; k++) {
            if ((iLast - k < 0) || (board[iLast - k][jLast] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        // NE-SW
        counter = 0;

        for (int k = 1; k < 4; k++) {
            if ((iLast - k < 0) || (jLast + k >= n) || (board[iLast - k][jLast + k] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k < 4; k++) {
            if ((iLast + k >= m) || (jLast - k < 0) || (board[iLast + k][jLast - k] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        // NW-SE
        counter = 0;

        for (int k = 1; k < 4; k++) {
            if ((iLast - k < 0) || (jLast - k < 0) || (board[iLast - k][jLast - k] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k < 4; k++) {
            if ((iLast + k >= m) || (jLast + k >= n) || (board[iLast + k][jLast + k] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        return false;
    }

    public boolean isTie() {
        for (int j = 0; j < n; j++)
            if (board[0][j] == EMPTY)
                return false;
        return true;
    }

    @Override
    public int hashCode() {
        byte[] flat = new byte[n * m];
        int k = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                flat[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flat);
    }
}
