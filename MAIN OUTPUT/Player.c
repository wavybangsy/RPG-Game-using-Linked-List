/*	Programmed by:	CULALA, Mary Erika L.	S11
	Description:	This initializes the player.
	Last Modified:	SEP-14-2021
	[Acknowledgements:	]
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* CHECKLIST

[/] - Player Data structure
[/] - Player Stat structure
[/] - Player Initialization

[] - Integreate/adjust with Eugene's code (specific: User input username)

FEEL free to add anything on checklist/code if you need to, Eugeneee. Or tell me para ma-change ko.  Thankiees :)
*/

typedef char string15[16];

typedef struct playerStats
{
    int CON;
    int HP;
    int ATK;
    int DEF;
    int SPD;
} plrStat;

struct accessory{
	char statFocus[4];
	int value;	
	char rootName[31];
	char prefix[9];
	char suffix[14];
	char fullName[52];
};

struct Player 
{
    string15 playerName;
    int score;
    int accCount;
    struct accessory accessory;
    char accsList[5][51];
    struct playerStats Stat;
};


struct Player playerInit(String15 name)  //string15 inputName <-- add this too as parameter.
{
    struct Player str;

    strcpy(str.playerName, name);  //remove comment later on when combined with Eugene's code.
    str.Stat.CON = 10;
    str.Stat.HP = str.Stat.CON;
    str.Stat.ATK = 2;
    str.Stat.DEF = 2;
    str.Stat.SPD = 3;
    str.score =  0;
    str.accCount = 0;

    char ans[4];
    int points  =  10;
    printf("You are given 10 stat points to distribute to your current stat.\n\n");
    printf("CON: %d\n", str.Stat.CON);
    printf("ATK: %d\n", str.Stat.ATK);
    printf("DEF: %d\n", str.Stat.DEF);
    printf("SPD: %d\n\n", str.Stat.SPD);

    int userPoint = 0;

    while ( points > 0)
    {
        printf("Type the name of stat(e.g \"CON\"): ");
        scanf("%s", ans);
        fflush(stdin);

    if (strcmp(ans, "CON") == 0 || strcmp(ans, "con") == 0)
    {
        printf("Add how many points to CON? ");
        scanf("%d", &userPoint);
        str.Stat.CON += userPoint;
        str.Stat.HP = str.Stat.CON;
        printf("\n\nYou have added %d to CON!\n", userPoint);
        points -= userPoint;
        printf("\n\nYou still have remaining %d to distribute\n\n", points);
        userPoint = 0;  
    }
    else if (strcmp(ans, "ATK") == 0 || strcmp(ans, "atk") == 0)
    {
        printf("Add how many points to ATK? ");
        scanf("%d", &userPoint);
        str.Stat.ATK += userPoint;
        printf("\n\nYou have added %d to ATK!\n", userPoint);
        points -= userPoint;
        printf("You still have remaining %d to distribute\n\n", points);
        userPoint = 0;  
    }
    else if (strcmp(ans, "DEF") == 0 || strcmp(ans, "def") == 0)
    {
        printf("Add how many points to DEF? ");
        scanf("%d", &userPoint);
        str.Stat.DEF += userPoint;
        printf("\n\nYou have added %d to DEF!\n", userPoint);
        points -= userPoint;
        printf("You still have remaining %d to distribute\n\n", points);
        userPoint = 0;  
    }
    else if (strcmp(ans, "SPD") == 0 || strcmp(ans, "spd") == 0)
    {
        printf("Add how many points to SPD? ");
        scanf("%d", &userPoint);
        str.Stat.SPD += userPoint;
        printf("\n\nYou have added %d to SPD!\n", userPoint);
        points -= userPoint;
        printf("You still have remaining %d to distribute\n\n", points);
        userPoint = 0;  
    }
    }

    return str;
};

void showStats(struct Player *player){
    printf("HEALTH: %d/%d\n", player->Stat.HP, player->Stat.CON);
    printf("ATK: %d\n", player->Stat.ATK);
    printf("DEF: %d\n", player->Stat.DEF);
    printf("SPD: %d\n", player->Stat.SPD);
    printf("SCORE: %d\n\n", player->score);
}

/*
int main(){

    struct Player player;

    player = playerInit();

    //checker
    printf("%d\n",player.Stat.CON);
    printf("%d\n",player.Stat.HP);
    printf("%d\n",player.Stat.ATK);
    printf("%d\n",player.Stat.DEF);
    printf("%d",player.Stat.SPD);


    return 0;

}*/