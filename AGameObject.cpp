#include "AGameObject.h"


AGameObject::AGameObject(float x, float y, size_t sx, size_t sy)
  : Point(x,y),
    _size(sx, sy)
{}

AGameObject::AGameObject(Point<float> pos, Point<size_t> size)
  : Point(pos),
    _size(size)
{}

AGameObject::AGameObject(const AGameObject & r)
  : Point(r.GetPos()->_x, r.GetPos()->_y),
    _size(r.GetSize()._x, r.GetSize()._y)
{}

const Point<float> *	AGameObject::GetPos(void) const
{
  return static_cast<const Point<float> *>(this);
}

const Point<size_t> &	AGameObject::GetSize(void) const
{
  return this->_size;
}

void			AGameObject::SetPos(float x, float y)
{
  this->_x	= x;
  this->_y	= y;
}

void			AGameObject::SetPos(const Point<float> & p)
{
  this->_x	= p._x;
  this->_y	= p._y;
}

void			AGameObject::SetPos(Point<float> * p)
{
  this->_x	= p->_x;
  this->_y	= p->_y;
  delete p;
}

void			AGameObject::SetPos(const Point<float> * p)
{
  this->_x	= p->_x;
  this->_y	= p->_y;
}

void			AGameObject::SetSize(size_t x, size_t y)
{
#ifdef MOVEABLE_SAFETY_ON
  assert(x > 0 && y > 0);
  assert(this->_x + x <= GS::SCREEN_WIDTH &&
	 this->_y + y <= GS::SCREEN_HEIGHT);
#endif

  this->_size._x	= x;
  this->_size._y	= y;
}
