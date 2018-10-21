#include <stdio.h>

void constructer(int field_size);
void carrot_linker(int field[][100],int field_size);
void print_field(int field[][100],int field_size);
int carrot_helper(int field[][100],int grid_size,int lvl,int col,int row,char dir,int links,char del);
int carrot_transform(int field[][100],int grid_size,int lvl,int col,int row);

int chain_reaction(int field[][100],int grid_size,int lvl,int col, int row,int control);

int main()
{
	int N;
	/*get the size of the field. (N x N) */
	scanf(" %d",&N);

	constructer(N);

	return 0;
}

void constructer(int grid_size)
{
	/*initialize the field. all cells have 0 at the beginning.*/
	int field[100][100],i,j;
	for(i=0; i<grid_size; i++)
	{	
		for(j=0; j<grid_size; j++)
		{
			field[j][i] = 0;
		}
	}
	/*starts the real processs.*/
	carrot_linker(field,grid_size);	
}


/*main organizing function.gets input and passes it to link finding functions.*/
void carrot_linker(int field[][100],int grid_size)
{
	int lvl,col,row;
	/*the part where we get the input. and for each input it checks whether enough links are formed by using below defined functions*/
	while(scanf(" %d %d %d",&lvl,&col,&row) != EOF)
	{
		int i = 0;
		int a = 1;
		/*fill the current(original) cell with given level carrot.*/
		field[col][row] = lvl;
		/*this is for chain reaction handling.As said below, carrot_transform returns 1 means that we need to do the same calculations again.
		(in order to see if chain reaction(s) happen.*/
		
		
		chain_reaction(field,grid_size,lvl,col,row,1);
	}
	/*we are done.print the constructed field*/
	print_field(field,grid_size);
}



int chain_reaction(int field[][100],int grid_size,int lvl,int col, int row,int control)
{
	if(control == 1)
	{
		control = carrot_transform(field,grid_size,lvl,col,row);
		chain_reaction(field,grid_size,lvl+1,col,row,control);
	}
}


/*will return 1 if enough links formed (i.e. a transformation happened.(could be chain reaction, so we must go on.(at most 4 times!)) */
int carrot_transform(int field[][100],int grid_size,int lvl,int col,int row)
{
		int num_links;
		/* helper will return the number of links formed. */
		num_links = carrot_helper(field,grid_size,lvl,col,row,'0',0,'n');
		if(num_links >= 2)
		{
			/* if link is formed , go through the same configuration again and make cells that are part of the link , zero. */
			carrot_helper(field,grid_size,lvl,col,row,'0',0,'Y');
			/* make the starting cell one level higher ! */
			field[col][row] = lvl+1;
			return 1;
		}
		else
		{	
			/*not enough links.no transformation,no need to check for chain reaction. not even triggered :PP */
			return 0;
		} 
}

int carrot_helper(int field[][100],int grid_size,int lvl,int col,int row,char dir,int links,char del)
{
		
		/* dir != 'S' here means that we did not came to this cell from SOUTH. 
		If that is the case, North neighbor would be our original cell ! And we shouldn't go back to it. Its infinite loop!! 
		 !!!! same logic applies to all directions below. !!!!!! */
		 
		/* if it has NORTH NEIGHBOR */
		if(( row > 0) && (dir != 'S'))
		{
			if(field[col][row-1] == lvl)
			{
				/* if this is for deleting carrots,then del will equal to Y */
				if(del == 'Y')
				{
					field[col][row-1] = 0;
				}
				/* normal case recursion call. */
				links = 1 + carrot_helper(field,grid_size,lvl,col,row-1,'N',links,del);
				
			}
		}
		
		/* if it has SOUTH NEIGHBOR */
		if((row < grid_size-1) && (dir != 'N'))
		{
			if(field[col][row+1] == lvl)
			{
				if(del == 'Y')
				{
					field[col][row+1] = 0;
				}
				links = 1 +  carrot_helper(field,grid_size,lvl,col,row+1,'S',links,del);
			}	
		}
		
		/* if it has West Neighbor */
		if(( col > 0) && (dir !='E'))
		{ 
			if(field[col-1][row] == lvl)
			{
				if(del == 'Y')
				{
					field[col-1][row] = 0;
				}
				links = 1+ carrot_helper(field,grid_size,lvl,col-1,row,'W',links,del);
			}		
		}
		
		/* if it has East Neighbor*/
		if((col < grid_size-1) && (dir != 'W'))
		{
			if(field[col+1][row] == lvl)
			{
				if(del == 'Y')
				{
					field[col+1][row] = 0;
				}
				links = 1+ carrot_helper(field,grid_size,lvl,col+1,row,'E',links,del);
			
			}
		}
		/*if no neighbor found,simply return the accumulated link.*/
		return links;
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
