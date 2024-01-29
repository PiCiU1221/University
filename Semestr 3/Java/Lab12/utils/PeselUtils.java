package lab12.Utils;

public class PeselUtils {
    public static boolean isNumeric(String pesel) {
        try {
            Double.parseDouble(pesel);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static boolean werifikacjaPesel(String pesel) {
        if (!weryfikacjaDlugosci(pesel)) {
            System.out.println("Numer PESEL musi składać się z 11 znaków\n");
            return false;
        }

        if (!isNumeric(pesel)) {
            System.out.println("Numer PESEL musi składać się z cyfr\n");
            return false;
        }

        int[] peselNumbers = convertPeselToArray(pesel);

        int sumaKontrolna = calculateChecksum(peselNumbers);

        if (isValidChecksum(sumaKontrolna)) {
            return true;
        } else {
            System.out.println("Numer PESEL jest niepoprawny\n");
            return false;
        }
    }

    private static boolean weryfikacjaDlugosci(String pesel) {
        return pesel.length() == 11;
    }

    private static int[] convertPeselToArray(String pesel) {
        int[] peselNumbers = new int[11];

        for (int i = 0; i < 11; i++) {
            peselNumbers[i] = Character.getNumericValue(pesel.charAt(i));
        }

        return peselNumbers;
    }

    private static int calculateChecksum(int[] peselNumbers) {
        int sumaKontrolna = 0;
        int[] wagi = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1};

        for (int i = 0; i < 11; i++) {
            sumaKontrolna += wagi[i] * peselNumbers[i];
        }

        return sumaKontrolna;
    }

    private static boolean isValidChecksum(int sumaKontrolna) {
        return sumaKontrolna % 10 == 0;
    }
}
