#include <iostream>
#include "Matrix.h"
#include <math.h>
using namespace std; 
int main () 
{ 
	int x; 
	x = 0;
	int y; 
	y = 1;
	while (y<11) 
	{ 
		cout << y; 
		cout << "\n"; 
		x = (x + y);
		y = (y + 1);
	
	 } 
	cout << x; 
	cout << "\n"; 
 
}

