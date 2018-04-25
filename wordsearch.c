/*
 * Daniel O'Connell
 * Intro to C programming
 * Assignment 2
 * Due 16 Feb 2016 @ 2359
 *
 */

#include <stdio.h>
#include <string.h>

void getWords();
int findWord();
int traverse();

int solved[25][25];
char input_grid[25][25];

int main (void){
        char input_string[50];
        int input_row = 0;
        int i, j, row, col, length, height;

                        
        scanf("%[^\n]%*c", input_string);
        length = strlen(input_string);
                                    
        for (i=0, col=0; i<length; i++){
            if (input_string[i]!=' '){
                input_grid[0][col] = input_string[i];
                col++;
            }
        }

        input_grid[input_row] [col]= '\0';
        height = strlen(input_grid[0]);

        for(j = 1; j < strlen(input_grid[input_row]); j++){
            col = 0;
            input_row++;
            scanf("%[^\n]%*c", input_string);
            for(i = 0; i < length;i++){
                if(input_string[i]!=' '){
                    input_grid[input_row][col] = input_string[i];
                    col++;
                }
            }
            input_grid[input_row] [col]= '\0';
        }

        getWords();

        /*
         * print solved grid
         */
        for(row = 0; row < length; row++){
            for(col = 0; col < height; col++){
                if(solved[row][col] != 0){
                    printf("%c ", input_grid[row][col]);
                }
                else{
                    printf("  ");
                }
            }
            printf("\n");
        }
        return 0;
}

void getWords(){
    int row, col;
    char input_string[50];
    int max = strlen(input_grid[0]);
    int found;

    scanf("%[^\n]%*c", input_string);
    do{
        /*iterate through the entire grid to find the first letter of this word*/
        for(row = 0; row < max; row++){
            for (col = 0; col < max; col++){
                if(input_string[0] == input_grid[row][col]){
                    /*
                     * check directions
                     */
                    found = findWord(row, col, input_string);
                    if(found == 1){
                        solved[row][col]++;
                    }
                }
            }
        }
        input_string[0] = '\0';
        scanf("%[^\n]%*c", input_string);
    }while ( input_string[0] != '\0');
}

int findWord(int row, int col, char word[]){
    int max = strlen(input_grid[0]);
    int try = 0;
    /*
     * directional values:
     * NE: 1
     * E : 2
     * SE: 3
     * S : 4
     * SW: 5
     * W : 6
     * NW: 7
     * N : 8
     */

    /* top */
    if(row == 0){
        /* top left*/
        if (col == 0){
            try = traverse(row    , col + 1, word, 1, 2) +
                  traverse(row + 1, col + 1, word, 1, 3) +
                  traverse(row + 1, col    , word, 1, 4);
            /*
             * try E, SE, S
             *     2, 3 , 4
             */
            if(try >= 1){
                return 1;
            }
        }

        /* top right*/
        if (col == max){
            try = traverse(row + 1, col    , word, 1, 4) +
                  traverse(row + 1, col - 1, word, 1, 5) +
                  traverse(row    , col - 1, word, 1, 6);
            /*
             * try S, SW, W
             *     4, 5 , 6
             */
            if(try >= 1){
                return 1;
            }
        }
    }

    /* bottom */
    else if(row == max){
        /* bottom left*/
        if (col == 0){
            /*
             * try N, NE, E
             *     8, 1 , 2
             */
            try = traverse(row - 1, col + 1, word, 1, 1) +
                  traverse(row    , col + 1, word, 1, 2) +
                  traverse(row - 1, col    , word, 1, 8);
            if(try >= 1){
                return 1;
            }
        }

        /* bottom right*/
        if (col == max){
            /*
             * try N, W, NW
             *     8, 6, 7
             */
            try = traverse(row    , col - 1, word, 1, 6) +
                  traverse(row - 1, col - 1, word, 1, 7) +
                  traverse(row - 1, col    , word, 1, 8);
            if(try >= 1){
                return 1;
            }
        }
    }

    /* left */
    else if(col == 0){
        /*
         * try N, NE, E, SE, S
         *     8, 1 , 2, 3 , 4
         */
        try = traverse(row - 1, col + 1, word, 1, 1) +
              traverse(row    , col + 1, word, 1, 2) +
              traverse(row + 1, col + 1, word, 1, 3) +
              traverse(row + 1, col    , word, 1, 4) +
              traverse(row - 1, col    , word, 1, 8);
        if(try >= 1){
            return 1;
        }
    }

    /* right */
    else if(col == max){
        /*
         * try N, S, SW, W, NW
         *     8, 4, 5 , 6, 7
         */
        try = traverse(row + 1, col    , word, 1, 4) +
              traverse(row + 1, col - 1, word, 1, 5) +
              traverse(row    , col - 1, word, 1, 6) +
              traverse(row - 1, col - 1, word, 1, 7) +
              traverse(row - 1, col    , word, 1, 8);
        if(try >= 1){
            return 1;
        }
    }

    else{
        /*
         * try everything
         */
        try = traverse(row - 1, col + 1, word, 1, 1) +
              traverse(row    , col + 1, word, 1, 2) +
              traverse(row + 1, col + 1, word, 1, 3) +
              traverse(row + 1, col    , word, 1, 4) +
              traverse(row + 1, col - 1, word, 1, 5) +
              traverse(row    , col - 1, word, 1, 6) +
              traverse(row - 1, col - 1, word, 1, 7) +
              traverse(row - 1, col    , word, 1, 8);
        if(try >= 1){
            return 1;
         }
    }
    return 0; /* word not found */
}

int traverse(int row, int col, char word[], int wordIndex, int direction){
    /*returns 1 if found, 0 if not*/
    if(word[wordIndex] == '\0'){
        /*base case met*/
        return 1;
    }

    if(word[wordIndex] == input_grid[row][col] &&
       wordIndex < strlen(word)){
        switch(direction){
            case 1: /*NE*/
                solved[row][col]++;
                return traverse(row - 1, col + 1, word, wordIndex + 1, 1);
                break;
            case 2: /*E*/
                solved[row][col]++;
                return traverse(row, col + 1, word, wordIndex + 1, 2);
                break;
            case 3: /*SE*/
                solved[row][col]++;
                return traverse(row + 1, col + 1, word, wordIndex + 1, 3);
                break;
            case 4: /*S*/
                solved[row][col]++;
                return traverse(row + 1, col, word, wordIndex + 1, 4);
                break;
            case 5: /*SW*/
                solved[row][col]++;
                return traverse(row + 1, col - 1, word, wordIndex + 1, 5);
                break;
            case 6: /*W*/
                solved[row][col]++;
                return traverse(row, col - 1, word, wordIndex + 1, 6);
                break;
            case 7: /*NW*/
                solved[row][col]++;
                return traverse(row - 1, col - 1, word, wordIndex + 1, 7);
                break;
            case 8: /*N*/
                solved[row][col]++;
                return traverse(row - 1, col, word, wordIndex + 1, 8);
                break;
            default:
                break;

        }
    }
    return 0;
}









