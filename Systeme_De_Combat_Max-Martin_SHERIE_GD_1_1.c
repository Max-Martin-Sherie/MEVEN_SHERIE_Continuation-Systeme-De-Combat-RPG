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

//Declaration des points de vies
int PDVJoueur=100;
int PDVMonstre=200;
int PMJoueur=4;
int PMMonstre=14;
int empoisonementJoueur=0;
int empoisonementMonstre=0;
int defense=0;
int numAttaque;

//Fonction d'une attaque simple
int attaqueSimple(int viesCible) {
	if(defense==1){
		viesCible=viesCible-5;
	}else{
		viesCible=viesCible-20;
	}
	
	return viesCible;
}

//Fonction d'une instance d'un empoisonnement
int empoisonement(int viesCible) {
	
	viesCible=viesCible-5;
	return viesCible;
}

int main(){
	setupColor();
	colorAqua();

	printf("\n Vous rencontrez un ennemis!\n Il est vert, hideux, et ressemble a Valentin\n Le combat commence!\n\n");
	
	while ((PDVJoueur>1) && (PDVMonstre>1)){
		printf("c'est a vous de jouer\n");
		PMJoueur++;
		printf("Vous avez %d PM\n",PMJoueur);
		printf("(1)attaque (2)se defense (3)poison (4)antidote\n");
		
		scanf("%d", &numAttaque);
		
		while(numAttaque != 1 && numAttaque != 2 && (numAttaque==3 && PMJoueur<5) && (numAttaque!=4&& PMJoueur<3)){
			if((PMJoueur<5 && numAttaque==3) || (numAttaque!=4&& PMJoueur<3)){
				printf("vous n'avez pas assez de PM pour lancer ce sort\n");
			}else{
				printf("Il n'y a pas d'attaque numero %d ! \n",numAttaque);
			}
			scanf("%d", &numAttaque);
		}
		if(numAttaque==1){
			PDVMonstre=attaqueSimple(PDVMonstre);
			printf("Vous frappez l'ennemi d'un glorieux coup de sabre !\n");
			defense=0;
		}else if(numAttaque==2){
			printf("Vous vous retraitez derriere votre bouclier en mythril!\n");
			defense=1;
		}else if(numAttaque==3){
			printf("Vous jetez un sort de poisson pourris sur l'ennemi!\n");
			PMJoueur=PMJoueur-5;
			empoisonementMonstre=3;
			defense=0;
		}else if(numAttaque=4){
			PMJoueur=PMJoueur-3;
			empoisonementJoueur=0;
			defense=0;
		}
		if(empoisonementMonstre>0){
			empoisonementMonstre--;
			printf("Le monstre empoissone perd 5 points de vie\n");
			PDVMonstre=empoisonement(PDVMonstre);
		}
		
		printf("Il reste %d points de vie au monstre\n \n",PDVMonstre);
		
		PMMonstre++;
		if(PMMonstre>14){
			numAttaque = rand()%3;
		}else{
			numAttaque = rand()%2;
		}
		
		if(numAttaque==0){
		PDVJoueur=attaqueSimple(PDVJoueur);
		printf("Le Monstre attaque d'un coup de pate hideuse!\n");
		defense=0;
		}else if(numAttaque==1){
			printf("Le monstre de protege\n");
			defense=1;
		}else if(numAttaque==2){
			printf("Le monstre vous crache dessus! Vous etes empoisonne.\n");
			PMMonstre=PMMonstre-5;
			empoisonementJoueur=5;
			defense=0;
		}
		
		if(empoisonementJoueur>0){
			empoisonementJoueur--;
			printf("Empoisonne, Vous perdez 5 points de vie\n");
			PDVJoueur=empoisonement(PDVJoueur);
			
		}
		
		printf("Il vous reste %d Points de vie\n \n",PDVJoueur);
	}
	if(PDVJoueur>0){
		printf("\nLe monstre est mort et vous rentrer chez vous satisfait.");
	}else{
		printf("\nLe monstre Se nourrit de votre chaire, celle-ci a ne plus jamais etre vue par votre maris ou vos enfants..");
	}

	//--------NO-TOUCH-------JUST-LOOK---------
	colorBlanc();
	return 0;
}