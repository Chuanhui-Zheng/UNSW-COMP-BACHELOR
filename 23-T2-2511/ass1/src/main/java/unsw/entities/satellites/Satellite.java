package unsw.entities.satellites;

import unsw.entities.Entity;
import unsw.utils.Angle;
import java.util.HashSet;
import java.util.Arrays;


public class Satellite extends Entity {
	public Satellite(String type, String id, Angle pos, double height) {
		super(type, height, pos, id);
		this.commTypeSupport = new HashSet<>(Arrays.asList("RelaySatellite", "StandardSatellite", "TeleportingSatellite"));
		this.entityType = 1;
	}
}
