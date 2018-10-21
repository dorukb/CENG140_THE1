#include <stdio.h>

void print_field(int field[][100],int field_size);
void part2(int);
int pathfinder(int grid[][100],int grid_size);
int pathfinder_helper(char path[][100],int grid[][100],int grid_size,int row,int col,int sum);
int path_printer(int grid[][100],int grid_size,int col,int row);

int main()
{
	int N,size_part2;
	
	scanf(" %d",&size_part2);
	part2(size_part2);
	
	
	return 0;
}


void part2(int grid_size)
{
	int i,j;
	int grid[100][100];
	for(i = 0; i < grid_size; i++)
	{
		for(j = 0; j < grid_size; j++)
		{
			scanf("%d",&grid[j][i]);
		}
	}
	pathfinder(grid,grid_size);
}


int pathfinder(int grid[][100],int grid_size)
{
	int row = 0,col = 0 ,step = 0;
	int max_energy,i,j;
	char path[100][100];
	int path_size;
	path_size = grid_size;
	
	for(i=0; i<grid_size; i++)
	{	
		for(j=0; j<grid_size; j++)
		{
			path[j][i] = 0;
		}
	}
	max_energy =  pathfinder_helper(path,grid,grid_size,row,col,0);
	path_printer(grid,grid_size,0,0);
	printf(", final energy: %d\n",max_energy*40);
	
}

int path_printer(int grid[][100],int grid_size,int col,int row)
{
	if(col == grid_size-1 && row == grid_size-1)
	{
		return 0;
	}
	else if (col == grid_size-1)
	{
		printf("S ");
		path_printer(grid,grid_size,col,row+1);
	}
	else if(row == grid_size-1)
	{
		printf("E ");
		path_printer(grid,grid_size,col+1,row);
	}
	else if(grid[col+1][row] >= grid[col][row+1])
	{
		printf("E ");
		path_printer(grid,grid_size,col+1,row);
	}
	else if(grid[col+1][row] < grid[col][row+1])
	{
		printf("S ");
		path_printer(grid,grid_size,col,row+1);
	}
}


int pathfinder_helper(char path[][100],int grid[][100],int grid_size,int row,int col,int sum)
{
	int east_sum,south_sum,my_value;
	
	my_value = grid[col][row];
	/*if can move East*/
	if(col < grid_size-1)
	{
		if(path[col+1][row] == 'y')
		{
			east_sum = grid[col+1][row];
		}
		else
		{
			east_sum = pathfinder_helper(path,grid,grid_size,row,col+1,sum+1);
		}

	}
	
	/*if can move South*/	
	if(row < grid_size-1)
	{
		if(path[col][row+1] == 'y')
		{
			south_sum = grid[col][row+1];
		}
		else
		{
			south_sum = pathfinder_helper(path,grid,grid_size,row+1,col,sum+1);
		}
	
	}
	
	else if((row == grid_size-1) && (col == grid_size-1))
	{

		return grid[col][row];
	}
	/*if both east_sum and south_sum exist*/
	if(col < grid_size-1 && row<grid_size-1) 
	{
		if(east_sum >= south_sum)
		{
			
			if(path[col][row] != 'y')
			{
				grid[col][row] = east_sum+ my_value;
				path[col][row] = 'y';
			}
			
			return grid[col][row];
		}
		
		else
		{	
			if(path[col][row] != 'y')
			{	
				grid[col][row] = south_sum+ my_value;
				path[col][row] = 'y';
			}	
			return grid[col][row];
		}
	}
	/*if only south sum exists*/
	else if(col == grid_size-1 && row < grid_size-1)
	{
		if(path[col][row] != 'y')
			{
				grid[col][row] = south_sum+ my_value;
				path[col][row] = 'y';
			}
		return grid[col][row];
	}
	
	/*if only east sum exists*/ 
	else if(row == grid_size-1 && col < grid_size-1)
	{
		if(path[col][row] != 'y')
			{
				grid[col][row] = east_sum+ my_value;
				path[col][row] = 'y';
			}
		return grid[col][row];
	}

}


/*simply prints the field(array) when everything is done.*/
void print_field(int field[][100],int grid_size)
{
	int i,j;
	for(i=0; i<grid_size; i++)
	{	
		for(j=0; j<grid_size; j++)
		{
			printf("%d ",field[j][i]);
			
		}
		printf("\n");
	}
}


