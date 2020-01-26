#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



//________COULEURS_DU_TEXTE_________________________________________________

//Variables globales des couleurs
WORD saved_attributes;
HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

//Fonctions de setup des couleurs
void setupColor(){
	hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
}

//Fonctions de changement de couleur de texte
void colorAqua(){
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE+FOREGROUND_GREEN);
}
void colorVert(){
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}
void colorJaune(){
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN+FOREGROUND_RED);
}
void colorRouge(){
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}
void colorBlanc(){
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	SetConsoleTextAttribute(hConsole, saved_attributes);
}
//__________________________________________________________________________


//Structure des entites du jeu
struct Entite{
	//Points de vie || Points de magie || Attaque de base || Experience || Niveau
	int PDV;
	int PDM;
	int ATK;
	int XP;
	int LVL;

	// 0 pas ennemi, 1 monstre type1, 2 monstre type 2;
	int ennemis;

	char nom[50];
};

//Declaration des variables globales
int jeuFini;
int nombreEnnemis;
int numAttaque;

//Fonction d'une instance d'une attaque simple
//Param__ATK: ATK du perso attaquant____viesCible: PDV de la cible
void attaqueSimple(int ATK,int viesCible) {

	viesCible=viesCible-ATK;
}


struct Entite ennemi[3];
struct Entite tank = {200,0,25,0,1,0};
struct Entite mage= {85,10,15,0,1,0};
struct Entite soin= {100,10,10,0,1,0};

int main(){
	srand(time(NULL));
	//Affectation_des_varibles_globales________________________________________

	for(int i=0; i<=2; i++){
		ennemi[i].PDV=0;
	}

	jeuFini=0;
	nombreEnnemis=0;

	//_________________________________________________________________________


	//Setup____________________________________________________________________
	setupColor();
	//_________________________________________________________________________

	printf("Vous etes dans un monde ou les monstres regnent sur la Terre. Votre equipe a ete elue pour devoir eradiquer tout ces monstres.\n");
	printf("Pensez-vous y arriver?...\n");
	printf("Choisissez les noms des personnages de votre equipe.\n");
	printf("\nChoisissez un nom pour votre Gardien: ");
	scanf("%s",&tank.nom);

	printf("\nChoisissez un nom pour votre Sorcier:");
	scanf("%s",&mage.nom);

	printf("\nChoisissez un nom pour votre Pretre:");
	scanf("%s",&soin.nom);


	//Boucle while du jeu de base
	while(jeuFini!=1)
	{
		//initiation combat
		
		nombreEnnemis=rand()%3+1;
		if(tank.LVL<5){
			if(nombreEnnemis==4){
				nombreEnnemis=1;
			}
		}else if(tank.LVL<10){
			if(nombreEnnemis==4){
				nombreEnnemis=2;
			}
		}else {
			if(nombreEnnemis==4){
				nombreEnnemis=3;
			}
		}

		for(int i=0;i<nombreEnnemis;i++){
			
			ennemi[i].ennemis=(rand()%2)+1;
			ennemi[i].LVL=(tank.LVL+rand()%3)-1;

			if(ennemi[i].LVL<=0){ennemi[i].LVL=1;}

			//si l'ennemi est de type1
			if(ennemi[i].ennemis==1){
				ennemi[i].PDV=400+100*(ennemi[i].LVL-1);
				ennemi[i].ATK=50+12*(ennemi[i].LVL-1);
			}

			//si l'ennemi est de type2
			if(ennemi[i].ennemis==2){
				ennemi[i].PDV=250+25*(ennemi[i].LVL-1);
				ennemi[i].ATK=20+4*(ennemi[i].LVL-1);
			}
		}

		printf("Il y a ");
		colorJaune();
		printf("%d",nombreEnnemis);
		colorBlanc();
		printf(" ennemis face a vous!\n");
		for (int i=0;i<nombreEnnemis;i++){
			printf("Un ");
			if(ennemi[i].ennemis==1){
				colorRouge();
				printf("Duraqwir");
				colorBlanc();
			}

			if(ennemi[i].ennemis==2){
				colorRouge();
				printf("Chene-a-pan");
				colorBlanc();
			}

			printf(" de niveau ");
			colorAqua();
			printf("%d \n",ennemi[i].LVL);
			colorBlanc();
		}

		//boucle while de combat
		while(tank.PDV+mage.PDV+soin.PDV>0 && ennemi[0].PDV+ennemi[1].PDV+ennemi[2].PDV>0){
			
			colorVert();
			printf("\n\n\nC'est a vous de jouer!\n");
			colorBlanc();
			printf("%s commence.\n",soin.nom);
			colorJaune();

			printf("PDV : %d ",soin.PDV);
			
			printf("|| PDM : %d ",soin.PDM);
			printf("|| ATK : %d\n",soin.ATK);
			
			colorBlanc();
			
			printf("\n");
			printf("\nQui voulez vous cibler?\n\n");

			for(int i=0;i<nombreEnnemis;i++){
				colorBlanc();
				printf("(%d) ",i+1);
				colorRouge();
				if(ennemi[i].ennemis==1){
					printf("Duraqwir");
				}else {
					printf("Chene-a-pan");
				}
				printf("(%d) ",ennemi[i].LVL);
				colorBlanc();
				printf("  %d/",ennemi[i].PDV);

				int x;
				if(ennemi[i].ennemis==1){
					x = 400+100*(ennemi[i].LVL-1);
					printf("%d",x);
				}else {
					x = 250+25*(ennemi[i].LVL-1);
					printf("%d",x);
				}
				printf("\n");
			}

			printf("(%d) Votre equipe",nombreEnnemis+1);
			

			colorBlanc();

			scanf("%d",&numAttaque);

			ennemi[0].PDV = ennemi[0].PDV-50;

			printf("%d",ennemi[0].PDV);

		}
		jeuFini=1;
	}
	//--------NO-TOUCH-------JUST-LOOK---------
	colorBlanc();
	return 0;
}