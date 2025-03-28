package org.example;

import org.example.Heuristic.ManhattanHeuristic;
import org.example.Heuristic.MisplacedTilesHeuristic;
import sac.graph.*;

public class Main {
    public static void main(String[] args) {
        int n = 3;
        int howManyScrambleMoves = 1000;
        int howManyProblems = 100;

//        int n = 4;
//        int howManyScrambleMoves = 30;
//        int howManyProblems = 10;

        Experiment.experiment(n, howManyScrambleMoves, howManyProblems);

//        SlidingPuzzle slidingPuzzle = new SlidingPuzzle(n);
//        slidingPuzzle.scrambleBoard(howManyScrambleMoves);
//        System.out.println(slidingPuzzle);
//
//        GraphSearchAlgorithm algo = new AStar(slidingPuzzle);
//        //SlidingPuzzle.setHFunction(new MisplacedTilesHeuristic());
//        SlidingPuzzle.setHFunction(new ManhattanHeuristic());
//        algo.execute();
//
//        SlidingPuzzle solution = (SlidingPuzzle) algo.getSolutions().get(0);
//
//        System.out.println("Rozwiazanie:");
//        System.out.println(solution);
//
//        System.out.println("Time [ms]: " + algo.getDurationTime());
//        System.out.println("Closed: " + algo.getClosedStatesCount());
//        System.out.println("Open: " + algo.getOpenSet().size());
//        System.out.println("Path length: " + solution.getPath().size());
//        System.out.println("Moves along path: " + solution.getMovesAlongPath());
    }
}