package menuoptions.wprowadzmacierze;

import java.util.Scanner;

public class WprowadzWymiary {
    public void enterDimensions(UtworzMacierze utworzMacierze) {
        System.out.println("\n\n1.1 Wprowadz wymiary");

        Scanner scanner = new Scanner(System.in);

        System.out.print("Wprowadz liczbe wierszy macierzy A: ");
        int aRows = scanner.nextInt();

        System.out.print("Wprowadz liczbe kolumn macierzy A: ");
        int aColumns = scanner.nextInt();

        System.out.print("Wprowadz liczbe wierszy macierzy B: ");
        int bRows = scanner.nextInt();

        System.out.print("Wprowadz liczbe kolumn macierzy B: ");
        int bColumns = scanner.nextInt();

        utworzMacierze.setDimensions(aRows, aColumns, bRows, bColumns);

        System.out.println("\nPomyslnie wprowadzono wymiary");
        System.out.println("Nacisnij ENTER, by wrocic");

        scanner.nextLine();
        scanner.nextLine();
    }
}
