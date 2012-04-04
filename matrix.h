//=============================================================================
// matrix.h
//
//  A matrix of doubles
//

#ifndef _matrix_H
#define _matrix_H

//=============================================================================
class matrix {
public:

  //---------------------------------------------------------------------------
  // Constructors, destructor and assignment
  //---------------------------------------------------------------------------

  matrix(const int x, const int y);
  // rectangular matrix constructor of x by y
  // Precondition: x > 0, y > 0

  matrix(const int n);
  // constructs a nxn square matrix
  // Precondition: n > 0

  void operator=(const matrix& m);
  void become(const matrix& m);
  // assignment operators
  // Precondition: m.valid()
  // Postcondition: valid()

  matrix(const matrix& m);
  // copy constructor
  // Precondition: m.valid()

  ~matrix();
  // Destructor

  //---------------------------------------------------------------------------
  // programming methods
  //---------------------------------------------------------------------------

  const bool valid() const;
  // returns m_valid

  void validate();
  // sets m_valid to true

  void print(const bool precision = true) const;
  // prints to standard output, if precision then it will try to work out how
  // many characters to print
  // Precondition: valid(), precision >= 0

  //---------------------------------------------------------------------------
  // member methods
  //---------------------------------------------------------------------------

  const double& operator()(const int i, const int j) const;
  double& operator()(const int i, const int j);
  const double& get(const int i, const int j) const;
  double& get(const int i, const int j);
  // returns item (i,j)
  // Precondition: i < m_x, j < m_y, valid()

  const double* column(const int i) const;
  // returns the ith column
  // Note: this gives ownership of the double* to the caller
  // Precondition: valid(), i < m_x
  
  const double* row(const int i) const;
  // returns the ith row
  // Note: this gives ownership of the double* to the caller
  // Precondition: valid(), i < m_y

  const int x() const;
  // returns x
  // Precondition: valid()

  const int y() const;
  // returns y
  // Precondition: valid()

  const double max() const;
  // returns the maximum element
  // Precondition: valid()

  const double min() const;
  // returns the minimum element
  // Precondition: valid()

  void change_size(const int x, const int y);
  // grows or shrinks the matrix to x by y, retains data and fills with 0
  // Precondition: valid(), x > 0, y > 0

  //---------------------------------------------------------------------------
  // matrix operatons
  //---------------------------------------------------------------------------

  matrix operator+(const matrix& m) const;
  matrix operator+=(const matrix& m);
  // matrix addition
  // Precondition: valid(), m.valid(), m.x() == m_x, m.y() == m_y

  matrix operator-(const matrix& m) const;
  matrix operator-=(const matrix& m);
  // matrix subtraction
  // Precondition: valid(), m.valid(), m.x() == m_x, m.y() == m_y

  matrix operator*(const matrix& m) const;
  matrix operator*=(const matrix& m);
  // matrix multiplication, returns a matrix of dimension m_y by m.x()
  // Precondition: valid(), m.valid(), m_x = m.y()

  matrix operator*(const double& d) const;
  matrix operator*=(const double& d);
  // scalar multiplication
  // Precondition: valid(), m.valid()

  const bool operator==(const matrix& m) const;
  // equaility operator
  // Precondition: valid(), m.valid(), m.x() == m_x, m.y() == m_y

  const bool operator!=(const matrix& m) const;
  // inequaility operator
  // Precondition: valid(), m.valid(), m.x() == m_x, m.y() == m_y

  void transpose();
  // transposes the matrix
  // Precondition: valid()

  const double determinant() const;
  // finds the determinant of the matrix
  // Precondition: valid(), square()

  matrix invert();
  // inverts the matrix
  // Precondition: vaild(), square()

  void LUfactor(const matrix& lower, const matrix& upper);
  // returns by reference a lower triangular matrix lower, and an upper
  // triangular matrix upper such that this=lower*upper
  // Will only give meaningful results if this(0,0) != 0 and will not work if
  // determinant is 0 but checking this would take longer
  // Precondition: valid(), square()

  //---------------------------------------------------------------------------
  // types of matrices
  //---------------------------------------------------------------------------

  void identity();
  // sets to the identity matrix
  // Precondition: valid(), square()

  void scalar(const double& d);
  // sets the matrix to the matrix dI, I is identity
  // Precondition: valid(), square()

  void zero();
  // sets the matrix to zero
  // Precondition: valid()

  void constant(const double& d);
  // sets the matrix to all elements d
  // Precondition: valid()

  const bool square() const;
  // returns true if square
  // Precondition: valid()

  const bool triangular() const;
  // returns true is the matrix is triangular

  const bool lower_triangular() const;
  // returns true is the matrix is lower triangular

  const bool upper_triangular() const;
  // returns true is the matrix is upper triangular

  const bool diagonal() const;
  // returns true is the matrix is diagonal

protected:

  matrix();
  // Prohibited default constructor

  // functions
  const double* array() const;
  // returns the array
  // Precondition: valid()

  // variables

private:

  // functions

  // variables
  double* m_array;
  int m_x;
  int m_y;
  bool m_valid;
};

#endif
