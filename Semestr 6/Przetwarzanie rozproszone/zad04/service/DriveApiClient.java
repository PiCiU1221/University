package edu.zut.service;

import java.net.URI;
import java.net.URLEncoder;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.util.ArrayList;
import java.util.List;

import edu.zut.model.DriveFile;
import org.json.JSONArray;
import org.json.JSONObject;

public class DriveApiClient {
    private final HttpClient httpClient;
    private String accessToken;
    private final String refreshToken;
    private final String clientId;
    private final String clientSecret;

    public DriveApiClient(String accessToken, String refreshToken, String clientId, String clientSecret) {
        this.accessToken = accessToken;
        this.refreshToken = refreshToken;
        this.clientId = clientId;
        this.clientSecret = clientSecret;
        this.httpClient = HttpClient.newBuilder()
                .connectTimeout(Duration.ofSeconds(10))
                .build();
    }

    private void refreshAccessToken() throws Exception {
        System.out.println("Refreshing access token...");

        String url = "https://oauth2.googleapis.com/token";

        String body = "client_id=" + URLEncoder.encode(clientId, "UTF-8") +
                "&client_secret=" + URLEncoder.encode(clientSecret, "UTF-8") +
                "&refresh_token=" + URLEncoder.encode(refreshToken, "UTF-8") +
                "&grant_type=refresh_token";

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .header("Content-Type", "application/x-www-form-urlencoded")
                .POST(HttpRequest.BodyPublishers.ofString(body))
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        if (response.statusCode() != 200) {
            throw new RuntimeException("Failed to refresh token: HTTP " + response.statusCode() + " - " + response.body());
        }

        JSONObject json = new JSONObject(response.body());
        this.accessToken = json.getString("access_token");
        System.out.println("Access token refreshed successfully.");
    }

    private HttpResponse<String> sendRequestWithAutoRefresh(HttpRequest request) throws Exception {
        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());
        if (response.statusCode() == 401) {
            refreshAccessToken();

            HttpRequest newRequest = HttpRequest.newBuilder(request.uri())
                    .method(request.method(), request.bodyPublisher().orElse(HttpRequest.BodyPublishers.noBody()))
                    .headers(
                            "Authorization", "Bearer " + accessToken,
                            "Accept", request.headers().firstValue("Accept").orElse("*/*"),
                            "Content-Type", request.headers().firstValue("Content-Type").orElse("application/json")
                    )
                    .build();

            response = httpClient.send(newRequest, HttpResponse.BodyHandlers.ofString());
        }
        return response;
    }

    public List<DriveFile> listFiles(String parentId, String pageToken, StringBuilder nextPageTokenOut) throws Exception {
        String encodedParent = URLEncoder.encode("'" + parentId + "' in parents", "UTF-8");
        String url = "https://www.googleapis.com/drive/v3/files?q=" + encodedParent +
                "&pageSize=5&fields=nextPageToken,files(id,name,mimeType)";

        if (pageToken != null && !pageToken.isEmpty()) {
            url += "&pageToken=" + URLEncoder.encode(pageToken, "UTF-8");
        }

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .header("Authorization", "Bearer " + accessToken)
                .header("Accept", "application/json")
                .GET()
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() != 200) {
            throw new RuntimeException("Failed to list files: HTTP " + response.statusCode());
        }

        JSONObject json = new JSONObject(response.body());
        nextPageTokenOut.setLength(0);
        nextPageTokenOut.append(json.optString("nextPageToken", ""));

        List<DriveFile> files = new ArrayList<>();
        JSONArray filesArray = json.optJSONArray("files");
        if (filesArray != null) {
            for (int i = 0; i < filesArray.length(); i++) {
                JSONObject f = filesArray.getJSONObject(i);
                files.add(new DriveFile(f.getString("id"), f.getString("name"), f.getString("mimeType")));
            }
        }
        return files;
    }

    public void deleteFile(String fileId) throws Exception {
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://www.googleapis.com/drive/v3/files/" + fileId))
                .header("Authorization", "Bearer " + accessToken)
                .DELETE()
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() != 204) {
            throw new RuntimeException("Failed to delete file: HTTP " + response.statusCode() + " - " + response.body());
        }
    }

    public void renameFile(String fileId, String newName) throws Exception {
        JSONObject bodyJson = new JSONObject();
        bodyJson.put("name", newName);

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://www.googleapis.com/drive/v3/files/" + fileId))
                .header("Authorization", "Bearer " + accessToken)
                .header("Content-Type", "application/json")
                .method("PATCH", HttpRequest.BodyPublishers.ofString(bodyJson.toString()))
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() < 200 || response.statusCode() >= 300) {
            throw new RuntimeException("Failed to rename file: HTTP " + response.statusCode() + " - " + response.body());
        }
    }

    public JSONObject uploadFile(Path filePath) throws Exception {
        String boundary = "----JavaBoundary" + System.currentTimeMillis();

        String metadataJson = "{\"name\": \"" + filePath.getFileName().toString() + "\"}";
        byte[] fileBytes = Files.readAllBytes(filePath);

        String lineEnd = "\r\n";
        String twoHyphens = "--";

        var byteArrayOutputStream = new java.io.ByteArrayOutputStream();
        var outputStreamWriter = new java.io.OutputStreamWriter(byteArrayOutputStream, "UTF-8");

        outputStreamWriter.write(twoHyphens + boundary + lineEnd);
        outputStreamWriter.write("Content-Type: application/json; charset=UTF-8" + lineEnd + lineEnd);
        outputStreamWriter.write(metadataJson + lineEnd);

        outputStreamWriter.write(twoHyphens + boundary + lineEnd);
        outputStreamWriter.write("Content-Type: application/octet-stream" + lineEnd + lineEnd);
        outputStreamWriter.flush();

        byteArrayOutputStream.write(fileBytes);
        outputStreamWriter.write(lineEnd);
        outputStreamWriter.write(twoHyphens + boundary + twoHyphens + lineEnd);
        outputStreamWriter.flush();

        byte[] multipartBody = byteArrayOutputStream.toByteArray();

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://www.googleapis.com/upload/drive/v3/files?uploadType=multipart"))
                .header("Authorization", "Bearer " + accessToken)
                .header("Content-Type", "multipart/related; boundary=" + boundary)
                .POST(HttpRequest.BodyPublishers.ofByteArray(multipartBody))
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() < 200 || response.statusCode() >= 300) {
            throw new RuntimeException("Failed to upload file: HTTP " + response.statusCode() + " - " + response.body());
        }

        return new JSONObject(response.body());
    }

    public JSONObject getFileMetadata(String fileId) throws Exception {
        String url = "https://www.googleapis.com/drive/v3/files/" + fileId
                + "?fields=id,name,createdTime,modifiedTime,mimeType,size";

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .header("Authorization", "Bearer " + accessToken)
                .header("Accept", "application/json")
                .GET()
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() != 200) {
            throw new RuntimeException("Failed to get file metadata: HTTP " + response.statusCode() + " - " + response.body());
        }

        return new JSONObject(response.body());
    }

    public void downloadFile(String fileId, String fileName) throws Exception {
        Path downloadDir = Paths.get("filesDownloaded");
        if (!java.nio.file.Files.exists(downloadDir)) {
            java.nio.file.Files.createDirectories(downloadDir);
        }

        Path targetPath = downloadDir.resolve(fileName);

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://www.googleapis.com/drive/v3/files/" + fileId + "?alt=media"))
                .header("Authorization", "Bearer " + accessToken)
                .GET()
                .build();

        HttpResponse<Path> response = httpClient.send(request, HttpResponse.BodyHandlers.ofFile(targetPath));

        if (response.statusCode() != 200) {
            throw new RuntimeException("Failed to download file: HTTP " + response.statusCode());
        }

        System.out.println("File downloaded to: " + targetPath.toAbsolutePath());
    }

    public void moveFileToFolder(String fileId, String oldFolderId, String newFolderId) throws Exception {
        String url = "https://www.googleapis.com/drive/v3/files/" + fileId +
                "?addParents=" + URLEncoder.encode(newFolderId, "UTF-8") +
                "&removeParents=" + URLEncoder.encode(oldFolderId, "UTF-8");

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .method("PATCH", HttpRequest.BodyPublishers.ofString("{}"))
                .header("Authorization", "Bearer " + accessToken)
                .header("Content-Type", "application/json")
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() != 200) {
            throw new RuntimeException("Failed to move file: HTTP " + response.statusCode() + " - " + response.body());
        }
    }

    public String createFolder(String folderName, String parentFolderId) throws Exception {
        JSONObject metadata = new JSONObject();
        metadata.put("name", folderName);
        metadata.put("mimeType", "application/vnd.google-apps.folder");

        if (parentFolderId != null && !parentFolderId.isEmpty()) {
            JSONArray parents = new JSONArray();
            parents.put(parentFolderId);
            metadata.put("parents", parents);
        }

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://www.googleapis.com/drive/v3/files"))
                .header("Authorization", "Bearer " + accessToken)
                .header("Content-Type", "application/json")
                .POST(HttpRequest.BodyPublishers.ofString(metadata.toString()))
                .build();

        HttpResponse<String> response = sendRequestWithAutoRefresh(request);

        if (response.statusCode() != 200 && response.statusCode() != 201) {
            throw new RuntimeException("Failed to create folder: HTTP " + response.statusCode() + " - " + response.body());
        }

        JSONObject jsonResponse = new JSONObject(response.body());
        return jsonResponse.getString("id");
    }
}
