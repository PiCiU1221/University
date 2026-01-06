package edu.zut;

import edu.zut.model.DriveFile;
import edu.zut.service.DriveService;
import org.json.JSONObject;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    private static DriveService driveService;
    private static String nextPageToken = null;
    private static int currentPage = 1;

    private static String currentFolderId = "root";
    private static Stack<String> folderHistory = new Stack<>();

    public static void main(String[] args) {
        String accessToken = Config.ACCESS_TOKEN;
        String refreshToken = Config.REFRESH_TOKEN;
        String clientId = Config.CLIENT_ID;
        String clientSecret = Config.CLIENT_SECRET;

        driveService = new DriveService(accessToken, refreshToken, clientId, clientSecret);

        while (true) {
            printMenu();
            int choice = getUserChoice();

            try {
                switch (choice) {
                    case 1:
                        uploadFile();
                        break;
                    case 2:
                        listDriveContentPaginated();
                        break;
                    case 0:
                        System.out.println("Exiting application.");
                        scanner.close();
                        System.exit(0);
                    default:
                        System.out.println("Invalid option. Please try again.");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private static void uploadFile() throws Exception {
        System.out.print("Enter filename to upload (relative to filesToUpload/): ");
        String filename = scanner.nextLine();
        Path filePath = Paths.get("filesToUpload", filename);

        if (!java.nio.file.Files.exists(filePath) || !java.nio.file.Files.isRegularFile(filePath)) {
            System.out.println("File does not exist or is not a regular file at path: " + filePath.toAbsolutePath());
            return;
        }

        driveService.uploadFile(filePath);
        System.out.println("File uploaded successfully!");
    }

    private static void listDriveContentPaginated() throws Exception {
        while (true) {
            System.out.println("\n-- Drive Content Page " + currentPage + " --");

            StringBuilder nextTokenBuilder = new StringBuilder();
            List<DriveFile> files = driveService.listFiles(currentFolderId, nextPageToken, nextTokenBuilder);
            nextPageToken = !nextTokenBuilder.isEmpty() ? nextTokenBuilder.toString() : null;

            if (files.isEmpty()) {
                System.out.println("No files found.");
            } else {
                for (int i = 0; i < files.size(); i++) {
                    DriveFile file = files.get(i);
                    String typeLabel = file.isFolder() ? "[Folder]" : "";
                    System.out.printf("%d. %s %s (id: %s)%n", i + 1, file.getName(), typeLabel, file.getId());
                }
            }

            System.out.println("\nOptions: (N)ext page, (U)p one folder, (C)reate folder, (B)ack to main menu");
            System.out.println("Or enter file number to manage or enter folder.");
            System.out.print("Select option: ");
            String input = scanner.nextLine().trim();

            if ("N".equalsIgnoreCase(input) && nextPageToken != null) {
                currentPage++;
            } else if ("U".equalsIgnoreCase(input) && !folderHistory.isEmpty()) {
                currentFolderId = folderHistory.pop();
                nextPageToken = null;
                currentPage = 1;
            } else if ("C".equalsIgnoreCase(input)) {
                System.out.print("Enter new folder name: ");
                String folderName = scanner.nextLine().trim();
                if (!folderName.isEmpty()) {
                    String newFolderId = driveService.createFolder(folderName, currentFolderId);
                    System.out.println("Folder created with ID: " + newFolderId);
                    nextPageToken = null;
                    currentPage = 1;
                } else {
                    System.out.println("Folder name cannot be empty.");
                }
            } else if ("B".equalsIgnoreCase(input)) {
                currentFolderId = "root";
                nextPageToken = null;
                currentPage = 1;
                break;
            } else {
                try {
                    int fileIndex = Integer.parseInt(input) - 1;
                    if (fileIndex >= 0 && fileIndex < files.size()) {
                        DriveFile selected = files.get(fileIndex);
                        if (selected.isFolder()) {
                            folderHistory.push(currentFolderId);
                            currentFolderId = selected.getId();
                            nextPageToken = null;
                            currentPage = 1;
                        } else {
                            manageFileMenu(selected);
                        }
                    } else {
                        System.out.println("Invalid file number.");
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Invalid option.");
                }
            }
        }
    }

    private static void manageFileMenu(DriveFile file) {
        while (true) {
            System.out.println("\nSelected file: " + file.getName() + " (id: " + file.getId() + ")");
            System.out.println("1. Delete file");
            System.out.println("2. Modify file metadata (rename)");
            System.out.println("3. View file metadata");
            System.out.println("4. Download file");
            System.out.println("5. Move file to another folder");
            System.out.println("0. Back to file list");
            System.out.print("Choose an option: ");

            String choice = scanner.nextLine().trim();
            try {
                switch (choice) {
                    case "1":
                        driveService.deleteFile(file);
                        System.out.println("File deleted successfully.");
                        return;
                    case "2":
                        System.out.print("Enter new file name: ");
                        String newName = scanner.nextLine();
                        driveService.renameFile(file, newName);
                        System.out.println("File renamed successfully.");
                        break;
                    case "3":
                        showFileMetadata(file);
                        break;
                    case "4":
                        driveService.downloadFile(file);
                        break;
                    case "5":
                        System.out.print("Enter target folder ID: ");
                        String newFolderId = scanner.nextLine().trim();
                        driveService.moveFileToFolder(file, currentFolderId, newFolderId);
                        System.out.println("File moved successfully.");
                        return;
                    case "0":
                        return;
                    default:
                        System.out.println("Invalid option.");
                }
            } catch (Exception e) {
                System.out.println("Operation failed: " + e.getMessage());
            }
        }
    }

    private static void printMenu() {
        System.out.println("\n-- Google Drive CLI --");
        System.out.println("1. Upload file");
        System.out.println("2. List Drive content");
        System.out.println("0. Exit");
        System.out.print("Enter your choice: ");
    }

    private static int getUserChoice() {
        try {
            return Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    private static void showFileMetadata(DriveFile file) {
        try {
            JSONObject metadata = driveService.getFileMetadata(file);

            System.out.println("\n--- File Metadata ---");
            System.out.println("ID: " + metadata.optString("id"));
            System.out.println("Name: " + metadata.optString("name"));
            System.out.println("Created Time: " + metadata.optString("createdTime"));
            System.out.println("Modified Time: " + metadata.optString("modifiedTime"));
            System.out.println("MIME Type: " + metadata.optString("mimeType"));
            System.out.println("Size: " + metadata.optString("size") + " bytes");
            System.out.println("---------------------\n");

        } catch (Exception e) {
            System.out.println("Failed to retrieve metadata: " + e.getMessage());
        }
    }
}
