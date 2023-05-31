/*	Programmed by:	SILLONA, John Eugene J.	S11
	Description:	This script prepares the game by asking the name of the player as well as name generation.
	Last Modified:	SEP-12-2021
	[Acknowledgements:	Remove Trailing Line: https://www.codegrepper.com/code-examples/c/how+to+remove+%5Cn+from+a+string+c
						File Reading: https://www.youtube.com/watch?v=8nIilb2kiSU]
*/

/*	
	This function asks for the name of the player
	@return (String15) nameInput is where the input gets pasted.
*/
void getName(String15 nameInput){
	printf("Please type your name: ");
	fgets(nameInput, 15, stdin);
	nameInput[strcspn(nameInput, "\n")] = 0;	//This just removes the trailing line from the input
	fflush(stdin);
}

/*	
	This function copies all the contents of a file to a string array
	@param (String15) tempName refers to the name of the player
	@return (String30) all the strings from the file containing Accessory Names
	@return (String30) all the strings from the file containing Enemy Name
*/
void getFileInfo(String15 tempName, String30 **temp1, String30 **temp2, int *temp1Add, int *temp2Add){
	*temp1 = malloc(sizeof(String30) * 50);
	*temp2 = malloc(sizeof(String30) * 50);
	
	//CHECK IF THE ALLOCATION IS SUCCESSFUL
	if(*temp1== NULL || *temp2 == NULL)
	{
		printf("\nWhoops! Something looks wrong!\n");
		printf("The program couldn't allocate enough memory.\n");
		printf("Terminating program!");
		exit(1);
	}
	
	//INDICES FOR LOOPS
	int i = 0, j = 0, k = 0, l = 0;
	
	String30 sTemp;
	
	//MAIN FILE DECLARATION
	FILE *acc;
	FILE *enem;	
	
	int nChoice;	//User input if they want to add name or stick with default
	
	//CHECK IF THE FILES EXIST IN DIRECTORY OF .C FILE
	if((acc = fopen("ArtifactList.txt", "a")) == NULL || (enem = fopen("MonsterList.txt", "a")) == NULL)
	{
		printf("\nWhoops! Something looks wrong!\n");
		printf("Please ensure that \"ArtifactList.txt\" is in the same folder as the .c file.\n");
		printf("Terminating program!");
		exit(1);
	}		
	
	//ASK PLAYER IF THEY WANT TO ADD CUSTOM NAMES TO THE DEFAULT FILES
	printf("Hello, %s! Do you want to add custom names for accessories and enemies?\n", tempName);
	printf("1. Sure!\n2. No thanks!\n");
	printf("Input your answer here: ");
	scanf("%d", &nChoice);
	
	if(nChoice == 1)
	{
		//ACCESSORY
		printf("Input names for ACCESSORIES (MAXIMUM 30 CHARACTERS).\nIf you do not want to add names or you're done adding names, type \"done\" or \"DONE\"\n");
		do
		{
			fflush(stdin);
			printf("INPUT ITEM %d: ", k + 1);
			fgets(sTemp, 32, stdin); // need ata this 32 para sa '\0' at \n
			sTemp[strcspn(sTemp, "\n")] = 0;	//removes the trailing line after fgets
			if(strcmp(sTemp, "done") != 0 && strcmp(sTemp, "DONE") != 0)	//check if the player typed "DONE"
			{
						//since we removed the trailing line to detect the keyword, we have to put it back by adding it there
				fprintf(acc, "%s", sTemp);	//main input of player
				k++;
			}
		} while(strcmp(sTemp, "done") != 0 && strcmp(sTemp, "DONE") != 0);
		printf("%d names have been added!\n", k);
		
		//ENEMIES

		//Pretty much the same algorithm as for accessory
		printf("Input names for ENEMIES (MAXIMUM 30 CHARACTERS).\nIf you do not want to add names or you're done adding names, type \"done\" or \"DONE\"\n");
		do
		{
			printf("INPUT ITEM %d: ", l + 1);
			fgets(sTemp, 30, stdin);
			sTemp[strcspn(sTemp, "\n")] = 0;
			if(strcmp(sTemp, "done") != 0 && strcmp(sTemp, "DONE") != 0)
			{
				fprintf(enem, "\n");	
				fprintf(enem, "%s", sTemp);
				l++;
			}
		}while(strcmp(sTemp, "done") != 0 && strcmp(sTemp, "DONE") != 0);
		printf("%d names have been added!\n", l);

		

		//REALLOCATE POINTERS TO MAIN POINTER TEMP
		*temp1 = realloc(*temp1, sizeof(String30) * (50 + k));
		*temp2 = realloc(*temp2, sizeof(String30) * (50 + l));
		
		//Check if the pointers were able to allocate memory
		if(*temp1 == NULL || *temp2 == NULL)
		{
			printf("\nWhoops! Something looks wrong!\n");
			printf("The program couldn't allocate enough memory.\n");
			printf("Terminating program!");
			exit(1);
		}	
	}
	
	fflush(stdin);

	//close both files.
	fclose(acc);
	fclose(enem);

	//reopen them as a readable file
	acc = fopen("ArtifactList.txt", "r");

	
	while(!feof(acc) && i < 50 + k)
	{
		fgets(sTemp, 30, acc);
		sTemp[strcspn(sTemp, "\n")] = 0;
		strcpy(*(*temp1 + i), sTemp);
		i++;
	}
	
	//CLOSE FILE FOR ACCESSORIES
	fclose(acc);
	
	enem = fopen("MonsterList.txt", "r");

	while(!feof(enem) && j < 50 + l)
	{
		fgets(sTemp, 30, enem);
		sTemp[strcspn(sTemp, "\n")] = 0;
		strcpy(*(*temp2 + j), sTemp);
		j++;
	}
	fclose(enem);
	//CLOSE FILE FOR ENEMIES
	

	//SET ADDITIVE VALUES
	*temp1Add = k;
	*temp2Add = l;
}

/*int main(){
	
	String15 name;
	String30 accessoryList[50];
	String30 enemyList[50];
	
	getName(name);
		
	getFileInfo(name, accessoryList, enemyList);
	
	//GAME INIT HERE

	return 0;
}*/


