
main () { 
	matrix m1 = matrixRead ( "../samples/my_code_1a.data" ) ;
	matrix m2 = matrixRead ( "../samples/my_code_1b.data" ) ;
	
	int r1;
	r1 = numRows(m1);
	int c1;
	c1 = numCols(m1);
	
	int r2;
	r2 = numRows(m2);
	int c2;
	c2 = numCols(m2);
	
	matrix m[r1:c2] i:j = 0;
	int i;
	int j;
	int k;
	
	  repeat (i = 0 to r1-1) {
      repeat (j = 0 to c2-1) {
          repeat (k = 0 to c1-1) {
              m[i:j] = m[i:j] + (m1[i:k] * m2[k:j]);
          }
      }
  }  
  print (r1);
  print (" ");
  print (c2);
  print ("\n");
        repeat (i = 0 to r1-1) {
        repeat (j = 0 to c2-1) {
			print (m[i:j]);
			print (" ");
        }
        print ("\n");
        }
																																																																																																								
}
