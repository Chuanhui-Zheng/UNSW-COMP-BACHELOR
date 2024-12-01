package dungeonmania.entities.enemies;

import java.util.List;

import dungeonmania.Game;
import dungeonmania.entities.Entity;
import dungeonmania.util.Position;

public class Spider extends Enemy {
    private List<Position> movementTrajectory;
    private int nextPositionElement;
    private boolean forward;

    public static final int DEFAULT_SPAWN_RATE = 0;
    public static final double DEFAULT_ATTACK = 5;
    public static final double DEFAULT_HEALTH = 10;

    public Spider(Position position, double health, double attack) {
        super(position.asLayer(Entity.DOOR_LAYER + 1), health, attack);
        /**
         * Establish spider movement trajectory Spider moves as follows:
         *  8 1 2       10/12  1/9  2/8
         *  7 S 3       11     S    3/7
         *  6 5 4       B      5    4/6
         */
        movementTrajectory = position.getAdjacentPositions();
        nextPositionElement = 1;
        forward = true;
        setStrategy(new SpiderMove());
    };

    public void updateNextPosition() {
        if (forward) {
            nextPositionElement++;
            if (nextPositionElement == 8) {
                nextPositionElement = 0;
            }
        } else {
            nextPositionElement--;
            if (nextPositionElement == -1) {
                nextPositionElement = 7;
            }
        }
    }

    public void reverseDirection() {
        this.forward = !this.forward;
    }

    public List<Position> getMovementTrajectory() {
        return movementTrajectory;
    }

    public int getNextPositionElement() {
        return nextPositionElement;
    }

    public boolean isForward() {
        return forward;
    }

    @Override
    public void move(Game game) {
        getStrategy().move(game, this);
    }
}
