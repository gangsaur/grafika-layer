#ifndef shape_h
#define shape_h
#include "point.h"
#include <list>

class shape{
	private:
		int corners;
		list<point*> points;
		
	public:	
		shape(int n){
			corners = n;
		}
		
		~shape(){
			points.clear();
		}
		
		void add(point* p) {
			points.push_back(p);
		}
		
		void add(int x, int y){
			points.push_back(new point(x,y));
		}
		
		point* get(int n){
			if (n < corners){
				std::list<point*>::iterator it = points.begin();
				int i = 0;
				while (i != n){
					++it;
					i++;
				}
				return *it;
			}
			else {
				return new point();
			}
		}
		
		int count(){
			return points.size();
		}
		
		int getCorner(){
			return corners;
		}
};
#endif
