#include "ConfFileParser.h"
#include "MapLoader.h"

int	main(void)
{
  // ConfFileParser	cf("./map1.map");
  // cf.Dump();

  MapLoader		m("./map1.map");

  m.Dump();

  return 0;
}
