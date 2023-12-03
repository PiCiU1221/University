import lab09.view.Menu;

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
