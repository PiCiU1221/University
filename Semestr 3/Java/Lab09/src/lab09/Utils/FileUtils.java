package lab09.Utils;

import lab09.controller.PracownikHolder;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.zip.*;

public class FileUtils {
    public static void saveToZipFile(PracownikHolder pracownikHolder, String fileName) {
        try (ZipOutputStream zipOut = new ZipOutputStream(new BufferedOutputStream(Files.newOutputStream(Paths.get(fileName))))) {
            // Specify DEFLATE compression method
            zipOut.setLevel(Deflater.DEFAULT_COMPRESSION);

            // Create a ZIP entry for the object
            ZipEntry entry = new ZipEntry("pracownikHolder.ser");
            zipOut.putNextEntry(entry);

            // Wrap the ZipOutputStream around the ObjectOutputStream
            try (ObjectOutputStream oos = new ObjectOutputStream(zipOut)) {
                // Write the object to the ZIP file
                oos.writeObject(pracownikHolder);
            }

            System.out.println("Dane zachowane pomyślnie do pliku ZIP.");
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Błąd podczas zapisu danych do pliku ZIP: " + e.getMessage());
        }
    }

    public static void saveToGZipFile(PracownikHolder pracownikHolder, String fileName) {
        try (ObjectOutputStream oos = new ObjectOutputStream(
                new BufferedOutputStream(
                        new GZIPOutputStream(
                                Files.newOutputStream(Paths.get(fileName)))))) {
            oos.writeObject(pracownikHolder);
            System.out.println("Dane zachowane pomyślnie.");
        } catch (IOException e) {
            System.out.println("Błąd podczas zapisu danych do pliku: " + e.getMessage());
        }
    }

    public static PracownikHolder readFromFile(String fileName) {
        PracownikHolder pracownikHolder = null;

        try (ObjectInputStream ois = new ObjectInputStream(
                new BufferedInputStream(
                        getInputStreamBasedOnExtension(fileName)))) {
            pracownikHolder = (PracownikHolder) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Błąd podczas odczytu danych z pliku: " + e.getMessage());
        }

        return pracownikHolder;
    }

    private static InputStream getInputStreamBasedOnExtension(String fileName) throws IOException {
        String lowerCaseFileName = fileName.toLowerCase();

        if (lowerCaseFileName.endsWith(".gz")) {
            return new GZIPInputStream(Files.newInputStream(Paths.get(fileName)));
        } else if (lowerCaseFileName.endsWith(".zip")) {
            ZipInputStream zipInputStream = new ZipInputStream(Files.newInputStream(Paths.get(fileName)));
            zipInputStream.getNextEntry(); // Move to the first entry in the ZIP file
            return zipInputStream;
        } else {
            throw new UnsupportedOperationException("Złe rozszerzenie pliku");
        }
    }
}
