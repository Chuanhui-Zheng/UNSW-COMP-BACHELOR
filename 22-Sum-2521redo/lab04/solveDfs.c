// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

static void printRoad(Maze m, Cell start,
                      Cell end, Cell **predcessor);
static bool useCell(Maze m, Cell w);

bool solve(Maze m) {
    int height = MazeHeight(m);
    int width = MazeWidth(m);
    //create visited array
    bool **visited = createBoolMatrix(height, width);
    //create predecessor array
    Cell **predcessor = createCellMatrix(height, width);
    Stack s = StackNew();
    Cell start = MazeGetStart(m);
    bool is_found = false;
    StackPush(s, start);
    while (!is_found && !StackIsEmpty(s)) {
        Cell v = StackPop(s);
        if (visited[v.row][v.col]) {
            continue;
        }
        visited[v.row][v.col] = true;
        if (MazeVisit(m, v)) {
            printRoad(m, start, v, predcessor);
            is_found = true;
            break;
        }

        Cell edges[4] = {
            {.row = v.row - 1, .col = v.col}, //up
            {.row = v.row, .col = v.col + 1}, //right
            {.row = v.row + 1, .col = v.col}, //down
            {.row = v.row, .col = v.col - 1}, //left
        };
        for (int i = 0; i < 4; i++) {
            Cell w = edges[i];
            if (useCell(m, w) && !MazeIsWall(m, w) && !visited[w.row][w.col]) {
                StackPush(s, w);
                predcessor[w.row][w.col] = v;
            }
        }
    }
    StackFree(s);
    freeBoolMatrix(visited);
    freeCellMatrix(predcessor);
    return is_found;
}

static void printRoad(Maze m, Cell start,
                      Cell end, Cell **predcessor) {
    Cell current = end;
    while (!(current.col == start.col
             && current.row == start.row)) {
        MazeMarkPath(m, current);
        current = predcessor[current.row][current.col];
    }
    //print the start point;
    MazeMarkPath(m, start);
}

static bool useCell(Maze m, Cell w) {
    return(w.row >=0 && w.row < MazeHeight(m)
        && w.col >= 0 && w.col < MazeWidth(m));
}

