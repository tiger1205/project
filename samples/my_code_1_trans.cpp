#include <iostream>
#include "Matrix.h"
#include <math.h>
using namespace std; 
int main () { 
matrix m1( matrix::matrixRead ("../samples/my_code_1a.data" ) ) ; 
matrix m2( matrix::matrixRead ("../samples/my_code_1b.data" ) ) ; 
int r1; 
r1 = m1.numRows();
int c1; 
c1 = m1.numCols();
int r2; 
r2 = m2.numRows();
int c2; 
c2 = m2.numCols();
matrix m( r1,c2) ; 
for (int i = 0;i < r1; i ++ ) { 
		for (int j = 0;j < c2; j ++ ) { 
			*(m.access(i,j)) = 0 ;} } 
			int i; 
			int j; 
			int k; 
			for (i = 0 ;i <= (r1-1); i++ )	{ 
				for (j = 0 ;j <= (c2-1); j++ )	{ 
					for (k = 0 ;k <= (c1-1); k++ )	{ 
						*(m.access(i, j)) = (*( m.access(i, j)) +(*( m1.access(i, k)) **( m2.access(k, j)) )) ; 
						} 

 
					 } 

				} 

			cout << r1; 
			cout << " "; 
			cout << c2; 
			cout << "\n"; 
			for (i = 0 ;i <= (r1-1); i++ )	{ 
				for (j = 0 ;j <= (c2-1); j++ )	{ 
					cout << *( m.access(i, j)) ; 
					cout << " "; 
                 } 

			cout << "\n"; 
           } 

 
}
