package lab13.utils;

import lab13.testutils.PeselGenerator;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class PeselUtilsTest {

    // 1.8) testy sparametryzowane (parameterized test) dla weryfikacji poprawności sumy
    // kontrolnej numeru PESEL (Laboratorium 9) dla:
    // a) minimum 10 poprawnych numerów,
    // b) minimum 10 niepoprawnych numerów
    // Zdefiniuj możliwie kilka testów sparametryzowanych.

    @ParameterizedTest
    @MethodSource("generateCorrectPeselNumbers")
    public void isPeselValid_CorrectPesels_NoExceptionsThrown(String pesel) {
        assertDoesNotThrow(() -> PeselUtils.isPeselValid(pesel));
    }

    // 1.12) co najmniej jeden test, którego oczekiwanym rezultatem jest wystąpienie
    // wyjątku

    @ParameterizedTest
    @MethodSource("generateInvalidPeselNumbers")
    public void isPeselValid_InvalidPesels_ThrowsIllegalArgumentException(String pesel) {
        assertThrows(IllegalArgumentException.class, () -> PeselUtils.isPeselValid(pesel));
    }

    private static String[] generateCorrectPeselNumbers() {
        int numberOfPeselNumbersForTest = 10;

        String[] correctPeselNumbers = new String[numberOfPeselNumbersForTest];

        for (int i = 0; i < numberOfPeselNumbersForTest; i++) {
            correctPeselNumbers[i] = PeselGenerator.generatePesel();
        }

        return correctPeselNumbers;
    }

    private static String[] generateInvalidPeselNumbers() {
        int numberOfPeselNumbersForTest = 10;

        String[] invalidPeselNumbers = new String[numberOfPeselNumbersForTest];

        for (int i = 0; i < numberOfPeselNumbersForTest; i++) {
            invalidPeselNumbers[i] = PeselGenerator.generateInvalidPesel();
        }

        return invalidPeselNumbers;
    }
}