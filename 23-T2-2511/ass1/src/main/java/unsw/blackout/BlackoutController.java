package unsw.blackout;

import unsw.entities.files.File;
import unsw.response.models.EntityInfoResponse;
import unsw.entities.satellites.Standard;
import unsw.entities.Entity;
import unsw.slope.Slope;
import unsw.entities.devices.Desktop;
import unsw.entities.devices.Handler;
import unsw.entities.satellites.Teleport;
import unsw.entities.files.TransFile;
import unsw.entities.devices.Device;
import unsw.entities.devices.Laptop;
import unsw.entities.satellites.Relay;
import unsw.utils.Angle;

import java.util.stream.Collectors;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
public class BlackoutController {
    public void createSatellite(String id, String type, double height, Angle position) {
        Entity satellite = type.equals("RelaySatellite") ? new Relay(type, id, position, height)
                : type.equals("StandardSatellite") ? new Standard(type, id, position, height)
                : new Teleport(id, type, height, position);
        entities.put(id, satellite);
    }

    public void removeSatellite(String satelliteId) {
        entities.remove(satelliteId);
    }

    public void createDevice(String id, String type, Angle position) {
        Entity device = type.equals("DesktopDevice") ? new Desktop(type, id, position)
                : type.equals("HandheldDevice") ? new Handler(type, id, position)
                : new Laptop(type, id, position);
        entities.put(id, device);
    }

    public List<String> listSatelliteIds() {
        List<String> satellites = listEntity(1);
        return satellites;
    }

    public List<String> listDeviceIds() {
        List<String> devices = listEntity(0);
        return devices;
    }

    public void addFileToDevice(String deviceId, String filename, String content) {
        Device d = (Device) entities.get(deviceId);
        d.addFile(filename, content);
    }

    private final Map<String, Entity> entities = new HashMap<>();

    public void simulate() {
        entities.values().forEach(entity -> {
            if (entity.getEntityType() == 0) {
                entity.move(slopes);
            } else {
                entity.move();
            }
        });

        Iterator<TransFile> iterator = transFiles.iterator();
        while (iterator.hasNext()) {
            TransFile fileLink = iterator.next();
            boolean isOver = fileLink.transfer();
            if (isOver) {
                iterator.remove();
            }
        }

    }

    private final ArrayList<Slope> slopes = new ArrayList<>();

    public EntityInfoResponse getInfo(String id) {
        return entities.get(id).toEntityInfoResponse();
    }

    /**
     * Simulate for the specified number of minutes.
     * You shouldn't need to modify this function.
     */
    public void simulate(int numberOfMinutes) {
        for (int i = 0; i < numberOfMinutes; i++) {
            simulate();
        }
    }

    private void checkSend(String fromId, String toId, String name) throws FileTransferException {
        Entity to = entities.get(toId);
        for (int i = 0; i < to.getFiles().size(); i++) {
            File f = to.getFiles().get(i);
            String toFileName = f.getName();
            if (name.equals(toFileName))
                throw new FileTransferException.VirtualFileAlreadyExistsException(name);
        }
        if (to.receiveOverload()) {
            overLoad(toId);
        }

        Entity from = entities.get(fromId);
        if (from.sendingOverload()) {
            overLoad(fromId);
        }
        to.hasCapacity(from.getFile(name).getSize());
    }

    private void transFile(Entity from, Entity to, File file, File toFile) {
        int fileSize = file.getSize();
        from.addSendingNum(1);
        file.setComplete(false);
        to.addReceiveNum(1);
        toFile.setSize(fileSize);
        toFile.setComplete(false);
        to.addFile(toFile);
        transFiles.add(new TransFile(to, from, toFile, file));
    }

    public void sendFile(String name, String fromId, String toId) throws FileTransferException {
        Entity to = entities.get(toId);
        Entity from = entities.get(fromId);
        checkSend(fromId, toId, name);
        File file = from.getFile(name);
        File toFile = new File(name, "");
        transFile(from, to, file, toFile);
    }

    public void createDevice(String id, String type, Angle pos, boolean movable) {
        createDevice(id, type, pos);
        if (movable) {
            ((Device) entities.get(id)).setMovable(true);
        }
    }

    public List<String> communicableEntitiesInRange(String id) {
        Entity source = this.entities.get(id);

        return this.entities.values().stream()
                .filter(entity -> !entity.getId().equals(id))
                .filter(source::isInRange)
                .map(Entity::getId)
                .collect(Collectors.toList());
    }

    public void createSlope(int start, int end, int gradient) {

        ArrayList<Slope> crossed;
        Slope slope = new Slope(end, start, gradient);
        crossed = findCrossed(slope);
        if (crossed.size() > 0) {
            this.updateSlope(crossed);
        }
        this.slopes.add(slope);
    }

    public void removeDevice(String id) {
        entities.remove(id);
    }

    private ArrayList<Slope> findCrossed(Slope s) {
        for (int i = 0; i < slopes.size(); i++) {
            if (slopes.get(i).findCrossed(s).size() != 0)
                return slopes.get(i).findCrossed(s);
        }
        return new ArrayList<>();
    }


    private List<String> listEntity(int type) {
        List<String> outcome = entities.entrySet().stream()
                .filter(entry -> entry.getValue().getEntityType() == type)
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());

        return outcome;
    }

    private void overLoad(String id) throws FileTransferException {
        throw new FileTransferException.VirtualFileNoBandwidthException(id);
    }

    private void updateSlope(ArrayList<Slope> old) {
        Slope slope1 = old.get(0);
        int gradient1 = slope1.getGradient();
        Slope slope2 = old.get(1);
        int gradient2 = slope2.getGradient();

        boolean condition1 = (gradient1 > 0 && gradient2 > 0 && gradient1 > gradient2);
        boolean condition2 = (gradient1 > 0 && gradient2 > 0 && gradient1 <= gradient2);
        boolean condition3 = (gradient1 > 0 && gradient2 <= 0);
        boolean condition4 = (gradient1 <= 0 && gradient2 < 0 && gradient1 < gradient2);
        boolean condition5 = (gradient1 <= 0 && gradient2 < 0 && gradient1 >= gradient2);
        boolean condition6 = (gradient1 <= 0 && gradient2 >= 0);

        slope2.modify(condition1 || condition3 || condition5 ? slope1.getEnd() : slope2.getStart(), true);
        slope1.modify(condition2 || condition4 || condition6 ? slope2.getStart() : slope1.getEnd(), false);
    }
    private final ArrayList<TransFile> transFiles = new ArrayList<>();
}
