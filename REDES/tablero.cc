#include "tablero.hpp"
#include <cstring>
#include <cstdio>

#include <sstream> //for using ostringstream

using namespace std;

bool Tablero::getUserSelection(char letter,int y){

  int x = letter - 'a';

  if(((unsigned int)x < getPCBoard().size() && x >= 0) && ((unsigned int)y < getPCBoard().size() && y >= 0)){

    return true;
  }
  else{
    return false;
  }
}

char Tablero::getCell(int x, int y){

  return PCboard[x][y];
}


bool Tablero::userSelection(int x, int y, int f, int turno){

  //in case flag was chosen
  if(f == 1){
    if(PCboard[x][y]!='0'||PCboard[x][y]!='1'||PCboard[x][y]!='2'||PCboard[x][y]!='3'||PCboard[x][y]!='4'||PCboard[x][y]!='5'||PCboard[x][y]!='6'||PCboard[x][y]!='7'||PCboard[x][y]!='8'){
      if(turno==1){
        if(PCboard[x][y]=='B'){
          PCboard[x][y]='F'; //AB
          return false;
        }
        if(PCboard[x][y]=='A'){ //PARA RECTIFICAR BANDERAS
          PCboard[x][y]='-';
          return false;
        }
        if(PCboard[x][y]=='F'){ //PARA RECTIFICAR BANDERAS
          PCboard[x][y]='B';
          return false;
        }
        PCboard[x][y] = 'A';
        return false;
      }
      if(turno==2){
        if(PCboard[x][y]=='A'){
          PCboard[x][y]='F'; //AB
          return false;
        }
        if(PCboard[x][y]=='B'){ //PARA RECTIFICAR BANDERAS
          PCboard[x][y]='-';
          return false;
        }
        if(PCboard[x][y]=='F'){ //PARA RECTIFICAR BANDERAS
          PCboard[x][y]='A';
          return false;
        }
        PCboard[x][y] = 'B';
        return false;
      }

    }

  }


  //in case there were no mines near the selected box recursively
  if(board[x][y]== 0 ){
    PCboard[x][y]='0';

    //open boxes near it
    int a = -1;
    if(x == 0)
    a = 0;

    for (;a <=1;++a){
      int b= -1;
      if(y==0)
      b=0;
      for(;b<=1;++b){

        if(x+a < (int)getPCBoard().size() && y+b < (int)getPCBoard().size()){
          if(PCboard[x+a][y+b]!='-')
          continue;

          userSelection(x+a,y+b,f,turno);

        }
      }
    }

    return false;
  }

  // in case of a mine
  if(board[x][y]== -1){
    PCboard[x][y]='*';
    return true;
  }

  PCboard[x][y]=board[x][y] + '0';


  return false;

}

void Tablero::fillBoard(size_t height, size_t width, size_t mines){

  board = std::vector< std::vector<int> >(height, std::vector<int> (width));

  srand (time(NULL));

  //initialize board with zeros
  for(unsigned int a=0;a<height;++a)
  for(unsigned int b=0; b<width;++b)
  board[a][b] = 0;

  //fill board with mines
  int i,j;
  for(unsigned int counter=0; counter < mines;++counter){
    i = rand() % height;
    j = rand() % width;
    if(board[i][j] == 0)
    board[i][j] = -1;
    else
    --counter;

  }

  //fill board with mines count around each box
  for(unsigned int a=0;a<height;++a)
  for(unsigned int b=0; b<width;++b){
    if(board[a][b]== -1)
    continue;
    int x = -1;
    if(a == 0)
    x =0;


    for (;x <=1;++x){
      int y=-1;
      if(b==0)
      y=0;
      for(;y<=1;++y)
      if(x+a < height && y+b < width)
      if(board[a+x][b+y]==-1)
      ++board[a][b];


    }
  }
}

void Tablero::fillPCBoard(size_t height, size_t width){

  PCboard = std::vector< std::vector<char> >(height, std::vector<char> (width, '-'));
}

bool Tablero::checkForWin(int turno, int minas){
  bool win=true;
  int contador=0;
  for(unsigned int i=0;i<getPCBoard().size();i++){
    for(unsigned int j=0; j<getPCBoard().size();j++){
      if( (turno == 1) && ((PCboard[i][j]=='A')||(PCboard[i][j]=='F')) && (board[i][j]==-1) ){
        contador++;
      }
      else{
        win=false;
      }

      if( (turno == 2) && ((PCboard[i][j]=='B')||(PCboard[i][j]=='F')) && (board[i][j]==-1) ){
        contador++;
      }
      else{
        win=false;
      }

    }
  }
  if(minas != -1){
    if(contador == minas){
      return true;
    }
  }

  return win;

}
