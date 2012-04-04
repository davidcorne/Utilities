#include "matrix.h"
#include "boolean_matrix.h"
#include <assert.h>
#include <iostream>

using namespace std;


int global_test_count = 0;

//=============================================================================
//
//D test function for the utils library when crash is true it will assert on
//D failure.
//D Using TDD thus when crash is false assert if the test passes else print
//D expected
//
void test(bool test, const char* message, bool crash=true)
{
  ++global_test_count;
  const char* expected = "(Expected) ";
  const char* unexpected = "(Not Expected) ";
  if (test) {
    if (!crash) {
      cout << "Test " << global_test_count << " Passed: " << unexpected
           << message << endl;
      assert(false);
    } else {
      cout << "Test " << global_test_count << " Passed: " <<  message << endl;
    }
  } else {
    if (!crash) {
      cout << "Test " << global_test_count << " Failed: " <<  expected
           << message << endl;
    } else {
      cout << "Test " << global_test_count << " Failed: " <<  message << endl;
    }
  }
  if (crash) {
    assert(test);
  }
}

void print_banner(const char* message)
{
  cout << endl;
  cout << "-------------------------------------------------------------------"
       << "------------" << endl;
  cout << message << endl;
  cout << "-------------------------------------------------------------------"
       << "------------" << endl;
  cout << endl;
}

//=============================================================================
//
//D test harness for the utils library
//
int main() {
  print_banner("Construction and assignment");
  matrix test1(11);
  // assigning test1
  for (int i = 0; i < test1.x(); ++i) {
    for (int j = 0; j < test1.y(); ++j) {
      test1(i,j) = j;
    }
  }
  test(test1.valid(), "construction and value setting makes a valid matrix");
  test(test1.square(), "made a square matrix");

  matrix test2 = test1;
  test(test1 == test2, "assignment and equality operator");

  for (int i = 0; i < test2.x(); ++i) {
    for (int j = 0; j < test2.y(); ++j) {
      test2(i,j) = i;
    }
  }

  print_banner("General operations");
  test1.transpose();
  test(test1 == test2, "is test1 the transpose of test2? ");
  test1.transpose();
  test(test1 != test2, "!= operator ");
  matrix test3 = test1 + test2;
  bool test_value = true;
  for (int i = 0; i < test3.x(); ++i) {
    for (int j = 0; j < test3.y(); ++j) {
      test_value = test_value && (test3(i,j) == i + j);
    }
  }
  test(test_value, "addition and transposition");

  print_banner("Types of matrices");
  test3.scalar(4);
  test_value = true;
  for (int i = 0; i < test3.x(); ++i) {
    for (int j = 0; j < test3.y(); ++j) {
      if (i == j) {
        test_value = test_value && (test3(i,j) == 4);
      } else {
        test_value = test_value && (test3(i,j) == 0);
      }
    }
  }
  test(test_value, "making a scalar matrix");

  test_value = true;
  test3.constant(4);
  for (int i = 0; i < test3.x(); ++i) {
    for (int j = 0; j < test3.y(); ++j) {
      test_value = test_value && (test3(i,j) == 4);
    }
  }
  test(test_value, "making a constant matrix");

  test3.identity();


  int x_4 = 3;
  int y_4 = 5;
  matrix test4(x_4,y_4);
  for (int i = 0; i < x_4; ++i) {
    test4(i,i) = 2;
  }
  test(test4.x() == x_4 && test4.y() == y_4,
       "correct dimensions for a rectangular matrix");
  test4.transpose();
  test(test4.x() == y_4 && test4.y() == x_4,
       "correct dimensions for a rectangular matrix after transposition");

  print_banner("Changing size");
  // growing in both, (3,5) -> (6,4)
  test4.change_size(6,4);
  test_value = true;
  test_value = test4.x() == 6 && test4.y() == 4;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value, "growing in both directions, information retained");

  // growing in x, (6,4) -> (7,4)
  test4.change_size(7,4);
  test_value = true;
  test_value = test4.x() == 7 && test4.y() == 4;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value, "growing in x, information retained");

  // growing in y, (7,4) -> (7,5)
  test4.change_size(7,5);
  test_value = true;
  test_value = test4.x() == 7 && test4.y() == 5;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value, "growing in y, information retained");

  // shrinking in x, (7,5) -> (4,5)
  test4.change_size(4,5);
  test_value = true;
  test_value = test4.x() == 4 && test4.y() == 5;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value,
       "shrinking in x, information retained");

  // shrinking in y (4,5) -> (4,4)
  test4.change_size(4,4);
  test_value = true;
  test_value = test4.x() == 4 && test4.y() == 4;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  // also checks it's square
  test_value = test_value && test4.square();
  test(test_value,
       "shrinking in y, information retained");

  // growing in x, shrinking in y (4,4) -> (5,3)
  test4.change_size(5,3);
  test_value = true;
  test_value = test4.x() == 5 && test4.y() == 3;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value,
       "growing in x, shrinking in y, information retained");


  // shrinking in x, growing in y (5,3) -> (3,5)
  test4.change_size(3,5);
  test_value = true;
  test_value = test4.x() == 3  && test4.y() == 5;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value,
       "shrinking in x, growing in y, information retained");


  // shrinking in both (3,5) -> (2,2)
  test4.change_size(2,2);
  test_value = true;
  test_value = test4.x() == 2 && test4.y() == 2;
  // check it has kept the data
  for (int i = 0; i < test4.x(); ++i) {
    for (int j = 0; j < test4.y(); ++j) {
      if (i == j && i < 3) {
        test_value = test_value && (test4(i,j) == 2);
      } else {
        test_value = test_value && (test4(i,j) == 0);
      }
    }
  }
  test(test_value,
       "shrinking in both directions, information retained");

  print_banner("Large matrix operations");
  int large = 10000;
  matrix giant(large);
  for (int i = 0; i < large; ++i) {
    for (int j = 0; j < large; ++j) {
      giant(i,j) = i+j;
    }
  }
  test(giant.max() == 19998, "largest member of a giant matrix");
  test(giant.min() == 0, "smallest member of a giant matrix");
  test(giant.x() == large && giant.y() == large, "giant matrix dimensions");
  giant.change_size(10,10);

  print_banner("Multiplication and identity");
  // now test multiplication and identity
  matrix id = matrix(10);
  id.identity();

  // a matrix going from 1 to 100 left to right, top to bottom
  matrix for_mul(10);
  for (int i = 0; i < 100; ++i) {
    for_mul(i % 10,i / 10) = i + 1;
  }
  // test the column function works
  double actual_column[10] = {6,16,26,36,46,56,66,76,86,96};
  const double* column = new double[10];
  column = for_mul.column(5);
  test_value = true;
  for (int i = 0; i < 10; ++i) {
    test_value = test_value && (column[i] == actual_column[i]);
  }
  test(test_value, "column works");
  delete [] column;

  // test the row function works
  double actual_row[10] = {51,52,53,54,55,56,57,58,59,60};
  const double* row = new double[10];
  row = for_mul.row(5);
  test_value = true;
  for (int i = 0; i < 10; ++i) {
    test_value = test_value && (row[i] == actual_row[i]);
  }
  delete [] row;

  test(test_value, "row works");
  test(id*for_mul == for_mul, "left multiplying by the identity");
  test(for_mul*id == for_mul, "right multiplying by the identity");

  // this matrix (originly randomly generated) defined by hand:
  // 1 1 1 1 1 1 1 1 0 1
  // 1 1 0 1 0 0 1 1 1 0
  // 0 0 1 1 1 1 1 0 0 1
  // 1 1 1 1 1 1 0 1 1 0
  // 0 1 1 1 1 1 1 0 1 1
  // 1 1 0 0 1 1 1 1 0 1
  // 1 1 1 0 1 0 0 1 0 0
  // 1 1 0 0 0 0 0 0 0 0
  // 0 0 1 0 0 1 0 1 1 1
  // 0 1 0 0 1 1 1 0 1 0
  
  // which has inverse:
  // -1.75  0.50  1.75  0.25 -0.75  0.50  0.25  1.25  0.25 -0.25
  //  1.75 -0.50 -1.75 -0.25  0.75 -0.50 -0.25 -0.25 -0.25  0.25
  //  0.50  0.00  0.50 -0.50 -0.50 -1.00  0.50  0.50  0.50  0.50
  //  0.50  0.00 -0.50  0.50  0.50  0.00 -0.50 -0.50 -0.50 -0.50
  // -1.50  0.00  0.50  0.50  0.50  1.00  0.50 -0.50 -0.50 -0.50
  //  1.25 -0.50 -0.25  0.25 -0.75 -0.50 -0.75  0.25  0.25  0.75
  //  0.25  0.50  0.75 -0.75 -0.75 -0.50  0.25  0.25  0.25  0.75
  //  1.00  0.00 -1.00  0.00  0.00  0.00  0.00 -1.00  0.00  0.00
  // -1.75  0.50  0.75  0.25  0.25  0.50  0.25  0.25  0.25 -0.25
  // -1.00  0.00  0.00  0.00  1.00  1.00  0.00  0.00  0.00 -1.00
  
  print_banner("Inversion");
  matrix hand(10);
  hand(0,0) = 1; hand(1,0) = 1; hand(2,0) = 1; hand(3,0) = 1; hand(4,0) = 1;
  hand(5,0) = 1; hand(6,0) = 1; hand(7,0) = 1; hand(8,0) = 0; hand(9,0) = 1;
  hand(0,1) = 1; hand(1,1) = 1; hand(2,1) = 0; hand(3,1) = 1; hand(4,1) = 0;
  hand(5,1) = 0; hand(6,1) = 1; hand(7,1) = 1; hand(8,1) = 1; hand(9,1) = 0;
  hand(0,2) = 0; hand(1,2) = 0; hand(2,2) = 1; hand(3,2) = 1; hand(4,2) = 1;
  hand(5,2) = 1; hand(6,2) = 1; hand(7,2) = 0; hand(8,2) = 0; hand(9,2) = 1;
  hand(0,3) = 1; hand(1,3) = 1; hand(2,3) = 1; hand(3,3) = 1; hand(4,3) = 1;
  hand(5,3) = 1; hand(6,3) = 0; hand(7,3) = 1; hand(8,3) = 1; hand(9,3) = 0;
  hand(0,4) = 0; hand(1,4) = 1; hand(2,4) = 1; hand(3,4) = 1; hand(4,4) = 1;
  hand(5,4) = 1; hand(6,4) = 1; hand(7,4) = 0; hand(8,4) = 1; hand(9,4) = 1;
  hand(0,5) = 1; hand(1,5) = 1; hand(2,5) = 0; hand(3,5) = 0; hand(4,5) = 1;
  hand(5,5) = 1; hand(6,5) = 1; hand(7,5) = 1; hand(8,5) = 0; hand(9,5) = 1;
  hand(0,6) = 1; hand(1,6) = 1; hand(2,6) = 1; hand(3,6) = 0; hand(4,6) = 1;
  hand(5,6) = 0; hand(6,6) = 0; hand(7,6) = 1; hand(8,6) = 0; hand(9,6) = 0;
  hand(0,7) = 1; hand(1,7) = 1; hand(2,7) = 0; hand(3,7) = 0; hand(4,7) = 0;
  hand(5,7) = 0; hand(6,7) = 0; hand(7,7) = 0; hand(8,7) = 0; hand(9,7) = 0;
  hand(0,8) = 0; hand(1,8) = 0; hand(2,8) = 1; hand(3,8) = 0; hand(4,8) = 0;
  hand(5,8) = 1; hand(6,8) = 0; hand(7,8) = 1; hand(8,8) = 1; hand(9,8) = 1;
  hand(0,9) = 0; hand(1,9) = 1; hand(2,9) = 0; hand(3,9) = 0; hand(4,9) = 1;
  hand(5,9) = 1; hand(6,9) = 1; hand(7,9) = 0; hand(8,9) = 1; hand(9,9) = 0;

  matrix inv(10);
  inv(0,0) = -1.75; inv(1,0) =  0.50; inv(2,0) =  1.75; inv(3,0) =  0.25;
  inv(4,0) = -0.75; inv(5,0) =  0.50; inv(6,0) =  0.25; inv(7,0) =  1.25;
  inv(8,0) =  0.25; inv(9,0) = -0.25; inv(0,1) =  1.75; inv(1,1) = -0.50;
  inv(2,1) = -1.75; inv(3,1) = -0.25; inv(4,1) =  0.75; inv(5,1) = -0.50;
  inv(6,1) = -0.25; inv(7,1) = -0.25; inv(8,1) = -0.25; inv(9,1) =  0.25;
  inv(0,2) =  0.50; inv(1,2) =  0.00; inv(2,2) =  0.50; inv(3,2) = -0.50;
  inv(4,2) = -0.50; inv(5,2) = -1.00; inv(6,2) =  0.50; inv(7,2) =  0.50;
  inv(8,2) =  0.50; inv(9,2) =  0.50; inv(0,3) =  0.50; inv(1,3) =  0.00;
  inv(2,3) = -0.50; inv(3,3) =  0.50; inv(4,3) =  0.50; inv(5,3) =  0.00;
  inv(6,3) = -0.50; inv(7,3) = -0.50; inv(8,3) = -0.50; inv(9,3) = -0.50;
  inv(0,4) = -1.50; inv(1,4) =  0.00; inv(2,4) =  0.50; inv(3,4) =  0.50;
  inv(4,4) =  0.50; inv(5,4) =  1.00; inv(6,4) =  0.50; inv(7,4) = -0.50;
  inv(8,4) = -0.50; inv(9,4) = -0.50; inv(0,5) =  1.25; inv(1,5) = -0.50;
  inv(2,5) = -0.25; inv(3,5) =  0.25; inv(4,5) = -0.75; inv(5,5) = -0.50;
  inv(6,5) = -0.75; inv(7,5) =  0.25; inv(8,5) =  0.25; inv(9,5) =  0.75;
  inv(0,6) =  0.25; inv(1,6) =  0.50; inv(2,6) =  0.75; inv(3,6) = -0.75;
  inv(4,6) = -0.75; inv(5,6) = -0.50; inv(6,6) =  0.25; inv(7,6) =  0.25;
  inv(8,6) =  0.25; inv(9,6) =  0.75; inv(0,7) =  1.00; inv(1,7) =  0.00;
  inv(2,7) = -1.00; inv(3,7) =  0.00; inv(4,7) =  0.00; inv(5,7) =  0.00;
  inv(6,7) =  0.00; inv(7,7) = -1.00; inv(8,7) =  0.00; inv(9,7) =  0.00;
  inv(0,8) = -1.75; inv(1,8) =  0.50; inv(2,8) =  0.75; inv(3,8) =  0.25;
  inv(4,8) =  0.25; inv(5,8) =  0.50; inv(6,8) =  0.25; inv(7,8) =  0.25;
  inv(8,8) =  0.25; inv(9,8) = -0.25; inv(0,9) = -1.00; inv(1,9) =  0.00;
  inv(2,9) =  0.00; inv(3,9) =  0.00; inv(4,9) =  1.00; inv(5,9) =  1.00;
  inv(6,9) =  0.00; inv(7,9) =  0.00; inv(8,9) =  0.00; inv(9,9) = -1.00;

  test((inv*hand) == id,
       "left multiplication of manual inverse yields identity");

  test((hand*inv) == id,
       "right multiplication of manual inverse yields identity");

  double determinant = 4;
  test(hand.determinant() == determinant, "determinant function", false);

  test_value = true;

  // use a 10^-15 tolerance with the inputted matrix
  matrix test_matrix(10);
  test_matrix = hand.invert() - inv;
  for (int i = 0; i < 100; ++i) {
    test_value = test_value && (test_matrix(i % 10, i / 10) < 10e-15)
      && (-10e-15 < test_matrix(i % 10, i / 10));
  }

  test(test_value, "inversion function, approximate answer", false);
  test(hand.invert() == inv, "inversion function, exact answer", false);

  print_banner("Triangular matrices and LU factorisation");
  matrix tri(10);
  // set up a matrix of all 5s below (and on) the diagonal and zero elsewhere
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (j >= i) {
        tri(i,j) = 5;
      }
    }
  }
  test(tri.triangular(), "lower triangular matrices are triangular");
  test(tri.lower_triangular(), "a lower triangular matrix");

  // reset tri and make it upper triangular
  tri.zero();
  // set up a matrix of all 5s above (and on) the diagonal and zero elsewhere
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (i >= j) {
        tri(i,j) = 5;
      }
    }
  }

  test(tri.triangular(), "upper triangular matrices are triangular");
  test(tri.upper_triangular(), "an upper triangular matrix");

  // reset tri and make it diagonal
  tri.zero();
  // set up a matrix of all 5s on the diagonal and zero elsewhere
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (i == j) {
        tri(i,j) = 5;
      }
    }
  }

  test(tri.triangular(), "diagonal matrices are triangular");
  test(tri.diagonal(), "a diagonal matrix");

  matrix lower(10);
  matrix upper(10);
  hand.LUfactor(lower, upper);
  cout << "lower: " << endl;
  lower.print();
  cout << "upper: " << endl;
  upper.print();
  test(lower.lower_triangular(), "L is lower triangular in LU factorisation", false);
  test(upper.upper_triangular(), "U is upper triangular in LU factorisation", false);
  test(hand == (lower*upper), "LU gives a factorisation", false);

  return 0;
}
