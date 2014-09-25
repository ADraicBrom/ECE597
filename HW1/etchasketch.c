#include <stdio.h>

int gridSize;

int main()
{
	int i, k;
	int x=0;
	int y=0;
	int moveX, moveY;
	printf("Input grid size");
	scanf("%d", gridSize;
	
	char grid[gridSize][gridSize];
	char *pGrid=&grid;
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			grid[i][k]=' ';
		}
	}
	
	printGrid(*pGrid);
	
	while(true){
		printf("Input X and Y movement");
		scanf("%d %d", moveX, moveY);
		if(abs(moveX) > 1 || abs(moveY) > 1){
			printf("Invalid Input");
		}else if(x+moveX > gridSize || x+moveX < 0){
			printf("Out of bounds: X");
		}else if(x+moveX > gridSize || x+moveX < 0){
			printf("Out of bounds: Y");
		}else{
			x += moveX;
			y += moveY;
			grid[x][y] = 'X';
			printGrid(*pGrid);
		}
	}
}

void printGrid(char *pGrid)
{
	int i, k;
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			printf(*pGrid[i][k]);
		}
		printf('\n');
	}
	printf('\n');
}
