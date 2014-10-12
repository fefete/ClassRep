#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

//#include <mainfunction.h>
//#include <structs.h>
enum Type{
  KPIEDRA = 1,
  KPAPEL,
  KTIJERA,
};
struct Player{
  int tipo;
  std::string pais;
};
struct Score{
  Player remaining[10];
  int player_score;
};
FILE* g_estados;  
Player g_machine[10];
Score g_final_score;

void generatePlayer(Player machine[10]){
  std::string line;
  std::string countries[53];
  int random;
  int got_numbers[10];
  int index=0;
  srand(time(NULL));
  std::ifstream my_file("estados.txt");
  if (my_file.is_open()){
    while (getline(my_file, line)){
      std::string country = line.c_str();
      countries[index] = country;
      ++index;
    }
  }
  for (int a = 1; a <= 10; ++a){
    random = rand() % 50;
    for (int b = 0; b < a; ++b){
      if (random == got_numbers[b]){
        a--;
        break;
      }else{
        if (b == (a - 1)){
          got_numbers[a-1] = random;
          machine[a - 1].pais = countries[random];
          machine[a - 1].tipo = (rand()%3 + 1);
        }
      }
    }
  }
  my_file.close();

}

/*void insertScore(struct Score finalScore){
  FILE* scoreList;
  scoreList = fopen("//scores.txt", "a");
  fwrite(&finalScore, sizeof(Score), 1, scoreList);
  fclose(scoreList);
}*/

int FightResult(int played, int machine_move, int &score){
  if (played == machine_move){
     ++score;
     return -1;
  }
  if ((played == KPIEDRA && machine_move == KTIJERA) || 
     (played == KPAPEL && machine_move == KPIEDRA) ||
     (played == KTIJERA && machine_move == KPAPEL)) {
    ++score;
    return 1;
  } else {
    if ((machine_move == KPIEDRA && played == KTIJERA) ||
       (machine_move == KPAPEL && played == KPIEDRA) ||
       (machine_move == KTIJERA && played == KPAPEL)) {
       return 0;
    }
  }
}

int main(){
  printf("//////////////////////////////////////////////////\n");
  printf("///////////   ROCK PAPER SCISSORS!!   ////////////\n");
  printf("//////////////////////////////////////////////////\n");
  generatePlayer(g_machine);
  bool end = false;
  int score = 0;
  int fight = 0;
  char selected;
  char cursor;
  do
  {
    printf("Challenger %d :\n %s. \n YOUR MOVE \n", score, g_machine[score].pais.c_str());
    printf("Select R/P/S:  \n");
    do
    {
      selected = getchar();
    } while (selected != 'R' && selected != 'P' && selected != 'S');
    
    if (selected == 'R'){
      fight = FightResult(1, g_machine[score].tipo, score);
    } else {
      if (selected == 'S'){
        fight = FightResult(2, g_machine[score].tipo, score);
      } else {
        if (selected == 'P'){
          fight = FightResult(3, g_machine[score].tipo, score);
        }
      }
    }
    fflush(stdin);
  } while (fight != 0 && score < 9);

  if (score != 10){
    printf("\n// YOU LOSE \\ \n");
    printf("REMAINING CHALLENGERS \n");
    int arraySize = score;
    for(arraySize; arraySize < 10; ++arraySize){
      printf("%s --  \n", g_machine[arraySize].pais.c_str());
      g_machine[arraySize] = g_final_score.remaining[arraySize - score];
    }
    g_final_score.player_score = score;
  }
  else{
    printf("\n// YOU WIN, CONGRATULATIONS MOTHER******\\ \n");
  }
  
  _getch();


}