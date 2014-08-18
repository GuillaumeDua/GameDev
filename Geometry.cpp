#include "./Geometry.h"



RatiolizedVector2D::RatiolizedVector2D(float cX, float cY,
				       float dX, float dY)
{
  this->SetVars(cX, cY,
		dX, dY);
}

RatiolizedVector2D::RatiolizedVector2D(const RatiolizedVector2D & v)
{
  this->_x	= v._x;
  this->_y	= v._y;
}

RatiolizedVector2D::RatiolizedVector2D(const Point<float> & p1,
				       const Point<float> & p2)
{
  this->SetVars(p1, p2);
}

void		RatiolizedVector2D::SetVars(float cX, float cY,
					    float dX, float dY)
{
  this->_x	= dX - cX;
  this->_y	= dY - cY;

  const float ratio = RatiolizedVector2D::GetRatio(this->_x, this->_y);

  this->_x	/= ratio;
  this->_y	/= ratio;
}

void		RatiolizedVector2D::SetVars(const Point<float> & p1,
					    const Point<float> & p2)
{
  this->_x = (p2._x - p1._x);
  this->_y = (p2._y - p1._y);
    
  const float ratio = RatiolizedVector2D::GetRatio(this->_x, this->_y);
    
  this->_x	/= ratio;
  this->_y	/= ratio;
}

void		RatiolizedVector2D::Reverse(void)
{
  this->_x *= -1;
  this->_y *= -1;
}
