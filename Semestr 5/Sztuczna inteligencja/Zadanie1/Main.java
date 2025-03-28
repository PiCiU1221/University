package org.example;

import sac.IdentifierType;
import sac.graph.BestFirstSearch;
import sac.graph.GraphSearchAlgorithm;
import sac.graph.GraphSearchConfigurator;
import sac.graph.GraphState;

import java.util.List;

public class Main {
    public static void main(String[] args) {
        // 4x4
        //String sudokuAsTxt = "0030206009003050010018064000081029007000000080067082000026095008002030090050103002343423423423423423412234123412341231234124100302060090030500100180640000810290070000000800670820000260950080020300900501030000302060090030500100180640000810290070000000800674";
        // 3x3
        String sudokuAsTxt = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
        //String sudokuAsTxt = "000000000000005001001806400008102900700000008006708200002609500800203009005010300";
        // 2x2
        //String sudokuAsTxt = "1200040000100032";

        Sudoku s = new Sudoku(3);
        s.fromString(sudokuAsTxt);

        System.out.println(s);

        GraphSearchConfigurator conf = new GraphSearchConfigurator();
        //conf.setWantedNumberOfSolutions(Integer.MAX_VALUE);
        conf.setIdentifierType(IdentifierType.STRING);

        GraphSearchAlgorithm algo = new BestFirstSearch(s, conf);
        Sudoku.setHFunction(new HeuristicEmptyCells());
        algo.execute();

        List<GraphState> solutions = algo.getSolutions();

        System.out.println("Rozwiazanie:");

        for (GraphState sol : solutions) {
            System.out.println(sol);
        }

        System.out.println("Time [ms]: " + algo.getDurationTime());
        System.out.println("Closed: " + algo.getClosedStatesCount());
        System.out.println("Open: " + algo.getOpenSet().size());
        System.out.println("Solutions: " + solutions.size());;
    }
}