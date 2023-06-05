#ifndef MACRO_H
#define MACRO_H

#include <iostream>
#define DEBUGGING

#ifdef DEBUGGING
#define SHOW_WHERE  std::cout << __PRETTY_FUNCTION__ << std::endl;
#define ECHO(msg)   std::cout << msg << std::endl;
#define ERR(msg)   std::cerr << msg << std::endl;
#else
#define SHOW_WHERE
#define ECHO(msg)
#define ERR(msg)
#endif

#endif // MACRO_H
