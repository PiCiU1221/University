package lab13.testutils;

import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;

public class PeselGenerator {

    public static void main(String[] args) {
        String pesel = generatePesel();
        System.out.println("Generated PESEL: " + pesel);
    }

    public static String generatePesel() {
        // Generate a random birth date
        Calendar calendar = generateRandomBirthDate();

        // Format the birth date as YYMMDD
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyMMdd");
        String birthDatePart = dateFormat.format(calendar.getTime());

        // Generate a random serial number (four digits)
        String serialNumberPart = generateRandomSerialNumber();

        // Combine the parts and calculate the checksum
        String peselWithoutChecksum = birthDatePart + serialNumberPart;
        int checksum = calculateChecksum(peselWithoutChecksum);

        // Append the checksum to complete the PESEL
        return peselWithoutChecksum + checksum;
    }

    private static Calendar generateRandomBirthDate() {
        // Generate a random birth date between 1900 and 2099
        Random random = new Random();
        int year = random.nextInt(200) + 1900;
        int month = random.nextInt(12) + 1;
        int day = random.nextInt(28) + 1; // Assume all months have 28 days for simplicity

        Calendar calendar = Calendar.getInstance();
        calendar.set(year, month - 1, day); // Month is 0-based
        return calendar;
    }

    private static String generateRandomSerialNumber() {
        // Generate a random four-digit serial number
        Random random = new Random();
        DecimalFormat decimalFormat = new DecimalFormat("0000");
        return decimalFormat.format(random.nextInt(10000));
    }

    private static int calculateChecksum(String peselWithoutChecksum) {
        // Calculate the PESEL checksum
        int[] weights = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1}; // Weights for each digit
        int checksum = 0;

        for (int i = 0; i < peselWithoutChecksum.length(); i++) {
            int digit = Integer.parseInt(peselWithoutChecksum.substring(i, i + 1));
            checksum += digit * weights[i];
        }

        checksum = (10 - (checksum % 10)) % 10;
        return checksum;
    }

    public static String generateInvalidPesel() {
        // Generate a PESEL with an intentionally incorrect checksum
        String validPesel = generatePesel();

        // Modify the last digit to make the checksum invalid
        char[] peselChars = validPesel.toCharArray();
        int lastDigit = Character.getNumericValue(peselChars[peselChars.length - 1]);
        int invalidLastDigit = (lastDigit + 1) % 10;
        peselChars[peselChars.length - 1] = Character.forDigit(invalidLastDigit, 10);

        return new String(peselChars);
    }
}
