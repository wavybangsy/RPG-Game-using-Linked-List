/*	Programmed by:	SILLONA, John Eugene J.	S11
	Description:	This script contains the generation of tiles in the game.
	Last Modified:	SEP-11-2021
	[Acknowledgements:	Prime Number Program: https://www.tutorialspoint.com/learn_c_by_examples/prime_number_program_in_c.htm
						Dereference pointer incrementing: https://stackoverflow.com/questions/3655728/increment-value-of-int-being-pointed-to-by-pointer]
*/

/*
    This function initializes a Tile Node to point all the structure pointers to null.
*/
Tile *initialize()
{
    return NULL;
}

/*
    This function allows the randomization of the number of doors inside a tile. Each door (excluding the door which which
    backtracks to the previous tile) has a 30% chance of spawning.

    @param (Tile *) currentTile refers to current structure present
*/
void generateDoors(Tile *currentTile)
{
    //initRandom();
    int MAXPROBABILITY = 10;    //CHANGE THIS TO 10 BEFORE SENDING IT OFF TO SIR
    int nNorthProb = getRandomNum(1, MAXPROBABILITY), nWestProb = getRandomNum(1, MAXPROBABILITY),
        nSouthProb = getRandomNum(1, MAXPROBABILITY), nEastProb = getRandomNum(1, MAXPROBABILITY);   //Probability of each door to spawn.

    //These switch statements determine the 3 in 10 chance the door spawns. 
    //Regardless if the backtrack door is set to false, it will be overwritten eventually in the main script.
    switch(nNorthProb)
    {
        case 1 ... 3:
            currentTile->TileContent.northExist = TRUE;
            break;
        default:
            currentTile->TileContent.northExist = FALSE;
            break;
    }
    switch(nWestProb)
    {
        case 1 ... 3:
            currentTile->TileContent.westExist = TRUE;
            break;
        default:
            currentTile->TileContent.westExist = FALSE;
            break;
    }
    switch(nSouthProb)
    {
        case 1 ... 3:
            currentTile->TileContent.southExist = TRUE;
            break;
        default:
            currentTile->TileContent.southExist = FALSE;
            break;
    }
    switch(nEastProb)
    {
        case 1 ... 3:
            currentTile->TileContent.eastExist = TRUE;
            break;
        default:
            currentTile->TileContent.eastExist = FALSE;
            break;
    }
}

/*
    This function displays the current tile. Inside the display features the following:
    1. A simple graphic to show the tile and its openings.
    2. 'X' which is displayed between the opening if the path/tile is unavailable.
    3. N, W, S, E is displayed so that it would be easy for players to navigate through the dungeon.

    @param (Tile *) currentTile refers to current structure present
*/
void showTile(Tile *currentTile)
{
    char cNorthBlock, cNorthShow, cWestBlock, cWestShow, cSouthBlock, cSouthShow, cEastBlock, cEastShow;
    if(currentTile->TileContent.northExist == TRUE)
    {
        cNorthBlock = ' ';
        cNorthShow = 'N';
    } 
    else 
    {
        cNorthBlock = 'X';
        cNorthShow = ' ';
    }

    if(currentTile->TileContent.westExist == TRUE)
    {
        cWestBlock = ' ';
        cWestShow = 'W';
    } 
    else 
    {
        cWestBlock = 'X';
        cWestShow = ' ';
    }

    if(currentTile->TileContent.southExist == TRUE)
    {
        cSouthBlock = ' ';
        cSouthShow = 'S';
    } 
    else 
    {
        cSouthBlock = 'X';
        cSouthShow = ' ';
    }

    if(currentTile->TileContent.eastExist == TRUE)
    {
        cEastBlock = ' ';
        cEastShow = 'E';
    } 
    else 
    {
        cEastBlock = 'X';
        cEastShow = ' ';
    }

    printf("o---| %c |---o\n", cNorthBlock);
	printf("|     %c     |\n", cNorthShow);
	printf("-           -\n");
	printf("%c %c       %c %c\n", cWestBlock, cWestShow, cEastShow, cEastBlock);
	printf("-           -\n");
	printf("|     %c     |\n", cSouthShow);
	printf("o---| %c |---o\n", cSouthBlock);
    printf("TILE NUMBER: %d\n", currentTile->TileContent.tileNum);
}

/*
    This function identifies if the given number is prime.


    @param (int) number refers to the given number
    @return (int)   TRUE if the given number is prime
                    FALSE if the given number is not prime
*/
int isPrime(int number)
{
    int i;
    for(i = 2; i < number; i++)
    {
        if((number % i) == 0)
            return FALSE;
    }
    return TRUE;
}

/*
	This function generates tiles if the direction chosen by the user points to NULL.
	However, if there is an existing tile, the game directs to that tile (Backtracking)

	@param (Tile **) currentTile refers to the tile that the game is currently in.
	@param (Tile **) newTile refers to the tile that is newly generated thru malloc
	@param (Tile **) previousTile refers to the last tile that the player was before they got in the current tile
	@param (char) cChoice refers to the input that the player chose (It can be either n, w, s, or e)
	@param (int *) nTileCount refers to the number of tiles that have been generated. This is used to identify what to spawn
*/
void generateTile(Tile **currentTile, Tile **newTile, Tile **previousTile, char cChoice, int *nTileCount)
{
    if((cChoice == 'N' || cChoice == 'n') && (*currentTile)->TileContent.northExist == TRUE)
    {
        if((*currentTile)->north == NULL)
        {
            (*nTileCount)++;
            *newTile = malloc(sizeof(Tile));
            
            (*newTile)->TileContent.tileNum = *nTileCount;

            if(*nTileCount % 10 != 0)
                generateDoors(*newTile);
            else
            {
                (*newTile)->TileContent.northExist = FALSE;
                (*newTile)->TileContent.westExist = FALSE;
                (*newTile)->TileContent.southExist = FALSE;
                (*newTile)->TileContent.eastExist = FALSE;
            }
            
            (*newTile)->north = NULL;
            (*newTile)->west = NULL;
            (*newTile)->east = NULL;

            (*newTile)->south = *currentTile;
            (*newTile)->TileContent.southExist = TRUE;

            *currentTile = *newTile;
        } 
        else 
        {
            *previousTile = *currentTile;
            *currentTile = (*currentTile)->north;
            (*currentTile)->south = *previousTile;
        }
        
    } 
    else if((cChoice == 'W' || cChoice == 'w') && (*currentTile)->TileContent.westExist == TRUE) 
    {
        if((*currentTile)->west == NULL)
        {
            (*nTileCount)++;
            *newTile = malloc(sizeof(Tile));

            (*newTile)->TileContent.tileNum = *nTileCount;
            if(*nTileCount % 10 != 0)
                generateDoors(*newTile);
            else
            {
                (*newTile)->TileContent.northExist = FALSE;
                (*newTile)->TileContent.westExist = FALSE;
                (*newTile)->TileContent.southExist = FALSE;
                (*newTile)->TileContent.eastExist = FALSE;
            }

            (*newTile)->north = NULL;
            (*newTile)->west = NULL;
            (*newTile)->south = NULL;

            (*newTile)->east = *currentTile;
            (*newTile)->TileContent.eastExist = TRUE;

            *currentTile = *newTile;
        } 
        else 
        {
            *previousTile = *currentTile;
            *currentTile = (*currentTile)->west;
            (*currentTile)->east = *previousTile;
        }
    } 
    else if((cChoice == 'S' || cChoice == 's') && (*currentTile)->TileContent.southExist == TRUE)
    {
        if((*currentTile)->south == NULL)
        {
            (*nTileCount)++;
            *newTile = malloc(sizeof(Tile));

            (*newTile)->TileContent.tileNum = *nTileCount;
            if(*nTileCount % 10 != 0)
                generateDoors(*newTile);
            else
            {
                (*newTile)->TileContent.northExist = FALSE;
                (*newTile)->TileContent.westExist = FALSE;
                (*newTile)->TileContent.southExist = FALSE;
                (*newTile)->TileContent.eastExist = FALSE;
            }

            (*newTile)->west = NULL;
            (*newTile)->south = NULL;
            (*newTile)->east = NULL;

            (*newTile)->north = *currentTile;
            (*newTile)->TileContent.northExist = TRUE;
            *currentTile = *newTile;
        } 
        else 
        {
            *previousTile = *currentTile;
            *currentTile = (*currentTile)->south;
            (*currentTile)->north = *previousTile;
        }
    } 
    else if((cChoice == 'E' || cChoice == 'e') && (*currentTile)->TileContent.eastExist == TRUE) 
    {
        if((*currentTile)->east == NULL)
        {
            (*nTileCount)++;

            *newTile = malloc(sizeof(Tile));

            (*newTile)->TileContent.tileNum = *nTileCount;
            if(*nTileCount % 10 != 0)
                generateDoors(*newTile);
            else
            {
                (*newTile)->TileContent.northExist = FALSE;
                (*newTile)->TileContent.westExist = FALSE;
                (*newTile)->TileContent.southExist = FALSE;
                (*newTile)->TileContent.eastExist = FALSE;
            }

            (*newTile)->north = NULL;
            (*newTile)->south = NULL;
            (*newTile)->east = NULL;

            (*newTile)->west = *currentTile;
            (*newTile)->TileContent.westExist = TRUE;
            *currentTile = *newTile;
        } 
        else 
        {
            *previousTile = *currentTile;
            *currentTile = (*currentTile)->east;
            (*currentTile)->west = *previousTile;
        }
    } 
    else if((*currentTile)->TileContent.northExist == FALSE || (*currentTile)->TileContent.westExist == FALSE 
                || (*currentTile)->TileContent.southExist == FALSE || (*currentTile)->TileContent.eastExist == FALSE)
        printf("The passage is blocked. Try another path\n");
}