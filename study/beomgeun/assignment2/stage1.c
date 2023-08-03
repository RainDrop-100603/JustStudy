// Program name
//
// This program was written by [your name] (z5555555)
// on [date]
//
// TODO: Description of program

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

enum land_type { GRASS, WATER, PATH_START, PATH_END, PATH_UP, PATH_RIGHT, PATH_DOWN, PATH_LEFT, TELEPORTER };

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

struct tile {
    enum land_type land;
    enum entity entity;

    int n_enemies;
};

int valid_point(int row, int column);
void add_lake(struct tile map[MAP_ROWS][MAP_COLUMNS], int startRow, int startCol, int height, int width);

void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);

int main(void) {
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    initialise_map(map);

    int lives, money;
    int startRow, startCol, endRow, endCol;

    printf("Starting Lives: ");
    scanf("%d", &lives);

    printf("Starting Money($): ");
    scanf("%d", &money);

    printf("Start Point: ");
    scanf("%d %d", &startRow, &startCol);

    printf("End Point: ");
    scanf("%d %d", &endRow, &endCol);

    map[startRow][startCol].land = PATH_START;
    map[endRow][endCol].land = PATH_END;

    print_map(map, lives, money);

    int initialEnemies;
    printf("Initial Enemies: ");
    scanf("%d", &initialEnemies);

    if (initialEnemies > 0) {
        map[startRow][startCol].entity = ENEMY;
        map[startRow][startCol].n_enemies = initialEnemies;
    }

    print_map(map, lives, money);

    int lakeRow, lakeCol, lakeHeight, lakeWidth;
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &lakeRow, &lakeCol, &lakeHeight, &lakeWidth);

    add_lake(map, lakeRow, lakeCol, lakeHeight, lakeWidth);

    print_map(map, lives, money);

    return 0;
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

void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

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
                printf(" ");
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
