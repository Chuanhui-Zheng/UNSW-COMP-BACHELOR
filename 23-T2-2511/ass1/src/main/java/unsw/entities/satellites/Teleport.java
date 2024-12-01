package unsw.entities.satellites;

import unsw.utils.Angle;
import unsw.utils.MathsHelper;

import java.util.Arrays;

public class Teleport extends Satellite {
    public void move() {
        Angle commonAngle = this.entityMove();
        Angle newPosition = direct == MathsHelper.ANTI_CLOCKWISE ? pos.add(commonAngle) : pos.subtract(commonAngle);
        pos = (newPosition.toDegrees() - 180) * (this.pos.toDegrees() - 180) <= 0 ? Angle.fromDegrees(0) : newPosition;
    }

    public Teleport(String id, String type, double height, Angle position) {
        super(type, id, position, height);
        this.linearSpeed = 1000;
        this.commTypeSupport.addAll(Arrays.asList("HandheldDevice", "LaptopDevice", "DesktopDevice"));
        this.commRange = 200000;
        this.byteMax = 200;
        this.fileMax = 200;
        this.recvSpeed = 15;
        this.sendSpeed = 10;
        this.direct = MathsHelper.ANTI_CLOCKWISE;
    }
}
