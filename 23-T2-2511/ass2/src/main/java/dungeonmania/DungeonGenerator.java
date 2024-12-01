package dungeonmania;

import java.util.ArrayList;
import java.util.Random;

import org.json.JSONArray;
import org.json.JSONObject;

public class DungeonGenerator {
    private static boolean validPos(int x, int y, int width, int height) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    private static ArrayList<int[]> getAdjacentWalls(int x, int y, boolean[][] walls) {
        ArrayList<int[]> adjWalls = new ArrayList<>();
        int[][] directions = {
                {
                        1, 0
                }, {
                        -1, 0
                }, {
                        0, 1
                }, {
                        0, -1
                }
        };

        for (int[] dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (validPos(newX, newY, walls[0].length, walls.length) && walls[newY][newX]) {
                adjWalls.add(new int[] {
                        newX, newY
                });
            }
        }

        return adjWalls;
    }

    public static JSONObject generate(int xStart, int yStart, int xEnd, int yEnd) {

        JSONObject dungeon = new JSONObject();
        JSONArray entities = new JSONArray();

        // placing player
        JSONObject player = new JSONObject();
        player.put("type", "player");
        player.put("x", xStart);
        player.put("y", yStart);
        entities.put(player);

        // placing exit
        JSONObject exit = new JSONObject();
        exit.put("type", "exit");
        exit.put("x", xEnd);
        exit.put("y", yEnd);
        entities.put(exit);

        // adding wall border around player and exit
        for (int i = Math.min(xStart, xEnd); i <= Math.max(xStart, xEnd); i++) {
            JSONObject border = new JSONObject();
            border.put("type", "wall");
            border.put("x", i);
            border.put("y", Math.max(yStart, yEnd) + 1);
            entities.put(border);
        }
        for (int i = Math.min(xStart, xEnd); i <= Math.max(xStart, xEnd); i++) {
            JSONObject border = new JSONObject();
            border.put("type", "wall");
            border.put("x", i);
            border.put("y", Math.min(yStart, yEnd) - 1);
            entities.put(border);
        }
        for (int i = Math.min(yStart, yEnd) - 1; i <= Math.max(yStart, yEnd) + 1; i++) {
            JSONObject border = new JSONObject();
            border.put("type", "wall");
            border.put("x", Math.min(xStart, xEnd) - 1);
            border.put("y", i);
            entities.put(border);
        }
        for (int i = Math.min(yStart, yEnd) - 1; i <= Math.max(yStart, yEnd) + 1; i++) {
            JSONObject border = new JSONObject();
            border.put("type", "wall");
            border.put("x", Math.max(xStart, xEnd) + 1);
            border.put("y", i);
            entities.put(border);
        }

        // generating maze walls
        int height = Math.abs(yStart - yEnd) + 1;
        int width = Math.abs(xStart - xEnd) + 1;

        boolean[][] walls = new boolean[height][width];
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                walls[row][col] = true;
            }
        }

        Random rand = new Random();
        int startX = 0;
        int startY = 0;

        walls[startY][startX] = false;

        ArrayList<int[]> queue = new ArrayList<>();
        queue.add(new int[] {
                startX, startY
        });

        while (!queue.isEmpty()) {
            int[] pos = queue.remove(rand.nextInt(queue.size()));
            int x = pos[0];
            int y = pos[1];

            ArrayList<int[]> wallNeighbours = getAdjacentWalls(x, y, walls);

            if (!wallNeighbours.isEmpty()) {
                int[] wallNeighbour = wallNeighbours.get(rand.nextInt(wallNeighbours.size()));
                int wallX = wallNeighbour[0];
                int wallY = wallNeighbour[1];

                int connectX = (x + wallX) / 2;
                int connectY = (y + wallY) / 2;
                walls[connectY][connectX] = false;

                queue.add(new int[] {
                        wallX, wallY
                });

                ArrayList<int[]> wallNeighboursOfNeighbour = getAdjacentWalls(wallX, wallY, walls);
                queue.addAll(wallNeighboursOfNeighbour);
            }

            boolean isConnected = false;
            int[][] directions = {
                    {
                            -1, 0
                    }, {
                            1, 0
                    }, {
                            0, -1
                    }, {
                            0, 1
                    }
            };
            for (int[] dir : directions) {
                x = xEnd + dir[0];
                y = yEnd + dir[1];
                if (validPos(x, y, width, height) && !walls[y][x]) {
                    isConnected = true;
                }
            }
            if (isConnected) {
                break;
            }

        }

        // placing maze walls
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int x = Math.min(xStart, xEnd) + col;
                int y = Math.min(yStart, yEnd) + row;

                if (walls[row][col] && !(x == xStart && y == yStart) && !(x == xEnd && y == yEnd)) {
                    JSONObject wall = new JSONObject();
                    wall.put("type", "wall");
                    wall.put("x", x);
                    wall.put("y", y);
                    entities.put(wall);
                }
            }
        }

        dungeon.put("entities", entities);

        // adding exit goal
        JSONObject goalCondition = new JSONObject();
        goalCondition.put("goal", "exit");
        dungeon.put("goal-condition", goalCondition);

        return dungeon;
    }
}
