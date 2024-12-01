package unsw.entities.files;

import unsw.response.models.FileInfoResponse;

public class File {
    boolean complete = true;
    private String name;
    private int size;
    private String data;

    public String getName() {
        return name;
    }

    public File(String filename, String data) {
        name = filename;
        this.data = data;
        size = data.length();
    }

    public FileInfoResponse getResponse() {
        return new FileInfoResponse(name, data, size, complete);
    }

    public int getSize() {
        return size;
    }
    public boolean getComplete() {
        return complete;
    }


    public void receive(String data) {
        this.data += data;
    }

    public void setComplete(boolean complete) {
        this.complete = complete;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public String getData() {
        return data;
    }

}
