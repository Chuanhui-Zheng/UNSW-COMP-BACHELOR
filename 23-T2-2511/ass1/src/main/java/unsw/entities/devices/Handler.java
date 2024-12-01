package unsw.entities.devices;

import unsw.utils.Angle;
import java.util.Arrays;
import java.util.HashSet;


public class Handler extends Device{
	public Handler(String type, String id, Angle pos) {
		super(type, id, pos);
		linearSpeed = 50;
		commRange = 50000;
		commTypeSupport = new HashSet<>(Arrays.asList("RelaySatellite", "StandardSatellite", "TeleportingSatellite"));
	}
}
