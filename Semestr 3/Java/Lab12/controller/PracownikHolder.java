package lab12.controller;

import lab12.model.PracownicyKlasy.Pracownik;
import lab12.utils.FileUtils;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class PracownikHolder {
    private final List<Pracownik> pracownicy;
    private final Executor executor;

    public PracownikHolder() {
        this.pracownicy = new ArrayList<>();
        this.executor = Executors.newFixedThreadPool(10);
    }

    public void dodajPracownika(Pracownik pracownik) {
        pracownicy.add(pracownik);
    }

    public void wyswietlListePracownikow() {
        System.out.println("Lista pracowników:");
        for (Pracownik pracownik : pracownicy) {
            System.out.println(pracownik);
        }
    }

    public int getSize() {
        return pracownicy.size();
    }

    public Pracownik getPracownikAtPosition(int position) {
        if (position >= 0 && position < pracownicy.size()) {
            return pracownicy.get(position);
        } else {
            throw new IndexOutOfBoundsException("Invalid position");
        }
    }

    public Pracownik getPracownik(String pesel) {
        for (Pracownik pracownik : pracownicy) {
            if (pracownik.getPesel().equals(pesel)) {
                return pracownik;
            }
        }
        return null;
    }

    public void usunPracownika(Pracownik pracownik) {
        if (pracownik != null) {
            pracownicy.remove(pracownik);
            System.out.println("Pracownik usunięty pomyślnie.");
        } else {
            System.out.println("Podany pracownik nie istnieje.");
        }
    }

    public void saveToGZipFile() {
        createDataFolder();

        CompletableFuture<Void>[] futures = new CompletableFuture[pracownicy.size()];

        // Save each Pracownik to a separate GZIP file
        for (int i = 0; i < pracownicy.size(); i++) {
            Pracownik pracownik = getPracownikAtPosition(i);
            futures[i] = FileUtils.savePracownikGZipAsync(pracownik, "pracownik_" + pracownik.getPesel() + ".gz", executor);
        }

        // Combine all CompletableFuture instances into one
        CompletableFuture<Void> allOf = CompletableFuture.allOf(futures);

        // Wait for all CompletableFuture to complete and handle exceptions
        try {
            allOf.get(); // This will block until all futures are complete
        } catch (InterruptedException | ExecutionException e) {
            System.err.println("Error while saving pracownik: " + e.getMessage());
        }
    }

    public void saveToZipFile() {
        createDataFolder();

        CompletableFuture<Void>[] futures = new CompletableFuture[pracownicy.size()];

        // Save each Pracownik to a separate ZIP file
        for (int i = 0; i < pracownicy.size(); i++) {
            Pracownik pracownik = getPracownikAtPosition(i);
            futures[i] = FileUtils.savePracownikZipAsync(pracownik, "pracownik_" + pracownik.getPesel() + ".zip", executor);
        }

        // Combine all CompletableFuture instances into one
        CompletableFuture<Void> allOf = CompletableFuture.allOf(futures);

        // Wait for all CompletableFuture to complete and handle exceptions
        try {
            allOf.get(); // This will block until all futures are complete
        } catch (InterruptedException | ExecutionException e) {
            System.err.println("Error while saving pracownik: " + e.getMessage());
        }
    }

    private static void createDataFolder() {
        // Check if the "data" folder exists, create it if not
        Path dataFolderPath = Paths.get("data");
        if (!Files.exists(dataFolderPath)) {
            try {
                Files.createDirectory(dataFolderPath);
            } catch (IOException e) {
                e.printStackTrace();
                System.out.println("Błąd podczas tworzenia folderu 'data': " + e.getMessage());
            }
        } else {
            deleteFolderContents("data");
        }
    }

    public static void deleteFolderContents(String folderPath) {
        File folder = new File(folderPath);

        // Check if the folder exists
        if (folder.exists() && folder.isDirectory()) {
            File[] files = folder.listFiles();

            if (files != null) {
                // Loop through each file and delete it
                for (File file : files) {
                    if (file.isDirectory()) {
                        deleteFolderContents(file.getAbsolutePath());
                    } else {
                        file.delete();
                    }
                }
            }
        } else {
            System.out.println("Błąd podczas usuwania zawartości folderu");
        }
    }

    public void readFromFiles() {
        Path dataFolderPath = Paths.get("data");

        try {
            // Get a list of files in the data folder
            List<Path> files = Files.list(dataFolderPath)
                    .collect(Collectors.toList());

            // Collect CompletableFutures in a list
            List<CompletableFuture<Pracownik>> futures = files.stream()
                    .map(filePath -> FileUtils.readPracownikAsync(filePath.toString(), executor))
                    .collect(Collectors.toList());

            // Wait for CompletableFuture to complete and handle exceptions
            for (CompletableFuture<Pracownik> future : futures) {
                try {
                    Pracownik pracownik = future.get();
                    if (pracownik != null) {
                        // Check if PESEL is already in use
                        if (!isPeselInUse(pracownik.getPesel())) {
                            // Add the read Pracownik object to the pracownicy list
                            pracownicy.add(pracownik);
                            System.out.println("Pomyślnie wczytano pracownika o numerze PESEL: " + pracownik.getPesel());
                        } else {
                            System.out.println("Pracownik o numerze PESEL " + pracownik.getPesel() + " już istnieje. Pomijanie.");
                        }
                    } else {
                        System.out.println("Błąd podczas czytania pracownika z pliku: obiekt null");
                    }
                } catch (InterruptedException | ExecutionException e) {
                    System.err.println("Błąd podczas czytania pracownika: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Błąd podczas listowania plików w folderze 'data': " + e.getMessage());
        }
    }

    public boolean isPeselInUse(String pesel) {
        for (Pracownik pracownik : pracownicy) {
            if (pracownik.getPesel().equals(pesel)) {
                return true;
            }
        }
        return false;
    }
}