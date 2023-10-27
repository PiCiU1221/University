package menuoptions.wyswietlmacierze;

import matrixpackage.MatrixHolder;

import java.util.Scanner;

public class WyswietlWejsciowe {
    public void displayInput(MatrixHolder matrixHolder) {
        Scanner scanner = new Scanner(System.in);

        if (matrixHolder.getA() == null || matrixHolder.getB() == null) {
            System.out.println("\nMacierze nie zostaly utworzone");
            System.out.print("Nacisnij ENTER, by wrocic");

            scanner.nextLine();
            return;
        }

        matrixHolder.displayA();
        matrixHolder.displayB();

        System.out.print("\nNacisnij ENTER, by wrocic");

        scanner.nextLine();
    }
}
