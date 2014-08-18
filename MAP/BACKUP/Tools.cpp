#include "./Tools.h"

int	StringToInt(const std::string & str)
{
  int n;
  if (!(std::istringstream(str) >> n)) n = 0;
  return n;
}
