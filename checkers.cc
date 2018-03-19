/*

	Evan Bradford
	4/11/16
	Checkers

*/

#include "checkers.h"
#include "colors.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;

Checkers::Checkers()
{
	for(int k = 0;k < 8; k++)
	{
		for(int l = 1; l < 8; l += 2)
		{
			board[k][l].set_black();
		}
		for(int j = 0;j < 8; j+=2)
		{
			board[k][j].set_red();
		}
	}
	move = "A6B5";
	//pieces colors and positions
	for(int y = 0; y < 8; y ++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(y == 0 || y == 1 || y == 2 || y == 5 || y == 6 || y == 7)
			{
				if(((y == 0 && (j == 1 || j == 3 || j == 5 || j == 7)) || ((y == 1 && (j == 0 || j == 2 || j == 4 || j == 6)) || ((y == 2 && (j == 1 || j == 3 || j == 5 || j == 7))))))
				{
					board[y][j].set_occupy();
					board[y][j].set_white();
					board[y][j].unset_kingme();
				}
				else if(((y == 5 && (j == 0 || j == 2 || j == 4 || j == 6)) || ((y == 6 && (j == 1 || j == 3 || j == 5 || j == 7)) || ((y == 7 && (j == 0 || j == 2 || j == 4 || j == 6))))))
				{
					board[y][j].set_occupy();
					board[y][j].set_cyan();
					board[y][j].unset_kingme();
				}
			}
		}
	}
}
void Checkers::display_status()
{	
	cout << "     A          B           C          D          E          F         G         H\n";
	for(int y = 0; y < 8; y ++)
	{
		if(y%2 == 0)
		{
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 8; j++)
				{
					if(board[i][j].is_red() == true)
					{
							cout << B_RED << setw(15) << RESET;
					}
					else
					{
							if(board[y][j].kinged() == true && board[y][j].occupied() == true && board[y][j].is_white() == true && i == 2)
								cout << B_BLACK << WHITE << "     K     " << RESET;
							else if(board[y][j].kinged() == true && board[y][j].occupied() == true && board[y][j].is_white() == false && i == 2)
								cout << B_BLACK << RED << "     K     " << RESET;
							else if(board[y][j].occupied() == true && board[y][j].is_white() == true && i == 2)
								cout << B_BLACK << WHITE << "     @     " << RESET;
							else if(board[y][j].occupied() == true && board[y][j].is_white() == false && i == 2)
								cout << B_BLACK << RED << "     @     " << RESET;
							else
								cout << B_BLACK << setw(15) << RESET;
					}
				}
				if(i == 2)
				{
					cout << y+1;
				}
				cout << endl;
			}
		}
		else
		{
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 8; j++)
				{

					if(board[i][j].is_red() == false)
					{
							cout << B_RED << setw(15) << RESET;
					}
					else
					{
							if(board[y][j].kinged() == true && board[y][j].occupied() == true && board[y][j].is_white() == true && i == 2)
								cout << B_BLACK << WHITE << "     K     " << RESET;
							else if(board[y][j].kinged() == true && board[y][j].occupied() == true && board[y][j].is_white() == false && i == 2)
								cout << B_BLACK << RED << "     K     " << RESET;
							else if(board[y][j].occupied() == true && board[y][j].is_white() == true && i == 2)
								cout << B_BLACK << WHITE << "     @     " << RESET;
							else if(board[y][j].occupied() == true && board[y][j].is_white() == false && i == 2)
								cout << B_BLACK << RED << "     @     " << RESET;
							else
								cout << B_BLACK << setw(15) << RESET;
					}
				}
				if(i == 2)
				{
					cout << y+1;
				}
				cout << endl;
			}
		}
	}
}
bool Checkers::is_legal(const string& move, const bool player)const
{
	int row, col, new_row, new_col;
	col = (int)std::toupper(move[0]-'A');
	row = (int)(move[1]-'1');
	new_col = (int)std::toupper(move[2]-'A');
	new_row = (int)(move[3]-'1');
	//off the sides of the board
	if(new_col < 0 || new_col > 7 || new_row < 0 || new_row > 7)
		return false;
	//if(board[row][col].is_red() == true || board[new_row][new_col].is_red() == true)
		//return false;
	//trying to move on same colored piece
	if(board[new_row][new_col].occupied() == true)
		return false;
		
	if(board[new_row][new_col].occupied() == true && board[row][col].is_white() == board[new_row][new_col].is_white())
		return false;

	//cyan kings
	if(board[row][col].kinged() == true && board[new_row][new_col].occupied() == false && board[row][col].occupied()&& board[row][col].is_white() == false && player == true)
	{
		//allows movement in all 4 diagonals
		if((col+1 == new_col && row+1 == new_row) || (col-1 == new_col && row+1 ==  new_row) || (col+1 == new_col && row-1 == new_row) || (col-1 == new_col && row-1 ==  new_row))
			return true;
		//jumping in all 4 directions
		if(col+2 == new_col && row-2 == new_row)
		{
			if(board[row-1][col+1].is_white() == true)
				return true;
		}
		if(col-2 == new_col && row-2 ==  new_row)
		{
			if(board[row-1][col-1].is_white() == true)
				return true;
		}
		if(col+2 == new_col && row+2 == new_row)
		{
			if(board[row+1][col+1].is_white() == true)
				return true;
		}
		if(col-2 == new_col && row+2 == new_row)
		{
			if(board[row+1][col-1].is_white() == true)
				return true;
		}
	}
	//white kings
	if(board[row][col].kinged() == true && board[new_row][new_col].occupied() == false && board[row][col].occupied()&& board[row][col].is_white() == true && player == false)
	{
		//allows movement in all 4 diagonals
		if((col+1 == new_col && row+1 == new_row) || (col-1 == new_col && row+1 ==  new_row) || (col+1 == new_col && row-1 == new_row) || (col-1 == new_col && row-1 ==  new_row))
			return true;
		//jumping in all 4 directions
		if(col+2 == new_col && row-2 == new_row)
		{
			if(board[row-1][col+1].is_white() == false)
				return true;
		}
		if(col-2 == new_col && row-2 ==  new_row)
		{
			if(board[row-1][col-1].is_white() == false)
				return true;
		}
		if(col+2 == new_col && row+2 == new_row)
		{
			if(board[row+1][col+1].is_white() == false)
				return true;
		}
		if(col-2 == new_col && row+2 == new_row)
		{
			if(board[row+1][col-1].is_white() == false)
				return true;
		}
	}
	//cyan moving
	if(board[new_row][new_col].occupied() == false && board[row][col].occupied() == true && board[row][col].is_white() == false && player == true)
	{
		if((col+1 == new_col && row-1 == new_row) || (col-1 == new_col && row-1 ==  new_row))
			return true;
		//jumps over white
		if(col+2 == new_col && row-2 == new_row)
		{
			if(board[row-1][col+1].is_white() == true)
				return true;
		}
		if(col-2 == new_col && row-2 ==  new_row)
		{
			if(board[row-1][col-1].is_white() == true)
				return true;
		}
		return false;
	}
	//white moving
	if(board[new_row][new_col].occupied() == false && board[row][col].occupied() == true && board[row][col].is_white() == true && player == false)
	{
		if((col+1 == new_col && row+1 == new_row) || (col-1 == new_col && row+1 ==  new_row))
			return true;
		//jumps over cyan
		if(col+2 == new_col && row+2 == new_row)
		{
			if(board[row+1][col+1].is_white() == false)
				return true;
		}
		if(col-2 == new_col && row+2 == new_row)
		{
			if(board[row+1][col-1].is_white() == false)
				return true;
		}
		return false;
	}	
	return false;	
}
void Checkers::make_move(const string& move, const bool player)
{

	bool jumping = false;
	int row, col, new_row, new_col;
	col = (int)toupper(move[0]-'A');
	row = (int)(move[1]-'1');
	new_col = (int)toupper(move[2]-'A');
	new_row = (int)(move[3]-'1');
	

	//all ifs should also cover kings jumping in any direction
	//cyan jumping white right or king
	if(col+2 == new_col && row-2 == new_row)
	{
		board[row-1][col+1].unset_kingme();
		board[row-1][col+1].unset_occupy();
		jumping = true;
	}
	//cyan jumping white left or king
	else if(col-2 == new_col && row-2 ==  new_row)
	{
		board[row-1][col-1].unset_kingme();
		board[row-1][col-1].unset_occupy();
		jumping = true;
	}
	//white jumping cyan right or king
	else if(col+2 == new_col && row+2 == new_row)
	{
		board[row+1][col+1].unset_kingme();
		board[row+1][col+1].unset_occupy();
		jumping = true;
	}
	//white jumping cyan left or king
	else if(col-2 == new_col && row+2 == new_row)
	{
		board[row+1][col-1].unset_kingme();
		board[row+1][col-1].unset_occupy();
		jumping = true;
	}
	board[row][col].unset_occupy();
	board[new_row][new_col].set_occupy();
	//keeps track of kings
	if(board[row][col].kinged() == true)
	{
		board[row][col].unset_kingme();
		board[new_row][new_col].set_kingme();
	}
	//keeps track of color of piece moved
	if(player == true)
		board[new_row][new_col].set_cyan();
	else
		board[new_row][new_col].set_white();
	//kings piece
	if(new_row == 7 || new_row == 0)
	{
		board[new_row][new_col].set_kingme();
		//stops further movement after kinging ceremony
		return;
	}
	if(jumping == true)
	{
		if(double_jump(new_row, new_col) == true)
		{
			make_double_move(player, new_row, new_col);
		}
	}
}
void Checkers::make_move_cpu(const string& move, const bool player)
{
	bool jumping = false;
	int row, col, new_row, new_col;
	col = (int)toupper(move[0]-'A');
	row = (int)(move[1]-'1');
	new_col = (int)toupper(move[2]-'A');
	new_row = (int)(move[3]-'1');
	string double_move = "";

	jumping = false;

	//all ifs should also cover kings jumping in any direction
	//cyan jumping white right
	if(col+2 == new_col && row-2 == new_row)
	{
		board[row-1][col+1].unset_occupy();
		jumping = true;
	}
	//cyan jumping white left
	else if(col-2 == new_col && row-2 ==  new_row)
	{
		board[row-1][col-1].unset_occupy();
		jumping = true;
	}
	//white jumping cyan right
	else if(col+2 == new_col && row+2 == new_row)
	{
		board[row+1][col+1].unset_occupy();
		jumping = true;
	}
	//white jumping cyan left
	else if(col-2 == new_col && row+2 == new_row)
	{
		board[row+1][col-1].unset_occupy();
		jumping = true;
	}
	board[row][col].unset_occupy();
	board[new_row][new_col].set_occupy();
	//keeps track of kings
	if(board[row][col].kinged() == true)
	{
		board[row][col].unset_kingme();
		board[new_row][new_col].set_kingme();
	}
	//keeps track of color of piece moved
	if(player == true)
		board[new_row][new_col].set_cyan();
	else
		board[new_row][new_col].set_white();
	//kings piece
	if(new_row == 7 || new_row == 0)
	{
		board[new_row][new_col].set_kingme();
		//stops further movement after kinging ceremony
		return;
	}
	if(jumping == true)
	{
		if(double_jump(new_row, new_col) == true)
		{
			//jumps
			//down 2 left 2
        	double_move += new_row;
			double_move += new_col;
        	double_move += new_row+2;
			double_move += new_col-2;
			double_move[0] = double_move[0] + 'A';
			double_move[1] = double_move[1] + '1';
			double_move[2] = double_move[2] + 'A';
			double_move[3] = double_move[3] + '1';
			if(is_legal(move, player) == true)
				make_move_cpu(move, player);
			double_move = "";
			//up 2 left 2
        	double_move += new_row;
			double_move += new_col;
        	double_move += new_row - 2;
			double_move += new_col-2;
			double_move[0] = move[0] + 'A';
			double_move[1] = move[1] + '1';
			double_move[2] = move[2] + 'A';
			double_move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				make_move_cpu(move, player);
			double_move = "";
			//down 2 right 2
			double_move += new_row;
			double_move += new_col;
        	double_move += new_row + 2;
			double_move += new_col+2;
			double_move[0] = move[0] + 'A';
			double_move[1] = move[1] + '1';
			double_move[2] = move[2] + 'A';
			double_move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				make_move_cpu(move, player);
			double_move = "";
			//up 2 right 2
        	double_move += new_row;
			double_move += new_col;
        	double_move += new_row-2;
			double_move += new_col+2;
			double_move[0] = move[0] + 'A';
			double_move[1] = move[1] + '1';
			double_move[2] = move[2] + 'A';
			double_move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				make_move_cpu(move, player);
			double_move = "";
		}
	}
}
bool Checkers::is_game_over(const bool fact)const
{
	if(fact == true)
		return true;
	int cyan = 0;
	int white = 0;
	static int turns = 0;
	for(int j = 0; j < 8; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			if(board[j][i].occupied() && board[j][i].is_white() == true)
				white++;
			else if(board[j][i].occupied() && board[j][i].is_white() == false)
				cyan++;
		}
	}
	cout << "WHITE has " << white << " Pieces remaining.\n";
	cout << "RED has " << cyan << " Pieces remaining.\n";
	if(white == 0)
	{
		cout << "RED Wins!!!!\n";
		return true;
	}
	else if(cyan == 0)
	{
		cout << "WHITE Wins!!!!\n";
		return true;
	}
	else if(turns == 200)
	{
		if(white > cyan)
			cout << "WHITE Wins!!!!\n";
		else if(cyan > white)
			cout << "RED Wins!!!!\n";
		else
			cout << "It is a tie :(\n";
		return true;	
	}
	else
	{
		turns++;
		return false;
	}
}
bool Checkers::double_jump(int row, int col)const
{
	//checking for double jumps if cyan king
	if(board[row][col].kinged() == true && board[row][col].occupied() == true && board[row][col].is_white() == false)
	{
		//checks for adjacent piece
		if(board[row+1][col+1].occupied() == true)
		{
			//checks if enemy
			if(board[row+1][col+1].is_white() == true)
			{
				//checks for open space
				if(board[row+2][col+2].occupied() == false)
				{
                	if(col+2 <= 7 && row+2 <= 7)
                    {
                    	return true;
                    }
				}
			}
		}
		//checks for adjacent piece
		if(board[row-1][col-1].occupied() == true)
		{
			//checks if enemy
			if(board[row-1][col-1].is_white() == true)
			{
				//checks for open space
				if(board[row-2][col-2].occupied() == false)
				{
                	if(col-2 >= 0 && row-2 >= 0)
                    {
                    	return true;
                    }
				}
			}
		}
		//checks for adjacent piece
		if(board[row+1][col-1].occupied() == true)
		{
			//checks if enemy
			if(board[row+1][col-1].is_white() == true)
			{
				//checks for open space
				if(board[row+2][col-2].occupied() == false)
				{
               		if(col-2 >= 0 && row+2 <= 7)
                	{
                		return true;
                	}
				}
			}
		}
		//checks for adjacent piece
		if(board[row-1][col+1].occupied() == true)
		{
			//checks if enemy
			if(board[row-1][col+1].is_white() == true)
			{
				//checks for open space
				if(board[row-2][col+2].occupied() == false)
				{
                	if(col+2 <= 7 && row-2 >= 0)
                	{
                		return true;
                	}
				}
			}
		}
	}
	//check for doublejumps white king
	if(board[row][col].kinged() == true && board[row][col].occupied() == true && board[row][col].is_white() == true)
	{
		//each else looks at every possible move

		//checks for adjacent piece
		if(board[row+1][col+1].occupied() == true)
		{
			//checks if enemy
			if(board[row+1][col+1].is_white() == false)
			{
				//checks for open space
				if(board[row+2][col+2].occupied() == false)
				{
					if(col+2 <= 7 && row+2 <= 7)
                    {
                    	return true;
                    }
				}
			}
		}
		//checks for adjacent piece
		if(board[row-1][col-1].occupied() == true)
		{
			//checks if enemy
			if(board[row-1][col-1].is_white() == false)
			{
				//checks for open space
				if(board[row-2][col-2].occupied() == false)
				{
					if(col-2 >= 0 && row-2 >= 0)
                    {
                    	return true;
                    }
				}
			}
		}
		//checks for adjacent piece
		if(board[row+1][col-1].occupied() == true)
		{
			//checks if enemy
			if(board[row+1][col-1].is_white() == false)
			{
				//checks for open space
				if(board[row+2][col-2].occupied() == false)
				{
					if(col-2 >= 0 && row+2 <= 7)
                    {
                   		return true;
                    }
				}
			}
		}
		//checks for adjacent piece
		if(board[row-1][col+1].occupied() == true)
		{
			//checks if enemy
			if(board[row-1][col+1].is_white() == false)
			{
				//checks for open space
				if(board[row-2][col+2].occupied() == false)
				{
					if(col+2 <= 7  && row-2 >= 0)
                    {
                    	return true;
                    }
				}
			}
		}
	}
	//check for doublejumps cyan
	if(board[row][col].occupied() == true && board[row][col].is_white() == false)
	{
		//checks for adjacent piece
		if(board[row-1][col-1].occupied() == true)
		{
			//checks if enemy
			if(board[row-1][col-1].is_white() == true)
			{
				//checks for open space
				if(board[row-2][col-2].occupied() == false)
				{
					if(col-2 >= 0 && row-2 >= 0)
					{
						return true;
					}
				}
			}
		}
		//checks for adjacent piece
		if(board[row-1][col+1].occupied() == true)
		{
			//checks if enemy
			if(board[row-1][col+1].is_white() == true)
			{
				//checks for open space
				if(board[row-2][col+2].occupied() == false)
				{
					if(col+2 <= 7 && row-2 >= 0)
                    {
                    	return true;
                    }
				}
			}
		}
	}
	//check for doublejumps white
	if(board[row][col].occupied() == true && board[row][col].is_white() == true)
	{
		//checks for adjacent piece
		if(board[row+1][col-1].occupied() == true)
		{
			//checks if enemy
			if(board[row+1][col-1].is_white() == false)
			{
				//checks for open space
				if(board[row+2][col-2].occupied() == false)
				{
                	if(col-2 >= 0 && row+2 <= 7)
                    {
                    	return true;
                    }
				}
			}
		}
		//checks for adjacent piece
		if(board[row+1][col+1].occupied() == true)
		{
			//checks if enemy
			if(board[row+1][col+1].is_white() == false)
			{
				//checks for open space
				if(board[row+2][col+2].occupied() == false)
				{
                    if(col+2 <= 7 && row+2 <= 7)
                   	{
                    	return true;
                	}
				}
			}
		}
	}		
	return false;
}
bool Checkers::move_available(const bool player)
{
	for(int j = 0; j < 8; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			//checks for possible white moves
			if(board[j][i].occupied() == true && board[j][i].is_white() == true && player == false)
			{
				if(board[j+1][i-1].occupied() == false || board[j+1][i+1].occupied() == false)
				{
					return true;
				}
			}
			//checks for possible cyan moves
			else if(board[j][i].occupied() && board[j][i].is_white() == false && player == true)
			{
				if(board[j-1][i-1].occupied() == false || board[j-1][i+1].occupied() == false)
				{
					return true;
				}
			}
		}
	}
	return false;
}
void Checkers::make_double_move(const bool player, int row, int col)
{
			int is_equal_row;
			int is_equal_col;
			display_status();
    		string move;
			if(player == true)
				display_message("Player 1(RED), further move available\n");
			else
				display_message("Player 2(WHITE), further move available\n");
			move = get_user_move(player);
			is_equal_col = (int)toupper(move[0]-'A');
			is_equal_row = (int)(move[1]-'1');
			//makes sure the move is still moving the same piece
			while(row != is_equal_row || col != is_equal_col)
			{
				cout << "Must continue double jump!\n";
				move = get_user_move(player);
				is_equal_col = (int)toupper(move[0]-'A');
				is_equal_row = (int)(move[1]-'1');
			}
			while(!is_legal(move, player))
			{
			    display_message("Illegal move.\n");
			    move = get_user_move(player);
				is_equal_col = (int)toupper(move[0]-'A');
				is_equal_row = (int)(move[1]-'1');
				//makes sure that it is still the same piece and also a legal move although if it isn't legal it likely didn't make it to this stage, redundance is probalby never a bad idea
				while(row != is_equal_row || col != is_equal_col)
				{
					cout << "Must continue double jump!\n";
					move = get_user_move(player);
					is_equal_col = (int)toupper(move[0]-'A');
					is_equal_row = (int)(move[1]-'1');
				}
        	}
			make_move(move, player);
}
void Checkers::compute_moves(queue<string>& moves)const
{
	bool player = false;
	string move = "";
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			//down and left
        	move += i;
			move += j;
        	move += i+1;
			move += j-1;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//up and left
        	move += i;
			move += j;
        	move += i-1;
			move += j-1;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//down and right
        	move += i;
			move += j;
        	move += i+1;
			move += j+1;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//up and right
        	move += i;
			move += j;
        	move += i-1;
			move += j+1;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//jumps
			//down 2 left 2
        	move += i;
			move += j;
        	move += i+2;
			move += j-2;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//up 2 left 2
        	move += i;
			move += j;
        	move += i-2;
			move += j-2;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//down 2 right 2
			move += i;
			move += j;
        	move += i+2;
			move += j+2;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
			//up 2 right 2
        	move += i;
			move += j;
        	move += i-2;
			move += j+2;
			move[0] = move[0] + 'A';
			move[1] = move[1] + '1';
			move[2] = move[2] + 'A';
			move[3] = move[3] + '1';
			if(is_legal(move, player) == true)
				moves.push(move);
			move = "";
		}
	}
}
int Checkers::evaluate()const
{
	int score = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j].occupied() == true && board[i][j].is_white() == true && board[i][j].kinged() == false)
				score += 1;
			if(board[i][j].occupied() == true && board[i][j].is_white() == false && board[i][j].kinged() == false)
				score -= 1;
			if(board[i][j].occupied() == true && board[i][j].is_white() == true && board[i][j].kinged() == true)
				score += 2;
			if(board[i][j].occupied() == true && board[i][j].is_white() == false && board[i][j].kinged() == true)
				score -= 2;
		}
	}
	return score;
}
