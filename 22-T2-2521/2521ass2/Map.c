// Implementation of the Map ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"

struct map { 
    // TODO
    Road *allroad;
    int cityamount;
    int roadamount;
    char **citysname;
};

/**
 * Creates a new map with the given number of cities
 * Assumes that numCities is positive
 */
Map MapNew(int numCities) {
    Map newmap = malloc(sizeof(struct map));
    int cityamount = numCities;
    Road *road = malloc(cityamount*(cityamount-1)*sizeof(Road));
    newmap->allroad = road;
    newmap->cityamount = numCities;
    newmap->roadamount = 0;
    char **citysname = malloc(cityamount * sizeof(char*));
    newmap->citysname = citysname;
    return newmap;
}

/**
 * Frees all memory associated with the given map
 */
void MapFree(Map m) {
    // TODO
    for (int i = 0; i < m->cityamount; i++){
        free(m->citysname[i]);
    }
    free(m->citysname);
    free(m->allroad);
    free(m);
}

/**
 * Returns the number of cities on the given map
 */
int MapNumCities(Map m) {
    // TODO
    return m->cityamount;
}

/**
 * Returns the number of roads on the given map
 */
int MapNumRoads(Map m) {
    // TODO
    return m->roadamount;
}

/**
 * Inserts a road between two cities with the given length
 * Does nothing if there is already a road between the two cities
 * Assumes that the cities are valid and are not the same
 * Assumes that the length of the road is positive
 */
void MapInsertRoad(Map m, int city1, int city2, int length) {
    // TODO
    int now = m->roadamount;
    m->allroad[now]= (Road) {city1, city2, length};
    now++;
    m->allroad[now] =(Road) {city2, city1, length};
    now++;
    m->roadamount = now;
}

/**
 * Sets the name of the given city
 */
void MapSetName(Map m, int city, char *name) {
    // TODO
    m->citysname[city] = (char*)malloc(strlen(name) + 1);
    strcpy(m->citysname[city], name);

}

/*
 * Returns the name of the given city
 */
char *MapGetName(Map m, int city) {
    // TODO
    if (m->citysname[city] == NULL){
        return "unnamed";
    }
    else{
        return m->citysname[city];
    }
}

/**
 * Checks if there is a road between the two given cities
 * Returns the length of the road if there is a road, and 0 otherwise
 */
int MapContainsRoad(Map m, int city1, int city2) {
    // TODO
    int length = 0;
    for (int i = 0; i < m->roadamount; i++){
        if (m->allroad[i].from == city1){
            if (m->allroad[i].to == city2){
                length = m->allroad[i].length;
            }
        }
    }
    return length;
}

/**
 * Returns the number of roads connected to the given city and stores
 * them in the given roads array. The `from` field should be equal to
 * `city` for all the roads in the array.
 * Assumes that the roads array is large enough to store all the roads
 */
int MapGetRoadsFrom(Map m, int city, Road roads[]) {
    // TODO
    int fromroad = 0;
    for (int j = 0; j < m->roadamount; j++){
        if (m->allroad[j].from == city){
            roads[fromroad] = m->allroad[j];
            fromroad++;
        }
    }
    return fromroad;
}

/**
 * Displays the map
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * This function will work once the other functions are working
 */
void MapShow(Map m) {
    printf("Number of cities: %d\n", MapNumCities(m));
    printf("Number of roads: %d\n", MapNumRoads(m));
    
    Road *roads = malloc(MapNumRoads(m) * sizeof(Road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);    
    }
    
    for (int i = 0; i < MapNumCities(m); i++) {
        printf("[%d] %s has roads to:", i, MapGetName(m, i));
        int numRoads = MapGetRoadsFrom(m, i, roads);
        for (int j = 0; j < numRoads; j++) {
            if (j > 0) {
                printf(",");
            }
            printf(" [%d] %s (%d)", roads[j].to, MapGetName(m, roads[j].to),
                   roads[j].length);
        }
        printf("\n");
    }
    
    free(roads);
}

