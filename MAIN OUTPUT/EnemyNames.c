#include <stdio.h>
#include  <string.h>
/* CHECK LIST

[/] - Open preferred enemy text file
[/] - Copy list to an array

FEEL free to add anything on checklist/code if you need to, Eugeneee. Or tell me para ma-change ko.  Thankiees :)
*/

void enemyNamesInit(FILE *fPointer, char enemyName[][31])
{
    int i = 0;
    if (fPointer == NULL)
        printf("Unable to open file");

    else
        {
            while (!feof(fPointer))  // until end of  the file
                {
                    fgets(enemyName[i], 31, fPointer);  // assigns list to an array
                    i++;
                }
            //printf("Success! EnemyNames are copied in an Array.");
            fclose(fPointer); 
        }

}

//checking
void printEnemyNames(char enemyName[][31])
{
    int i;

    for (i = 0; i < 50; i++)
        printf("%s", enemyName[i]);
}
