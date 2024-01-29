package lab12.utils;

import lab12.controller.PracownikHolder;
import lab12.model.PracownicyKlasy.Pracownik;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.Executor;
import java.util.zip.*;

import java.util.concurrent.CompletableFuture;

public class FileUtils {

    public static CompletableFuture<Void> savePracownikGZipAsync(Pracownik pracownik, String fileName, Executor executor) {
        return CompletableFuture.runAsync(() -> savePracownikToGZipFile(pracownik, fileName), executor)
                .exceptionally(throwable -> {
                    System.err.println("Error saving pracownik: " + throwable.getMessage());
                    return null;
                });
    }

    public static void savePracownikToGZipFile(Pracownik pracownik, String fileName) {
        String filePath = "data/" + fileName;
        String pesel = pracownik.getPesel();

        try (ObjectOutputStream oos = new ObjectOutputStream(
                new BufferedOutputStream(
                        new GZIPOutputStream(
                                Files.newOutputStream(Paths.get(filePath)))))) {
            oos.writeObject(pracownik);
            System.out.println("Dane pracownika " + pesel + " zachowane pomyślnie do pliku GZIP.");
        } catch (IOException e) {
            System.out.println("Błąd podczas zapisu danych pracownika do pliku GZIP: " + e.getMessage());
        }
    }

    public static CompletableFuture<Void> savePracownikZipAsync(Pracownik pracownik, String fileName, Executor executor) {
        return CompletableFuture.runAsync(() -> savePracownikToZipFile(pracownik, fileName), executor)
                .exceptionally(throwable -> {
                    System.err.println("Error saving pracownik: " + throwable.getMessage());
                    return null;
                });
    }

    public static void savePracownikToZipFile(Pracownik pracownik, String fileName) {
        String filePath = "data/" + fileName;
        String pesel = pracownik.getPesel();

        try (ZipOutputStream zipOut = new ZipOutputStream(new BufferedOutputStream(Files.newOutputStream(Paths.get(filePath))))) {
            zipOut.setLevel(Deflater.DEFAULT_COMPRESSION);

            // Create a ZIP entry for the object
            zipOut.putNextEntry(new ZipEntry("pracownik_" + pesel + ".ser"));

            // Write the object to the ZIP file
            try (ObjectOutputStream oos = new ObjectOutputStream(zipOut)) {
                oos.writeObject(pracownik);
            }

            System.out.println("Dane pracownika " + pesel + " zachowane pomyślnie do pliku ZIP.");
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Błąd podczas zapisu danych pracownika do pliku ZIP: " + e.getMessage());
        }
    }

    public static CompletableFuture<Pracownik> readPracownikAsync(String fileName, Executor executor) {
        return CompletableFuture.supplyAsync(() -> readPracownikFromFile(fileName), executor)
                .exceptionally(throwable -> {
                    System.err.println("Blad odczytu z pliku: " + throwable.getMessage());
                    return null;
                });
    }

    public static Pracownik readPracownikFromFile(String fileName) {
        try (InputStream inputStream = getInputStreamBasedOnExtension(fileName)) {
            if (inputStream != null) {
                ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(inputStream));
                return (Pracownik) ois.readObject();
            } else {
                System.err.println("Plik nie istnieje: " + fileName);
                return null;
            }
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Blad odczytu z pliku: " + e.getMessage());
            return null;
        }
    }

    private static InputStream getInputStreamBasedOnExtension(String fileName) throws IOException {
        String lowerCaseFileName = fileName.toLowerCase();

        Path path = Paths.get(fileName);

        if (lowerCaseFileName.endsWith(".gz")) {
            return new GZIPInputStream(Files.newInputStream(path));
        } else if (lowerCaseFileName.endsWith(".zip")) {
            ZipInputStream zipInputStream = new ZipInputStream(Files.newInputStream(path));
            zipInputStream.getNextEntry();
            return zipInputStream;
        } else {
            throw new UnsupportedOperationException("Rozszerzenie niewspierane");
        }
    }
}
