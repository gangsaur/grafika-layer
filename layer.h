#ifndef layer_h
#define layer_h
#include "shape.h"
#include <list>

class layer{
	private:
		list<shape*> shapes;
		
	public:
		layer(){
			
		}
		
		~layer(){
			shapes.clear();
		}
		
		void add(shape* s) {
			shapes.push_back(s);
		}
		
		shape* get(int n){
			if (n < shapes.size()){
				std::list<shape*>::iterator it = shapes.begin();
				int i = 0;
				while (i != n){
					++it;
					i++;
				}
				return *it;
			}
			else {
				return new shape(-1);
			}
		}
		
		int count(){
			return shapes.size();
		}
};
#endif
