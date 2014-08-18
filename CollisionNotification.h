#ifndef __COLLISION_NOTIFICATION__
# define __COLLISION_NOTIFICATION__

# include "Collisionable.h"

class Collisionable;

// Declaration is forwarded into "Collisionable.h"
struct CollisionNotification
{
  CollisionNotification(Collisionable *,
			const Collisionable::FACE & f1 = Collisionable::NONE,
			const Collisionable::FACE & f2 = Collisionable::NONE);
  bool			IsCollisionOnFace(const Collisionable::FACE & f);

  Collisionable *	_target;
  Collisionable::FACE	_face1;
  Collisionable::FACE	_face2;
};


#endif // __COLLISION_NOTIFICATION__
