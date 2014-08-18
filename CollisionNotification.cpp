#include "CollisionNotification.h"

CollisionNotification::CollisionNotification(Collisionable * c,
					     const Collisionable::FACE & f1,
					     const Collisionable::FACE & f2)
  :_target(c),
   _face1(f1),
   _face2(f2)
{}

bool			CollisionNotification::IsCollisionOnFace(const Collisionable::FACE & f)
{
  return (this->_face1 == f || this->_face2 == f);
}
