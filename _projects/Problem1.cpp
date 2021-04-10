// integrate 8x^3 from 2 to 6
// theoretical answer from wolframalpha: 2560
// integral of 8x^3 equals 2x^4 + constant

// Includes needed files
#include <iostream>

// allow for not using std:: in code
using namespace std;

// Main function
int main()
{
  // Set up givens
  float a = 2;
  float b = 6;

  // Calculate answer
  float top = 2 * b * b * b * b;
  float bottom = 2 * a * a * a * a;
  float result = top - bottom;

  // Output
  cout << "The answer is: " << result << endl;

  // end function
  system("sleep 3");
  return 0;
}