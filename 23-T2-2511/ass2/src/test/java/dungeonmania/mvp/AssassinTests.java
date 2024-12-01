package dungeonmania.mvp;

import dungeonmania.DungeonManiaController;
import dungeonmania.exceptions.InvalidActionException;
import dungeonmania.response.models.DungeonResponse;
import dungeonmania.util.Direction;
import dungeonmania.util.Position;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

// Most parts of the tests are just copied from the Mercenary tests and change
// "mercenary" to "assassin".

public class AssassinTests {
    @Test
    @Tag("16-1")
    @DisplayName("Test assassin in line with Player moves towards them")
    public void moveTowards() {
        //                                  Wall    Wall   Wall    Wall    Wall    Wall
        // P1       P2      P3      P4      A4      A3      A2      A1      .      Wall
        //                                  Wall    Wall   Wall    Wall    Wall    Wall
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_towardsPlayer", "c_assTest_towardsPlayer");

        assertEquals(new Position(8, 1), getAssassinPos(res));
        res = dmc.tick(Direction.RIGHT);
        assertEquals(new Position(7, 1), getAssassinPos(res));
        res = dmc.tick(Direction.RIGHT);
        assertEquals(new Position(6, 1), getAssassinPos(res));
        res = dmc.tick(Direction.RIGHT);
        assertEquals(new Position(5, 1), getAssassinPos(res));
    }

    @Test
    @Tag("16-2")
    @DisplayName("Test assassin stops if they cannot move any closer to the player")
    public void stopMovement() {
        //                  Wall     Wall    Wall
        // P1       P2      Wall      M1     Wall
        //                  Wall     Wall    Wall
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_stopMovement", "c_assTest_stopMovement");

        Position startingPos = getAssassinPos(res);
        res = dmc.tick(Direction.RIGHT);
        assertEquals(startingPos, getAssassinPos(res));
    }

    @Test
    @Tag("16-3")
    @DisplayName("Test assassins can not move through closed doors")
    public void doorMovement() {
        //                  Wall     Door    Wall
        // P1       P2      Wall      M1     Wall
        // Key              Wall     Wall    Wall
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_doorMovement", "c_assTest_doorMovement");

        Position startingPos = getAssassinPos(res);
        res = dmc.tick(Direction.RIGHT);
        assertEquals(startingPos, getAssassinPos(res));
    }

    @Test
    @Tag("16-4")
    @DisplayName("Test assassin moves around a wall to get to the player")
    public void evadeWall() {
        //                  Wall      M2
        // P1       P2      Wall      M1
        //                  Wall      M2
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_evadeWall", "c_assTest_evadeWall");

        res = dmc.tick(Direction.RIGHT);
        assertTrue(new Position(4, 1).equals(getAssassinPos(res)) || new Position(4, 3).equals(getAssassinPos(res)));
    }

    @Test
    @Tag("16-5")
    @DisplayName("Testing an assassin can be bribed with a certain amount")
    public void bribeAmount() {
        //                                                          Wall     Wall     Wall    Wall    Wall
        // P1       P2/Treasure      P3/Treasure    P4/Treasure      M4       M3       M2     M1      Wall
        //                                                          Wall     Wall     Wall    Wall    Wall
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_bribeAmount", "c_assTest_bribeAmount");

        String assassinId = TestUtils.getEntitiesStream(res, "assassin").findFirst().get().getId();

        // pick up first treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(1, TestUtils.getInventory(res, "treasure").size());
        assertEquals(new Position(7, 1), getAssassinPos(res));

        // attempt bribe
        assertThrows(InvalidActionException.class, () -> dmc.interact(assassinId));
        assertEquals(1, TestUtils.getInventory(res, "treasure").size());

        // pick up second treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(2, TestUtils.getInventory(res, "treasure").size());
        assertEquals(new Position(6, 1), getAssassinPos(res));

        // attempt bribe
        assertThrows(InvalidActionException.class, () -> dmc.interact(assassinId));
        assertEquals(2, TestUtils.getInventory(res, "treasure").size());

        // pick up third treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(3, TestUtils.getInventory(res, "treasure").size());
        assertEquals(new Position(5, 1), getAssassinPos(res));

        // achieve bribe
        res = assertDoesNotThrow(() -> dmc.interact(assassinId));
        assertEquals(0, TestUtils.getInventory(res, "treasure").size());
    }

    @Test
    @Tag("16-6")
    @DisplayName("Testing an assassin can be bribed within a radius")
    public void bribeRadius() {
        //                                         Wall     Wall    Wall    Wall  Wall
        // P1       P2/Treasure      P3    P4      M4       M3       M2     M1    Wall
        //                                         Wall     Wall    Wall    Wall  Wall
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_bribeRadius", "c_assTest_bribeRadius");

        String assassinId = TestUtils.getEntitiesStream(res, "assassin").findFirst().get().getId();

        // pick up treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(1, TestUtils.getInventory(res, "treasure").size());
        assertEquals(new Position(7, 1), getAssassinPos(res));

        // attempt bribe
        assertDoesNotThrow(() -> dmc.interact(assassinId));
        assertEquals(1, TestUtils.getInventory(res, "treasure").size());
    }

    @Test
    @Tag("16-7")
    @DisplayName("Testing an allied assassin does not battle the player")
    public void allyBattle() {
        //                                  Wall    Wall    Wall
        // P1       P2/Treasure      .      M2      M1      Wall
        //                                  Wall    Wall    Wall
        DungeonManiaController dmc = new DungeonManiaController();
        DungeonResponse res = dmc.newGame("d_assTest_allyBattle", "c_assTest_allyBattle");

        String assassinId = TestUtils.getEntitiesStream(res, "assassin").findFirst().get().getId();

        // pick up treasure
        res = dmc.tick(Direction.RIGHT);
        assertEquals(1, TestUtils.getInventory(res, "treasure").size());

        // achieve bribe
        res = assertDoesNotThrow(() -> dmc.interact(assassinId));
        assertEquals(0, TestUtils.getInventory(res, "treasure").size());

        // walk into mercenary, a battle does not occur
        res = dmc.tick(Direction.RIGHT);
        assertEquals(0, res.getBattles().size());
    }

    private Position getAssassinPos(DungeonResponse res) {
        return TestUtils.getEntities(res, "assassin").get(0).getPosition();
    }

}
