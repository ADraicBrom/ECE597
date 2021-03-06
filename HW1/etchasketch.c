#include <stdio.h>

int gridSize=8;

void printGrid(char pGrid[gridSize][gridSize])
{
	int i, k;
	printf("Help\n");
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			printf("%c", pGrid[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

void clear(char pGrid[gridSize][gridSize])
{
	int i;
	int k;
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			pGrid[i][k]=' ';
		}
	}
}

int main()
{
	int i, k;
	int x=0;
	int y=0;
	int moveX, moveY;
	char string[8];
	
	printf("Input grid size\n");
	scanf("%i", &gridSize);
	printf("size input\n");
	
	char grid[gridSize][gridSize];

	printf("grid created\n");
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			grid[i][k]=' ';
		}
	}
	printf("grid set\n");

	
	printGrid(grid);
	
	while(1){
		printf("Input Movement\n");
		scanf("%s", &string);
		if(strcmp(string,"up")==0){moveX=0; moveY=-1;}
		else if(strcmp(string,"down")==0){moveX=0; moveY=1;}
		else if(strcmp(string,"left")==0){moveX=-1; moveY=0;}
		else if(strcmp(string,"right")==0){moveX=1; moveY=0;}
		else if(strcmp(string,"clear")==0){clear(grid); x=0; y=0; moveX=0; moveY=0;}
		else{moveX=0; moveY=0; printf("ERROR\n");}
		
		if(x+moveX > gridSize || x+moveX < 0 || y+moveY > gridSize || y+moveY < 0){printf("OUT OF BOUNDS\n");}
		else{
			x += moveX;
			y += moveY;
			grid[y][x] = 'X';
			printGrid(grid);
		}
	}
}


