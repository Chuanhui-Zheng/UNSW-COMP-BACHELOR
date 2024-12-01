package dungeonmania.mvp;

import dungeonmania.DungeonManiaController;
import dungeonmania.response.models.DungeonResponse;
import dungeonmania.util.Direction;
import dungeonmania.util.Position;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

public class SunStoneTest {
    @Test
    @Tag("15-1")
    @DisplayName("Test sunstone open door")
    public void testSunStone() {
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = startNewGame(dmc, "d_sunStoneTest", "c_DoorsKeysTest_useKeyWalkThroughOpenDoor");

        res = tickAndAssertInventory(dmc, Direction.RIGHT, "sun_stone", 1);
        Position pos = getPlayerPosition(res);

        res = tickAndAssertInventory(dmc, Direction.RIGHT, "sun_stone", 1);
        assertNotEquals(pos, getPlayerPosition(res));
    }

    private DungeonResponse startNewGame(DungeonManiaController dmc, String dungeonId, String characterId) {
        return dmc.newGame(dungeonId, characterId);
    }

    private DungeonResponse tickAndAssertInventory(DungeonManiaController dmc, Direction direction, String item,
            int expectedSize) {
        DungeonResponse res = dmc.tick(direction);
        assertEquals(expectedSize, TestUtils.getInventory(res, item).size());
        return res;
    }

    private Position getPlayerPosition(DungeonResponse res) {
        return TestUtils.getEntities(res, "player").get(0).getPosition();
    }

    @Test
    @Tag("15-2")
    @DisplayName("Test sunstone mutliple doors")
    public void testSunStone2Door() {
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_sunStoneTest", "c_DoorsKeysTest_useKeyWalkThroughOpenDoor");

        res = dmc.tick(Direction.RIGHT);
        assertEquals(1, TestUtils.getInventory(res, "sun_stone").size());

        res = dmc.tick(Direction.RIGHT);
        assertEquals(1, TestUtils.getInventory(res, "sun_stone").size());
        assertEquals(new Position(3, 1), getPlayerPos(res));

        res = dmc.tick(Direction.DOWN);
        assertEquals(1, TestUtils.getInventory(res, "sun_stone").size());
        assertEquals(new Position(3, 2), getPlayerPos(res));
    }

    private Position getPlayerPos(DungeonResponse res) {
        return TestUtils.getEntities(res, "player").get(0).getPosition();
    }
}
