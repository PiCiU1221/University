package lab13.controller;

import lab13.model.Dyrektor;
import lab13.model.Handlowiec;
import lab13.model.base.Pracownik;
import lab13.testutils.PracownikGenerator;
import org.junit.Test;
import org.junit.Before;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Random;

import static org.junit.Assert.*;

public class PracownikHolderTest {

    private PracownikHolder pracownikHolder;

    @Before
    public void setUp() {
        this.pracownikHolder = new PracownikHolder();
    }

    // 1.1) dodanie pracownika typu Handlowiec do pustego kontenera (Laboratorium 9)

    @Test
    public void addPracownik_AddHandlowiecToEmptyHolder_HolderContainsNewHandlowiec() {
        Handlowiec handlowiec = new Handlowiec();

        handlowiec.setPesel("58082168819");
        handlowiec.setImie("Adam");
        handlowiec.setNazwisko("Slowacki");
        handlowiec.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(handlowiec);

        // Empty container, so the added Handlowiec should be at the first positon
        Pracownik returnedPracownik = pracownikHolder.getPracownikAtIndex(0);

        // Assert that the pracownikHolder size is 1 after add
        assertEquals(1, pracownikHolder.getSize());

        // Assert that the only pracownik is equal to the one that we created before
        assertEquals(returnedPracownik, handlowiec);
    }

    // 1.2) dodanie pracownika typu Dyrektor do pustego kontenera (Laboratorium 9)

    @Test
    public void addPracownik_AddDyrektorToEmptyHolder_HolderContainsNewDyrektor() {
        Dyrektor dyrektor = new Dyrektor();

        dyrektor.setPesel("64032587689");
        dyrektor.setImie("Juliusz");
        dyrektor.setNazwisko("Mickiewicz");
        dyrektor.setStanowisko("Dyrektor");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(dyrektor);

        // Empty container, so the added Handlowiec should be at the first positon
        Pracownik returnedPracownik = pracownikHolder.getPracownikAtIndex(0);

        // Assert that the pracownikHolder size is 1 after add
        assertEquals(1, pracownikHolder.getSize());

        // Assert that the only pracownik is equal to the one that we created before
        assertEquals(returnedPracownik, dyrektor);
    }

    // 1.3) dodanie pracownika typu Handlowiec do kontenera zawierającego innych
    // pracowników (Laboratorium 9)

    @Test
    public void addPracownik_AddHandlowiecToNonEmptyHolder_HolderContainsNewHandlowiec() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();

        Handlowiec handlowiecToTest = new Handlowiec();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        handlowiecToTest.setPesel("57012085798");
        handlowiecToTest.setImie("Genowefa");
        handlowiecToTest.setNazwisko("Lecka");
        handlowiecToTest.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        // Act
        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(handlowiecToTest);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // The handlowiecToTest should be at the index 2
        Pracownik returnedPracownik = pracownikHolder.getPracownikAtIndex(2);

        // Assert that the only pracownik is equal to the one that we created before
        assertEquals(returnedPracownik, handlowiecToTest);
    }

    // 1.4) dodanie pracownika typu Dyrektor do kontenera zawierającego innych
    // pracowników (Laboratorium 9)

    @Test
    public void addPracownik_AddDyrektorToNonEmptyHolder_HolderContainsNewDyrektor() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();

        Dyrektor dyrektorToTest = new Dyrektor();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        dyrektorToTest.setPesel("57012085798");
        dyrektorToTest.setImie("Genowefa");
        dyrektorToTest.setNazwisko("Lecka");
        dyrektorToTest.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        // Act
        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(dyrektorToTest);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // The handlowiecToTest should be at the index 2
        Pracownik returnedPracownik = pracownikHolder.getPracownikAtIndex(2);

        // Assert that the only pracownik is equal to the one that we created before
        assertEquals(returnedPracownik, dyrektorToTest);
    }

    // 1.5) dodanie do pustego kontenera minimum 10 pracowników losowych typów
    // (Laboratorium 9)

    @Test
    public void addPracownik_AddRandomPracownikObjectsToHolder_HolderContainsNewPracownikObjects() {
        int numberOfEmployeesInTest = 20;

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        Random random = new Random();
        int randomTestIndex = random.nextInt(numberOfEmployeesInTest);

        Pracownik testPracownik = null;

        for (int i = 0; i < numberOfEmployeesInTest; i++) {
            Pracownik pracownik = PracownikGenerator.generateRandomPracownik();

            pracownikHolder.addPracownik(pracownik);

            if (i == randomTestIndex) {
                testPracownik = pracownik;
            }
        }

        // Assert that the pracownikHolder size is equal to numberOfEmployeesInTest after add
        assertEquals(numberOfEmployeesInTest, pracownikHolder.getSize());

        // Get the Pracownik from the randomized index to test
        Pracownik returnedPracownik = pracownikHolder.getPracownikAtIndex(randomTestIndex);

        // Assert that the only pracownik is equal to the one that we created before
        assertEquals(returnedPracownik, testPracownik);
    }

    // 1.6) usunięcie pracownika typu Handlowiec z kontenera zawierającego innych
    // pracowników (Laboratorium 9)

    @Test
    public void deletePracownik_RemoveHandlowiecFromHolderContainingOtherPracownikObjects_HandlowiecRemovedFromHolder() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();

        Handlowiec handlowiecToTest = new Handlowiec();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        handlowiecToTest.setPesel("57012085798");
        handlowiecToTest.setImie("Genowefa");
        handlowiecToTest.setNazwisko("Lecka");
        handlowiecToTest.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(handlowiecToTest);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // Act
        pracownikHolder.deletePracownik(handlowiecToTest);

        // Assert that the pracownikHolder size is 2 after delete
        assertEquals(2, pracownikHolder.getSize());

        Pracownik returnedPracownik1 = pracownikHolder.getPracownikAtIndex(0);
        Pracownik returnedPracownik2 = pracownikHolder.getPracownikAtIndex(1);

        // Assert that the only remaining objects are not the deleted one
        assertNotEquals(returnedPracownik1, handlowiecToTest);
        assertNotEquals(returnedPracownik2, handlowiecToTest);
    }

    // 1.7) usunięcie pracownika typu Dyrektor z kontenera zawierającego innych
    // pracowników (Laboratorium 9)

    @Test
    public void deletePracownik_RemoveDyrektorFromHolderContainingOtherPracownikObjects_DyrektorRemovedFromHolder() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();

        Dyrektor dyrektorToTest = new Dyrektor();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        dyrektorToTest.setPesel("57012085798");
        dyrektorToTest.setImie("Genowefa");
        dyrektorToTest.setNazwisko("Lecka");
        dyrektorToTest.setStanowisko("Dyrektor");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(dyrektorToTest);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // Act
        pracownikHolder.deletePracownik(dyrektorToTest);

        // Assert that the pracownikHolder size is 2 after delete
        assertEquals(2, pracownikHolder.getSize());

        Pracownik returnedPracownik1 = pracownikHolder.getPracownikAtIndex(0);
        Pracownik returnedPracownik2 = pracownikHolder.getPracownikAtIndex(1);

        // Assert that the only remaining objects are not the deleted one
        assertNotEquals(returnedPracownik1, dyrektorToTest);
        assertNotEquals(returnedPracownik2, dyrektorToTest);
    }

    @Test
    public void deletePracownik_PracownikDoesNotExist_PrintMessage() {
        // Arrange
        Pracownik nullPracownik = null;

        // Redirect System.out to capture printed messages
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));

        try {
            // Act
            pracownikHolder.deletePracownik(nullPracownik);

            // Assert
            String expectedMessage = "Podany pracownik nie istnieje.";
            assertEquals(expectedMessage, outContent.toString().trim());
        } finally {
            // Reset System.out to its original state
            System.setOut(System.out);
        }
    }

    @Test
    public void getPracownik_PracownikExists_ReturnsPracownik() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        pracownikHolder.addPracownik(dyrektor1);

        // Act
        Pracownik pracownik = pracownikHolder.getPracownik(dyrektor1.getPesel());

        // Assert
        assertNotNull(pracownik);
    }

    @Test
    public void getPracownik_PracownikDoesNotExists_ReturnsNull() {
        // Arrange
        String wrongPesel = "64032587689";

        // Act
        Pracownik pracownik = pracownikHolder.getPracownik(wrongPesel);

        // Assert
        assertNull(pracownik);
    }

    @Test
    public void isPeselInUse_PeselInUse_ReturnsTrue() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        pracownikHolder.addPracownik(dyrektor1);

        // Act and Assert
        assertTrue(pracownikHolder.isPeselInUse(dyrektor1.getPesel()));
    }

    @Test
    public void isPeselInUse_PeselNotInUse_ReturnsFalse() {
        // Arrange
        String nonUsedPesel = "64032587689";

        // Act and Assert
        assertFalse(pracownikHolder.isPeselInUse(nonUsedPesel));
    }
}