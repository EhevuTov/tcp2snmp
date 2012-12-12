#include "elem.h"

class tlv{
  elem element;
  public:
  tlv(char* data);
  private:
  int decode(char* data);
  int encode(char* data);
};
