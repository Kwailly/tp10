////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
FILE *f;
int N;
f=fopen("nextFact","r");
fread(&N,sizeof(int),1,f);
fclose(f);
//printf("\n--->lu N=%d",N);
return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
int m,c,d,u;
char cm,cc,cd,cu;
m=N/1000;cm=48+m;
N%=1000;
c=N/100;cc=48+c;
N%=100;
d=N/10;cd=48+d;
u=N%10;
cu=48+u;
N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}

int lireCommande(FILE *ficCommande, int N) {
    char nom_client[50];
    int ref, ref_prod_stock , stock;
    int qtt = 0; 
    int ref_prod;
    float prix;
    char nom_prod[50];
    char nom_fichier[50];
    float total = 0; 

    fscanf(ficCommande, "%s", nom_client);

    sprintf(nom_fichier, "./factures/facture_%d_%s.txt", N, nom_client);
    FILE *fichier_commande = fopen(nom_fichier, "w");
    fprintf(fichier_commande, "Client: %s\n", nom_client);

    while (fscanf(ficCommande, "%i %i", &ref, &qtt) == 2) {
        FILE *ficProduit = fopen("produits.txt", "rt");
        ref_prod = 0;
        do {
            FILE *ficStock = fopen("stock.txt" , "r+w");
            fscanf(ficProduit, "%i %s %f", &ref_prod, nom_prod, &prix);
            if (ref_prod == ref) {
                while (!(feof(ficStock))) {
                    fscanf(ficStock, "%i %i", &ref_prod_stock, &stock);
                    if (ref_prod_stock == ref) {
                        break;
                    }
                }
                if (stock >= qtt) { 
                    fscanf(ficStock, "%i %i", &ref_prod_stock, &stock);
                        fprintf(fichier_commande, "Produit: %s", nom_prod);
                        fprintf(fichier_commande, " - Quantité: %d", qtt);
                        fprintf(fichier_commande, " - Prix unitaire: %f\n", prix);
                        total += prix * qtt; 
						int stock2 = stock - qtt;
						fprintf(ficStock, "%i" , stock);
                }
				else{
					sprintf(nom_fichier, "ALERTES.txt");
 					FILE *fichier_alertes = fopen(nom_fichier, "w");
    				fprintf(fichier_alertes, "reference_manquante: %i\n", ref);

				}
            }
            fclose(ficStock);
        } while (!(feof(ficProduit)));
        fclose(ficProduit);
    }
   
    fprintf(fichier_commande, "Total: %f\n", total);
    fclose(fichier_commande);
    return 0;
}




void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
FILE *ficCommande=NULL;
int FINI=0;
int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
char NNNN[5];
char nomCommande[29];

do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	//printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	//printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present",nomCommande);
			lireCommande(ficCommande , N); // à vous de coder cette fonction lors de ce TP9
			fclose(ficCommande);
		}
	else
		{
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		

}



int main()
{
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	
	FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);
	

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	

	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}
