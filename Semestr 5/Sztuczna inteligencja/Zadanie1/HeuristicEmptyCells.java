package org.example;

import sac.State;
import sac.StateFunction;

public class HeuristicEmptyCells extends StateFunction {
    @Override
    public double calculate(State state) {
        Sudoku s = (Sudoku) state;
        return s.getZeros();
    }
}
