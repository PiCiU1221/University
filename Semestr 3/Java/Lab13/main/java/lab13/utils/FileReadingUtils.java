package lab13.utils;

import lab13.model.base.Pracownik;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionException;
import java.util.concurrent.Executor;
import java.util.zip.GZIPInputStream;
import java.util.zip.ZipException;
import java.util.zip.ZipInputStream;

public class FileReadingUtils {

    public static CompletableFuture<Pracownik> readPracownikAsync(String fileName, Executor executor) {
        return CompletableFuture.supplyAsync(() -> {
                    try {
                        return readPracownikFromFile(fileName);
                    } catch (IOException e) {
                        throw new CompletionException(e);
                    }
                }, executor)
                .exceptionally(throwable -> {
                    if (throwable.getCause() instanceof IOException) {
                        System.err.println("Blad odczytu z pliku: " + throwable.getCause().getMessage());
                    } else {
                        System.err.println("Blad odczytu z pliku: " + throwable.getMessage());
                    }
                    return null;
                });
    }

    public static Pracownik readPracownikFromFile(String fileName) throws IOException {
        try (InputStream inputStream = getInputStreamBasedOnExtension(fileName)) {
            ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(inputStream));
            return (Pracownik) ois.readObject();
        } catch (ZipException | StreamCorruptedException e) {
            throw new IOException("uszkodzony plik zapisu: " + fileName);
        } catch (IOException | ClassNotFoundException | UnsupportedOperationException e) {
            throw new IOException(e.getMessage());
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
