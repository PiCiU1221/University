package edu.zut.model;

public class DriveFile {
    private final String id;
    private String name;
    private String mimeType;

    public DriveFile(String id, String name, String mimeType) {
        this.id = id;
        this.name = name;
        this.mimeType = mimeType;
    }

    public String getId() { return id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getMimeType() { return mimeType; }
    public boolean isFolder() {
        return "application/vnd.google-apps.folder".equals(mimeType);
    }
}
