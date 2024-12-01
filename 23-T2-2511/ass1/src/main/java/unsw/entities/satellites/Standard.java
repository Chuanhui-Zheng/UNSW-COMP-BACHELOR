package unsw.entities.satellites;

import unsw.utils.Angle;
import unsw.utils.MathsHelper;

import java.util.Arrays;

public class Standard extends Satellite {
    public void move() {
        pos = direct == MathsHelper.ANTI_CLOCKWISE ? pos.add(entityMove()) : pos.subtract(entityMove());
    }
    public Standard(String type, String id, Angle position, double height) {
        super(type, id, position, height);
        this.commTypeSupport.addAll(Arrays.asList("HandheldDevice", "LaptopDevice"));
        this.linearSpeed = 2500;
        this.fileMax = 3;
        this.recvSpeed = 1;
        this.sendSpeed = 1;
        this.commRange = 150000;
        this.byteMax = 80;
    }
}
