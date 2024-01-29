package lab13.service;

import lab13.controller.PracownikHolder;
import lab13.model.base.Pracownik;
import lab13.utils.FileReadingUtils;
import lab13.utils.FileWritingUtils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.nio.file.NoSuchFileException;

import static lab13.utils.SaveFolderUtils.createDataFolder;

public class FileIOService {
    private final PracownikHolder pracownikHolder;
    private final Executor executor;
    private final String folderName;

    // Divided constructors to change the save path for testing purposes
    public FileIOService(PracownikHolder pracownikHolder) {
        this.pracownikHolder = pracownikHolder;
        this.executor = Executors.newFixedThreadPool(10);
        this.folderName = "data";
    }

    public FileIOService(PracownikHolder pracownikHolder, String folderName) {
        this.pracownikHolder = pracownikHolder;
        this.executor = Executors.newFixedThreadPool(10);
        this.folderName = folderName;
    }

    public void saveToGZipFiles() throws IOException {
        createDataFolder(folderName);

        CompletableFuture<Void>[] futures = new CompletableFuture[pracownikHolder.getSize()];

        // Save each Pracownik to a separate GZIP file
        for (int i = 0; i < pracownikHolder.getSize(); i++) {
            Pracownik pracownik = pracownikHolder.getPracownikAtIndex(i);
            futures[i] = FileWritingUtils.savePracownikGZipAsync(pracownik, "pracownik_" + pracownik.getPesel() + ".gz", executor, folderName);
        }

        // Combine all CompletableFuture instances into one
        CompletableFuture<Void> allOf = CompletableFuture.allOf(futures);

        // Wait for all CompletableFuture to complete and handle exceptions
        try {
            allOf.get(); // This will block until all futures are complete
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException("Blad podczas zapisu pracownika: " + e.getMessage(), e);
        }
    }

    public void saveToZipFiles() throws IOException {
        createDataFolder(folderName);

        CompletableFuture<Void>[] futures = new CompletableFuture[pracownikHolder.getSize()];

        // Save each Pracownik to a separate ZIP file
        for (int i = 0; i < pracownikHolder.getSize(); i++) {
            Pracownik pracownik = pracownikHolder.getPracownikAtIndex(i);
            futures[i] = FileWritingUtils.savePracownikZipAsync(pracownik, "pracownik_" + pracownik.getPesel() + ".zip", executor, folderName);
        }

        // Combine all CompletableFuture instances into one
        CompletableFuture<Void> allOf = CompletableFuture.allOf(futures);

        // Wait for all CompletableFuture to complete and handle exceptions
        try {
            allOf.get(); // This will block until all futures are complete
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException("Blad podczas zapisu pracownika: " + e.getMessage(), e);
        }
    }

    public void readFromFiles() throws IOException {
        Path dataFolderPath = Paths.get(folderName);

        try {
            // Get a list of files in the data folder
            List<Path> files = Files.list(dataFolderPath)
                    .collect(Collectors.toList());

            // Collect CompletableFutures in a list
            List<CompletableFuture<Pracownik>> futures = files.stream()
                    .map(filePath -> FileReadingUtils.readPracownikAsync(filePath.toString(), executor))
                    .collect(Collectors.toList());

            // Wait for CompletableFuture to complete and handle exceptions
            for (CompletableFuture<Pracownik> future : futures) {
                try {
                    Pracownik pracownik = future.get();
                    if (pracownik != null) {
                        // Check if PESEL is already in use
                        if (!pracownikHolder.isPeselInUse(pracownik.getPesel())) {
                            // Add the read Pracownik object to the pracownicy list
                            pracownikHolder.addPracownik(pracownik);
                            System.out.println("Pomyślnie wczytano pracownika o numerze PESEL: " + pracownik.getPesel());
                        } else {
                            System.out.println("Pracownik o numerze PESEL " + pracownik.getPesel() + " już istnieje. Pomijanie.");
                        }
                    } /*else {
                        System.out.println("Błąd podczas wczytania pracownika z pliku: obiekt null");
                    }*/
                } catch (InterruptedException | ExecutionException e) {
                    System.err.println("Błąd podczas czytania pracownika: " + e.getMessage());
                }
            }
        } catch (NoSuchFileException e) {
            throw new IOException("Folder '" + folderName + "' nie istnieje. Proszę najpierw zapisać przed odczytem.", e);
        } catch (IOException e) {
            throw new IOException("Błąd podczas listowania plików w folderze '" + folderName + "': " + e.getMessage(), e);
        }
    }
}
