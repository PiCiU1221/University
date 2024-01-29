package lab13.utils;

public class PeselUtils {

    public static boolean isNumeric(String pesel) {
        try {
            Double.parseDouble(pesel);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static boolean isPeselValid(String pesel) throws IllegalArgumentException {
        if (!verifyLength(pesel)) {
            throw new IllegalArgumentException("PESEL musi składać się z 11 znaków");
        }

        if (!isNumeric(pesel)) {
            throw new IllegalArgumentException("PESEL musi składać się z cyfr");
        }

        int[] peselNumbers = convertPeselToArray(pesel);

        int checksum = calculateChecksum(peselNumbers);

        if (!isValidChecksum(checksum)) {
            throw new IllegalArgumentException("Niepoprawny numer PESEL");
        }

        return true;
    }

    private static boolean verifyLength(String pesel) {
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
        int checksum = 0;
        int[] weights = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1};

        for (int i = 0; i < 11; i++) {
            checksum += weights[i] * peselNumbers[i];
        }

        return checksum;
    }

    private static boolean isValidChecksum(int checksum) {
        return checksum % 10 == 0;
    }
}