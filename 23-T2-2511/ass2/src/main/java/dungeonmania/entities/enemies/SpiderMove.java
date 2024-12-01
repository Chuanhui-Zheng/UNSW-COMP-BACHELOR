package dungeonmania.entities.enemies;

import java.util.List;

import dungeonmania.Game;
import dungeonmania.entities.Boulder;
import dungeonmania.entities.Entity;
import dungeonmania.util.Position;

public class SpiderMove implements MovingStrategy {
    public void move(Game game, Enemy e) {

        Spider s = (Spider) e;
        Position nextPos = s.getMovementTrajectory().get(s.getNextPositionElement());
        List<Entity> entities = game.getMap().getEntities(nextPos);
        if (entities != null && entities.size() > 0
                && entities.stream().anyMatch(entity -> entity instanceof Boulder)) {
            s.reverseDirection();
            s.updateNextPosition();
            s.updateNextPosition();
        }
        nextPos = s.getMovementTrajectory().get(s.getNextPositionElement());
        entities = game.getMap().getEntities(nextPos);
        if (entities == null || entities.size() == 0
                || entities.stream().allMatch(entity -> entity.canMoveOnto(game.getMap(), e))) {
            game.getMap().moveTo(e, nextPos);
            s.updateNextPosition();
        }
    }
}
