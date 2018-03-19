// File: game.cxx

#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include "game.h"     // Provides definition of game class
using namespace std;

namespace main_savitch_14
{
    //*************************************************************************
    // STATIC MEMBER CONSTANTS
    // const int game::SEARCH_LEVELS;
    
    //*************************************************************************
    // PUBLIC MEMBER FUNCTIONS

    game::who game::play()
    // The play function should not be overridden. It plays one round of the
    // game, with the human player moving first and the computer second.
    // The return value is the winner of the game (or NEUTRAL for a tie).
    {
    	bool factoid = false;
		int answer;
		cout << " Welcome to virtual Checkers please choose one of the following: \n";
		cout << " 1. Single Player\n 2. Two-player\n 3. Quit\n";
		cin >> answer;
		if(answer == 1)
		{
			cin.ignore();
			restart();
			bool player = true;
	
			while(!is_game_over(factoid))
			{
				display_status();
			    if(player == true)
				{
					make_human_move(player);
				}
			    else
				{
					cout << "computer moving\n";
					make_computer_move( );
				}
				player = !player;
			}
			display_status( );
			return HUMAN;
		}
		else if(answer == 2)
		{
			cin.ignore();
			bool player = true;
			restart();
	
			while(!is_game_over(factoid))
			{
				display_status();
				make_human_move(player);
				player = !player;
			}
			display_status();
			return HUMAN;
		}
    }


    
    //*************************************************************************
    // OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)

    void game::display_message(const string& message) const
    {
		cout << message;
    }

    string game::get_user_move(const bool player)const
    {
		string answer;
		bool fact = true;
		display_message("Your move, please(EXAMPLE: A6B5): ");
		getline(cin, answer);
		if(answer == "Q" || answer == "q")
		{
			if(player == true)
			{
				cout << "WHITE Wins!!!!\n";
				is_game_over(fact);
			}	
			else
			{
				cout << "RED WINS!!!!\n";
				is_game_over(fact);
			}
		}
		answer[0] = toupper(answer[0]);
		answer[2] = toupper(answer[2]);
		return answer;
    }

    game::who game::winning( ) const
    {
	int value = evaluate( ); // Evaluate based on move that was just made.

	if (value > 0)
	    return last_mover( );
	else if (value < 0)
	    return next_mover( );
	else
	    return NEUTRAL;
    }



    //*************************************************************************
    // PRIVATE FUNCTIONS (these are the same for every game)

    int game::eval_with_lookahead(int look_ahead, int beat_this)
    // Evaluate a board position with lookahead.
    // --int look_aheads:  How deep the lookahead should go to evaluate the move.
    // --int beat_this: Value of another move that we?re considering. If the
    // current board position can't beat this, then cut it short.
    // The return value is large if the position is good for the player who just
    // moved. 
    {
    	queue<string> moves;   // All possible opponent moves
		int value;             // Value of a board position after opponent moves
    	int best_value;        // Evaluation of best opponent move
    	game* future;          // Pointer to a future version of this game
		bool player = false;
	
        // Base case:
		if (look_ahead == 0)
		{
		    if (last_mover( ) == COMPUTER)
		        return evaluate( );
		    else
				return -evaluate( );
		}

        // Recursive case:
        // The level is above 0, so try all possible opponent moves. Keep the
		// value of the best of these moves from the opponent's perspective.
    	compute_moves(moves); 
		// assert(!moves.empty());
    	best_value = INT_MIN;
    	while (!moves.empty( ))
    	{
		    future = clone( );
		    future->make_move_cpu(moves.front( ), player);
		    value = future->eval_with_lookahead(look_ahead-1, best_value);
		    delete future;
		    if (value > best_value)
		    {
				if (-value <= beat_this)
					return INT_MIN + 1; // Alpha-beta pruning
			best_value = value;
		    }
		    moves.pop( );
    	}
    	// The value was calculated from the opponent's perspective.
    	// The answer we return should be from player's perspective, so multiply times -1:
    	return -best_value;
    }

    void game::make_computer_move( )
    {
		queue<string> moves;
		int value;
		int best_value;
		bool player = false;
		string best_move;
		game* future;
	
		// Compute all legal moves that the computer could make.
		compute_moves(moves);
		assert(!moves.empty( ));
	
		// Evaluate each possible legal move, saving the index of the best
		// in best_index and saving its value in best_value.
		best_value = INT_MIN;
		while (!moves.empty( ))
		{
	 	   future = clone( );
	 	   future->make_move_cpu(moves.front( ), player);
	 	   value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
	 	   delete future;
	  	   if (value >= best_value)
	  	   {
				best_value = value;
				best_move = moves.front( );
	   	   }
	       moves.pop( );
		}
	    
		// Make the best move.
		make_move_cpu(best_move, player);
    }

    void game::make_human_move(const bool player)
    {
    	string move;
		if(player == true)
			display_message("Player 1(RED)\n");
		else
			display_message("Player 2(WHITE)\n");
		if(move_available(player) == true)
		{
			move = get_user_move(player);
			while(!is_legal(move, player))
			{
		 	   display_message("Illegal move.\n");
		 	   move = get_user_move(player);
        	}
			make_move(move, player);
		}
		else
			cout << "No move available skipping turn\n";	
    }
}
