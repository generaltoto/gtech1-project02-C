#include <stdio.h>
#define NBL 6
#define NBC 7

char tab[NBL][NBC];
char token [] = "OX";
int player = 1;
int count = 0;

//construction du tableau de jeu
void Init(void) {
  for(int l=0; l<NBL; l++) {
    for(int c=0; c<NBC; c++) {
      tab[l][c] = '.';
    }
  }
}

//fonction pour changements de couleurs d'affichage
void red(void){
  printf("\033[0;31m");
}

void green(void){
  printf("\033[0;32m");
}

void yellow(void){
  printf("\033[0;33m");

}

void cyan(void){
  printf("\033[0;36m");
}

void white(void){
  printf("\033[0;37m");
}

//fonction d'affichage du tableau à chaque tour
void Disp(void){

  for(int l=0; l<NBL; l++) {
    printf(" \n|");
    for(int c=0; c<NBC; c++) {
      if(tab[l][c] == token[0]){
        red();
        printf(" %c ",tab[l][c]);

      } else if (tab[l][c] == token[1]){
        yellow();
        printf(" %c ",tab[l][c]);

      } else {
        white();
        printf(" %c ",tab[l][c]);
      }
    }
    white();
    printf(" |");
  }
  white();
  printf("\n  1  2  3  4  5  6  7  \n");
}

//fonction permettant de prendre l'entrée du joueur
void Empty(void){
  int c = getchar();
  while (c != '\n' && c != EOF){
    c = getchar();
  }
}

//fonctions pour les rentrées d'informations des joueurs
int Verif(int range){
  int save;
  int answer;
  for (;;) {
    white();
    //entrée du joueur
    save = scanf (" %d", &answer);
    red();

    if (save == EOF) {
      fputs ("You didn't write anything...\n", stderr);
      return 0;
    }

    //vérification du type rentré
    else if (save == 0) {
      fputs ("Could you choose an intager please ? ...\n", stderr);
      Empty();
    }

    //vérifier qu'il s'agisse d'une réponse attendue
    else if (answer < 1 || range < answer) {
      fputs ("This is not a choice...\n", stderr);
      Empty();
    }
    
    else {  
      Empty();
      return answer;
    }
  }
}

//Vérification du l'état du jeu
int StatusGame(){
  red();
  //à partir du moment où il y a assez de jetons pour gagner
  if (count>6){
    //on test toutes les possibilités d'alignement par lignes, colonnes et diagonales
    for(int l=0; l<NBL; l++) {
      for(int c=0; c<NBC-2; c++) {
        if (tab[l][c] == token[player] && tab[l][c+1] == token[player] && tab[l][c+2] == token[player] && tab[l][c+3] == token[player]){
          //et on déclare un vainqueur s'il y en a un
          printf("\nPlayer %d won !! \n", player+1);
          return 1;
        } 
      }  
    }

    for(int c=0; c<NBC-1; c++) {
      for(int l=0; l<NBL-2; l++) {
        if (tab[l][c] == token[player] && tab[l+1][c] == token[player] && tab[l+2][c] == token[player] && tab[l+3][c] == token[player]){
          printf("\nPlayer %d won !! \n", player+1);
          return 1;
        } 
      }
    }

    for(int c=NBC-1; c>2; c--) {
      for(int l=0; l<NBL-3; l++) {
        if (tab[l][c] == token[player] && tab[l+1][c-1] == token[player] && tab[l+2][c-2] == token[player] && tab[l+3][c-3] == token[player]){
          printf("\nPlayer %d won !! \n", player+1);
          return 1;
        } 
      }
    }

    for(int c=0; c<NBC-3; c++) {
      for(int l=0; l<NBL-2; l++) {
        if (tab[l][c] == token[player] && tab[l+1][c+1] == token[player] && tab[l+2][c+2] == token[player] && tab[l+3][c+3] == token[player]){
          printf("\nPlayer %d won !! \n", player+1);
          return 1;
        } 
      }
    }
  }

  //cas d'égalité où le tableau est plein
  if (count >= 42){
    printf("\nThe game is full !\n");
    return 1;
  }
  white();
  return 0;
}

void main(void) {
  int replay = 1;
  //boucle de jeu
  while (replay == 1){
    //initialisation de la partie
    Init();
    Disp();
    while(StatusGame() == 0){

      int column, i=5;
      player = !player;
      green();
      printf("\nPlayer %d (%c) is playing ! \nWhich column do you choose ?\n",player+1, token[player]);
      column = Verif(7);
      //demandes d'entrée pour le joueur en choisissant une colonne
      while(tab[0][column-1] != '.'){
        printf("\nThis column is full, choose an other one please.\nWhich column do you choose ?\n");
        column = Verif(7);
        }
      //calcul de l'emplacement du jeton 
      while (tab[i][column-1] != '.'){
        i --;
      }
      //mise à jour du tableau, affichage de celui-ci
      tab[i][column-1] = token[player];
      white();
      Disp();
      count ++;
      printf("---------------------\n");
    }

    replay = 0;
    cyan();
    printf("\nDo you want to play again ?\n1 for Yes\n2 for No\n");
    replay = Verif(2);
    //fin de partie, proposition pour rejouer
    while (replay != 1 && replay != 2){
      cyan();
      printf("\nDo you want to play again ?\n1 for Yes\n2 for No\n");
      replay = Verif(2);
    }
    white();
    if (replay == 1){
      printf("\nAh shit ... here we go again..\n");
    }
    count = 0;
  }
  red();
  printf("\nGame Over ! See You !\n\n");
  white();
}