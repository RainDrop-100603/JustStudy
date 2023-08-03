// Program name
//
// This program was written by [your name] (z5555555)
// on [date]
//
// This program is a game in which the user controls a map with various entities
// and tiles. The user can define the start and end points, the number of enemies,
// and the position of a lake in the map.

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Defined types for various land types and entities in the game.
enum land_type { GRASS, WATER, PATH_START, PATH_END, PATH_UP, PATH_RIGHT, PATH_DOWN, PATH_LEFT, TELEPORTER };

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

// Structure defining the tile of the map.
struct tile {
    enum land_type land;
    enum entity entity;
    int n_enemies;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Function prototypes.

// stage 1.1
void stage1_1(struct tile map[MAP_ROWS][MAP_COLUMNS], int* lives, int* money, int* startRow, int* startCol, int* endRow, int* endCol);

// stage 2.2
void stage2_2(struct tile map[MAP_ROWS][MAP_COLUMNS], int* initialEnemies, int startRow, int startCol);

// Validates if a given point is within map boundaries.
// Returns 1 if valid, 0 otherwise.
int valid_point(int row, int column);

// Adds a lake to the map at the specified location.
void add_lake(struct tile map[MAP_ROWS][MAP_COLUMNS], int startRow, int startCol, int height, int width);

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Initializes all the tiles of the map to GRASS and EMPTY.
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);

// Prints the map along with the lives and money.
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);

// Prints a tile based on its land and entity values.
void print_tile(struct tile tile, int entity_print);

// Main function of the program.
int main(void) {
    // This `map` variable is a 2D array of `struct tile`s.
    // It is `MAP_ROWS` x `MAP_COLUMNS` in size (which is 6x12 for this
    // assignment!)
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    // This will initialise all tiles in the map to have GRASS land and EMPTY
    // entity values.
    initialise_map(map);

    // TODO: Start writing code here!

    // TODO: Stage 1.1 - Scan in lives, money and start/ending points, then
    // print out the map!
    int lives, money;
    int startRow, startCol, endRow, endCol;
    stage1_1(map, &lives, &money, &startRow, &startCol, &endRow, &endCol);
    print_map(map, lives, money);

    // TODO: Stage 1.2 - Scan in the initial enemies. Make sure you change the
    // `entity` at the starting position to be ENEMY, and that you update the
    // `n_enemies` value at that position to be this scanned value!

    int initialEnemies;
    stage2_2(map, &initialEnemies, startRow, startCol);
    print_map(map, lives, money);

    int lakeRow, lakeCol, lakeHeight, lakeWidth;
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &lakeRow, &lakeCol, &lakeHeight, &lakeWidth);

    add_lake(map, lakeRow, lakeCol, lakeHeight, lakeWidth);

    print_map(map, lives, money);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void stage1_1(struct tile map[MAP_ROWS][MAP_COLUMNS], int* lives, int* money, int* startRow, int* startCol, int* endRow, int* endCol) {
    printf("Starting Lives: ");
    scanf("%d", lives);

    printf("Starting Money($): ");
    scanf("%d", money);

    printf("Start Point: ");
    scanf("%d %d", startRow, startCol);

    printf("End Point: ");
    scanf("%d %d", endRow, endCol);

    map[*startRow][*startCol].land = PATH_START;
    map[*endRow][*endCol].land = PATH_END;
}

void stage2_2(struct tile map[MAP_ROWS][MAP_COLUMNS], int* initialEnemies, int startRow, int startCol) {
    printf("Initial Enemies: ");
    scanf("%d", initialEnemies);

    if (initialEnemies > 0) {
        map[startRow][startCol].entity = ENEMY;
        map[startRow][startCol].n_enemies = *initialEnemies;
    }
}

int valid_point(int row, int column) { return row >= 0 && row < MAP_ROWS && column >= 0 && column < MAP_COLUMNS; }

void add_lake(struct tile map[MAP_ROWS][MAP_COLUMNS], int startRow, int startCol, int height, int width) {
    if (!valid_point(startRow + height - 1, startCol + width - 1)) {
        printf("Error: Lake out of bounds, ignoring...\n");
        return;
    }

    for (int row = startRow; row < startRow + height; ++row) {
        for (int col = startCol; col < startCol + width; ++col) {
            map[row][col].land = WATER;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialises map tiles to contain GRASS land and EMPTY entity.
 *
 * Parameters:
 *     map - The map to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}
/**
 * Prints all map tiles based on their value, with a header displaying lives
 * and money.
 *
 * Parameters:
 *     map   - The map to print tiles from.
 *     lives - The number of lives to print with the map.
 *     money - The amount of money to print with the map.
 * Returns:
 *     Nothing.
 */
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}
/**
 * Prints either the land or entity component of a single tile, based on
 * the `land_print` parameter;
 *
 * Parameters:
 *     tile         - The tile to print the land/entity from
 *     land_print - Whether to print the land part of the tile or the entity
 *         part of the tile. If this value is 0, it prints the land, otherwise
 *         it prints the entity.
 * Returns:
 *     Nothing.
 */
void print_tile(struct tile tile, int entity_print) {
    if (entity_print) {
        switch (tile.land) {
            case GRASS:
                printf(" . ");
                break;
            case WATER:
                printf(" ~ ");
                break;
            case PATH_START:
                printf(" S ");
                break;
            case PATH_END:
                printf(" E ");
                break;
            case PATH_UP:
                printf(" ^ ");
                break;
            case PATH_RIGHT:
                printf(" > ");
                break;
            case PATH_DOWN:
                printf(" v ");
                break;
            case PATH_LEFT:
                printf(" < ");
                break;
            case TELEPORTER:
                printf("( )");
                break;
            default:
                printf(" ? ");
                break;
        }
    } else {
        switch (tile.entity) {
            case EMPTY:
                printf("   ");
                break;
            case ENEMY:
                printf("%03d", tile.n_enemies);
                break;
            case BASIC_TOWER:
                printf("[B]");
                break;
            case POWER_TOWER:
                printf("[P]");
                break;
            case FORTIFIED_TOWER:
                printf("[F]");
                break;
            default:
                printf(" ? ");
                break;
        }
    }
}
