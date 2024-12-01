package unsw.entities.devices;

import unsw.utils.Angle;

import java.util.Arrays;
import java.util.HashSet;

public class Laptop extends Device{
	public Laptop(String type, String id, Angle pos) {
		super(type, id, pos);
		linearSpeed = 30;
		commRange = 100000;
		this.commTypeSupport = new HashSet<>(Arrays.asList("RelaySatellite", "StandardSatellite", "TeleportingSatellite"));
	}
}
