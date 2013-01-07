#include <iostream>

#define ENTERPRISE(s) 1,3,6,1,3,1,36872
//#define NUMBER3 #NUMBER1 ## #NUMBER2
#define NUMBER3(TRAP) TRAP ## 4
#define NUMBER4() 123 ## 4
#define NUMBER5 NUMBER3(123)
//#define TRAP(OID) ENTERPRISE ## OID


int main(void) {
  std::cout << NUMBER3(123) << std::endl;
  std::cout << NUMBER4() << std::endl;
  std::cout << NUMBER5 << std::endl;
  std::cout << TRAP << std::endl;
};
