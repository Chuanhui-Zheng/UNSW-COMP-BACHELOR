package dungeonmania.entities.enemies;

import dungeonmania.Game;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

import dungeonmania.entities.collectables.potions.InvincibilityPotion;
import dungeonmania.map.GameMap;
import dungeonmania.util.Direction;
import dungeonmania.util.Position;

public class ZombieToastMove implements MovingStrategy {
    private Random randGen = new Random();

    @Override
    public void move(Game game, Enemy e) {
        Position nextPos;
        GameMap map = game.getMap();
        if (map.getPlayer().getEffectivePotion() instanceof InvincibilityPotion) {
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
            List<Position> pos = e.getPosition().getCardinallyAdjacentPositions();
            pos = pos.stream().filter(p -> map.canMoveTo(e, p)).collect(Collectors.toList());
            if (pos.size() == 0) {
                nextPos = e.getPosition();
            } else {
                nextPos = pos.get(randGen.nextInt(pos.size()));
            }
        }
        game.getMap().moveTo(e, nextPos);

    }

}
