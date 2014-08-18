#ifndef __DISPLAY_ZONE__
# define __DISPLAY_ZONE__

# include "./Spec.h"
# include "./Entity.h"


class DisplayZone : public Entity
{
 public:
 DisplayZone(sf::Window * app,
       boost::shared_ptr<AEntitySprites> const & v,
       float x, float y)
   : Entity(app, v, 0, x, y, GS::SCREEN_WIDTH, GS::SCREEN_HEIGHT)
    {
      this->SetType(Collisionable::DISPLAY_ZONE);
    }

 DisplayZone(sf::Window * app,
	     boost::shared_ptr<AEntitySprites> const & v,
	     Point<float> pos)
   : Entity(app, v, 0, pos, Point<size_t>(GS::SCREEN_WIDTH, GS::SCREEN_HEIGHT))
      {
	this->SetType(Collisionable::DISPLAY_ZONE);
      }

 protected:
  const	Moveable *	_bindedEntity;
};


#endif // __DISPLAY_ZONE__
