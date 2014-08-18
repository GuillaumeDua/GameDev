#include "./Collisionable.h"


Collisionable::Collisionable(sf::Window * app,
			     unsigned int s,
			     float x, float y,
			     size_t sx, size_t sy)
  : Moveable(app, s, x, y, sx, sy),
    _hasBorderCollision(false),
    _needGravityAction(true),
    _type(UNDEFINED)
{}

Collisionable::Collisionable(sf::Window * app,
			     unsigned int s,
			     Point<float> pos,
			     Point<size_t> size)
  : Moveable(app, s, pos, size),
    _hasBorderCollision(false),
    _needGravityAction(true),
    _type(UNDEFINED)
{}

Collisionable::Collisionable(const Collisionable & m)
  : Moveable(m),
    _hasBorderCollision(m.GetHasBorderCollision()),
    _needGravityAction(m.GetNeedGravityAction()),
    _type(m.GetType())
{}

Collisionable::~Collisionable()
{
  // std::cout << this << " : Collisionable : dtor called" << std::endl;
  this->DestroyAnimation();
}

bool					Collisionable::GetHasCollision(void) const
{
  return (this->_collisionStack.size() != 0);
}

bool					Collisionable::GetHasBorderCollision(void) const
{
  return this->_hasBorderCollision;
}

bool					Collisionable::GetNeedGravityAction(void) const
{
  return this->_needGravityAction;
}

void					Collisionable::SetNeedGravityAction(const bool & v)
{
  this->_needGravityAction = v;
}


bool					Collisionable::IsCollision(void)
{
  return (this->GetHasBorderCollision() ||
	  this->GetHasCollision());
}

bool					Collisionable::IsCollision(const Collisionable & c)
{
  CollisionableVector::iterator	it;

  for (it = this->_collisionStack.begin(); it != this->_collisionStack.end(); ++it)
    if (*it == &c)
      return true;
  return false;
}

bool					Collisionable::IsCollisionRealTime(const Moveable & m)
{
  // if (this->_x + this->_size._x <= m.GetPos()->_x	||
  //     this->_y + this->_size._y <= m.GetPos()->_y	||
  //     this->_x <= m.GetPos()->_x + m.GetSize()._x	||
  //     this->_y <= m.GetPos()->_y + m.GetSize()._y
  //     )

  if ((m.GetPos()->_x >= this->_x + this->_size._x)
      ||	(m.GetPos()->_y >= this->_y + this->_size._y)
      ||	(m.GetPos()->_x + m.GetSize()._x <= this->_x)
      ||	(m.GetPos()->_y + m.GetSize()._y <= this->_y))
    return false; 
  return true;
}

bool					Collisionable::IsCollisionRealTime(const Moveable & m,
									   const Point<float> & pos)
{
  if ((pos._x >= this->_x + this->_size._x)
      ||	(pos._y >= this->_y + this->_size._y)
      ||	(pos._x + m.GetSize()._x <= this->_x)
      ||	(pos._y + m.GetSize()._y <= this->_y))
    return false; 
  return true;
}

// expensive
bool					Collisionable::IsBorderCollision(void)
{
  if (this->_x + this->_size._x <= 0
      ||	this->_y + this->_size._y <= 0
      ||	this->_x + this->_size._x >= this->_app->GetWidth()
      ||	this->_y + this->_size._y >= this->_app->GetHeight()
      )
    {
      this->_hasBorderCollision = true;
      return true;
    }
  return false;
}
  
void					Collisionable::NotifyCollision(Collisionable * e)
{
  this->_collisionStack.push_back(e);
}

void					Collisionable::DestroyAnimation(void)
{
  // std::cout << this << "Collisionable::DestroyAnimation : called" << std::endl;
}

void					Collisionable::ResetCollision(void)
{
  this->_collisionStack.clear();
}

void					Collisionable::ResetCollision(const Collisionable * c)
{
  CollisionableVector::iterator it;

  for (it = this->_collisionStack.begin(); it != this->_collisionStack.end(); ++it)
    {
      if (*it == c)
	  it = this->_collisionStack.erase(it);
    }
}

void					Collisionable::ResetBorderCollision(void)
{
  this->_hasBorderCollision = false;
}

Collisionable::CollisionableVector &	Collisionable::GetCollisionStack(void)
{
  return this->_collisionStack;
}

const Collisionable::TYPE &		Collisionable::GetType(void) const
{
  return this->_type;
}

void					Collisionable::SetType(const Collisionable::TYPE & t)
{
  this->_type = t;
}


// USELESS with MoveRequest system
// Collisionable::FACE			Collisionable::GetCollisionFace(const Collisionable & c)
// {
//   float	cx;
//   float	cy;

//   FACE	fx;
//   FACE	fy;

//   if (c.GetPos()->_y < this->_y)
//     {
//       if ((cy = (this->_y - c.GetPos()->_y)) < this->GetSize()._y)
// 	  fy = UP;
//       else fy = NONE;
//       cy = (this->_y + this->GetSize()._y) - c.GetPos()->_y;
//     }
//   else
//     {
//       if ((cy = (c.GetPos()->_y - this->_y)) < this->GetSize()._y)
// 	  fy = DOWN;
//       else fy = NONE;
//       cy = (c.GetPos()->_y + c.GetSize()._y) - this->GetPos()->_y;
//     }

//   if (fy == NONE) return NONE;

//   if (c.GetPos()->_x < this->_x)
//     {
//       if ((cx = (this->_x - c.GetPos()->_x)) < this->GetSize()._x)
// 	fx = LEFT;
//       else fx = NONE;
//       cx = (this->_x + this->GetSize()._x) - c.GetPos()->_x;
//     }
//   else
//     {
//       if ((cx = (c.GetPos()->_x - this->_x)) < this->GetSize()._x)
// 	fx = RIGHT;
//       else fx = NONE;
//       cx = (c.GetPos()->_x + c.GetSize()._x) - this->GetPos()->_x;
//     }

//   if (fx == NONE) return NONE;

//   return (cx > cy ? fx : fy);
// }

// // Useless with MoveRequest System
// void				Collisionable::CorrectPos(const Collisionable & c,
// 							  const Collisionable::FACE & f)
// {
//   switch (f)
//     {
//     case LEFT :
//       {
// 	std::cout << "LEFT" << std::endl;
// 	this->_x = c.GetPos()->_x + c.GetSize()._x;
// 	break;
//       }
//     case RIGHT :
//       {
// 	std::cout << "RIGHT" << std::endl;
// 	this->_x = c.GetPos()->_x - this->GetSize()._x;
// 	break;
//       }
//     case UP :
//       {
// 	std::cout << "UP" << std::endl;
// 	this->_y = c.GetPos()->_y + c.GetSize()._y;
// 	break;
//       }
//     case DOWN :
//       {
// 	std::cout << "DOWN" << std::endl;
// 	this->_y = c.GetPos()->_y - this->GetSize()._y;
// 	break;
//       }
//     default :
//       {
// 	std::cout << "FAIL" << std::endl;
// 	break;
//       }
//     }
// }

// // Useless with MoveRequest System
// void				Collisionable::CorrectPos(const Collisionable & c)
// {
//   Collisionable::FACE f = this->GetCollisionFace(c);
//   this->CorrectPos(c, f);
// }
