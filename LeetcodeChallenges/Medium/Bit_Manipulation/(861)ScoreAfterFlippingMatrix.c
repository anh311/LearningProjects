/*#include <math.h>
void flipCol(int** grid, int gridSize, int i,int gridColSize){
    int count =0;
    for (int l=0;l<gridSize; l++){
        if(grid[l][i]==0){
            count++;
        }
    }
    if(count * 2 >= gridSize){
        for (int l=0;l<gridSize; l++){
            if(grid[l][i]==1){
                grid[l][i]=0;
            }else{
                grid[l][i]=1;
            }
        }
    }
}
void flipRow(int** grid, int gridColSize, int i){
    for (int l=0;l<gridColSize; l++){
        if(grid[i][l]==1){
            grid[i][l]=0;
        }else{
            grid[i][l]=1;
        }
    }
}
int matrixScore(int** grid, int gridSize, int* gridColSize) {
    for (int l=0; l<gridSize;l++){
        if(grid[l][0]==0){
            flipRow(grid,gridColSize[0],l);
        }
    }
    
    for (int l=0;l<gridColSize[0]; l++){
            flipCol(grid,gridSize,l,gridColSize[0]);
        }
    
    for (int i = 0; i < gridSize; i++) {
        for (int l = 0; l < gridColSize[0]; l++) {

            printf("%d ", grid[i][l]);
        }
        printf("\n");
    }
   
    int result=0;
    for (int i=0; i<gridSize; i++){
        for (int l=0;l<gridColSize[0];l++){
            if( grid[i][l]!=0 || (gridColSize[0]-l-1)!=0){
                result+=pow(2*grid[i][l],(gridColSize[0]-l-1));
            }
        }
    }
    return result;
}
*/


void flipCol(int** grid, int gridSize, int i,int gridColSize){
    int count =0;
    for (int l=0;l<gridSize; l++){
        if(grid[l][i]==0){
            count++;
        }
    }
    if(count * 2 >= gridSize){
        for (int l=0;l<gridSize; l++){
            grid[l][i]^=1;
        }
    }
}
void flipRow(int** grid, int gridColSize, int i){
    for (int l=0;l<gridColSize; l++){
        grid[i][l]^=1;

    }
}
int matrixScore(int** grid, int gridSize, int* gridColSize) {
    for (int l=0; l<gridSize;l++){
        if(grid[l][0]==0){
            flipRow(grid,gridColSize[0],l);
        }
    }
    
    for (int l=0;l<gridColSize[0]; l++){
            flipCol(grid,gridSize,l,gridColSize[0]);
        }

    int result=0;
    for (int i=0; i<gridSize; i++){
        int platz=0;
        for (int l=0;l<gridColSize[0];l++){
            platz=(platz<<1) | grid[i][l];
        }
        result+=platz;
    }
    return result;
}