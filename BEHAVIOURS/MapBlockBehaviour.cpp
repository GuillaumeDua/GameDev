#include "./MapBlockBehaviour.h"

MapBlockBehaviour::MapBlockBehaviour(AEntity * e)
  : IEntityBehaviour(e, 0x0)
{}

bool		MapBlockBehaviour::OnBorderCollision(void)
{
  std::cout << this->_this << " #===> MapBlock : Border Collision detected !" << std::endl;
  return false;
}

bool		MapBlockBehaviour::OnCollision(void)
{
  std::cout << this->_this << " #===> MapBlock : Collision detected !" << std::endl;
  this->_this->ResetCollision();
  return true;
}

bool		MapBlockBehaviour::Routine(void)
{
  if (!(this->_this->GetCollisionStack().empty()))
    return false;
  return true;
}
