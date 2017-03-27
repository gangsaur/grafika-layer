#include "framebuffer.h"
#include "layer.h"
#include <iostream>

using namespace std;

int main() {
	list<layer*> layers;
	framebuffer* fb = new framebuffer();
	layer* templ;
	shape* temps;
	list<layer*>::iterator it;
	list<shape*>::iterator currentshape;
	list<point*>::iterator currentpoint;
	int temp;
	int x,y,xn,yn;
	int i = 0;
	int j = 0;
	char ch;

	while(ch != 'x') {
		//system("clear");
		cout << "\nMain\n";
		ch = '\0';
		cin >> ch;
		switch(ch){
			case 'l':
				cout << "Layer making\n";
				templ = new layer();
				layers.push_back(templ);
				break;
			case 's':
				cout << "Shape making\n";
				it = layers.begin();
				i = 0;
				cin >> temp;
				while (i != temp){
					++it;
					i++;
				}
				cin >> temp;
				temps = new shape(temp);
				i = 0;
				while (i < temps->getCorner()){
					cin >> x;
					cin >> y;
					temps->add(x,y);
					i++;
				}
				(*it)->add(temps);
				break;
			case 'w':
				cout << "Write\n";
				it = layers.begin();
				i = 0;
				cin >> temp;
				while (i != temp){
					++it;
					i++;
				}
				cin >> temp;
				temps = (*it)->get(temp);
				cout << temps->count() << " Count\n";
				i = 0;
				/*
				while (i < temps->count()){
					cout << temps->get(i)->getX() + " X Pos ";
					cout << temps->get(i)->getY() + " Y Pos\n";
					i++;
					cout << temps->count();
				}
				*/
				while (i < temps->count()){
					x = temps->get(i)->getX();
					y = temps->get(i)->getY();
					i++;
					cout << x << " " << y << "\n";
				}
				break;
			case 'd':
				cout << "Draw\n";
				system("clear"); 
				it = layers.begin();
				//Pick a layer
				int c;
				c = 0;
				while (it != layers.end()){
					i = 0;
					//Pick a shape
					while (i < (*it)->count()){
						temps = (*it)->get(i);
						j = 0;
						//Pick a point
						while (j < temps->count()){
							if (j+1 < temps->count()){
								x = temps->get(j)->getX();
								y = temps->get(j)->getY();
								xn = temps->get(j+1)->getX();
								yn = temps->get(j+1)->getY();
								fb->insertLine(x,y,xn,yn,255,255,255);
							}
							else {
								x = temps->get(j)->getX();
								y = temps->get(j)->getY();
								xn = temps->get(0)->getX();
								yn = temps->get(0)->getY();
								fb->insertLine(x,y,xn,yn,255,255,255);
								}
							}
							//cout << x << " " << y << "\n";
							//cout << xn << " " << yn << "\n\n";
							j++;
						}
						i++;
					}
					it++;
					c++;
				}
				break;
			case 'x':
				break;
		}
	}
	
	delete fb;
}
