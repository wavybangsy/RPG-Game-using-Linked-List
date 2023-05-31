/*	Programmed by: 	CULALA, Mary Erika L.	S11
					SILLONA, John Eugene J.	S11
	Description: This function creates an accessory.
	Last Modified: AUG-21-2021
	[Acknowledgements: 	Switch Range: https://www.geeksforgeeks.org/using-range-switch-case-cc/
						File Reading: https://www.youtube.com/watch?v=8nIilb2kiSU	
						Remove Trailing Line: https://www.codegrepper.com/code-examples/c/how+to+remove+%5Cn+from+a+string+c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "defs.h"
#include "EnemyNames.c"
#include "Enemies.c" // contains PotionTreas.c  which contains Player.c

typedef char String15[16];
typedef char String30[31];
typedef char String51[52];


/* 	
	Function for the spawning of accessories
	@param (char/String30) nameList is an array that contains the accessories names from the opened file.
	@param (struct/accessory) accs is a dynamic list that will store the latest accessories equiped
	@param (int) tileCount is the current tile that the player is in
	@param (struct/ Player) play is a structure variable which holds player's records
	@param (int) accCount counts the times the player has equiped an accessory
	@return (void) does not return anything.
*/
void getAccessory(String30 nameList[50], struct accessory *accs, struct Player *play)
{
	//struct accessory acc;

	int ans = 0;
	
	initRandom();
	
	strcpy(play->accessory.rootName, nameList[getRandomNum(0, 49)]);
	play->accessory.value = getRandomNum(2, 7);
	
	switch(play->accessory.value){
		case 2 ... 3:
			strcpy(play->accessory.prefix, "Lesser ");
			break;
		case 5 ... 7:
			strcpy(play->accessory.prefix, "Greater ");
			break;
	}
	switch(getRandomNum(1, 10)){
		case 1 ... 2:	//CON ACCESSORY
			strcpy(play->accessory.statFocus, "CON");
			strcpy(play->accessory.suffix, " of Vitality");
			play->Stat.CON += play->accessory.value;
			break;
		case 3 ... 4:	//SPD ACCESSORY
			strcpy(play->accessory.statFocus, "SPD");
			strcpy(play->accessory.suffix, " of Lightning");
            play->Stat.SPD += play->accessory.value;
			break;
		case 5 ... 7:	//ATK ACCESSORY
			strcpy(play->accessory.statFocus, "ATK");
			strcpy(play->accessory.suffix, " of Bravery");
			play->Stat.ATK += play->accessory.value;
			break;
		case 8 ... 10:	//DEF ACCESSORY
			strcpy(play->accessory.statFocus, "DEF");
			strcpy(play->accessory.suffix, " of Courage");
			play->Stat.DEF += play->accessory.value;
			break;
	}
	
	//CONCATENATE STRINGS INTO ONE
	if(play->accessory.value <= 3 || play->accessory.value > 5 )
		strcpy(play->accessory.fullName, play->accessory.prefix);
	else
		strcpy(play->accessory.fullName, "\0");
	strcat(play->accessory.fullName, play->accessory.rootName);
	//play->accessory.fullName[strlen(play->accessory.fullName)- 1] = '\0';
	strcat(play->accessory.fullName, play->accessory.suffix);
	
	//DISPLAY PLAYER ABOUT THE ACCESSORY
	printf("\nYOU GOT AN ACCESSORY!\n");
	printf("%s\n", play->accessory.fullName);
	printf("This accessory boosts %s by %d points.\n", play->accessory.statFocus, play->accessory.value);

	//COPY TO ACCESSORY LIST FOR HIGH SCORE
	if (play->accCount < 5)
	{
		printf("Do you want to equip the accessory or not?\nYes - 1, No - other digit: ");  // CHANGE
		scanf("%d", &ans); //CHANGE
		fflush(stdin); // CHANGE

		if (ans == 1) // CHANGE
		{

		strcpy(play->accsList[play->accCount], play->accessory.fullName);  //CHANGE HERE IN THE "play->accCount"
		strcpy(accs[play->accCount].fullName, play->accessory.fullName);
		accs[play->accCount].value = play->accessory.value;
		strcpy(accs[play->accCount].statFocus, play->accessory.statFocus);

		play->accCount = play->accCount + 1;
		printf("\nAccessory Acquired!\n\n");

		} //CHANGE
		else
			printf("\nAccessory discarded.\n");
	}
	else if (play->accCount ==  5)
	{
		ans = 0; // initialize again // CHANGE
		printf("Only 5 accessories are allowed. Do you want to switch this accessory to another one? Yes - 1/ No - any digit: ");
		scanf("%d", &ans);
		fflush(stdin);

		if (ans == 1)
		{
			ans = 0;
			int k;
			for (k = 0; k < 5; k++) 
				printf("# %d: %s\n", (k+1), play->accsList[k]);

			printf("Are you sure you want to switch? Yes - 1, No - Any digit: ");
			scanf("%d", &ans);
			fflush(stdin);

			int j = 0;

			if (ans == 1)
			{	
				ans = 0;
			
				printf("Type the number of accessory you want to switch: ");
				scanf("%d", &ans);
				fflush(stdin);

				j = ans;

				printf("\n");
				strcpy(accs[ans-1].fullName, play->accessory.fullName);
				
				if (strcmp(accs[ans-1].statFocus, "CON") == 0)
				{
					if(strcmp(play->accessory.statFocus, "CON") == 0)
					{
						printf("Removed %d points from CON: %d\n", accs[ans-1].value, ((play->Stat.CON) - (play->accessory.value)));
						play->Stat.CON -= accs[ans-1].value;

						if (play->Stat.CON < play->Stat.HP)  //ADDED
							play->Stat.HP = play->Stat.HP - (play->Stat.HP -  play->Stat.CON); //ADDED
					}
					else{
						printf("Removed %d points from CON: %d\n", accs[ans-1].value, play->Stat.CON);
						play->Stat.CON -= accs[ans-1].value;

						if (play->Stat.CON < play->Stat.HP) // ADDED
							play->Stat.HP = play->Stat.HP - (play->Stat.HP -  play->Stat.CON); ///ADDED
					}

					
				}
					
				else if (strcmp(accs[ans-1].statFocus, "ATK")== 0)
				{
					if(strcmp(play->accessory.statFocus, "ATK") == 0)
					{
						printf("Removed %d points from ATK: %d\n", accs[ans-1].value, ((play->Stat.ATK) - (play->accessory.value)));
						play->Stat.ATK -= accs[ans-1].value;

						if (play->Stat.ATK < 0) //ADDED tHROUGH OUT THE STATS [lahat ng STATS may ganito nang if-statement. See below]
							play->Stat.ATK = 0; //added ^
					}
					else{
						printf("Removed %d points from ATK: %d\n", accs[ans-1].value, play->Stat.ATK);
						play->Stat.ATK -= accs[ans-1].value;

						if (play->Stat.ATK < 0)
							play->Stat.ATK = 0;
					}
				}
				else if (strcmp(accs[ans-1].statFocus, "SPD")== 0)
				{
					if(strcmp(play->accessory.statFocus, "SPD") == 0)
					{
						printf("Removed %d points from SPD: %d\n", accs[ans-1].value, ((play->Stat.SPD) - (play->accessory.value)));
						play->Stat.SPD -= accs[ans-1].value;

						if (play->Stat.SPD < 0)
							play->Stat.SPD = 0;
					}
					else{
						printf("Removed %d points from SPD: %d\n", accs[ans-1].value, play->Stat.SPD);
						play->Stat.SPD -= accs[ans-1].value;

						if (play->Stat.SPD < 0)
							play->Stat.SPD = 0;
					}
				}
				else if (strcmp(accs[ans-1].statFocus, "DEF")== 0)
				{
					if(strcmp(play->accessory.statFocus, "DEF") == 0)
					{
						printf("Removed %d points from DEF: %d\n", accs[ans-1].value, ((play->Stat.CON) - (play->accessory.value)));
						play->Stat.DEF -= accs[ans-1].value;

						if (play->Stat.DEF < 0)
							play->Stat.DEF = 0;
					}
					else{
						printf("Removed %d points from DEF: %d\n", accs[ans-1].value, play->Stat.DEF);
						play->Stat.DEF -= accs[ans-1].value;

						if (play->Stat.DEF < 0)
							play->Stat.DEF = 0;
					}
				}


				strcpy(accs[j-1].statFocus, play->accessory.statFocus);
				accs[j-1].value = play->accessory.value;

				printf("Successfully equiped %s! It has added %d to your %s\n\n", accs[j-1].fullName, accs[j-1].value, accs[j-1].statFocus);
			}

			// STORE the latest equiped accessories to player's Accessory List 
			int i = 0;
			for (i = 0; i < 5; i++)
				strcpy(play->accsList[i], accs[i].fullName);	
		}

	}
}

void accessoryInit(FILE *fAcc, String30 name, String30 nameList[50])
{
    int i = 0;

    if((fAcc = fopen("defAccessoryName.txt", "r")) == NULL){
		printf("No such file exists. Terminating program");
		exit(1);
	}
    else 
    	while(!feof(fAcc) && i < 50)
        {
		fgets(name, 31, fAcc);
		name[strcspn(name, "\n")] = 0;
		strcpy(nameList[i], name);
		i++;
        }
    
	fclose(fAcc);
}

/* 	
	Function for sorting players in High Score table
	@param (Player) New is a structure dynamic list which holds players data from the opened file
	@param (int) num is the number of elements in the file being read
	@return (void) does not return anything. Just sorts
*/
void Sort(struct Player *New, int num)
{
    struct Player temp;
    int i = 0;
	int j = 0;

    for(i=0; i<num; i++)
    {
        for(j=0; j<num-1-i; j++)
        {
            if(New[j].score < New[j+1].score)
            {
                //swap 
                temp = New[j+1];
                New[j+1] = New[j];
                New[j] = temp;
            }
        }
    }

}

/*
	Displays players' records
	@param (struct/ Player) New is a structure dynamic list which holds players data from the opened file
	@return (void) does not return anything. Just displays
*/
void checkPlayers (struct Player *New, int countRec)  
{
    int ans = 0;
    int i = 0; 
    int checker = 0;

    printf("Do you want to see player data? Yes - 1 / No - any number ");  //CHANGE
    scanf(" %d", &ans); //CHANGE
    fflush(stdin); //CHANGE

	if (ans == 1)  //CHANGE
	{
		ans = 0; //CHANGE
		while (checker != 1) 
		{
			if (checker == 2)  //CHANGE
				for (i = 0; i < (countRec - (countRec - 10)); i++)  //CHANGE
					printf("# %d:\t%15s %10d\n", (i+1), New[i].playerName, New[i].score);  //CHANGE

			checker = 2; //CHANGE
			printf("Pick number: ");
			scanf(" %d", &ans);
			fflush(stdin);

			i = 0;
			if (ans > 0 && ans < 11) //CHANGE whole
			{
				printf("LIST %d", New[ans-1].accCount);   // CHECKER LANG

				printf("\nName %s | ",New[ans-1].playerName);
				printf("%d\n\n", New[ans-1].score);
				printf("Acessories acquired:\n");

				for (i = 0; i < New[ans-1].accCount; i++)
					printf("%s\n", New[ans-1].accsList[i]);

				printf("\nPlayer Stats:\nCON: %d\nHP: %d\nATK: %d\nDEF: %d\nSPD: %d\n", New[ans-1].Stat.CON,  New[ans-1].Stat.HP,  New[ans-1].Stat.ATK,  New[ans-1].Stat.DEF,  New[ans-1].Stat.SPD);
			}  // hanggang dito

			printf("Do you want to check another player's data or continue to game? 1 - check / Any digit - Continue to game\n");
			scanf("%d", &ans);
			if (ans != 1){
				checker = 1;
				fflush(stdin);
			}
		}
	}
}

/* 
	Displays the High Score Table
	@param nothing
	@return (void) because it does not return anything. This function  just displays
*/

void highScoreData()
{

    struct Player *New = malloc(sizeof(struct Player)*100);
    FILE *fData;
    int i = 0, k = 0;
    //int ans = 0;

    fData = fopen("HighScore.dat", "rb");

         while ((fread(&*(New + i), sizeof(struct Player), 1, fData))!= 0)
        {
            i++;
            Sort(New, i);
        }
	
    fclose(fData);

    printf("RANK\t    NAME\t     SCORE\n\n");    // CHANGE HERE - spacing

	if (i <= 10 && i >= 0)
	{
    	for(k = 0; k < i ; k++)
    		printf("# %d:\t%15s %10d\n", (k+1), New[k].playerName, New[k].score); // CHANGE HERE
	}

	else if (i > 10)
	{
		for (k = 0; k < 10; k++)
			printf("# %d:\t%15s %10d\n", (k+1), New[k].playerName, New[k].score); //CHANGE
	}
	

	if ( i > 0)   // PREVENTS from printing when high score has no data yet. //CHANGE
        checkPlayers(New, i);  //CHANGE


}

/* 	
	Function for Combat
	@param (Enemy) enemyType holds the specific enemy structure
	@param (Player) plr holds the data of player in structure
	@return (int) returns 1 if player is defeated, 0 if enemy is defeated
*/
//NEW FUNCTION FOR COMBAT
void combat (Enemy *enemyType, Tile **currentTile,  struct Player *plr, String15 name, int *check)
{
	int ans = 0;
	int plrDamage = 0, emyDamage = 0, i = 0;
	*check = 0;
	displayEnemStats(name, enemyType);
	printf("Do you want to fight %s?\nYes - 1, No - any digit: ", enemyType->emyName);
	fflush(stdin);
	scanf("%d", &ans);
	fflush(stdin);

	if (ans == 1)
	{

		if (plr->Stat.SPD > enemyType->emyStat.SPD)
		{
			printf("You will attack first!\n");

			while (plr->Stat.HP != 0 && enemyType->emyStat.HP != 0)
			{
				plrDamage = plr->Stat.ATK - enemyType->emyStat.DEF;
				emyDamage = enemyType->emyStat.ATK - plr->Stat.DEF;

				if (plrDamage < 1)
					plrDamage = 1;
				if (emyDamage < 1)
					emyDamage = 1;

				if (plr->Stat.HP > 0)
				{
					if (i == 0)
						printf("You have dealt a damage.\n");
					else
						printf("Your turn to attack\n");

					enemyType->emyStat.HP -= plrDamage;

						if (enemyType->emyStat.HP <=  0)
						{
							enemyType->emyStat.HP = 0;
							*check = 0;
						}

						printf("- %d to %s's HP | Enemy's remaining HP: %d\n\n", plrDamage, enemyType->emyName, enemyType->emyStat.HP);

						printf("press any key to continue\n");
						getchar();
				}

				if (enemyType->emyStat.HP > 0)
				{
					printf("%s's turn to attack.\n", enemyType->emyName);
					plr->Stat.HP -= emyDamage;

						if (plr->Stat.HP <= 0)
						{
							plr->Stat.HP = 0;
							*check = 1;
						}


						printf("- %d to your HP | Your remaining HP: %d\n\n", emyDamage, plr->Stat.HP);
								
						printf("press any key to continue\n");
						getchar();
				}
				i++;
			}
			if (*check == 1)
				printf("You have lost!\n\n");
				
			if (*check == 0)
				printf("%s has lost\n\n", enemyType->emyName);

			//return check;
		}
		else if (plr->Stat.SPD < enemyType->emyStat.SPD)
		{
			printf("%s attacks first!\n", enemyType->emyName);
			i = 0;

			while (plr->Stat.HP != 0 && enemyType->emyStat.HP != 0)
			{
				plrDamage = plr->Stat.ATK - enemyType->emyStat.DEF;
				emyDamage = enemyType->emyStat.ATK - plr->Stat.DEF;

				if (plrDamage < 1)
					plrDamage = 1;
				if (emyDamage < 1)
					emyDamage = 1;

				if (enemyType->emyStat.HP > 0)
				{
					if (i == 0)
						printf("%s has dealt a damage!\n", enemyType->emyName);
					else
						printf("%s's turn to attack\n",enemyType->emyName);

					plr->Stat.HP -= emyDamage;

						if (plr->Stat.HP <= 0)
						{
							plr->Stat.HP = 0;
							*check = 1;
						}

					printf("- %d to your HP | Your remaining HP: %d\n\n", emyDamage, plr->Stat.HP);
								
					printf("press any key to continue\n");
					getchar();
				}

				if (plr->Stat.HP > 0)
				{
					printf("Your turn to attack.\n");
					enemyType->emyStat.HP -= plrDamage;

						if (enemyType->emyStat.HP <=  0)
						{
							enemyType->emyStat.HP = 0;
							*check = 0;
						}
					printf("- %d to %s's HP | Enemy's remaining HP: %d\n\n", plrDamage, enemyType->emyName, enemyType->emyStat.HP);

					printf("press any key to continue\n");
					getchar();
				}
				i++;
			}
			if (*check == 1)
				printf("You have lost!\n\n");
			if (*check == 0)
				printf("%s has lost\n\n", enemyType->emyName);

			//return check;
		}
		//if (*status == 1)
		//{
		//	*status = 0; // because nafight na, back to 0 na. 
		//}
		(*currentTile)->TileContent.enemyExists = TRUE;
		(*currentTile)->TileContent.interactionDone = TRUE;
	}
	else // STORES THE ENEMY DATA TO ANOTHER STRUCTURE para if nag backtrack same stats and name ng enemy. 
	{
		(*currentTile)->TileContent.avoidedEnemy = *enemyType;
		(*currentTile)->TileContent.enemyExists = TRUE;
		printf("%s\n", (*currentTile)->TileContent.avoidedEnemy.emyName); //  checker if nag store
		printf("%d", (*currentTile)->TileContent.avoidedEnemy.emyStat.DEF);
		(*currentTile)->TileContent.interactionDone = FALSE;
		//*status = 1;	//Refers to an enemy that hasn't been engaged
	}

	//return check;

}
