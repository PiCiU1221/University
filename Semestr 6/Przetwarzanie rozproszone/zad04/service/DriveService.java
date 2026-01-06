package edu.zut.service;

import edu.zut.model.DriveFile;
import org.json.JSONObject;

import java.nio.file.Path;
import java.util.List;

public class DriveService {
    private final DriveApiClient apiClient;

    public DriveService(String accessToken, String refreshToken, String clientId, String clientSecret) {
        this.apiClient = new DriveApiClient(accessToken, refreshToken, clientId, clientSecret);
    }

    public List<DriveFile> listFiles(String parentId, String pageToken, StringBuilder nextPageToken) throws Exception {
        return apiClient.listFiles(parentId, pageToken, nextPageToken);
    }

    public void deleteFile(DriveFile file) throws Exception {
        apiClient.deleteFile(file.getId());
    }

    public void renameFile(DriveFile file, String newName) throws Exception {
        apiClient.renameFile(file.getId(), newName);
        file.setName(newName);
    }

    public void uploadFile(Path filePath) throws Exception {
        apiClient.uploadFile(filePath);
    }

    public JSONObject getFileMetadata(DriveFile file) throws Exception {
        return apiClient.getFileMetadata(file.getId());
    }

    public void downloadFile(DriveFile file) throws Exception {
        apiClient.downloadFile(file.getId(), file.getName());
    }

    public void moveFileToFolder(DriveFile file, String oldFolderId, String newFolderId) throws Exception {
        apiClient.moveFileToFolder(file.getId(), oldFolderId, newFolderId);
    }

    public String createFolder(String folderName, String parentFolderId) throws Exception {
        return apiClient.createFolder(folderName, parentFolderId);
    }
}

