#ifndef TABLERO_HPP_
#define TABLERO_HPP_

#include <iostream>
#include<limits>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>


class Tablero{

	private:

		std::vector< std::vector<int> > board;
		std::vector< std::vector<char> > PCboard;

	public:

		Tablero();

		Tablero(size_t height, size_t width, size_t mines){
			fillPCBoard(height, width);
			fillBoard(height, width, mines);
		}

		bool checkForWin(int turno, int minas);
		char getCell(int x, int y);
		bool userSelection(int x, int y, int f, int turno);
		void fillBoard(size_t height, size_t width, size_t mines);
		void fillPCBoard(size_t height, size_t width);
		bool getUserSelection(char letter,int y);

		std::vector< std::vector<char> > getPCBoard()const{
			return PCboard;
		}

		std::vector< std::vector<int> > getBoard()const{
			return board;
		}

		void operator=(const Tablero &aux){
	  	board = aux.getBoard();
	  	PCboard = aux.getPCBoard();
	  }

};


#endif
