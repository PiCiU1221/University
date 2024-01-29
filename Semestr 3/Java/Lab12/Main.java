package lab12;

import lab12.view.Menu;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            Menu.displayMenu();

            int choice = scanner.nextInt();

            Menu.handleChoice(choice);
        }
    }
}
