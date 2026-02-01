#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 3

typedef struct {
    int value;
} Tile;

// Structuur bboord
typedef struct {
    int size;
    Tile*** grid;  // 2D array van pointers naar Tiles
    int empty_row;
    int empty_col;
} Board;

Board* create_board(int size);
void init_board(Board* board);
void shuffle_board(Board* board, int moves);
void print_board(Board* board);
void swap_tiles(Board* board, int row1, int col1, int row2, int col2);
int is_valid_swap(Board* board, int row1, int col1, int row2, int col2);
int is_solved(Board* board);
void free_board(Board* board);
int get_valid_input(const char* prompt, int min, int max);

Board* create_board(int size) {
    Board* board = (Board*)malloc(sizeof(Board));
    if (board == NULL) {
        fprintf(stderr, "Fout: Geheugen allocatie mislukt voor board\n");
        exit(1);
    }

    board->size = size;

    board->grid = (Tile***)malloc(size * sizeof(Tile**));
    if (board->grid == NULL) {
        fprintf(stderr, "Fout: Geheugen toewijzen mislukt voor grid\n");
        free(board);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        board->grid[i] = (Tile**)malloc(size * sizeof(Tile*));
        if (board->grid[i] == NULL) {
            fprintf(stderr, "Fout: Geheugen toewijzen mislukt voor rij %d\n", i);
            for (int j = 0; j < i; j++) {
                free(board->grid[j]);
            }
            free(board->grid);
            free(board);
            exit(1);
        }

        for (int j = 0; j < size; j++) {
            board->grid[i][j] = (Tile*)malloc(sizeof(Tile));
            if (board->grid[i][j] == NULL) {
                fprintf(stderr, "Fout: Geheugen toewijzen mislukt voor tile [%d][%d]\n", i, j);
                for (int k = 0; k < j; k++) {
                    free(board->grid[i][k]);
                }
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < size; l++) {
                        free(board->grid[k][l]);
                    }
                    free(board->grid[k]);
                }
                free(board->grid[i]);
                free(board->grid);
                free(board);
                exit(1);
            }
        }
    }

    return board;
}

void init_board(Board* board) {
    int value = 1;
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (i == board->size - 1 && j == board->size - 1) {
                board->grid[i][j]->value = 0;  
                board->empty_row = i;
                board->empty_col = j;
            } else {
                board->grid[i][j]->value = value++;
            }
        }
    }
}

// pointers verwisselen
void swap_tiles(Board* board, int row1, int col1, int row2, int col2) {
    Tile* temp = board->grid[row1][col1];
    board->grid[row1][col1] = board->grid[row2][col2];
    board->grid[row2][col2] = temp;

    // Update lege tile als dat nodig is 
    if (board->grid[row1][col1]->value == 0) {
        board->empty_row = row1;
        board->empty_col = col1;
    } else if (board->grid[row2][col2]->value == 0) {
        board->empty_row = row2;
        board->empty_col = col2;
    }
}

int is_valid_swap(Board* board, int row1, int col1, int row2, int col2) {
    if (row1 < 0 || row1 >= board->size || col1 < 0 || col1 >= board->size ||
        row2 < 0 || row2 >= board->size || col2 < 0 || col2 >= board->size) {
        return 0;
    }

    int row_diff = abs(row1 - row2);
    int col_diff = abs(col1 - col2);

    return (row_diff == 0 && col_diff == 1) || (row_diff == 1 && col_diff == 0);
}

void shuffle_board(Board* board, int moves) {
    srand(time(NULL));

    for (int i = 0; i < moves; i++) {
        int direction = rand() % 4;  
        int new_row = board->empty_row;
        int new_col = board->empty_col;

        switch (direction) {
            case 0: new_row--; break;  // omhoog
            case 1: new_row++; break;  // beneden
            case 2: new_col--; break;  // links
            case 3: new_col++; break;  // rechts
        }

        if (is_valid_swap(board, board->empty_row, board->empty_col, new_row, new_col)) {
            swap_tiles(board, board->empty_row, board->empty_col, new_row, new_col);
        }
    }
}


void print_board(Board* board) {
    printf("\n");
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->grid[i][j]->value == 0) {
                printf("   ");
            } else {
                printf("%2d ", board->grid[i][j]->value);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int is_solved(Board* board) {
    int expected = 1;
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (i == board->size - 1 && j == board->size - 1) {
                if (board->grid[i][j]->value != 0) {
                    return 0;
                }
            } else {
                if (board->grid[i][j]->value != expected) {
                    return 0;
                }
                expected++;
            }
        }
    }
    return 1;
}

void free_board(Board* board) {
    if (board == NULL) return;

    if (board->grid != NULL) {
        for (int i = 0; i < board->size; i++) {
            if (board->grid[i] != NULL) {
                for (int j = 0; j < board->size; j++) {
                    if (board->grid[i][j] != NULL) {
                        free(board->grid[i][j]);
                    }
                }
                free(board->grid[i]);
            }
        }
        free(board->grid);
    }

    free(board);
}

int get_valid_input(const char* prompt, int min, int max) {
    int value;
    int valid = 0;

    while (!valid) {
        printf("%s", prompt);

        if (scanf("%d", &value) != 1) {
            printf("Fout: Voer een geldig getal in.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } else if (value < min || value > max) {
            printf("Fout: Getal moet tussen %d en %d zijn.\n", min, max);
        } else {
            valid = 1;
        }
    }

    return value;
}

int main() {
    printf("=== Schuifpuzzel ===\n");
    printf("Grootte: %dx%d\n", GRID_SIZE, GRID_SIZE);

    Board* board = create_board(GRID_SIZE);
    init_board(board);

    printf("Bord wordt geschud...\n");
    shuffle_board(board, GRID_SIZE * GRID_SIZE * 10);

    int moves = 0;

    while (!is_solved(board)) {
        print_board(board);

        printf("Voer de positie in van twee tegels om te wisselen:\n");

        int row1 = get_valid_input("Rij van tegel 1 (0-%d): ", 0, board->size - 1);
        int col1 = get_valid_input("Kolom van tegel 1 (0-%d): ", 0, board->size - 1);
        int row2 = get_valid_input("Rij van tegel 2 (0-%d): ", 0, board->size - 1);
        int col2 = get_valid_input("Kolom van tegel 2 (0-%d): ", 0, board->size - 1);

        if (!is_valid_swap(board, row1, col1, row2, col2)) {
            printf("Ongeldige zet! Tegels moeten horizontaal of verticaal naast elkaar staan.\n");
            continue;
        }

        swap_tiles(board, row1, col1, row2, col2);
        moves++;
    }

    print_board(board);
    printf("Gefeliciteerd! puzzel opgelist");

    // Geheugen vrijgeven
    free_board(board);

    return 0;
}
