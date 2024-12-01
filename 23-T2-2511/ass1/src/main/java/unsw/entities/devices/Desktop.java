package unsw.entities.devices;

import unsw.utils.Angle;

import java.util.Arrays;
import java.util.HashSet;

public class Desktop extends Device{
	public Desktop(String type, String id, Angle pos) {
		super(type, id, pos);
		commRange = 200000;
		linearSpeed= 20;
		commTypeSupport = new HashSet<>(Arrays.asList("RelaySatellite",  "TeleportingSatellite"));
	}
}
