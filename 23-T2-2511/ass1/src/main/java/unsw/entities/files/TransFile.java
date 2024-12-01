package unsw.entities.files;

import unsw.entities.Entity;

public class TransFile {
    private int point = 0;
    final private Entity fromEntity;
    final private Entity toEntity;
    final private File fromFile;
    final private File toFile;
    final private String data;

    private void endTrans() {
        fromFile.setComplete(true);
        fromEntity.addSendingNum(-1);
        toFile.setComplete(true);
        toEntity.addReceiveNum(-1);
    }

    public TransFile(Entity toEntity, Entity fromEntity, File toFile, File fromFile) {
        this.fromFile = fromFile;
        this.fromEntity = fromEntity;
        this.toFile = toFile;
        this.toEntity = toEntity;
        this.data = fromFile.getData();
    }

    public boolean transfer() {
        int speed = Math.min(fromEntity.getAvgSendSpeed(), toEntity.getAvgRecvSpeed());
        int end = Math.min(point + speed, data.length());
        toFile.receive(data.substring(point, end));

        if (end >= data.length()) {
            endTrans();
            return true;
        }
        point += speed;
        return false;
    }
}
