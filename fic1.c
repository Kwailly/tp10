////////////////////////// lire un fichier texte quelconque CHAR par CHAR
// quelconque signifie : sans format spécifique

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_MOTS_DU_POEME 200
#define MAX 25
typedef char T_chaine[MAX];
/*******************************************************************/
/*    fonction : lireUnFichierTXTQuelconque 	                  */
/*    description  : lire 'importe quel fichier txt		  */
/*    paramètre : aucun						   */
/*    retourne : RIEN					           */
/*    condition : le fichier poeme.txt doit exister 		   */
/*    auteur : kub						   */
/*    date : 29/3/20						   */
/*******************************************************************/

int lireUnFichierTXTQuelconque(T_chaine *Tab_mots) 
{

char car;
int i=0,numMot=1;
FILE *fic=NULL;

	fic=fopen("poeme.txt","rt");//mode rt = "read" et "text"
	if (fic!=NULL)
		{ // le fichier txt existe
		do
		{

		fscanf(fic,"%c",&car);
		if (!(feof(fic)))		
		{
			if (car==' ' || car=='\n')
				{Tab_mots[numMot][i]='\0';i=0;numMot++;
				if(numMot>NB_MOTS_DU_POEME)
					{
				fclose(fic);return numMot;			
					}			
				}
			else {Tab_mots[numMot][i]=car;i++;}
		 
		
		printf("%c",car);
		}
		}while(!(feof(fic)));
		fclose(fic);
		
		}
return numMot-1;
}


/**************************************************************************/
/*        prepa au TP10 : lire et ecrire dans des fichiers txt        */
/**************************************************************************/
int main()
{
int j;
T_chaine leTableauDesMots[NB_MOTS_DU_POEME+1];

	int nbMotsDansLePoeme= lireUnFichierTXTQuelconque(leTableauDesMots);
	getchar();
	for(j=1;j<=nbMotsDansLePoeme;j++)
		printf("\n-->%s<--",leTableauDesMots[j]);
	printf("\n-->il y a %d mots dans ce fichier.",nbMotsDansLePoeme);


	return 0;
}

