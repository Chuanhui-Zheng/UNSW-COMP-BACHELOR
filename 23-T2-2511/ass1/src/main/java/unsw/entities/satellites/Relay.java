package unsw.entities.satellites;

import java.util.Arrays;
import unsw.utils.MathsHelper;
import unsw.utils.Angle;

public class Relay extends Satellite {
    public Relay(String type, String id, Angle pos, double height) {
        super(type, id, pos, height);
        this.linearSpeed = 1500;
        this.commRange = 300000;
        this.commTypeSupport.addAll(Arrays.asList("HandheldDevice", "LaptopDevice", "DesktopDevice"));
    }

    public void move() {
        if (pos.toDegrees() >= 190 && pos.toDegrees() <= 345) {
            this.direct = MathsHelper.CLOCKWISE;
        }
        if (pos.toDegrees() <= 140 || pos.toDegrees() >= 345) {
            this.direct = MathsHelper.ANTI_CLOCKWISE;
        }

        Angle angle = entityMove();
        pos = this.direct == MathsHelper.ANTI_CLOCKWISE ? pos.add(angle) : pos.subtract(angle);
        this.updateAngle();
    }
}
