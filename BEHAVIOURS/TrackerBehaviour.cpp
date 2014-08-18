#include "TrackerBehaviour.h"

TrackerBehaviour::TrackerBehaviour(AEntity * __this__,
				   AEntity * bondAEntity)
  : IEntityBehaviour(__this__, bondAEntity)
{
  assert(bondAEntity != 0x0);
}


bool		TrackerBehaviour::OnBorderCollision(void)
{
  std::cout << this->_this << " : TrackerBehaviour : OnBorderCollision" << std::endl;
  return false;
}

bool		TrackerBehaviour::OnCollision(void)
{
  Collisionable::CollisionableVector::iterator it;
  for (it = this->_this->GetCollisionStack().begin(); it != this->_this->GetCollisionStack().end(); ++it)
    std::cout << *it << std::endl;

  if (this->_this->IsCollision(*(this->_bondAEntity)))
    {
      std::cout << this->_this << " : TrackerBehaviour : OnCollision" << std::endl;
      return false;
    }
  return true;
}

bool		TrackerBehaviour::Routine(void)
{
  const float ratio	= RatiolizedVector2D::GetRatio(this->_bondAEntity->_x - this->_this->_x,
						       this->_bondAEntity->_y - this->_this->_y);
  
  this->_this->MoveInDirection((this->_bondAEntity->_x - this->_this->_x) / ratio,
			       (this->_bondAEntity->_y - this->_this->_y) / ratio);
  return true;
}
