package unsw.entities.devices;

import unsw.utils.Angle;
import unsw.entities.Entity;
import unsw.entities.files.File;
import unsw.utils.MathsHelper;
import unsw.slope.Slope;
import java.util.ArrayList;

public class Device extends Entity {
    protected boolean isMove = false;
    public void setMovable(boolean move) {
        isMove = move;
    }

    public void addFile(String name, String contx) {
        files.add(new File(name, contx));
    }

    public void move(ArrayList<Slope> slopes) {
        if (!isMove)
            return;
        double height = Math.max(MathsHelper.RADIUS_OF_JUPITER, this.height);

        double radians = linearSpeed / height;
        pos = direct == MathsHelper.ANTI_CLOCKWISE ? pos.add(Angle.fromRadians(radians)) : pos.subtract(Angle.fromRadians(radians));
        this.height = slopes.stream()
                .filter(slope -> slope.getStart() <= pos.toDegrees() && slope.getEnd() >= pos.toDegrees())
                .mapToDouble(slope -> slope.getHeight(pos.toDegrees()) + MathsHelper.RADIUS_OF_JUPITER)
                .findFirst()
                .orElse(this.height);
    }

    public Device(String type, String id, Angle pos) {
        super(type, MathsHelper.RADIUS_OF_JUPITER, pos, id);
        entityType = 0;
    }
}
