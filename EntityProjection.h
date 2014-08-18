#ifndef __ENTITY_PROJECTION__
# define __ENTITY_PROJECTION__

# include "./AEntity.h"

class EntityProjection : public AEntity
{
 public:
 EntityProjection(const AEntity & e) :
  _origin(&e),
    AEntity(NULL,
	    e.getVisuals(),
	    0,
	    e.GetMoveRequest()._x,
	    e.GetMoveRequest()._y,
	    e.GetSize()._x,
	    e.GetSize()._y)
      {}

  const AEntity *	GetOrigin(void) const
  {
    return this->_origin;
  }

  bool			Behave_e(void)
  {
    return false;
  }

 protected:
  const AEntity *	_origin;
};

#endif // __ENTITY_PROJECTION__
