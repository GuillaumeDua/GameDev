#include "./ConstMoveBehaviour.h"

ConstMoveBehaviour::ConstMoveBehaviour(AEntity * e, const RatiolizedVector2D & v)
  : IEntityBehaviour(e, 0x0),
    _vector(v)
{}

bool		ConstMoveBehaviour::OnBorderCollision(void)
{
  std::cout << this->_this << "#===> Border Collision detected !" << std::endl;
  this->_this->ResetCollision();
  return false;
}

bool		ConstMoveBehaviour::OnCollision(void)
{
  std::cout << "#===> Collision detected !" << std::endl;
  this->_this->ResetCollision();
  return false;
}

bool		ConstMoveBehaviour::Routine(void)
{
  this->_this->MoveInDirection(this->_vector);
  return true;
}
