//=============================================================================
//D class for matricies of doubles

#include "matrix.h"

#include <assert.h>
#include <iostream>
#include <iomanip>

// types: classes, enums, typedefs
// variables: consts, statics, exported variables (declared extern elsewhere)
// local forward function declarations

//=============================================================================
matrix::matrix()
//
//D Default constructor
//
  :m_x(0),
   m_y(0),
   m_valid(false)
{
  assert(false);
}


//=============================================================================
matrix::matrix(const int x, const int y)
//
//D rectangular matrix constructor of x by y
//
  :m_x(x),
   m_y(y),
   m_valid(true)
{
  assert(x > 0);
  assert(y > 0);
  m_array = new double[x*y];
  for (int i = 0; i < x*y; ++i) {
    m_array[i] = 0;
  }
}


//=============================================================================
matrix::matrix(const int n)
//
//D constructs a nxn square matrix
//
  :m_x(n),
   m_y(n),
   m_valid(true)
{
  assert(n > 0);
  m_array = new double[n*n];
  for (int i = 0; i < n*n; ++i) {
    m_array[i] = 0;
  }
}

//=============================================================================
void matrix::operator=(const matrix& m)
//
//D assignment operator
//
{
  this->become(m);
}

//=============================================================================
void matrix::become(const matrix& m)
//
//D assignment operator
//
{
  assert(m.valid());
  // if the size of the necessary arrays don't line up, MAKE THEM!!
  if (m_x*m_y != m.x()*m.y()) {
    delete [] m_array;
    m_array = new double[m.x()*m.y()];
  }

  // take a shallow copy of the new matricies array and copy it
  const double* shallow_copy = m.array();
  for (int i =0; i < m.x()*m.y(); ++i) {
    m_array[i] = shallow_copy[i];
  }
  m_x = m.x();
  m_y = m.y();
  m_valid = true;
  // <nnn> validate();
  assert(valid());
}

//=============================================================================
matrix::matrix(const matrix& m)
//
//D copy constructor
//
  :m_x(m.x()),
   m_y(m.y()),
   m_valid(true)
{
  assert(m.valid());
  m_array = new double[m.x()*m.y()];
  const double* shallow_copy = m.array();
  for (int i =0; i < m.x()*m.y(); ++i) {
    m_array[i] = shallow_copy[i];
  }
}

//=============================================================================
matrix::~matrix()
//
//D Destructor
//
{
  delete [] m_array;
}

//=============================================================================
void matrix::print(const bool precision) const
//
//D prints the matrix to standard output
//
{
  assert(valid());
  assert(precision >= 0);

  int index = 0;
  int power = 1;
  double largest = 0;
  // loop till you have the length of the alrgest number
  if (precision) {
    largest = max();
    while (largest > power) {
      ++index;
      power *= 10;
    }
    if (index == 0) index = 1;
  }
  for (int j = 0; j < m_y; ++j) {
    for (int i = 0; i < m_x; ++i) {
      std::cout << std::setw(index) << get(i,j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

//=============================================================================
double& matrix::get(const int i, const int j)
//
//D returns item i j
//
{
  assert(valid());
  assert(i < m_x);
  assert(j < m_y);
  return m_array[(j*m_x) + i];
}

//=============================================================================
const double& matrix::get(const int i, const int j) const
//
//D returns item i j
//
{
  assert(valid());
  assert(i < m_x);
  assert(j < m_y);
  return m_array[(j*m_x) + i];
}

//=============================================================================
const double& matrix::operator()(const int i, const int j) const
//
//D returns item i j
//
{
  assert(valid());
  assert(i < m_x);
  assert(j < m_y);
  return get(i,j);
}

//=============================================================================
double& matrix::operator()(const int i, const int j)
//
//D returns item i j
//
{
  assert(valid());
  assert(i < m_x);
  assert(j < m_y);
  return get(i,j);
}

//=============================================================================
void matrix::zero()
//
//D sets the matrix to zero;
//
{
  assert(valid());
  constant(0);
}

//=============================================================================
void matrix::scalar(const double& d)
//
//D sets the matrix to d*I where I is the identity;
//
{
  assert(valid());
  assert(square());
  identity();
  *this = *this * d;
}

//=============================================================================
void matrix::identity()
//
//D sets the matrix to the identity
//
{
  assert(square());
  assert(valid());
  for (int i =0; i < m_x; ++i) {
    for (int j =0; j < m_y; ++j) {
      if (i == j) {
        get(i,j) = 1;
      } else {
        get(i,j) = 0;
      }
    }
  }
}

//=============================================================================
void matrix::constant(const double& d)
//
//D sets the matrix to all entries d
//
{
  assert(valid());
  for (int i = 0; i < m_x*m_y; ++i) {
    m_array[i] = d;
  }
}

//=============================================================================
const int matrix::x() const
//
//D returns x
//
{
  assert(valid());
  return m_x;
}

//=============================================================================
const int matrix::y() const
//
//D returns y
//
{
  assert(valid());
  return m_y;
}

//=============================================================================
const double matrix::max() const
//
//D returns the maximum element
//
{
  assert(valid());
  double max = m_array[0];
  for (int i = 1; i < m_x*m_y; ++i) {
    if (m_array[i] > max) max = m_array[i];
  }
  return max;
}

//=============================================================================
const double matrix::min() const
//
//D returns the minimum element
//
{
  assert(valid());
  double min = m_array[0];
  for (int i = 1; i < m_x*m_y; ++i) {
    if (m_array[i] < min) min = m_array[i];
  }
  return min;
}

//=============================================================================
const bool matrix::valid() const
//
//D returns m_valid
//
{
  bool ok = true;
  ok = m_valid && (m_x != 0) && (m_y != 0);
  return ok;
}

//=============================================================================
void matrix::validate()
//
//D sets m_valid to true
//
{
  m_valid = true;
}

//=============================================================================
const double* matrix::array() const
//
//D returns the array, the outside world can't use this
//
{
  assert(valid());
  return m_array;
}

//=============================================================================
matrix matrix::operator+(const matrix& m) const
//
//D matrix addition
//
{
  assert(m.valid());
  assert(valid());
  assert(m.x() == m_x);
  assert(m.y() == m_y);

  matrix tmp(m_x,m_y);
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m_y; ++j) {
      tmp(i,j) = get(i,j) + m.get(i,j);
    }
  }
  return tmp;
}

//=============================================================================
matrix matrix::operator-(const matrix& m) const
//
//D matrix subtraction
//
{
  assert(m.valid());
  assert(valid());
  assert(m.x() == m_x);
  assert(m.y() == m_y);

  matrix tmp(m_x,m_y);
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m_y; ++j) {
      tmp(i,j) = get(i,j) - m.get(i,j);
    }
  }
  return tmp;
}

//=============================================================================
matrix matrix::operator*(const matrix& m) const
//
//D matrix multiplication, returns a matrix of dimension m_y by m.x()
//
{
  assert(m.valid());
  assert(valid());
  assert(m_x == m.y());

  matrix tmp(m_y,m.x());
  tmp.zero();

  // standard matrix multiplication algorithm in A*B:
  // for (i,j) sum the elementwise multiplication of the jth row of A by the
  // ith column of B
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m.y(); ++j) {
      const double* row = this->row(j);
      const double* column = m.column(i);
      double sum = 0;
      for (int k = 0; k < m_y; ++k) {
        sum += column[k]*row[k];
      }
      tmp(i,j) = sum;
      
      // clean up the memory
      delete [] row;
      delete [] column;
    }
  }

  return tmp;
}

//=============================================================================
matrix matrix::operator*(const double& d) const
//
//D scalar multiplication
//
{
  assert(valid());
  matrix tmp(m_x, m_y);
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m_y; ++j) {
      tmp(i,j) = d*get(i,j) ;
    }
  }

  return tmp;
}

//=============================================================================
matrix matrix::operator*=(const double& d)
//
//D scalar multiplication
//
{
  *this = (*this)*d;
}

//=============================================================================
matrix matrix::operator*=(const matrix& m)
//
//D matrix multiplication
//
{
  *this = (*this)*m;
}

//=============================================================================
matrix matrix::operator+=(const matrix& m)
//
//D matrix addition
//
{
  *this = (*this)+m;
}

//=============================================================================
matrix matrix::operator-=(const matrix& m)
//
//D matrix addition
//
{
  *this = (*this)-m;
}
//=============================================================================
const bool matrix::operator==(const matrix& m) const
//
//D equality operator
//
{
  assert(valid());
  assert(m.valid());
  assert(m_x == m.x());
  assert(m_y == m.y());
  const double* shallow_copy = m.array();
  for (int i = 0; i < m_x*m_y; ++i) {
    if (m_array[i] != shallow_copy[i]) return false;
  }
  return true;
}

//=============================================================================
const bool matrix::operator!=(const matrix& m) const
//
//D inequality operator
//
{
  return !(*this == m);
}

//=============================================================================
void matrix::transpose()
//
//D transposes the matrix
//
{
  assert(valid());
  matrix tmp(m_y, m_x);
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m_y; ++j) {
      tmp(j,i) = get(i,j);
    }
  }
  become(tmp);
}

//=============================================================================
const bool matrix::square() const
//
//D returns true if square
//
{
  assert(valid());
  return m_x == m_y;
}

//=============================================================================
const double matrix::determinant() const
//
//D returns the determinant
//
{
  assert(valid());
  assert(square());
  
  



  
  return 0;
}

//=============================================================================
matrix matrix::invert()
//
//D inverts the matrix
//
{
  assert(valid());
  assert(square());
  double det = determinant();
  // create a new square matrix
  matrix tmp(m_x);

  return tmp;
}

//=============================================================================
void matrix::change_size(const int x, const int y)
//
//D grows or shrinks the matrix to x by y, retains data and fills with 0
//
{
  assert(valid());
  assert(x > 0);
  assert(y > 0);

  // do nothing if nothing is needed
  if (x == m_x && y == m_y) return;

  matrix tmp(x,y);

  for (int i = 0; i < m_x; ++i) {
    if (i >= x) continue;
    for (int j = 0; j < m_y; ++j) {
      if (j >= y) break;
      tmp(i,j) = get(i,j);
    }
  }
  become(tmp);
}

//=============================================================================
const double* matrix::column(const int i) const
//
//D returns the ith column, gives ownership of this double* to the caller
//
{
  assert(valid());
  assert(i < m_x);
  double* tmp = new double[m_y];
  for (int j = 0; j < m_y; ++j) {
    tmp[j] = get(i,j);
  }
  return tmp;
}

//=============================================================================
const double* matrix::row(const int i) const
//
//D returns the ith row, gives ownership of this double* to the caller
//
{
  assert(valid());
  assert(i < m_y);
  double* tmp = new double[m_y];
  for (int j = 0; j < m_y; ++j) {
    tmp[j] = get(j,i);
  }
  return tmp;
}

//=============================================================================
void matrix::LUfactor(const matrix& lower, const matrix& upper)
//
//D returns by reference a lower triangular matrix L, and an upper triangular
//D matrix U such that this=L*U
//
{
  assert(valid());
  assert(square());
  
}

//=============================================================================
const bool matrix::lower_triangular() const
//
//D
//
{
  assert(valid());
  assert(square());
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m_y; ++j) {
      if (j < i) {
        if (get(i,j) != 0) return false;
      }
    }
  }
  return true;
}

//=============================================================================
const bool matrix::upper_triangular() const
//
//D
//
{
  assert(valid());
  assert(square());
  for (int i = 0; i < m_x; ++i) {
    for (int j = 0; j < m_y; ++j) {
      if (j > i) {
        if (get(i,j) != 0) return false;
      }
    }
  }
  return true;
}


//=============================================================================
const bool matrix::triangular() const
//
//D
//
{
  assert(valid());
  assert(square());
  return upper_triangular() || lower_triangular();
}

//=============================================================================
const bool matrix::diagonal() const
//
//D returns true if it is diagonal
//
{
  assert(valid());
  assert(square());
  // considering putting an actual implimentation here
  return upper_triangular() && lower_triangular();
}
