#ifndef __MAP_BLOCK__
# define __MAP_BLOCK__

# include "../Entity.h"
# include "../AEntitySprites.h"


namespace MAP
{
  class Block : public Entity
  {
  public:

    enum TYPE
    {
      UNDEFINED_TYPE	= 42,
      VOID,
      FIRE,
      WATER,
      METAL,
      EARTH,
      TREE
    };


  Block(const Block::TYPE & t,
	sf::Window * app,
	boost::shared_ptr<AEntitySprites> const & v,
	unsigned int s = Entity::DEFAULT_SPEED,
	float x = 0, float y = 0,
	size_t sx = 0, size_t sy = 0)
    : Entity(app, v, s, x, y, sx, sy),
      _BlockType(t)
      {
	this->_needGravityAction = false;
      }

    // overloader SetBehaviour

    const TYPE &	GetType(void) const
    {
      return this->_BlockType;
    }

  protected:
    TYPE		_BlockType;
  };
}

#endif // __MAP_BLOCK__
