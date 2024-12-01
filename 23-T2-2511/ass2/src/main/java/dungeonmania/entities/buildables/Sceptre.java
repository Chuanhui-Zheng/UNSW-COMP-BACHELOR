package dungeonmania.entities.buildables;

import dungeonmania.Game;
import dungeonmania.battles.BattleStatistics;

public class Sceptre extends Buildable {
    private int duration;

    public Sceptre(int mcduration) {
        super(null);
        this.duration = mcduration;
    }

    @Override
    public BattleStatistics applyBuff(BattleStatistics origin) {
        return BattleStatistics.applyBuff(origin, new BattleStatistics(0, 0, 0, 1, 1));
    }

    @Override
    public void use(Game game) {

    }

    @Override
    public int getDurability() {
        return 0;
    }

    public int getDuration() {
        return duration;
    }
}
