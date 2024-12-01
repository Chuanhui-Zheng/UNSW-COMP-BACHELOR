package dungeonmania.entities.enemies;

import dungeonmania.Game;
import dungeonmania.entities.Player;
import dungeonmania.util.Position;

import java.util.Random;

public class Assassin extends Mercenary {
    public static final double BRIBE_FAIL_PROB = 0.5;
    public static final double DEFAULT_ASSASSIN_ATTACK = 10.0;

    private boolean isAdjacentToPlayer = false;

    private Random random = new Random();
    private double bribeFailRate = Assassin.BRIBE_FAIL_PROB;

    public Assassin(Position position, double health, double attack, int bribeAmount, int bribeRadius,
            double allyAttack, double allyDefence, double bribeFailRate) {
        super(position, health, attack, bribeAmount, bribeRadius, allyAttack, allyDefence);
        this.bribeFailRate = bribeFailRate;
    }

    @Override
    public void interact(Player player, Game game) {
        bribe(player);
        if (random.nextDouble() >= bribeFailRate) {
            setAllied(true);
            if (!isAdjacentToPlayer && Position.isAdjacent(player.getPosition(), getPosition()))
                isAdjacentToPlayer = true;
        }
    }

}
