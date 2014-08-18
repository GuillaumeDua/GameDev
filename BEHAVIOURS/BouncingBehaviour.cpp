#include "BouncingBehaviour.h"


BouncingBehaviour::BouncingBehaviour(AEntity * __this__, const RatiolizedVector2D & d)
  : ConstMoveBehaviour(__this__, d)
{}


bool		BouncingBehaviour::OnBorderCollision(void)
{
  std::cout << this->_this << " : reversing vector" << std::endl;
  this->_vector.Reverse();
  this->_this->ResetCollision();
  return true;
}

bool		BouncingBehaviour::OnCollision(void)
{
  return false;
}

bool		BouncingBehaviour::Routine(void)
{
  this->_this->MoveInDirection(this->_vector);
  return true;
}
