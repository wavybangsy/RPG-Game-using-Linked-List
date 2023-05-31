/*	Programmed by:	CULALA, Mary Erika L.	S11
	Description:	This script allows the generation of potions and treasures.
	Last Modified:	SEP-14-2021
	[Acknowledgements:	]
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Player.c"

/* CHECKLIST

[/] - adjust to player struct
[/] - Potion Text
[/] - Treasure Text
*/

/*
    This function spawns a potion IF the void function 'spawnTreasorPotion' picks the potion
    @param (struct Player*) player accesses the stats of the player.
*/
void spawnPotion(struct Player *player)
{
    int nUpper = player->Stat.CON, nLower = floor(player->Stat.CON/2);
    int potionVal;
    int diff = 0;
    int prevHP = player->Stat.HP;

    potionVal = (rand() % (nUpper - nLower + 1)) + nLower;

    diff = player->Stat.CON - player->Stat.HP;

    if (potionVal > diff)
        player->Stat.HP += diff;
    else // (potionVal < diff)
        player->Stat.HP += potionVal;

    printf("-------- P O T I O N --------\n");
    printf("+ %s, you received a potion! +\n\n", player->playerName );
    printf("\tPlayer HP: %d\n", prevHP);
    printf("\tPotion Value: %d\n", potionVal);
    printf("\tCurrent HP: %d\n\n", player->Stat.HP);
   

}

/*
    This function spawns a treasure IF the void function 'spawnTreasorPotion' picks the treasure
    @param (struct Player*) player accesses the stats of the player.
*/
void spawnTreasure(struct Player *player)
{

    int nUpper = 1000, nLower = 500;
    int prevScore = player->score;
    int treasureVal;

    treasureVal = (rand() % (nUpper - nLower + 1)) + nLower;

    player->score += treasureVal;

    printf("+ %s, you found a treasure! +\n\n", player->playerName);
     printf("-------- T R E A S U R E --------\n");
    printf("\tPrevious player score: %d\n", prevScore);
    printf("\tCurrent player score: %d\n\n", player->score);  

}

/*
    This function determins whether the game should pick treasure or potion
    @param (struct Player*) player accesses the stats of the player.
*/
void spawnTreasOrPotion(struct Player *player)   // add this to main file: spawnTreasOrPotion(player) 
{
    int chance = (rand() % (10 - 1+ 1)) + 1; 

    switch(chance)
    {
        case 1 ... 5:
            spawnTreasure(player);
            break;
        case 6 ... 10:
            spawnPotion(player);
            break;
    }
}