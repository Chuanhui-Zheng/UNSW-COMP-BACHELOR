package dungeonmania.mvp;

import dungeonmania.DungeonManiaController;
import dungeonmania.response.models.DungeonResponse;
import dungeonmania.util.Direction;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class BasicGoalsTest {
    @Test
    @Tag("13-1")
    @DisplayName("Test achieving a basic exit goal")
    public void exit() {
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_exit", "c_basicGoalsTest_exit");

        // move player to right
        res = dmc.tick(Direction.RIGHT);

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":exit"));

        // move player to exit
        res = dmc.tick(Direction.RIGHT);

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));
    }

    @Test
    @Tag("13-2")
    @DisplayName("Test achieving a basic boulders goal")
    public void oneSwitch() {
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_oneSwitch", "c_basicGoalsTest_oneSwitch");

        // move player to right
        res = dmc.tick(Direction.RIGHT);

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":boulders"));

        // move boulder onto switch
        res = dmc.tick(Direction.RIGHT);

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));
    }

    @Test
    @Tag("13-3")
    @DisplayName("Test achieving a boulders goal where there are five switches")
    public void fiveSwitches() {
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_fiveSwitches", "c_basicGoalsTest_fiveSwitches");

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":boulders"));

        // move first four boulders onto switch
        res = dmc.tick(Direction.DOWN);
        res = dmc.tick(Direction.UP);
        res = dmc.tick(Direction.RIGHT);
        res = dmc.tick(Direction.DOWN);
        res = dmc.tick(Direction.UP);
        res = dmc.tick(Direction.RIGHT);
        res = dmc.tick(Direction.DOWN);
        res = dmc.tick(Direction.UP);
        res = dmc.tick(Direction.RIGHT);
        res = dmc.tick(Direction.DOWN);
        res = dmc.tick(Direction.UP);
        res = dmc.tick(Direction.RIGHT);

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":boulders"));

        // move last boulder onto switch
        res = dmc.tick(Direction.DOWN);

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));
    }

    @Test
    @Tag("13-4")
    @DisplayName("Test achieving a basic treasure goal")
    public void treasure() {
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_treasure", "c_basicGoalsTest_treasure");

        // move player to right
        res = dmc.tick(Direction.RIGHT);

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":treasure"));

        // collect treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(1, TestUtils.getInventory(res, "treasure").size());

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":treasure"));

        // collect treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(2, TestUtils.getInventory(res, "treasure").size());

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":treasure"));

        // collect treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(3, TestUtils.getInventory(res, "treasure").size());

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));
    }

    @Test
    @Tag("13-5")
    @DisplayName("Test achieving a basic destroy n enemies goal")
    public void destroyEnemies() {
        // PLA
        // MER
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_destroyEnemies", "c_basicGoalsTest_destroyEnemies");

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":enemies"));

        // move player down, killing mercenary
        res = dmc.tick(Direction.DOWN);

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));
    }

    @Test
    @Tag("13-6")
    @DisplayName("Test achieving an enemies goal with multiple of different types")
    public void destroyManyEnemies() {
        //       PLA
        // BLD  MER   BLD
        // BLD  ZT    BLD
        // BLD  SPI   BLD
        //      BLD
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_destroyManyEnemies", "c_basicGoalsTest_destroyManyEnemies");

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":enemies"));

        // move player down thrice, killing mercenary, zombie toast, and spider
        res = dmc.tick(Direction.DOWN);
        res = dmc.tick(Direction.DOWN);
        res = dmc.tick(Direction.DOWN);

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));
    }

    @Test
    @Tag("13-7")
    @DisplayName("Test achieving a basic destroy spawners goal")
    public void destroySpawners() {
        //  PLA  ZTS
        //  SWD
        DungeonManiaController dmc;
        dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_basicGoalsTest_destroySpawners", "c_basicGoalsTest_destroySpawners");

        // assert goal not met
        assertTrue(TestUtils.getGoals(res).contains(":spawners"));

        // pick up sword
        res = dmc.tick(Direction.DOWN);
        // move right
        res = dmc.tick(Direction.RIGHT);
        // destroy spawner
        String spawnerId = TestUtils.getEntities(res, "zombie_toast_spawner").get(0).getId();
        res = assertDoesNotThrow(() -> dmc.interact(spawnerId));

        // assert goal met
        assertEquals("", TestUtils.getGoals(res));

    }
}
