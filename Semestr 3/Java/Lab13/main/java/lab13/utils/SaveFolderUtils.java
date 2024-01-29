package lab13.utils;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SaveFolderUtils {
    public static void createDataFolder(String folderName) throws IOException {
        // Check if the "data" folder exists, create it if not
        Path dataFolderPath = Paths.get(folderName);

        if (!Files.exists(dataFolderPath)) {
            try {
                Files.createDirectory(dataFolderPath);
            } catch (IOException e) {
                throw new IOException("Błąd podczas tworzenia folderu 'data': " + e.getMessage(), e);
            }
        } else {
            try {
                deleteFolderContents(folderName);
            } catch (IOException e) {
                throw new IOException("Błąd podczas usuwania zawartości folderu 'data': " + e.getMessage(), e);
            }
        }
    }

    public static void deleteFolderContents(String folderPath) throws IOException {
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
                        if (!file.delete()) {
                            throw new IOException("Błąd podczas usuwania pliku '" + file.getAbsolutePath() + "'");
                        }
                    }
                }
            }
        } else {
            throw new IOException("Błąd podczas czyszczenia zawartości folderu: Folder nie istnieje");
        }
    }
}
