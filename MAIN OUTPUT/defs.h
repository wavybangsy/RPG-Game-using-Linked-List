/*	Programmed by:  SILLONA, John Eugene J.	S11
	Description:	This contains the definition of shared elements for all the scripts of the project.
	Last Modified:	SEP-14-2021
*/

#define TRUE 1
#define FALSE 0

typedef char String30[31];
typedef char String15[16];

/*-------------E N E M Y  S T R U C T U R E S-------------*/
struct enemyStat{
    int CON;
    int HP;
    int ATK;
    int DEF;
    int SPD;
};

struct Enemies{     // Enemy Data

    String30 emyName;
    struct enemyStat emyStat;
};
typedef struct Enemies Enemy;

/*-------------T I L E  S T R U C T U R E S-------------*/
struct tileTag
{
    int tileNum;            //Refers to the number of the tile in relation to the linked list

	//These refer to the condition of each direction if they exist or not.
    int northExist;
    int westExist;
    int southExist;
    int eastExist;

    int xCoord;
    int yCoord;

    int interactionDone;    //Notifies if the object actions are done


    int enemyExists;        //Notifies if an enemy exists
    Enemy avoidedEnemy;     //a struct which will store the enemy if the player wishes not to engage
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

/*-------------F U N C T I O N  D E C L A R A T I O N S-------------*/
void initRandom();
int getRandomNum(int low, int high);