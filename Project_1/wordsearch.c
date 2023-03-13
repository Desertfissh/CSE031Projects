#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
int fullSearch(char** arr, int**solution, char* word);
int checkNeighbors(char** puzzle, int** solution, char* word, int row, int col, int place);
void searchPuzzle(char** arr, char* word);


int bSize;


// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++) {
		for(int j = 0; j < bSize; j++) {
			printf("%c ", *(*(arr+i)+j));
		}
		printf("\n");
	}
	printf("\n");
}

char* upcase(char* str) {
    char* p;
    char* result;
    result = (char*)malloc(strlen(str)+1);
    strcpy(result,str);
    for(p = result; *p != '\0'; p++) {
        if(*p >= 'a' && *p <= 'z') {
            *p += 'A' - 'a';
        }
    }
    return result;
}

int fullSearch(char** arr, int** solution, char* word){
    int bool = 0;
    //search arr for first char in word;
    for(int i = 0; i < bSize; i++) {
		for(int j = 0; j < bSize; j++) {
            if(*(*(arr+i)+j) == *(word)) {// character youre looking at is the first character of the word
                if (checkNeighbors(arr, solution, word+1, i, j, 2)){
                    if(*(*(solution+i)+j) != 0){*(*(solution+i)+j) = *(*(solution+i)+j)*10 + 1;}
                    else{*(*(solution+i)+j) = 1;}
                    bool = 1;
                }
            }
			
		}
	}
    return 1;

}
   

int checkNeighbors(char** puzzle, int** solution, char* word, int row, int col, int place){

    if ( *(word) == '\0'){
        return 1;
    }

    for (int i=row-1; i<=row+1; i++){
        for (int j=col-1; j<=col+1; j++){
            
            if ((i == row && j == col) || (i < 0 || i>bSize || j<0 || j>bSize)){
                continue;
            }

            if (*(*(puzzle+i)+j) == *(word)){
                if (checkNeighbors(puzzle, solution, word+1, i, j, place+1)){
                    if(*(*(solution+i)+j) != 0){*(*(solution+i)+j) = *(*(solution+i)+j)*10 + place;}
                    else{*(*(solution+i)+j) = place;}
                    return 1;
                }    
            }
        }
    }
    return 0;

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    
    int i, j, bool;
    int* firstChar;

    // Allocate space for the solution path
    int **solution = (int**)malloc(bSize * sizeof(int*));

    for(i = 0; i < bSize; i++) {
        *(solution + i) = (int*)malloc(bSize * sizeof(int));
        for (j = 0; j < bSize; ++j) {
            *(*(solution + i) + j) = 0;
        }
    }

    word = upcase(word);    

    if (fullSearch(arr, solution, word)){
        printf("Word Found!\n");
        for(int i = 0; i < bSize; i++) {
		    for(int j = 0; j < bSize; j++) {
			    printf("%-10d", *(*(solution+i)+j));
		    }
		    printf("\n");
	    }
	    printf("\n");

    }
    else{printf("Word not found!\n");}
}

