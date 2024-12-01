package dungeonmania.entities.enemies;

import dungeonmania.battles.BattleStatistics;
import dungeonmania.util.Position;

public class Hydra extends ZombieToast {
    public static final double RECOVER_RATE = 0.5;
    public static final double RECOVER_AMOUNT = 1.0;
    public static final double DEFAULT_HYDRA_DEFENCE = 0;
    private double recoverRate = RECOVER_RATE;
    private double recoverAmount = RECOVER_AMOUNT;
    private BattleStatistics battlestatistics;

    public Hydra(Position position, double health, double attack, double recoverRate, double recoverAmount) {
        super(position, health, attack);
        this.recoverAmount = recoverAmount;
        this.recoverRate = recoverRate;
        battlestatistics = new BattleStatistics(health, attack, BattleStatistics.DEFAULT_ENEMY_DEFENCE,
                BattleStatistics.DEFAULT_DAMAGE_MAGNIFIER, BattleStatistics.DEFAULT_ENEMY_DAMAGE_REDUCER, recoverRate,
                recoverAmount);
    }

    public BattleStatistics getBattleStatistics() {
        return battlestatistics;
    }

    public double getRecoverRate() {
        return recoverRate;
    }

    public double getRecoverAmount() {
        return recoverAmount;
    }

}
