package dungeonmania.entities.enemies;

import dungeonmania.Game;

public interface MovingStrategy {
    public void move(Game game, Enemy e);
}
