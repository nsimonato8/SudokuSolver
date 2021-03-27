#include<stdio.h>
#include<stdlib.h>
#define MAXCHAR 100
#define SIDE 9
#define GRID_DIM ((SIDE) * (SIDE))
#define FILENAME "grids_X.txt"

enum el {ROW,COL,SQUARE};
typedef enum el elem;

int matrix[GRID_DIM] = {9,0,6,0,7,0,4,0,3,/**/0,0,0,4,0,0,2,0,0,/**/0,7,0,0,2,3,0,1,0,/**/5,0,0,0,0,0,1,0,0,/**/0,4,0,2,0,8,0,6,0,/**/0,0,3,0,0,0,0,0,5,/**/0,3,0,7,0,0,0,5,0,/**/0,0,7,0,0,5,0,0,0,/**/4,0,5,0,1,0,7,0,8,}; 
char str[MAXCHAR];

int read(char x) {
	int i = 0, max = GRID_DIM;
    FILE *fp;
    
    char* filename = FILENAME;
	char aux;
 
	filename[6] = x; /*Per leggere da più file*/
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 0;
    }
	
    do{
		aux = (char)fgetc(filename);
		if(aux != ' ' && aux != '\n')
			*str++ = aux;
	} while(aux != EOF);
        
    fclose(fp);
    return 1;
}

void str_to_matrix(){
	int i;
	for(i = 0; i < GRID_DIM; i++){
		matrix[i] = str[i] - '0';
	}
}

char *readFile(char *fileName)
{

  return code;
}

/*int* create_matrix(){ return malloc(GRID_DIM*sizeof(int));}*/

int get(int x, int y){
    return matrix[y * SIDE + x];
}

void set(int x, int y, int n){
    matrix[y * SIDE + x] = n;
}

int belongs(int x, int y, int n, elem e){
    int i;
    if(e == ROW){
        for(i = 0; i < SIDE; i++){
            if(get(i,y) == n)
                return 1;
        }
    } else if(e == COL){
        for(i = 0; i < SIDE; i++){
            if(get(x,i) == n)
                return 1;
        }
        
    } else{
		int j;
		for(i = x - x%3; i < x - x%3 + 3; i++){
			for(j = y - y%3; j < y - y%3 + 3; j++){
				if(i != x && j != y && get(i,j) == n){
					return 1;
				}
			}
		}
    }
    return 0;
}

void print_matrix(){
        int i,j;
    for(i = 0; i < SIDE; i++){
        for(j = 0; j < SIDE; j++){
            if(j && !(j%3)){
                printf("|");
                }
            printf("%d ",get(i,j));
            if((j + 1 == SIDE) && !((i+1) % 3)){
                int k;
                printf("\n");
                for(k = 0; k < (2 * SIDE + 1); k++){
                        printf("_");
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int is_possible(int x, int y, int n){
    return !belongs(x,y,n,ROW) && !belongs(x,y,n,COL) &&!belongs(x,y,n,SQUARE);
}

int solve(){
    int i,j,k,a = 0;
    
    for(i = 0; i < SIDE; i++){
        for(j = 0; j < SIDE; j++){
            if(get(i,j) == 0){
                for(k = 1; k < 10; k++){
                    if(is_possible(i,j,k)){
                        set(i,j,k);
                        a = solve();
                        if(a == 0)
                            set(i,j,0);
                    }
                }
                return a;
            }
        }
    }
    return 1;
}

int main(void){
	int i;
	print_matrix();
	i = solve();
	printf("%d\n\n",i);
	print_matrix();	
}