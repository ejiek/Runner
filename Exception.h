#ifndef _EXEPTION_H
#define _EXEPTION_H
#include <exception>
class NYException: public std::exception{
public:
  virtual const char* what() const throw()
  {
    return "There is a exception!";
  }
};
#endif