/*

	Evan Bradford
	4/11/16
	Checkers

*/
#ifndef checkers_h
#define checkers_h

#include <string>
#include "game.h"
#include "pieces.h"
using namespace main_savitch_14;

class Checkers : public game
{
	public:
	
		Checkers();
		void display_status();
		bool is_legal(const std::string& move,const bool player)const;
		void make_move(const std::string& move, const bool player);
		void make_move_cpu(const std::string& move, const bool player);
		bool is_game_over(const bool fact)const;
		bool double_jump(int row, int col)const;
		void make_double_move(const bool player, int row, int col);
		//part three
		game *clone()const{return new Checkers(*this);}
		void compute_moves(std::queue<std::string>& moves)const;
		int evaluate()const;
		bool move_available(const bool player);
		
		
		
	private:
		Pieces board[8][8];
		std::string move;
};
#endif
