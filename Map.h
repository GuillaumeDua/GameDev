#ifndef __MAP_SPECS__
# define __MAP_SPECS__

# include <vector>
# include "./Geometry.h"
# include "./Entity.h"

# define MAP_SYSTEM_DEBUG_OFF

namespace GS
{
  namespace Map
  {

    enum BLOCK_TYPE
    {
      EARTH,
      WATER,
      FIRE,
      LUMBER,
      METAL
    };

    class Block : public Entity
    {
    public:
    Block(sf::Window * app,
	  boost::shared_ptr<AEntitySprites> const & v,
	  float x, float y)
      : Entity(app, v, 0, x, y, 32, 32)
	{}

    Block(sf::Window * app,
	  boost::shared_ptr<AEntitySprites> const & v,
	  Point<float> pos)
      : Entity(app, v, 0, pos, Point<size_t>(32,32))
	{}

    protected:
      BLOCK_TYPE	_type;
    };

  }
}

#endif // __MAP_SPECS__
