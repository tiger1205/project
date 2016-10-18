#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <fstream>
#include <iostream>
using namespace std;

matrix::matrix (int _r, int _c)   {

  rows = _r;
  cols = _c;
  
  data = new float*[rows];
  
  for (int i = 0; i < rows; i++) {
      data[i] = new float[cols];
  }
    
}

// number of rows
int matrix::numRows () {return rows ; }

// number of cols
int matrix::numCols () {return cols ; }

// read a cell
float * matrix::access (const int i, const int j) const {
  return &data[i][j];
}

// overload output operator
std::ostream& operator<<(std::ostream &os, matrix &m) {
  os << m.numRows() << " " << m.numCols() << std::endl;
  
  for (int i = 0; i < m.numRows(); i++)	  {
		for (int j = 0; j < m.numCols(); j++) {
			os << *(m.access(i,j)) << "  ";	
		}
		os << std::endl;
  }
    
  return os;
}

// read matrix from a data file
matrix matrix::matrixRead (std::string filename) {
  int rows;
  int cols;
  
  std::ifstream in;
  in.open(filename.c_str());
  
  if (!in) {
	throw "File" + filename + " not found";
  }


  if (in.is_open()) {
	  in >> rows >> cols;
	  matrix m = matrix (rows, cols);
      
      for (int i = 0; i < m.numRows(); i++) {
		for (int j = 0; j < m.numCols(); j++) {
			in >> *(m.access(i,j));
		}
	  }
	in.close();
	
	return m;
	}
    else {
		throw "Cannot read the data file. ";
	}
}

// matrix copy function
matrix::matrix (const matrix& m) {
	rows = m.rows;
	cols = m.cols;
	 
	data = new float*[rows];
  
	for (int i = 0; i < rows; i ++) {
		data[i] = new float[cols];
    }
    
    for (int j = 0; j < rows; j++)	{
		for (int k = 0; k < cols; k++) {
			data[j][k] = *(m.access(j,k));
		}
	  }
    
}

  

