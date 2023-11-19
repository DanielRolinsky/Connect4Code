#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Point //declaration of a class with name "Point"
{
  //class data members are private by default
  private:
    //here, define all the data members you have
    double x,y;
    
    //make x as read only
    
  //functions are public by default
  public:
    
    //Constructors --> Default and Data
    //1 - Default Constructor
    //The constructor name must match the class name (i.e. "Point")
    //Constructors have no return (i.e. no return type, no void please)
    //For default constructor, no parameters are passed
    Point() //no parameters
    {
      x = 5;
      y = 2;
    } //This function is within the class scope and thus has access to the private data members (i.e. it knows x and y)
    
    //Getters or Accessors for the read only variables defined as PRIVATE
    double get_x() //get_x() has no input parameters, how it knows the Object?!
    //example: destination1.get_x(), the function is applied to destination1
    //destination1 is passed to the function by reference, it is called implicit passing
    {
      return x; //"this" is the local name used for the passed object
    }
    
    double get_y()
    {
      return y;
    }
    
    //Setters or Mutators for the write only variables defined as PRIVATE
    void set_x(double x_value)
    {
      
    }
  
};

int main()
{
  Point destination1; //creating variable (i.e. Object) of type Point
  //The object name is "destination1". This object has 2 data members x, and y
  
  cout << destination1.get_x() << ", " << destination1.get_y() << endl;
  
  return EXIT_SUCCESS;
}