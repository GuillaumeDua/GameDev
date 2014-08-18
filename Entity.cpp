#include "./Entity.h"


Entity::Entity(sf::Window * app,
	       boost::shared_ptr<AEntitySprites> const & v,
	       unsigned int s,
	       float x, float y,
	       size_t sx, size_t sy)
  : AEntity(app, v, s, x, y, sx, sy),
    _isDeleted(false)
{}
  

Entity::Entity(sf::Window * app,
	       boost::shared_ptr<AEntitySprites> const & v,
	       unsigned int s,
	       Point<float> p,
	       Point<size_t> sz)
  : AEntity(app, v, s, p, sz),
    _isDeleted(false)
{}

Entity::Entity(const Entity & e)
  : _isDeleted(e.IsDeleteNotified()),
    AEntity(e)
{}

bool						Entity::Behave(void)
{
  // HP management ...

  return this->Behave_e();
}

bool						Entity::Behave_e(void)
{
  if (this->_behaviour.use_count() == 0)
    {
      std::cerr << this << "no behaviour set !" << std::endl;
      return false;
    }
  if ((this->GetHasBorderCollision() && !(this->_behaviour->OnBorderCollision()))
      ||
      (this->GetHasCollision() && !(this->_behaviour->OnCollision())))
      return false;

  return this->_behaviour->Routine();
}

void						Entity::SetBehaviour(boost::shared_ptr<IEntityBehaviour> const & b)
{
  this->_behaviour = b;
}

const boost::shared_ptr<IEntityBehaviour> &	Entity::GetBehaviour(void) const
{
  return this->_behaviour;
}

bool						Entity::IsBehaviourSet(void) const
{
  return (this->_behaviour.use_count() != 0);
}


bool						Entity::NotifyDelete(void)
{
  this->_isDeleted = true;
}

bool						Entity::IsDeleteNotified(void) const
{
  return this->_isDeleted;
}
