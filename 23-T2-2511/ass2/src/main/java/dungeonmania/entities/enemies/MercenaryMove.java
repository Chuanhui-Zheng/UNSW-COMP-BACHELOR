package dungeonmania.entities.enemies;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

import dungeonmania.Game;
import dungeonmania.entities.Player;
import dungeonmania.entities.collectables.potions.InvincibilityPotion;
import dungeonmania.entities.collectables.potions.InvisibilityPotion;
import dungeonmania.map.GameMap;
import dungeonmania.util.Direction;
import dungeonmania.util.Position;

public class MercenaryMove implements MovingStrategy {
    private boolean allied = false;
    private boolean isAdjacentToPlayer = false;

    public MercenaryMove(boolean allied) {
        this.allied = allied;
    }

    @Override
    public void move(Game game, Enemy e) {
        Position nextPos;
        GameMap map = game.getMap();
        Player player = game.getPlayer();
        if (allied) {
            if (!isAdjacentToPlayer && Position.isAdjacent(player.getPosition(), e.getPosition()))
                isAdjacentToPlayer = true;
            nextPos = isAdjacentToPlayer ? player.getPreviousDistinctPosition()
                    : map.dijkstraPathFind(e.getPosition(), player.getPosition(), e);
            if (!isAdjacentToPlayer && Position.isAdjacent(player.getPosition(), nextPos))
                isAdjacentToPlayer = true;
        } else if (map.getPlayer().getEffectivePotion() instanceof InvisibilityPotion) {
            // Move random
            Random randGen = new Random();
            List<Position> pos = e.getPosition().getCardinallyAdjacentPositions();
            pos = pos.stream().filter(p -> map.canMoveTo(e, p)).collect(Collectors.toList());
            if (pos.size() == 0) {
                nextPos = e.getPosition();
                map.moveTo(e, nextPos);
            } else {
                nextPos = pos.get(randGen.nextInt(pos.size()));
                map.moveTo(e, nextPos);
            }
        } else if (map.getPlayer().getEffectivePotion() instanceof InvincibilityPotion) {
            Position plrDiff = Position.calculatePositionBetween(map.getPlayer().getPosition(), e.getPosition());

            Position moveX = (plrDiff.getX() >= 0) ? Position.translateBy(e.getPosition(), Direction.RIGHT)
                    : Position.translateBy(e.getPosition(), Direction.LEFT);
            Position moveY = (plrDiff.getY() >= 0) ? Position.translateBy(e.getPosition(), Direction.UP)
                    : Position.translateBy(e.getPosition(), Direction.DOWN);
            Position offset = e.getPosition();
            if (plrDiff.getY() == 0 && map.canMoveTo(e, moveX))
                offset = moveX;
            else if (plrDiff.getX() == 0 && map.canMoveTo(e, moveY))
                offset = moveY;
            else if (Math.abs(plrDiff.getX()) >= Math.abs(plrDiff.getY())) {
                if (map.canMoveTo(e, moveX))
                    offset = moveX;
                else if (map.canMoveTo(e, moveY))
                    offset = moveY;
                else
                    offset = e.getPosition();
            } else {
                if (map.canMoveTo(e, moveY))
                    offset = moveY;
                else if (map.canMoveTo(e, moveX))
                    offset = moveX;
                else
                    offset = e.getPosition();
            }
            nextPos = offset;
        } else {
            // Follow hostile
            nextPos = map.dijkstraPathFind(e.getPosition(), player.getPosition(), e);
        }
        map.moveTo(e, nextPos);
    }
}
