package org.example.Heuristic;

import org.example.SlidingPuzzle;
import sac.State;
import sac.StateFunction;

public class MisplacedTilesHeuristic extends StateFunction {
    @Override
    public double calculate(State state) {
        SlidingPuzzle slidingPuzzle = (SlidingPuzzle) state;

        int n = slidingPuzzle.getN();
        byte[][] board = slidingPuzzle.getBoard();
        double h = 0;
        int k = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 0) {
                    k++;
                    continue;
                }

                if (board[i][j] != k)
                    h++;

                k++;
            }
        }

        return h;
    }
}