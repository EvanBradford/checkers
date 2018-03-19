/*

	Evan Bradford
	4/8/16
	Checkers

*/
#ifndef pieces_h
#define pieces_h

class Pieces
{
	public:
		Pieces(){is_occupied = false; is_king = false; color = false; piece_color = false;}
		Pieces(bool occupied, bool king, bool ccolor, bool pieces){is_occupied = occupied; is_king = king; color = ccolor; piece_color = pieces;}
		void set_occupy(){is_occupied = true;}
		void unset_occupy(){is_occupied = false;}
		bool occupied()const{return is_occupied;}
		void set_kingme(){is_king = true;}
		void unset_kingme(){is_king = false;}
		bool kinged()const{return is_king;}
		void set_red(){color = true;}
		void set_black(){color = false;}
		bool is_red()const{return color;}
		void set_white(){piece_color = true;}
		void set_cyan(){piece_color = false;}
		bool is_white()const{return piece_color;}

	private:

		bool is_occupied;
		bool is_king;
		bool color;
		bool piece_color;
};
#endif
