package dungeonmania.entities.collectables;

import dungeonmania.entities.Entity;
import dungeonmania.entities.Player;
import dungeonmania.entities.inventory.InventoryItem;
import dungeonmania.map.GameMap;
import dungeonmania.util.Position;

public class CollectonOverlap extends Entity implements InventoryItem {
    public CollectonOverlap(Position position) {
        super(position);
    }

    public boolean isCollectable() {
        return true;
    }

    public void onPickUp(GameMap map) {
        map.removeNode(this);
    }

    @Override
    public void onOverlap(GameMap map, Entity entity) {
        if (entity instanceof Player) {
            if (!((Player) entity).pickUp(this))
                return;
            map.destroyEntity(this);
        }
    }
}
