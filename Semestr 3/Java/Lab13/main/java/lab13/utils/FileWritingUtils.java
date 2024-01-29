package lab13.utils;

import lab13.model.base.Pracownik;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionException;
import java.util.concurrent.Executor;
import java.util.zip.Deflater;
import java.util.zip.GZIPOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class FileWritingUtils {

    public static CompletableFuture<Void> savePracownikGZipAsync(Pracownik pracownik, String fileName, Executor executor, String folderName) {
        return CompletableFuture.runAsync(() -> {
            try {
                savePracownikToGZipFile(pracownik, fileName, folderName);
            } catch (IOException e) {
                throw new CompletionException(e); // Wrap checked exception in CompletionException
            }
        }, executor).exceptionally(throwable -> {
            if (throwable.getCause() instanceof IOException) {
                System.err.println(throwable.getCause().getMessage());
            } else {
                System.err.println("Blad podczas zapisu pracownika: " + throwable.getMessage());
            }
            return null;
        });
    }

    public static void savePracownikToGZipFile(Pracownik pracownik, String fileName, String folderName) throws IOException {
        String filePath = folderName + "/" + fileName;
        String pesel = pracownik.getPesel();

        try (ObjectOutputStream oos = new ObjectOutputStream(
                new BufferedOutputStream(
                        new GZIPOutputStream(
                                Files.newOutputStream(Paths.get(filePath)))))) {
            oos.writeObject(pracownik);
            System.out.println("Dane pracownika " + pesel + " zachowane pomyślnie do pliku GZIP.");
        } catch (IOException e) {
            throw new IOException("Błąd podczas zapisu danych pracownika do pliku GZIP: " + e.getMessage(), e);
        }
    }

    public static CompletableFuture<Void> savePracownikZipAsync(Pracownik pracownik, String fileName, Executor executor, String folderName) {
        return CompletableFuture.runAsync(() -> {
            try {
                savePracownikToZipFile(pracownik, fileName, folderName);
            } catch (IOException e) {
                throw new CompletionException(e); // Wrap checked exception in CompletionException
            }
        }, executor).exceptionally(throwable -> {
            if (throwable.getCause() instanceof IOException) {
                System.err.println(throwable.getCause().getMessage());
            } else {
                System.err.println("Blad podczas zapisu pracownika: " + throwable.getMessage());
            }
            return null;
        });
    }

    public static void savePracownikToZipFile(Pracownik pracownik, String fileName, String folderName) throws IOException {
        String filePath = folderName + "/" + fileName;
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
            throw new IOException("Błąd podczas zapisu danych pracownika do pliku ZIP: " + e.getMessage(), e);
        }
    }
}
