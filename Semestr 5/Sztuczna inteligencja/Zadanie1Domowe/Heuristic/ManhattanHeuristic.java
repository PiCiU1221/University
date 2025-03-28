package org.example.Heuristic;

import org.example.SlidingPuzzle;
import sac.State;
import sac.StateFunction;

public class ManhattanHeuristic extends StateFunction {
    @Override
    public double calculate(State state) {
        SlidingPuzzle slidingPuzzle = (SlidingPuzzle) state;

        int n = slidingPuzzle.getN();
        byte[][] board = slidingPuzzle.getBoard();
        double h = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 0) {
                    continue;
                }

                h += manhattan(slidingPuzzle, i, j);
            }
        }

        return h;
    }

    protected int manhattan(SlidingPuzzle slidingPuzzle, int col, int row) {
        int n = slidingPuzzle.getN();
        byte[][] board = slidingPuzzle.getBoard();

        int i = board[col][row] / n;
        int j = board[col][row] % n;
        return Math.abs(col - i) + Math.abs(row - j);
    }
}
