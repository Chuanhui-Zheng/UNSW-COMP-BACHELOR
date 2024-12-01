// Implementation of the Agent ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Agent.h"
#include "Map.h"

// This struct stores information about an individual agent and can be
// used to store information that the agent needs to remember.
struct agent {
    char *name;
    int startLocation;
    int location;
    int maxStamina; // max stamina
    int stamina;    // current stamina
    int strategy;
    Map map;
    int *cvn;
    // TODO: Add more fields here as needed
};

static Move chooseRandomMove(Agent agent, Map m);
static int filterRoads(Agent agent, Road roads[], int numRoads,
                       Road legalRoads[]);
static Move abc(Agent agent, Map m);
static Move dfs(Agent agent, Map m);
static Move abc(Agent agent, Map m){
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);

    // Filter out roads that the agent does not have enough stamina for
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

    Move move;
    if (numLegalRoads > 0) {
        // Sort the roads using insertion sort
        int min = 999999;
        int stamina = 999999;
        Road best;
        for (int i = 0; i < numLegalRoads; i++) {
            Road r = legalRoads[i];
            if (agent->cvn[r.to] < min) {
                min = agent->cvn[r.to];
                stamina = r.length;
                best = r;
            }
            else if(agent->cvn[r.to] == min && r.length < stamina){
                min = agent->cvn[r.to];
                stamina = r.length;
                best = r;
            }
        }

        move = (Move){best.to, best.length};
    } else {
        // The agent must stay in the same location
        move = (Move){agent->location, 0};
    }
    
    free(legalRoads);
    free(roads);
    return move;
}


/**
 * Creates a new agent
 */
Agent AgentNew(int start, int stamina, int strategy, Map m, char *name) {
    if (start >= MapNumCities(m)) {
        fprintf(stderr, "error: starting city (%d) is invalid\n", start);
        exit(EXIT_FAILURE);
    }
    
    Agent agent = malloc(sizeof(struct agent));
    if (agent == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    agent->startLocation = start;
    agent->location = start;
    agent->maxStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = m;
    agent->name = strdup(name);
    agent->cvn = malloc(MapNumCities(m)*sizeof(int));
    for (int i = 0; i < MapNumCities(m); i++){
        agent->cvn[i] = 0;
    }
    agent->cvn[agent->location]++;
    // TODO: You may need to add to this
    
    return agent;
}

/**
 * Frees all memory associated with the agent
 * NOTE: You should not free the map because the map is owned by the
 *       main program, and the main program will free it
 */
void AgentFree(Agent agent) {
    // TODO: You may need to update this to free any extra memory you use
    free(agent->name);
    free(agent->cvn);
    free(agent);
}

////////////////////////////////////////////////////////////////////////
// Making moves

/**
 * Calculates the agent's next move
 */
Move AgentGetNextMove(Agent agent, Map m) {
    switch (agent->strategy) {
        case STATIONARY: return (Move){agent->location, 0};
        case RANDOM:     return chooseRandomMove(agent, m);
        case CHEAPEST_LEAST_VISITED: return abc(agent, m);
        case DFS: return dfs(agent, m);
        // TODO: Implement more strategies here
        default:
            printf("error: strategy not implemented yet\n");
            exit(EXIT_FAILURE);
    }
}

static Move chooseRandomMove(Agent agent, Map m) {
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);

    // Filter out roads that the agent does not have enough stamina for
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

    Move move;
    if (numLegalRoads > 0) {
        // Sort the roads using insertion sort
        for (int i = 1; i < numLegalRoads; i++) {
            Road r = legalRoads[i];
            int j = i;
            while (j > 0 && r.to < legalRoads[j - 1].to) {
                legalRoads[j] = legalRoads[j - 1];
                j--;
            }
            legalRoads[j] = r;
        }
        
        // nextMove is randomly chosen from the legal roads
        int k = rand() % numLegalRoads;
        move = (Move){legalRoads[k].to, legalRoads[k].length};
    } else {
        // The agent must stay in the same location
        move = (Move){agent->location, 0};
    }
    
    free(legalRoads);
    free(roads);
    return move;
}

// Takes an array with all the possible roads and puts the ones the agent
// has enough stamina for into the legalRoads array
// Returns the number of legal roads
static int filterRoads(Agent agent, Road roads[], int numRoads,
                       Road legalRoads[]) {
    int numLegalRoads = 0;
    for (int i = 0; i < numRoads; i++) {
        if (roads[i].length <= agent->stamina) {
            legalRoads[numLegalRoads++] = roads[i];
        }
    }
    return numLegalRoads;
}

/**
 * Executes a given move by updating the agent's internal state
 */
void AgentMakeNextMove(Agent agent, Move move) {
    if (move.to == agent->location) {
        agent->stamina = agent->maxStamina;
    } else {
        agent->cvn[move.to]++;
        agent->stamina -= move.staminaCost;
    }
    agent->location = move.to;
    
    // TODO: You may need to add to this to handle different strategies
}

////////////////////////////////////////////////////////////////////////
// Gets information about the agent
// NOTE: It is expected that these functions do not need to be modified

/**
 * Gets the name of the agent
 */
char *AgentName(Agent agent) {
    return agent->name;
}

/**
 * Gets the current location of the agent
 */
int AgentLocation(Agent agent) {
    return agent->location;
}

/**
 * Gets the amount of stamina the agent currently has
 */
int AgentStamina(Agent agent) {
    return agent->stamina;
}

////////////////////////////////////////////////////////////////////////
// Learning information

/**
 * Tells the agent where the thief is
 */
void AgentGainInfo(Agent agent, int thiefLocation) {
    // TODO: Stage 3
}

////////////////////////////////////////////////////////////////////////
// Displaying state

/**
 * Prints information about the agent (for debugging purposes)
 */
void AgentShow(Agent agent) {
    // TODO: You can implement this function however you want
    //       You can leave this function blank if you want
}

////////////////////////////////////////////////////////////////////////

static Move dfs(Agent agent, Map m) {
    Road *cityroad = malloc(MapNumCities(m) * sizeof(Road));
    Road *adroad = malloc(MapNumCities(m) * sizeof(Road));

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, cityroad);

    // Get all roads have not been visited
    int numNextRoads = 0;
    for (int i = 0; i < numRoads; i++) {
        if (agent->cvn[cityroad[i].to] == 0) {
            adroad[numNextRoads] = cityroad[i];
            numNextRoads++;
        }
    }
    Move bestMove;
    if (numNextRoads == 0) {
        // find minimum id of roads
        int minId = 999999;
        int length = 999999;
        for (int i = 0; i < numRoads; i++) {
            if (cityroad[i].to < minId) {
                minId = cityroad[i].to;
                length = cityroad[i].length;
            }
        }
        bestMove = (Move){minId, length};
    } else {
        // find minimum id of roads
        int minId = 999999;
        int length = 999999;
        for (int i = 0; i < numNextRoads; i++) {
            if (adroad[i].to < minId) {
                minId = adroad[i].to;
                length = adroad[i].length;
            }
        }
        bestMove = (Move){minId, length};
    }
    free(cityroad);
    free(adroad);
    if (bestMove.staminaCost > agent->stamina) {
        bestMove = (Move){agent->location, 0};
    }
    return bestMove;
}