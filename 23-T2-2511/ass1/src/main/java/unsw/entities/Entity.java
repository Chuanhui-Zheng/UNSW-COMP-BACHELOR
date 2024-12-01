package unsw.entities;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Map;
import java.util.stream.Collectors;
import unsw.entities.files.File;
import unsw.blackout.FileTransferException;
import unsw.slope.Slope;
import unsw.response.models.EntityInfoResponse;
import unsw.response.models.FileInfoResponse;
import unsw.utils.Angle;
import unsw.utils.MathsHelper;

public class Entity {
    protected String id;
    protected String type;
    protected int recvSpeed = 999999;
    protected int sendSpeed = 999999;
    protected int entityType; //0 -> device and 1 -> satellite
    protected Angle pos;
    protected int fileMax = 999999;
    protected double height;
    protected ArrayList<File> files = new ArrayList<>();
    protected int commRange;
    protected HashSet<String> commTypeSupport;
    protected int curFiles = 0;
    protected int direct = MathsHelper.CLOCKWISE;
    protected int curBytes = 0;
    protected int linearSpeed;
    protected int byteMax = 999999;

    protected int fileSend = 0;
    protected int filerecv = 0;

    public Entity(String entityType, double entityHeight, Angle entityPos, String entityId) {
        commTypeSupport = new HashSet<>();
        type = entityType;
        height = entityHeight;
        pos = entityPos;
        id = entityId;
        updateAngle();
    }

    public double getHeight() {
        return height;
    }

    public String getId() {
        return id;
    }

    public String getType() {
        return type;
    }

    public Angle getPos() {
        return pos;
    }

    public int getEntityType() {
        return entityType;
    }

    public ArrayList<File> getFiles() {
        return files;
    }

    public int getAvgSendSpeed() {
        return sendSpeed / fileSend;
    }

    public int getAvgRecvSpeed() {
        return recvSpeed / filerecv;
    }

    public void addSendingNum(int i) {
        fileSend += i;
    }

    public void addReceiveNum(int i) {
        filerecv += i;
    }

    public boolean sendingOverload() {
        return sendSpeed == fileSend;
    }

    public boolean receiveOverload() {
        return recvSpeed == filerecv;
    }

    public boolean hasByteCapacity(int size) {
        return byteMax >= curBytes + size;
    }

    public boolean hasFileCapacity() {
        return fileMax >= curFiles + 1;
    }

    public void move() {
    }

    public void move(ArrayList<Slope> slopes) {
    }

    public void addFile(File file) {
        files.add(file);
    }

    public void updateAngle() {
        double degree = pos.toDegrees();
        while (degree > 360) degree -= 360;
        while (degree < 0) degree += 360;
        pos = Angle.fromDegrees(degree);
    }

    public Angle entityMove() {
        return Angle.fromRadians(linearSpeed / height);
    }

    public boolean isInRange(Entity o) {
        String type = o.getType();
        return (commTypeSupport.contains(type) &&
                MathsHelper.isVisible(height, pos, o.getHeight(), o.getPos()) &&
                MathsHelper.getDistance(height, pos, o.getHeight(), o.getPos()) <= commRange);
    }

    public EntityInfoResponse toEntityInfoResponse() {
        if (this.files.isEmpty()) {
            return new EntityInfoResponse(id, pos, height, type);
        }

        Map<String, FileInfoResponse> fileInfoResponseMap = files.stream()
                .collect(Collectors.toMap(File::getName, File::getResponse));

        return new EntityInfoResponse(id, pos, height, type, fileInfoResponseMap);
    }

    public File getFile(String filename) throws FileTransferException.VirtualFileNotFoundException {
        return this.files.stream()
                .filter(file -> file.getName().equals(filename))
                .findFirst()
                .filter(File::getComplete)
                .orElseThrow(() -> new FileTransferException.VirtualFileNotFoundException(filename));
    }

    public void hasCapacity(int size) throws FileTransferException {
        if (!this.hasFileCapacity())
            throw new FileTransferException.VirtualFileNoStorageSpaceException("Max Files Reached");
        if (!this.hasByteCapacity(size))
            throw new FileTransferException.VirtualFileNoStorageSpaceException("Max storage Reached");
    }
}
