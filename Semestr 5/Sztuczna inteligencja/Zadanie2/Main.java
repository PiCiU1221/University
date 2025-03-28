package org.example;

import sac.game.AlphaBetaPruning;
import sac.game.GameSearchAlgorithm;
import sac.game.GameSearchConfigurator;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        GameSearchConfigurator conf = new GameSearchConfigurator();
        conf.setDepthLimit(5.5);
        GameSearchAlgorithm algo = new AlphaBetaPruning();
        algo.setConfigurator(conf);

        Connect4.setHFunction(new C4Evaluation());
        Connect4 c4 = new Connect4();

        System.out.println(c4);

        while (true) {
            if (Connect4.IS_MAX_PLAYER_AI) {
                algo.setInitial(c4);
                System.out.println("AI THINKING...");
                algo.execute();
                System.out.println("MOVES SCORES: " + algo.getMovesScores());
                int jBestMove = Integer.valueOf(algo.getFirstBestMove());
                c4.move(jBestMove);
                System.out.println("MOVE PLAYED: " + jBestMove);
            } else {
                boolean moveOk = false;
                do {
                    System.out.print("MAX PLAYER 'O' - YOUR MOVE:");
                    int jMove = Integer.valueOf(scanner.nextLine());
                    moveOk = c4.move(jMove);
                } while (!moveOk);
            }

            System.out.println(c4);

            if (c4.isWin()) {
                System.out.println("MAX PLAYER 'O' WINS!");
                break;
            }

            if (c4.isTie()) {
                System.out.println("GAME ENDS WITH A TIE");
            }

            if (Connect4.IS_MIN_PLAYER_AI) {
                algo.setInitial(c4);
                System.out.println("AI THINKING...");
                algo.execute();
                System.out.println("MOVES SCORES: " + algo.getMovesScores());
                int jBestMove = Integer.valueOf(algo.getFirstBestMove());
                c4.move(jBestMove);
                System.out.println("MOVE PLAYED: " + jBestMove);
            } else {
                boolean moveOk = false;
                do {
                    System.out.print("MIN PLAYER 'X' - YOUR MOVE:");
                    int jMove = Integer.valueOf(scanner.nextLine());
                    moveOk = c4.move(jMove);
                } while (!moveOk);
            }

            System.out.println(c4);

            if (c4.isWin()) {
                System.out.println("MIN PLAYER 'X' WINS!");
                break;
            }

            if (c4.isTie()) {
                System.out.println("GAME ENDS WITH A TIE");
            }
        }

        scanner.close();
    }
}