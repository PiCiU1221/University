package menuoptions.wyswietlmacierze;

import matrixpackage.MatrixHolder;

import java.util.Scanner;

public class WyswietlWyjsciowe {
    public void displayOutput(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        if (matrixHolder.getC() == null) {
            System.out.println("\nMacierz nie zostala utworzona");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        }

        matrixHolder.displayC();

        System.out.print("\nNacisnij ENTER, by wrocic");

        scanner.nextLine();
    }
}
