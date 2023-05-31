/*	Programmed by:	CULALA, Mary Erika L.	S11
					SILLONA, John Eugene J.	S11
	Description:	This is the main script of our Roguelike Dungeon Crawler RPG which implements all the learnings of GDPROG2, especially structures and linked list.
	Last Modified:	SEP-15-2021
	[Acknowledgements:	]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "defs.h"

//#include "Enemies.c"
//#include "EnemyNames.c"
#include "preGame.c"
#include "tileGeneration.c"
#include "getAccessory2.c"

/* DELETE
#define TRUE 1
#define FALSE 0

typedef char String30[31];
typedef char String15[16];

struct tileTag
{
    int tileNum;            //Refers to the number of the tile in relation to the linked list

	//These refer to the condition of each direction if they exist or not.
    int northExist;
    int westExist;
    int southExist;
    int eastExist;
};

struct tileNode
{
    struct tileTag TileContent;	//MAIN DATA

	//POINTERS
    struct tileNode *north;
    struct tileNode *west;
    struct tileNode *south;
    struct tileNode *east;
};

typedef struct tileNode Tile;
*/

/*
	This function was provided in page 11 of the Minimum Requirements of GDPROG2 Machine Project 2 Specification.
	This is needed for the pseudo-random number generator which is also provided in the specs.
*/
void initRandom()
{
	time_t random_seed;
	random_seed = time(NULL);
	srand(random_seed);
}

/*
	This function was also provided in page 11 of the Minimum Requirements of GDPROG2 Machine Project 2 Specification.
	This picks a random number from a specific range.
	@param (int) low refers to the lowest possible number in the range
	@param (int) high refers to the highest possible number in the range
	@return (int) randomValue refers to the number which was randomly picked by the pseudo-random number generator.
*/
int getRandomNum(int low, int high)
{
	int randomValue;
	
	randomValue = low + rand() % (high - low + 1);
	return randomValue;
}

int main()
{
	/*
		-------------P R E G A M E-------------
		a. Compiles the game
		b. Sets name of the player and the text files containing names
	*/
	initRandom();
	int acListAdd, enListAdd;
	String15 name;
	FILE *fData;

	//ALLOCATE MEMORY FOR STRING ARRAY NAMES
	String30 *accessoryList;
	String30 *enemyList;
	
	highScoreData();
	getName(name);
	
	getFileInfo(name, &accessoryList, &enemyList, &acListAdd, &enListAdd);
	/*
		-------------G A M E  I N I T I A L I Z A T I O N-------------
		a. initializes the start tile and the player
	*/

	//STARTING TILE INSTANCIATION

	int nTileCount = 1;     	//Refers to how many tiles have been generated
    int continueGame = TRUE;	//Checks if the conditions suffice for the game to continue
	int playerWin = FALSE;
    int tileExceed20 = FALSE;	//Checks if the number of tiles generated is 20.
	int check = 0;
	int xCount = 0;
	int yCount = 0;

	char cChoice;				//Input of player

	Tile *tileHead, *newTile, *previousTile, *currentTile;
	/*
		RUNDOWN:
		tileHead - head of the linked list
		newTile - node generated thru malloc
		previousTile - used for backtracking
		currentTile - current tile that the player is in
	*/
    tileHead = initialize();
    newTile = malloc(sizeof(Tile));

	//Since this is the starting tile, its the first tile. Therefore, all the directions are available.
    newTile->TileContent.tileNum = nTileCount;
    newTile->TileContent.northExist = TRUE;
    newTile->TileContent.westExist = TRUE;
    newTile->TileContent.southExist = TRUE;
    newTile->TileContent.eastExist = TRUE;
	newTile->TileContent.interactionDone = TRUE;

	newTile->TileContent.xCoord = xCount;
	newTile->TileContent.yCoord = yCount;

	//Assign the new tile to the head of the linked list
    tileHead = newTile;
    newTile->north = NULL;
    newTile->west = NULL;
    newTile->south = NULL;
    newTile->east = NULL;

    currentTile = tileHead;

	//PLAYER INSTANTIATION
	struct accessory *currentAccs = malloc(sizeof(struct accessory)* 5);

	struct Player player;
	player = playerInit(name);

	//int accCount = 0;

	//ENEMY INSTANTIATION
	Enemy Regular, Strong, MiniBoss, Boss, Roaming;
	//Enemy *backTrack = malloc(sizeof(Enemy));
	
	/*
		-------------N E X T  T I L E-------------
		a. checks if the pointer chosen is pointing to NULL or to an existing tile
		b. generates tiles, points pointer of the new tile to the previous tile
		c. instantiates objects
	*/
	while(continueGame == TRUE && playerWin != TRUE)
	{
		printf("\n================================================================================================================\n\n");
		int nRoamingChance;
		if(tileExceed20 == TRUE && isPrime(currentTile->TileContent.tileNum))
		{
			printf("Trap Function Here\n");
		}
		if(currentTile->TileContent.tileNum % 10 == 0)
		{
			printf("A  D E A D - E N D!\nBe wary of your surroundings!\n\n");
		}
		if(currentTile->TileContent.interactionDone != TRUE)
		{
			if(currentTile->TileContent.tileNum % 2 == 0 && currentTile->TileContent.tileNum % 10 != 0)
			{
				//printf("Potion here\n");
				spawnTreasOrPotion(&player);
				currentTile->TileContent.interactionDone = TRUE;
			}

			if(currentTile->TileContent.tileNum % 3 == 0 && currentTile->TileContent.tileNum % 10 != 0)
			{
				getAccessory(accessoryList, currentAccs, &player);
				currentTile->TileContent.interactionDone = TRUE;
				//printf("Accessory here\n");
			}
			if(currentTile->TileContent.tileNum % 4 == 0 && currentTile->TileContent.tileNum % 10 != 0)
			{
				//printf("Spawn Regular Enemy\n");
				if (currentTile->TileContent.enemyExists == TRUE)
					combat(&currentTile->TileContent.avoidedEnemy, &currentTile, &player, name, &check);
				else{
					spawnRegular(&Regular, enemyList);
					combat(&Regular, &currentTile, &player, name, &check);
				}
			}
			if(currentTile->TileContent.tileNum % 5 == 0 && currentTile->TileContent.tileNum != 20)
			{
				//printf("Spawn Strong Enemy\n");
				if (currentTile->TileContent.enemyExists == TRUE)
					combat(&currentTile->TileContent.avoidedEnemy, &currentTile, &player, name, &check);
				else{
					spawnStrong(&Strong, enemyList);
					combat(&Strong, &currentTile, &player, name, &check);
				}
			}
			if(currentTile->TileContent.tileNum % 14 == 0)
			{
				//printf("Miniboss\n");
				
				if (currentTile->TileContent.enemyExists == TRUE)
					combat(&currentTile->TileContent.avoidedEnemy, &currentTile, &player, name, &check);
				else{
					spawnMiniBoss(&MiniBoss, enemyList);
					combat(&MiniBoss, &currentTile, &player, name, &check);
				}
			}
			if(currentTile->TileContent.tileNum == 20)
			{
				//printf("Bossing");
				
				if (currentTile->TileContent.enemyExists == TRUE)
					combat(&currentTile->TileContent.avoidedEnemy, &currentTile, &player, name, &check);
				else{
					spawnBoss(&Boss, player, enemyList);
					combat(&Boss, &currentTile, &player, name, &check);
				}
				if(check == 0)
					playerWin = TRUE;
			}
			if(tileExceed20 == TRUE)
			{
				nRoamingChance = getRandomNum(1, 20);
				switch(nRoamingChance)
				{
					case 1:
						if (currentTile->TileContent.enemyExists == TRUE)
							combat(&currentTile->TileContent.avoidedEnemy, &currentTile, &player, name, &check);
						else{
							spawnRoaming(&Roaming, player, enemyList);
							combat(&Boss, &currentTile, &player, name, &check);
						}
						break;
				}
			}
		}
		if(check == 0 && playerWin != TRUE){
			continueGame = TRUE;
			showStats(&player);
			//printf("TILE NUMBER: %d\n", currentTile->TileContent.tileNum);  //FOR CHECKING PURPOSES
			showTile(currentTile);
			printf("Where do you want to go? You can only pick either the following.\n");
			printf("DIRECTION: ");
			scanf(" %c", &cChoice);
			generateTile(&currentTile, &newTile, &previousTile, cChoice, &nTileCount);
			if(nTileCount == 20)
				tileExceed20 = TRUE;
		}		
		else if(check == 1)			//IF PLAYER DEAD
			continueGame = FALSE;
		
	}

	printf("\n================================================================================================================\n\n");

	if(playerWin == FALSE){
		printf("G A M E  O V E R\nYou have been killed.\n\n");
	}
	else
		printf("V I C T O R I O U S\nYou defeated the boss!\n\n");
	printf("POINTS: %d\n", player.score);
	printf("ITEMS COLLECTED:\n");
	int i = 0;
	for (i = 0; i < player.accCount; i++)  // only 5 items are allowed
		printf("%s\n", player.accsList[i]);
	
	fData = fopen("HighScore.dat", "ab");
    fwrite(&player, sizeof(struct Player), 1, fData);
    fclose(fData);
			
	
	//FREE ELEMENTS
	free(accessoryList);
	free(enemyList);
	return 0;
}
