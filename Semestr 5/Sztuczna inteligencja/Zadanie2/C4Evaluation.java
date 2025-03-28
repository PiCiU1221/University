package org.example;

import sac.State;
import sac.StateFunction;

import static org.example.Connect4.O;

public class C4Evaluation extends StateFunction {
    private static final int THREE_IN_A_ROW_SCORE = 100;
    private static final int TWO_IN_A_ROW_SCORE = 10;

    @Override
    public double calculate(State state) {
        Connect4 c4 = (Connect4) state;

        if (c4.isWin()) {
            return (c4.isMaximizingTurnNow()) ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY;
        }

        if (c4.isTie()) {
            return 0;
        }

        byte[][] board = c4.getBoard();
        int iLast = c4.getILast();
        int jLast = c4.getJLast();

        // first move
        if (iLast == -1 || jLast == -1) {
            return 0;
        }

        byte mySymbol = board[iLast][jLast];
        byte opponentSymbol = (mySymbol == O) ? Connect4.X : Connect4.O;

        int totalScore = 0;

        totalScore += evaluateDirection(board, iLast, jLast, mySymbol, 0, 1);
        totalScore += evaluateDirection(board, iLast, jLast, mySymbol, 1, 0);
        totalScore += evaluateDirection(board, iLast, jLast, mySymbol, 1, 1);
        totalScore += evaluateDirection(board, iLast, jLast, mySymbol, 1, -1);

        totalScore -= evaluateDirection(board, iLast, jLast, opponentSymbol, 0, 1);
        totalScore -= evaluateDirection(board, iLast, jLast, opponentSymbol, 1, 0);
        totalScore -= evaluateDirection(board, iLast, jLast, opponentSymbol, 1, 1);
        totalScore -= evaluateDirection(board, iLast, jLast, opponentSymbol, 1, -1);

        totalScore += calculateBonusPoints(jLast, board[0].length);

        return totalScore;
    }

    private int evaluateDirection(byte[][] board, int row, int col, byte symbol, int rowDelta, int colDelta) {
        int score = 0;

        int consecutive = 1;
        int spaces = 0;

        for (int i = 1; i < 4; i++) {
            int newRow = row + i * rowDelta;
            int newCol = col + i * colDelta;

            if (isInBounds(newRow, newCol, board) && board[newRow][newCol] == symbol) {
                consecutive++;
            } else if (isInBounds(newRow, newCol, board) && board[newRow][newCol] == Connect4.EMPTY) {
                spaces++;
                break;
            } else {
                break;
            }
        }

        for (int i = 1; i < 4; i++) {
            int newRow = row - i * rowDelta;
            int newCol = col - i * colDelta;

            if (isInBounds(newRow, newCol, board) && board[newRow][newCol] == symbol) {
                consecutive++;
            } else if (isInBounds(newRow, newCol, board) && board[newRow][newCol] == Connect4.EMPTY) {
                spaces++;
                break;
            } else {
                break;
            }
        }

        if (consecutive == 3 && spaces > 0) {
            score += THREE_IN_A_ROW_SCORE;
        } else if (consecutive == 2 && spaces > 0) {
            score += TWO_IN_A_ROW_SCORE;
        }

        return score;
    }

    private boolean isInBounds(int row, int col, byte[][] board) {
        return row >= 0 && row < board.length && col >= 0 && col < board[0].length;
    }

    private int calculateBonusPoints(int col, int totalColumns) {
        double center = (totalColumns - 1) / 2.0;

        double distanceFromCenter = Math.abs(col - center);

        int maxScore = 9;
        int minScore = 1;

        double score = maxScore - (distanceFromCenter / center) * (maxScore - minScore);

        return (int) Math.round(score);
    }
}
