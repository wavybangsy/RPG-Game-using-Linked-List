/*	Programmed by:	CULALA, Mary Erika L.	S11
	Description:	This script allows the generation of enemies
	Last Modified:	SEP-14-2021
	[Acknowledgements:	]
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include "Player.c"
//#include "EnemyNames.c"
#include "PotionTreas.c"  // #player.c is here
//#include "getAccessory.c"
//#include "AccessoryInit.c"


/* CHECKLIST

[/] - Enemy Data strucure
[/] - Enemy Stat structure
[/] - Enemy Stat Initialization
[/] - Enemy Name Random Gen
[/] - Spawn Enemy
[/] - Enemy Texts

[] - Integrate with Eugene's code (specifically User preferred enemey name text file)

FEEL free to add anything on checklist/code if you need to, Eugeneee. Or tell me para ma-change ko.  Thankiees :)
*/

typedef char stringEn30[31]; // string for enemyName

/*
    This function chooses the name for the enemy.
*/
int initEnemyName()
{
    int eL = 0, eU = 49,  emyN;
    int i;

    for (i = 0; i < 1; i++)
        emyN = (rand() % (eU - eL + 1)) + eL;

    return emyN;
}

/*
    Similar to getRandomNum
    @param (int) upper limit of range to randomly pick
    @param (int) lower limit of range to randomly pick
*/
int getRandom (int Upper,  int Lower)
{
    int value;

    value = (rand() % (Upper - Lower + 1)) + Lower; 

    return value;
}

/*
    This was used in checking if the enemies are created randomly
    @param (Enemy*) moves the stats to a Regular Enemy
    @param (Enemy*) moves the stats to a Strong Enemy
    @param (Enemy*) moves the stats to a MiniBoss
    @param (Enemy*) moves the stats to the Boss
    @param (struct Player) plr refers to the name of player
    @param (stringEn30) refers to the name of the enemy
*/
void enemyInit(Enemy *Regular, Enemy *Strong, Enemy *MiniBoss, Enemy *Boss, Enemy *Roaming, struct Player plr, stringEn30 enemyName[50])
{

    strcpy(Regular->emyName, enemyName[initEnemyName()]);       // Regular assignment
    Regular->emyName[strlen(Regular->emyName)- 1] = '\0';
    Regular->emyName[strlen(Regular->emyName)- 1] = '\0';
    Regular->emyStat.CON = getRandom(7,3);
    Regular->emyStat.HP = Regular->emyStat.CON;
    Regular->emyStat.ATK = getRandom(3,1);
    Regular->emyStat.DEF = getRandom(4,2);
    Regular->emyStat.SPD = getRandom(5,1);


    strcpy(Strong->emyName, enemyName[initEnemyName()]);        // Strong assignment
    Strong->emyName[strlen(Strong->emyName)- 1] = '\0';
    Strong->emyName[strlen(Strong->emyName)- 1] = '\0';
    Strong->emyStat.CON = getRandom(9,5);
    Strong->emyStat.HP = Strong->emyStat.CON;
    Strong->emyStat.ATK = getRandom(8,5);
    Strong->emyStat.DEF = getRandom(6,5);
    Strong->emyStat.SPD = getRandom(9,1); 

    strcpy(MiniBoss->emyName, enemyName[initEnemyName()]);      // Mini assignment
    MiniBoss->emyName[strlen(MiniBoss->emyName)- 1] = '\0';
    MiniBoss->emyName[strlen(MiniBoss->emyName)- 1] = '\0';
    MiniBoss->emyStat.CON = getRandom(20,15);
    MiniBoss->emyStat.HP = MiniBoss->emyStat.CON;
    MiniBoss->emyStat.ATK = getRandom(9,6);
    MiniBoss->emyStat.DEF = getRandom(7,6);
    MiniBoss->emyStat.SPD = getRandom(13,9); 

    strcpy(Boss->emyName, enemyName[initEnemyName()]);      // Boss assignment
    Boss->emyName[strlen(Boss->emyName)- 1] = '\0';
    Boss->emyName[strlen(Boss->emyName)- 1] = '\0';
    Boss->emyStat.CON = plr.Stat.CON;
    Boss->emyStat.HP = Boss->emyStat.CON;
    Boss->emyStat.ATK = (plr.Stat.ATK) - getRandom(4,2);
    Boss->emyStat.DEF = (plr.Stat.DEF) - getRandom(6,2);
    Boss->emyStat.SPD = getRandom(((plr.Stat.SPD)-2), ((plr.Stat.SPD)+2));

    strcpy(Roaming->emyName, enemyName[initEnemyName()]);       // Roaming assignment
    Roaming->emyName[strlen(Roaming->emyName)- 1] = '\0';
    Roaming->emyName[strlen(Roaming->emyName)- 1] = '\0';
    Roaming->emyStat.CON = getRandom(((plr.Stat.ATK)*2), plr.Stat.ATK);
    Roaming->emyStat.HP = Roaming->emyStat.CON;
    Roaming->emyStat.ATK = plr.Stat.CON;
    Roaming->emyStat.DEF = 0;
    Roaming->emyStat.SPD = getRandom(plr.Stat.SPD, ((plr.Stat.SPD)-1));
  
    if (Boss->emyStat.ATK <= 0)
        Boss->emyStat.ATK = 1;
    if (Boss->emyStat.DEF <= 0)
        Boss->emyStat.DEF = 1;
    if (Boss->emyStat.SPD <= 0)
        Boss->emyStat.SPD = 1;


    // checker

    printf("Regular: %s\n %d\n %d\n %d\n %d\n %d\n\n", Regular->emyName, Regular->emyStat.CON, Regular->emyStat.HP, Regular->emyStat.ATK, Regular->emyStat.DEF, Regular->emyStat.SPD);
    printf("Strong: %s\n %d\n %d\n %d\n %d\n %d\n\n", Strong->emyName, Strong->emyStat.CON, Strong->emyStat.HP, Strong->emyStat.ATK, Strong->emyStat.DEF, Strong->emyStat.SPD);
    printf("Mini: %s\n %d\n %d\n %d\n %d\n %d\n\n", MiniBoss->emyName, MiniBoss->emyStat.CON, MiniBoss->emyStat.HP, MiniBoss->emyStat.ATK, MiniBoss->emyStat.DEF, MiniBoss->emyStat.SPD);
    printf("Boss: %s\n %d\n %d\n %d\n %d\n %d\n\n", Boss->emyName, Boss->emyStat.CON, Boss->emyStat.HP, Boss->emyStat.ATK, Boss->emyStat.DEF, Boss->emyStat.SPD);
    printf("Roaming: %s\n %d\n %d\n %d\n %d\n %d\n\n", Roaming->emyName, Roaming->emyStat.CON, Roaming->emyStat.HP, Roaming->emyStat.ATK, Roaming->emyStat.DEF, Roaming->emyStat.SPD);

}

/*
    This spawns a Regular Enemy
    @param (Enemy*) enemy struct containing the stats
    @param (stringEn30) refers to the name of the enemy
*/
void spawnRegular(Enemy *Regular, stringEn30 enemyName[50])  // PINALITAN ko ng name Normal -> Regular
{

    strcpy(Regular->emyName, enemyName[initEnemyName()]);       // Regular assignment
    Regular->emyName[strlen(Regular->emyName)- 1] = '\0';
    Regular->emyName[strlen(Regular->emyName)- 1] = '\0';
    Regular->emyStat.CON = getRandom(7,3);
    Regular->emyStat.HP = Regular->emyStat.CON;
    Regular->emyStat.ATK = getRandom(3,1);
    Regular->emyStat.DEF = getRandom(4,2);
    Regular->emyStat.SPD = getRandom(5,1);
}

/*
    This spawns a Strong Enemy
    @param (Enemy*) enemy struct containing the stats
    @param (stringEn30) refers to the name of the enemy
*/
void spawnStrong(Enemy *Strong, stringEn30 enemyName[50])
{
    strcpy(Strong->emyName, enemyName[initEnemyName()]);        // Strong assignment
    Strong->emyName[strlen(Strong->emyName)- 1] = '\0';
    Strong->emyName[strlen(Strong->emyName)- 1] = '\0';
    Strong->emyStat.CON = getRandom(9,5);
    Strong->emyStat.HP = Strong->emyStat.CON;
    Strong->emyStat.ATK = getRandom(8,5);
    Strong->emyStat.DEF = getRandom(6,5);
    Strong->emyStat.SPD = getRandom(9,1); 
}

/*
    This spawns a Mini-boss
    @param (Enemy*) enemy struct containing the stats
    @param (stringEn30) refers to the name of the enemy
*/
void spawnMiniBoss(Enemy *MiniBoss, stringEn30 enemyName[50])
{
    strcpy(MiniBoss->emyName, enemyName[initEnemyName()]);      // Mini assignment
    MiniBoss->emyName[strlen(MiniBoss->emyName)- 1] = '\0';
    MiniBoss->emyName[strlen(MiniBoss->emyName)- 1] = '\0';
    MiniBoss->emyStat.CON = getRandom(20,15);
    MiniBoss->emyStat.HP = MiniBoss->emyStat.CON;
    MiniBoss->emyStat.ATK = getRandom(9,6);
    MiniBoss->emyStat.DEF = getRandom(7,6);
    MiniBoss->emyStat.SPD = getRandom(13,9);   
}

/*
    This spawns the boss
    @param (Enemy*) enemy struct containing the stats
    @param (stringEn30) refers to the name of the enemy
*/
void spawnBoss(Enemy *Boss, struct Player plr, stringEn30 enemyName[50])
{
    strcpy(Boss->emyName, enemyName[initEnemyName()]);      // Boss assignment
    Boss->emyName[strlen(Boss->emyName)- 1] = '\0';
    Boss->emyName[strlen(Boss->emyName)- 1] = '\0';
    Boss->emyStat.CON = plr.Stat.CON;
    Boss->emyStat.HP = Boss->emyStat.CON;
    Boss->emyStat.ATK = (plr.Stat.ATK) - getRandom(4,2);
    Boss->emyStat.DEF = (plr.Stat.DEF) - getRandom(6,2);
    Boss->emyStat.SPD = getRandom(((plr.Stat.SPD)-2), ((plr.Stat.SPD)+2));   
}

/*
    This spawns a Roaming Enemy
    @param (Enemy*) enemy struct containing the stats
    @param (stringEn30) refers to the name of the enemy
*/
void spawnRoaming(Enemy *Roaming,struct Player plr, stringEn30 enemyName[50])
{
    strcpy(Roaming->emyName, enemyName[initEnemyName()]);       // Roaming assignment
    Roaming->emyName[strlen(Roaming->emyName)- 1] = '\0';
    Roaming->emyName[strlen(Roaming->emyName)- 1] = '\0';
    Roaming->emyStat.CON = getRandom(((plr.Stat.ATK)*2), plr.Stat.ATK);
    Roaming->emyStat.HP = Roaming->emyStat.CON;
    Roaming->emyStat.ATK = plr.Stat.CON;
    Roaming->emyStat.DEF = 0;
    Roaming->emyStat.SPD = getRandom(plr.Stat.SPD, ((plr.Stat.SPD)-1));
}

/*
    This displays the stats of the enemy
    @param (String15) name of the player
    @param (Enemy*) refers to the enemy to access its stats
*/
void displayEnemStats(String15 name, Enemy *featuredEnem){
    printf("Beware, %s. There is a monster in this tile!\n", name);
    printf("You encountered \"%s\", a monster known for its profile:  \n\n", featuredEnem->emyName);
    
    printf("\t+-------- %s --------+\n", featuredEnem->emyName);
    printf("\t\t\t    CON: %d\n", featuredEnem->emyStat.CON);
    printf("\t\t\t    HP: %d\n", featuredEnem->emyStat.HP);
    printf("\t\t\t    ATK: %d\n", featuredEnem->emyStat.ATK);
    printf("\t\t\t    DEF: %d\n", featuredEnem->emyStat.DEF);
    printf("\t\t\t    SPD: %d\n\n", featuredEnem->emyStat.SPD);
}