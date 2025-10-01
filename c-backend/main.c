// // 
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// #define GRID_SIZE 5
// #define MAX_ZOMBIES 5

// typedef struct {
//     int x, y;
//     int health;
//     int score;
// } Player;

// typedef struct {
//     int x, y;
//     int health;
//     int alive;
// } Zombie;

// // Initialize player in the center with full health and zero score
// void initPlayer(Player *p) {
//     p->x = GRID_SIZE / 2;
//     p->y = GRID_SIZE / 2;
//     p->health = 100;
//     p->score = 0;
// }

// // Initialize zombies randomly on the grid with health and alive state
// void initZombies(Zombie zombies[], int count) {
//     for(int i = 0; i < count; i++) {
//         zombies[i].x = rand() % GRID_SIZE;
//         zombies[i].y = rand() % GRID_SIZE;
//         zombies[i].health = 50;
//         zombies[i].alive = 1;
//     }
// }

// // Print the grid with player and zombies positions
// void printGrid(Player p, Zombie zombies[], int zombieCount) {
//     for(int i = 0; i < GRID_SIZE; i++) {
//         for(int j = 0; j < GRID_SIZE; j++) {
//             if(p.x == j && p.y == i)
//                 printf("P ");
//             else {
//                 int isZombie = 0;
//                 for(int z = 0; z < zombieCount; z++) {
//                     if(zombies[z].alive && zombies[z].x == j && zombies[z].y == i) {
//                         printf("Z ");
//                         isZombie = 1;
//                         break;
//                     }
//                 }
//                 if(!isZombie)
//                     printf(". ");
//             }
//         }
//         printf("\n");
//     }
// }

// // Check if two positions are adjacent including diagonals
// int isAdjacent(int x1, int y1, int x2, int y2) {
//     return (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1);
// }

// // Move zombies toward the player and attack if adjacent
// void moveZombies(Player *p, Zombie zombies[], int count) {
//     for(int i = 0; i < count; i++) {
//         if(!zombies[i].alive) continue;

//         if(zombies[i].x < p->x) zombies[i].x++;
//         else if(zombies[i].x > p->x) zombies[i].x--;

//         if(zombies[i].y < p->y) zombies[i].y++;
//         else if(zombies[i].y > p->y) zombies[i].y--;

//         if(isAdjacent(zombies[i].x, zombies[i].y, p->x, p->y)) {
//             p->health -= 10;
//             printf("Zombie %d attacked you! Health now %d\n", i+1, p->health);
//             if(p->health <= 0) {
//                 printf("You died! Game Over.\n");
//                 exit(0);
//             }
//         }
//     }
// }

// // Player attack damages adjacent zombies
// void playerAttack(Zombie zombies[], int count, Player *p) {
//     int attacked = 0;
//     for(int i = 0; i < count; i++) {
//         if(zombies[i].alive && isAdjacent(p->x, p->y, zombies[i].x, zombies[i].y)) {
//             zombies[i].health -= 30;
//             printf("Attacked Zombie %d, health now %d\n", i+1, zombies[i].health);
//             if(zombies[i].health <= 0) {
//                 zombies[i].alive = 0;
//                 p->score += 100;
//                 printf("Zombie %d killed!\n", i+1);
//                 attacked = 1;
//             }
//         }
//     }
//     if (!attacked)
//         printf("No zombies in range to attack.\n");
// }

// // Move player according to input command
// void movePlayer(Player *p, char direction) {
//     switch(direction) {
//         case 'w': if(p->y > 0) p->y--; break;
//         case 's': if(p->y < GRID_SIZE - 1) p->y++; break;
//         case 'a': if(p->x > 0) p->x--; break;
//         case 'd': if(p->x < GRID_SIZE - 1) p->x++; break;
//         default: printf("Invalid move\n"); break;
//     }
// }

// // Count how many zombies are still alive
// int zombiesRemaining(Zombie zombies[], int count) {
//     int aliveCount = 0;
//     for(int i = 0; i < count; i++) {
//         if(zombies[i].alive) aliveCount++;
//     }
//     return aliveCount;
// }

// // Print ASCII bar graph for health
// void printHealthGraph(int health) {
//     printf("Player Health: ");
//     int bars = (health / 10); // 10% per bar, max 10 bars
//     for(int i = 0; i < bars; i++) printf("*");
//     printf(" (%d%%)\n", health);
// }

// // Print ASCII bar graph for zombies
// void printZombieGraph(int zombieCount) {
//     printf("Zombies Remaining: ");
//     int bars = (zombieCount * 2); // Scale to max 10 bars for 5 zombies
//     for(int i = 0; i < bars; i++) printf("*");
//     printf(" (%d)\n", zombieCount);
// }

// int main() {
//     srand(time(NULL));
//     Player player;
//     Zombie zombies[MAX_ZOMBIES];
//     int round = 1;
//     char input;

//     initPlayer(&player);
//     initZombies(zombies, MAX_ZOMBIES);

//     while(1) {
//         printf("\n--- Round %d ---\n", round);
//         printGrid(player, zombies, MAX_ZOMBIES);
//         printf("Player Health: %d\nZombies Remaining: %d\nScore: %d\n",
//             player.health, zombiesRemaining(zombies, MAX_ZOMBIES), player.score);
//         printHealthGraph(player.health);
//         printZombieGraph(zombiesRemaining(zombies, MAX_ZOMBIES));
//         printf("Move (w/a/s/d) or attack (f)? ");

//         scanf(" %c", &input);

//         if(input == 'f')
//             playerAttack(zombies, MAX_ZOMBIES, &player);
//         else
//             movePlayer(&player, input);

//         moveZombies(&player, zombies, MAX_ZOMBIES);

//         if(zombiesRemaining(zombies, MAX_ZOMBIES) == 0) {
//             printf("Congratulations! You survived all zombies.\n");
//             break;
//         }
//         round++;
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define GRID_SIZE 5
#define MAX_ZOMBIES 5
#define MAX_NODES (GRID_SIZE * GRID_SIZE)

// Graph Node for grid cell
typedef struct GraphNode {
    int x, y; // Coordinates
    int neighbors[8]; // Adjacent nodes (up, down, left, right, diagonals)
    int neighborCount;
} GraphNode;

// Linked List Node for move history
typedef struct MoveNode {
    char action; // 'w', 'a', 's', 'd', or 'f'
    struct MoveNode* next;
} MoveNode;

// Player structure
typedef struct {
    int x, y;
    int health;
    int score;
} Player;

// Zombie structure
typedef struct {
    int x, y;
    int health;
    int alive;
} Zombie;

// Game state with graph and move history
typedef struct {
    GraphNode grid[MAX_NODES];
    MoveNode* moveHistory;
} GameState;

// Initialize player in the center with full health and zero score
void initPlayer(Player *p) {
    p->x = GRID_SIZE / 2;
    p->y = GRID_SIZE / 2;
    p->health = 100;
    p->score = 0;
}

// Initialize zombies randomly on the grid with health and alive state
void initZombies(Zombie zombies[], int count) {
    for(int i = 0; i < count; i++) {
        zombies[i].x = rand() % GRID_SIZE;
        zombies[i].y = rand() % GRID_SIZE;
        zombies[i].health = 50;
        zombies[i].alive = 1;
    }
}

// Initialize graph for the 5x5 grid
void initGraph(GameState *state) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            int nodeIdx = i * GRID_SIZE + j;
            state->grid[nodeIdx].x = j;
            state->grid[nodeIdx].y = i;
            state->grid[nodeIdx].neighborCount = 0;

            // Add neighbors (up, down, left, right, diagonals)
            int directions[8][2] = {
                {-1, 0}, {1, 0}, {0, -1}, {0, 1}, // Up, down, left, right
                {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // Diagonals
            };
            for(int d = 0; d < 8; d++) {
                int nx = i + directions[d][0];
                int ny = j + directions[d][1];
                if(nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                    int neighborIdx = nx * GRID_SIZE + ny;
                    state->grid[nodeIdx].neighbors[state->grid[nodeIdx].neighborCount++] = neighborIdx;
                }
            }
        }
    }
    state->moveHistory = NULL;
}

// Add move to linked list
void addMove(GameState *state, char action) {
    MoveNode* newMove = (MoveNode*)malloc(sizeof(MoveNode));
    newMove->action = action;
    newMove->next = state->moveHistory;
    state->moveHistory = newMove;
}

// Print move history
void printMoveHistory(GameState *state) {
    printf("Move History: ");
    MoveNode* current = state->moveHistory;
    while(current != NULL) {
        printf("%c ", current->action);
        current = current->next;
    }
    printf("\n");
}

// Free move history linked list
void freeMoveHistory(GameState *state) {
    MoveNode* current = state->moveHistory;
    while(current != NULL) {
        MoveNode* temp = current;
        current = current->next;
        free(temp);
    }
    state->moveHistory = NULL;
}

// Print the grid with player and zombies positions
void printGrid(Player p, Zombie zombies[], int zombieCount) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            if(p.x == j && p.y == i)
                printf("P ");
            else {
                int isZombie = 0;
                for(int z = 0; z < zombieCount; z++) {
                    if(zombies[z].alive && zombies[z].x == j && zombies[z].y == i) {
                        printf("Z ");
                        isZombie = 1;
                        break;
                    }
                }
                if(!isZombie)
                    printf(". ");
            }
        }
        printf("\n");
    }
}

// Check if two positions are adjacent using graph
int isAdjacent(GameState *state, int x1, int y1, int x2, int y2) {
    int nodeIdx = y1 * GRID_SIZE + x1;
    int targetIdx = y2 * GRID_SIZE + x2;
    for(int i = 0; i < state->grid[nodeIdx].neighborCount; i++) {
        if(state->grid[nodeIdx].neighbors[i] == targetIdx)
            return 1;
    }
    return 0;
}

// Move zombies toward the player using graph
void moveZombies(Player *p, Zombie zombies[], int count, GameState *state) {
    for(int i = 0; i < count; i++) {
        if(!zombies[i].alive) continue;

        int currentIdx = zombies[i].y * GRID_SIZE + zombies[i].x;
        int playerIdx = p->y * GRID_SIZE + p->x;
        int minDist = GRID_SIZE * GRID_SIZE;
        int nextIdx = currentIdx;

        // Find the neighbor closest to the player
        for(int j = 0; j < state->grid[currentIdx].neighborCount; j++) {
            int neighborIdx = state->grid[currentIdx].neighbors[j];
            int nx = state->grid[neighborIdx].x;
            int ny = state->grid[neighborIdx].y;
            int dist = abs(nx - p->x) + abs(ny - p->y);
            if(dist < minDist) {
                minDist = dist;
                nextIdx = neighborIdx;
            }
        }

        // Update zombie position
        zombies[i].x = state->grid[nextIdx].x;
        zombies[i].y = state->grid[nextIdx].y;

        if(isAdjacent(state, zombies[i].x, zombies[i].y, p->x, p->y)) {
            p->health -= 10;
            printf("Zombie %d attacked you! Health now %d\n", i+1, p->health);
            if(p->health <= 0) {
                printf("You died! Game Over.\n");
                exit(0);
            }
        }
    }
}

// Player attack damages adjacent zombies
void playerAttack(Zombie zombies[], int count, Player *p, GameState *state) {
    int attacked = 0;
    for(int i = 0; i < count; i++) {
        if(zombies[i].alive && isAdjacent(state, p->x, p->y, zombies[i].x, zombies[i].y)) {
            zombies[i].health -= 30;
            printf("Attacked Zombie %d, health now %d\n", i+1, zombies[i].health);
            if(zombies[i].health <= 0) {
                zombies[i].alive = 0;
                p->score += 100;
                printf("Zombie %d killed!\n", i+1);
                attacked = 1;
            }
        }
    }
    if (!attacked)
        printf("No zombies in range to attack.\n");
}

// Validate and move player using graph
int movePlayer(Player *p, char direction, GameState *state) {
    int currentIdx = p->y * GRID_SIZE + p->x;
    int newX = p->x, newY = p->y;
    switch(direction) {
        case 'w': newY = p->y - 1; break;
        case 's': newY = p->y + 1; break;
        case 'a': newX = p->x - 1; break;
        case 'd': newX = p->x + 1; break;
        default: return 0; // Invalid move
    }
    if(newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
        int newIdx = newY * GRID_SIZE + newX;
        for(int i = 0; i < state->grid[currentIdx].neighborCount; i++) {
            if(state->grid[currentIdx].neighbors[i] == newIdx) {
                p->x = newX;
                p->y = newY;
                return 1; // Valid move
            }
        }
    }
    return 0; // Invalid move
}

// Count how many zombies are still alive
int zombiesRemaining(Zombie zombies[], int count) {
    int aliveCount = 0;
    for(int i = 0; i < count; i++) {
        if(zombies[i].alive) aliveCount++;
    }
    return aliveCount;
}

// Print ASCII bar graph for health
void printHealthGraph(int health) {
    printf("Player Health: ");
    int bars = (health / 10); // 10% per bar, max 10 bars
    for(int i = 0; i < bars; i++) printf("*");
    printf(" (%d%%)\n", health);
}

// Print ASCII bar graph for zombies
void printZombieGraph(int zombieCount) {
    printf("Zombies Remaining: ");
    int bars = (zombieCount * 2); // Scale to max 10 bars for 5 zombies
    for(int i = 0; i < bars; i++) printf("*");
    printf(" (%d)\n", zombieCount);
}

int main() {
    srand(time(NULL));
    Player player;
    Zombie zombies[MAX_ZOMBIES];
    GameState state;
    int round = 1;
    char input;

    initPlayer(&player);
    initZombies(zombies, MAX_ZOMBIES);
    initGraph(&state);

    while(1) {
        printf("\n--- Round %d ---\n", round);
        printGrid(player, zombies, MAX_ZOMBIES);
        printf("Player Health: %d\nZombies Remaining: %d\nScore: %d\n",
            player.health, zombiesRemaining(zombies, MAX_ZOMBIES), player.score);
        printHealthGraph(player.health);
        printZombieGraph(zombiesRemaining(zombies, MAX_ZOMBIES));
        printMoveHistory(&state);
        printf("Move (w/a/s/d), attack (f), or quit (q)? ");

        scanf(" %c", &input);

        if(input == 'q') {
            printf("Game ended. Final score: %d\n", player.score);
            freeMoveHistory(&state);
            break;
        }

        if(input == 'f') {
            playerAttack(zombies, MAX_ZOMBIES, &player, &state);
            addMove(&state, 'f');
        } else {
            if(movePlayer(&player, input, &state)) {
                addMove(&state, input);
            } else if(input != 'w' && input != 'a' && input != 's' && input != 'd') {
                printf("Invalid move\n");
            } else {
                printf("Cannot move there\n");
            }
        }

        moveZombies(&player, zombies, MAX_ZOMBIES, &state);

        if(zombiesRemaining(zombies, MAX_ZOMBIES) == 0) {
            printf("Congratulations! You survived all zombies.\n");
            printMoveHistory(&state);
            freeMoveHistory(&state);
            break;
        }
        round++;
    }
    return 0;
}