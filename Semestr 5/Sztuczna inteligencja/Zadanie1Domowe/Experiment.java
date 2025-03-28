package org.example;

import org.example.Heuristic.ManhattanHeuristic;
import org.example.Heuristic.MisplacedTilesHeuristic;
import sac.graph.AStar;
import sac.graph.GraphSearchAlgorithm;

public class Experiment {
    public static void experiment(int n, int howManyScrambleMoves, int howManyProblems) {
        int misplacedTilesOpenSum = 0;
        int misplacedTilesClosedSum = 0;
        double misplacedTilesDurationSum = 0;
        double misplacedTilesPathLengthSum = 0;

        int manhattanOpenSum = 0;
        int manhattanClosedSum = 0;
        double manhattanDurationSum = 0;
        double manhattanPathLengthSum = 0;

        SlidingPuzzle solution;

        for (int i = 0; i < howManyProblems; i++) {
            SlidingPuzzle slidingPuzzle = new SlidingPuzzle(n);
            slidingPuzzle.scrambleBoard(howManyScrambleMoves);

            GraphSearchAlgorithm algo = new AStar(slidingPuzzle);

            // Misplaced tiles heuristic
            SlidingPuzzle.setHFunction(new MisplacedTilesHeuristic());
            algo.execute();

            solution = (SlidingPuzzle) algo.getSolutions().get(0);

            misplacedTilesOpenSum += algo.getOpenSet().size();
            misplacedTilesClosedSum += algo.getClosedStatesCount();
            misplacedTilesDurationSum += algo.getDurationTime();
            misplacedTilesPathLengthSum += solution.getPath().size();

            // Manhattan heuristic
            SlidingPuzzle.setHFunction(new ManhattanHeuristic());
            algo.execute();

            solution = (SlidingPuzzle) algo.getSolutions().get(0);

            manhattanOpenSum += algo.getOpenSet().size();
            manhattanClosedSum += algo.getClosedStatesCount();
            manhattanDurationSum += algo.getDurationTime();
            manhattanPathLengthSum += solution.getPath().size();
        }

        System.out.println("n: " + n);
        System.out.println("howManyScrambleMoves: " + howManyScrambleMoves);
        System.out.println("howManyProblems: " + howManyProblems + "\n");

        System.out.println("Misplaced tiles heuristic average values:");
        System.out.println("Open: " + misplacedTilesOpenSum / howManyProblems);
        System.out.println("Closed: " + misplacedTilesClosedSum / howManyProblems);
        System.out.println("Duration: " + misplacedTilesDurationSum / howManyProblems + " ms");
        System.out.println("Path length: " + misplacedTilesPathLengthSum / howManyProblems);

        System.out.println("\nManhattan heuristic average values:");
        System.out.println("Open: " + manhattanOpenSum / howManyProblems);
        System.out.println("Closed: " + manhattanClosedSum / howManyProblems);
        System.out.println("Duration: " + manhattanDurationSum / howManyProblems + " ms");
        System.out.println("Path length: " + manhattanPathLengthSum / howManyProblems);
    }
}
