package lab13.service;

import lab13.controller.PracownikHolder;
import lab13.model.Dyrektor;
import lab13.model.Handlowiec;
import lab13.model.base.Pracownik;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import static org.junit.Assert.*;

public class FileIOServiceTest {
    private PracownikHolder pracownikHolder;
    private FileIOService fileIOService;

    private final String folderName = "data_test";

    @Before
    public void setUp() {
        this.pracownikHolder = new PracownikHolder();
        this.fileIOService = new FileIOService(pracownikHolder, folderName);
    }

    // 1.9) poprawna równoległa serializacja pracowników do skompresowanych plików
    // archiwów (Laboratorium 12)

    // 1.10) poprawna równoległa deserializacja pracowników ze skompresowanych plików
    // archiwów (Laboratorium 12)

    @Test
    public void saveToFileAndReadFromFiles_SerializeAndDeserializeObjectsToFiles_ReadDataMatchesOriginal() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();
        Handlowiec handlowiec2 = new Handlowiec();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        handlowiec2.setPesel("57012085798");
        handlowiec2.setImie("Genowefa");
        handlowiec2.setNazwisko("Lecka");
        handlowiec2.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(handlowiec2);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // Serializing objects to files
        try {
            fileIOService.saveToGZipFiles();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        pracownikHolder.deletePracownik(dyrektor1);
        pracownikHolder.deletePracownik(handlowiec1);
        pracownikHolder.deletePracownik(handlowiec2);

        // Assert that the pracownikHolder size is 0 after delete
        assertEquals(0, pracownikHolder.getSize());

        // Deserializing objects to test if they're the same
        try {
            fileIOService.readFromFiles();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // Assert that the pracownikHolder size is back to 3 after reading from files
        assertEquals(3, pracownikHolder.getSize());

        // Assert that the read objects are the same before the read
        assertPracownikEquals(dyrektor1, pracownikHolder.getPracownik(dyrektor1.getPesel()));
        assertPracownikEquals(handlowiec1, pracownikHolder.getPracownik(handlowiec1.getPesel()));
        assertPracownikEquals(handlowiec2, pracownikHolder.getPracownik(handlowiec2.getPesel()));

        // Dummy incorrect Pracownik to confirm that it's working
        Dyrektor dyrektorDummy = new Dyrektor();

        dyrektorDummy.setPesel("80040296584");
        dyrektorDummy.setImie("Wacek");
        dyrektorDummy.setNazwisko("Soplica");
        dyrektorDummy.setStanowisko("Dyrektor");

        assertPracownikNotEquals(dyrektorDummy, pracownikHolder.getPracownik(dyrektor1.getPesel()));
    }

    private void assertPracownikEquals(Pracownik expected, Pracownik actual) {
        assertEquals(expected.getPesel(), actual.getPesel());
        assertEquals(expected.getImie(), actual.getImie());
        assertEquals(expected.getNazwisko(), actual.getNazwisko());
        assertEquals(expected.getStanowisko(), actual.getStanowisko());
    }

    private void assertPracownikNotEquals(Pracownik expected, Pracownik actual) {
        assertNotEquals(expected.getPesel(), actual.getPesel());
    }

    // 1.11) niepoprawna (np. uszkodzony plik archiwum) równoległa deserializacja
    //  ze skompresowanych plików archiwów (Laboratorium 12)

    @Test
    public void readFromFiles_CorruptedGZipSaveFile_CorruptedObjectNotAdded() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();
        Handlowiec handlowiec2 = new Handlowiec();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        handlowiec2.setPesel("57012085798");
        handlowiec2.setImie("Genowefa");
        handlowiec2.setNazwisko("Lecka");
        handlowiec2.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(handlowiec2);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // Serializing objects to files
        try {
            fileIOService.saveToGZipFiles();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        pracownikHolder.deletePracownik(dyrektor1);
        pracownikHolder.deletePracownik(handlowiec1);
        pracownikHolder.deletePracownik(handlowiec2);

        // Assert that the pracownikHolder size is 0 after delete
        assertEquals(0, pracownikHolder.getSize());

        // Corrupting one save file
        try {
            corruptGZipFile(folderName + "/pracownik_" + dyrektor1.getPesel() + ".gz");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // Deserializing objects to test if they're the same
        try {
            fileIOService.readFromFiles();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // Assert that the pracownikHolder size is 2, because one file is corrupted
        assertEquals(2, pracownikHolder.getSize());

        // Assert that the read objects are the same before the read
        assertPracownikEquals(handlowiec1, pracownikHolder.getPracownik(handlowiec1.getPesel()));
        assertPracownikEquals(handlowiec2, pracownikHolder.getPracownik(handlowiec2.getPesel()));

        // Assert that the Pracownik with the corrupted file save is not present in the pracownikHolder
        assertFalse(pracownikHolder.isPeselInUse(dyrektor1.getPesel()));
    }

    private static void corruptGZipFile(String filePath) throws IOException {
        // Read the content of the file into a byte array
        byte[] fileContent = Files.readAllBytes(Paths.get(filePath));

        // Introduce corruption by modifying some bytes
        if (fileContent.length >= 10) {
            fileContent[10] = 0;  // Modify the 11th byte, for example
        }

        // Write the corrupted content back to the file
        Files.write(Paths.get(filePath), fileContent);
    }

    @Test
    public void readFromFiles_CorruptedZipSaveFile_CorruptedObjectNotAdded() {
        // Arrange
        Dyrektor dyrektor1 = new Dyrektor();
        Handlowiec handlowiec1 = new Handlowiec();
        Handlowiec handlowiec2 = new Handlowiec();

        dyrektor1.setPesel("64032587689");
        dyrektor1.setImie("Stanislaw");
        dyrektor1.setNazwisko("Rzecki");
        dyrektor1.setStanowisko("Dyrektor");

        handlowiec1.setPesel("54061545888");
        handlowiec1.setImie("Ignacy");
        handlowiec1.setNazwisko("Wokulski");
        handlowiec1.setStanowisko("Handlowiec");

        handlowiec2.setPesel("57012085798");
        handlowiec2.setImie("Genowefa");
        handlowiec2.setNazwisko("Lecka");
        handlowiec2.setStanowisko("Handlowiec");

        // Assert that the pracownikHolder size is 0 before add
        assertEquals(0, pracownikHolder.getSize());

        pracownikHolder.addPracownik(dyrektor1);
        pracownikHolder.addPracownik(handlowiec1);
        pracownikHolder.addPracownik(handlowiec2);

        // Assert that the pracownikHolder size is 3 after add
        assertEquals(3, pracownikHolder.getSize());

        // Serializing objects to files
        try {
            fileIOService.saveToZipFiles();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        pracownikHolder.deletePracownik(dyrektor1);
        pracownikHolder.deletePracownik(handlowiec1);
        pracownikHolder.deletePracownik(handlowiec2);

        // Assert that the pracownikHolder size is 0 after delete
        assertEquals(0, pracownikHolder.getSize());

        // Corrupting one save file
        try {
            corruptZipFile(folderName + "/pracownik_" + dyrektor1.getPesel() + ".zip");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // Deserializing objects to test if they're the same
        try {
            fileIOService.readFromFiles();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // Assert that the pracownikHolder size is 2, because one file is corrupted
        assertEquals(2, pracownikHolder.getSize());

        // Assert that the read objects are the same before the read
        assertPracownikEquals(handlowiec1, pracownikHolder.getPracownik(handlowiec1.getPesel()));
        assertPracownikEquals(handlowiec2, pracownikHolder.getPracownik(handlowiec2.getPesel()));

        // Assert that the Pracownik with the corrupted file save is not present in the pracownikHolder
        assertFalse(pracownikHolder.isPeselInUse(dyrektor1.getPesel()));
    }

    private static void corruptZipFile(String filePath) throws IOException {
        // Create a new ZIP file with arbitrary content
        Path zipFilePath = Paths.get(filePath);
        try (ZipOutputStream zipOutputStream = new ZipOutputStream(Files.newOutputStream(zipFilePath))) {
            // Create a ZIP entry
            zipOutputStream.putNextEntry(new ZipEntry("corrupted_file.txt"));

            // Write some content to the entry
            byte[] content = "This is a corrupted file.".getBytes();
            zipOutputStream.write(content, 0, content.length);

            // Close the entry
            zipOutputStream.closeEntry();
        }
    }
}
