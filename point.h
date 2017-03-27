#ifndef point_h
#define point_h
#include <list>

class point{
	private:
		int x;
		int y;
		
	public:	
		point(){
			x = 0;
			y = 0;
		}
		
		point(int x, int y){
			this->x = x;
			this->y = y;
		}
		
		~point(){
			
		}
		
		int getX(){
			return x;
		}

		int getY(){
			return y;
		}
};
#endif
