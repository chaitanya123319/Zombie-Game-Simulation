#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 5
#define MAX_ZOMBIES 5

typedef struct {
    int x, y;
    int health;
    int score;
} Player;

typedef struct {
    int x, y;
    int health;
    int alive;
} Zombie;

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

// Print the grid with player and zombies positions
void printGrid(Player p, Zombie zombies[], int zombieCount) {
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            if(p.x == j && p.y == i)
                printf("P "); // Player
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

// Check if two positions are adjacent including diagonals
int isAdjacent(int x1, int y1, int x2, int y2) {
    return (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1);
}

// Move zombies toward the player and attack if adjacent
void moveZombies(Player *p, Zombie zombies[], int count) {
    for(int i = 0; i < count; i++) {
        if(!zombies[i].alive) continue;

        if(zombies[i].x < p->x) zombies[i].x++;
        else if(zombies[i].x > p->x) zombies[i].x--;

        if(zombies[i].y < p->y) zombies[i].y++;
        else if(zombies[i].y > p->y) zombies[i].y--;

        if(isAdjacent(zombies[i].x, zombies[i].y, p->x, p->y)) {
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
void playerAttack(Zombie zombies[], int count, Player *p) {
    int attacked = 0;
    for(int i = 0; i < count; i++) {
        if(zombies[i].alive && isAdjacent(p->x, p->y, zombies[i].x, zombies[i].y)) {
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

// Move player according to input command
void movePlayer(Player *p, char direction) {
    switch(direction) {
        case 'w': if(p->y > 0) p->y--; break;
        case 's': if(p->y < GRID_SIZE - 1) p->y++; break;
        case 'a': if(p->x > 0) p->x--; break;
        case 'd': if(p->x < GRID_SIZE - 1) p->x++; break;
        default: printf("Invalid move\n"); break;
    }
}

// Count how many zombies are still alive
int zombiesRemaining(Zombie zombies[], int count) {
    int aliveCount = 0;
    for(int i = 0; i < count; i++) {
        if(zombies[i].alive) aliveCount++;
    }
    return aliveCount;
}

int main() {
    srand(time(NULL));
    Player player;
    Zombie zombies[MAX_ZOMBIES];
    int round = 1;
    char input;

    initPlayer(&player);
    initZombies(zombies, MAX_ZOMBIES);

    while(1) {
        printf("\n--- Round %d ---\n", round);
        printGrid(player, zombies, MAX_ZOMBIES);
        printf("Player Health: %d\nZombies Remaining: %d\nScore: %d\n",
            player.health, zombiesRemaining(zombies, MAX_ZOMBIES), player.score);
        printf("Move (w/a/s/d) or attack (f)? ");

        scanf(" %c", &input);

        if(input == 'f')
            playerAttack(zombies, MAX_ZOMBIES, &player);
        else
            movePlayer(&player, input);

        moveZombies(&player, zombies, MAX_ZOMBIES);

        if(zombiesRemaining(zombies, MAX_ZOMBIES) == 0) {
            printf("Congratulations! You survived all zombies.\n");
            break;
        }
        round++;
    }
    return 0;
}
