#include "Moveable.h"

Moveable::Moveable(sf::Window * app,
		   unsigned int s,
		   float x, float y,
		   size_t sx, size_t sy)
  : AGameObject(x, y, sx, sy)
{
#ifdef MOVEABLE_SAFETY_ON
  assert(x <= GS::SCREEN_WIDTH &&
	 y <= GS::SCREEN_HEIGHT);
#endif

  this->_speed	= s;
  this->_app	= app;
}


Moveable::Moveable(sf::Window * app,
		   unsigned int s,
		   Point<float> pos,
		   Point<size_t> size)
  : AGameObject(pos, size)
{
#ifdef MOVEABLE_SAFETY_ON
  assert(pos._x <= GS::SCREEN_WIDTH &&
	 pos._y <= GS::SCREEN_HEIGHT);
#endif

  this->_speed	= s;
  this->_app	= app;
}

Moveable::Moveable(const Moveable & m)
  : AGameObject(// m.GetPos(), m.GetSize()
		static_cast<AGameObject>(m))
{
  this->_speed	= m.GetSpeed();
  this->_app	= m.GetApp();
}


//
// -- Single axiales moves
//

void			Moveable::MoveLeft(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();
  if ((this->_x - s) < 0)
    this->_x = 0;
  else
    this->_x -= s;
  this->_directionX = false;
}

void			Moveable::MoveRight(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();

  if (this->_x + s + this->_size._x > (this->_app->GetWidth()))
    {
      this->_x = this->_app->GetWidth() - this->_size._x;
      return;
    }
  this->_x += s;
  this->_directionX = true;
}

void			Moveable::MoveUp(void)
{

  const float s = this->_speed * this->_app->GetFrameTime();
  if ((this->_y - s) < 0)
    this->_y = 0;
  else
    this->_y -= s;
}

void			Moveable::MoveDown(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();
  if (this->_y + s + this->_size._y > (this->_app->GetHeight()))
    {
      this->_y = this->_app->GetHeight() - this->_size._y;
      return;
    }
  this->_y += s;
}

void			Moveable::MoveLeft(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();
  if ((this->_x - s) < 0)
    this->_x = 0;
  else
    this->_x -= s;
  this->_directionX = false;
}

void			Moveable::MoveRight(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();

  if (this->_x + s + this->_size._x > (this->_app->GetWidth()))
    {
      this->_x = this->_app->GetWidth() - this->_size._x;
      return;
    }
  this->_x += s;
  this->_directionX = true;
}

void			Moveable::MoveUp(size_t speed)
{

  const float s = speed * this->_app->GetFrameTime();
  if ((this->_y - s) < 0)
    this->_y = 0;
  else
    this->_y -= s;
}

void			Moveable::MoveDown(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();
  if (this->_y + s + this->_size._y > (this->_app->GetHeight()))
    {
      this->_y = this->_app->GetHeight() - this->_size._y;
      return;
    }
  this->_y += s;
}


//
// -- Bi-axiales moves
//

void			Moveable::MoveLeftUp(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;

  if ((this->_x - s) < 0)
    this->_x = 0;
  else
    this->_x -= s;

  if ((this->_y - s) < 0)
    this->_y = 0;
  else
    this->_y -= s;

  this->_directionX = false;
}

void			Moveable::MoveRightDown(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;

  if (this->_x + s + this->_size._x > (this->_app->GetWidth()))
    this->_x = this->_app->GetWidth() - this->_size._x;
  else
    this->_x += s;

  if (this->_y + s + this->_size._y > (this->_app->GetHeight()))
    this->_y = this->_app->GetHeight() - this->_size._y;
  else
    this->_y += s;
  this->_directionX = true;
}

void			Moveable::MoveLeftDown(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;

  if (this->_x - s < 0)
    this->_x = 0;
  else
    this->_x -= s;

  if (this->_y + s + this->_size._y > (this->_app->GetHeight()))
    this->_y = this->_app->GetHeight() - this->_size._y;
  else
    this->_y += s;
  this->_directionX = false;
}

void			Moveable::MoveRightUp(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;

  if (this->_x + s + this->_size._x > (this->_app->GetWidth()))
    this->_x = this->_app->GetWidth() - this->_size._x;
  else
    this->_x += s;

  if (this->_y - s < 0)
    this->_y = 0;
  else
    this->_y -= s;
  this->_directionX = true;
}


void			Moveable::MoveRightDown(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;

  if (this->_x + s + this->_size._x > (this->_app->GetWidth()))
    this->_x = this->_app->GetWidth() - this->_size._x;
  else
    this->_x += s;

  if (this->_y + s + this->_size._y > (this->_app->GetHeight()))
    this->_y = this->_app->GetHeight() - this->_size._y;
  else
    this->_y += s;
  this->_directionX = true;
}

void			Moveable::MoveLeftDown(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;

  if (this->_x - s < 0)
    this->_x = 0;
  else
    this->_x -= s;

  if (this->_y + s + this->_size._y > (this->_app->GetHeight()))
    this->_y = this->_app->GetHeight() - this->_size._y;
  else
    this->_y += s;
  this->_directionX = false;
}

void			Moveable::MoveRightUp(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;

  if (this->_x + s + this->_size._x > (this->_app->GetWidth()))
    this->_x = this->_app->GetWidth() - this->_size._x;
  else
    this->_x += s;

  if (this->_y - s < 0)
    this->_y = 0;
  else
    this->_y -= s;
  this->_directionX = true;
}

void			Moveable::MoveLeftUp(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;

  if ((this->_x - s) < 0)
    this->_x = 0;
  else
    this->_x -= s;

  if ((this->_y - s) < 0)
    this->_y = 0;
  else
    this->_y -= s;
  this->_directionX = true;
}


//
// -- Complexes moves
//

void   			Moveable::MoveInDirection(float dx, float dy)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);

  this->_directionX	= (dx > this->_x ? true : false);
  this->_x		+= (dx / ratio) * s;
  this->_y		+= (dy / ratio) * s;
}

void	       		Moveable::MoveInDirection(const RatiolizedVector2D & v)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());


  this->_directionX	= (v._x > 0 ? true : false);
  this->_x		+= v._x * s;
  this->_y		+= v._y * s;
}

void		       	Moveable::MoveInDirection(const Point<float> & p)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);

  this->_directionX	= (p._x > this->_x ? true : false);
  this->_x		+= (p._x / ratio) * s;
  this->_y		+= (p._y / ratio) * s;
}


void   			Moveable::MoveTo(float dx, float dy)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);

  if (dx < this->_x)
    {
      this->_x += (dx / ratio) * s;
      if (this->_x < dx) this->_x = dx;
      this->_directionX	= false;
    }
  else if (dx > this->_x)
    {
      this->_x += (dx / ratio) * s;
      if (this->_x > dx) this->_x = dx;
      this->_directionX	= true;
    }

  if (dy < this->_y)
    {
      this->_y += (dy / ratio) * s;
      if (this->_y < dy) this->_y = dy;
    }
  else if (dy > this->_y)
    {
      this->_y += (dy / ratio) * s;
      if (this->_y > dy) this->_y = dy;
    }
}

void		       	Moveable::MoveTo(const Point<float> & p)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);



  if (p._x < this->_x)
    {
      this->_x += (p._x / ratio) * s;
      if (this->_x < p._x) this->_x = p._x;
      this->_directionX	= false;
    }
  else if (p._x > this->_x)
    {
      this->_x += (p._x / ratio) * s;
      if (this->_x > p._x) this->_x = p._x;
      this->_directionX	= true;
    }

  if (p._y < this->_y)
    {
      this->_y += (p._y / ratio) * s;
      if (this->_y < p._y) this->_y = p._y;
    }
  else if (p._y > this->_y)
    {
      this->_y += (p._y / ratio) * s;
      if (this->_y > p._y) this->_y = p._y;
    }
}

void   			Moveable::MoveInDirection(float dx, float dy, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);

  this->_directionX	= (dx < this->_x ? false : true);
  this->_x		+= (dx / ratio) * s;
  this->_y		+= (dy / ratio) * s;
}

void	       		Moveable::MoveInDirection(const RatiolizedVector2D & v, size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime());

  this->_directionX	= (v._x < 0 ? false : true);
  this->_x		+= v._x * s;
  this->_y		+= v._y * s;
}

void		       	Moveable::MoveInDirection(const Point<float> & p, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);

  this->_directionX	= (p._x < this->_x ? false : true);
  this->_x		+= (p._x / ratio) * s;
  this->_y		+= (p._y / ratio) * s;
}


void   			Moveable::MoveTo(float dx, float dy, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);

  if (dx < this->_x)
    {
      this->_x += (dx / ratio) * s;
      if (this->_x < dx) this->_x = dx;
      this->_directionX	= false;
    }
  else if (dx > this->_x)
    {
      this->_x += (dx / ratio) * s;
      if (this->_x > dx) this->_x = dx;
      this->_directionX	= true;
    }

  if (dy < this->_y)
    {
      this->_y += (dy / ratio) * s;
      if (this->_y < dy) this->_y = dy;
    }
  else if (dy > this->_y)
    {
      this->_y += (dy / ratio) * s;
      if (this->_y > dy) this->_y = dy;
    }
}

void		       	Moveable::MoveTo(const Point<float> & p, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);



  if (p._x < this->_x)
    {
      this->_x += (p._x / ratio) * s;
      if (this->_x < p._x) this->_x = p._x;
      this->_directionX	= false;
    }
  else if (p._x > this->_x)
    {
      this->_x += (p._x / ratio) * s;
      if (this->_x > p._x) this->_x = p._x;
      this->_directionX	= true;
    }

  if (p._y < this->_y)
    {
      this->_y += (p._y / ratio) * s;
      if (this->_y < p._y) this->_y = p._y;
    }
  else if (p._y > this->_y)
    {
      this->_y += (p._y / ratio) * s;
      if (this->_y > p._y) this->_y = p._y;
    }
}


//
// -- Moves requests
//


void			Moveable::RequestMoveLeft(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();  
  this->SetMoveRequest(this->_x - s, this->_y);
}

void			Moveable::RequestMoveRight(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x + s, this->_y);
}

void			Moveable::RequestMoveUp(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x, this->_y - s);
}

void			Moveable::RequestMoveDown(void)
{
  const float s = this->_speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x, this->_y + s);
}

void			Moveable::RequestMoveLeft(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x - s, this->_y);
}

void			Moveable::RequestMoveRight(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x + s, this->_y);
}

void			Moveable::RequestMoveUp(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x, this->_y - s);
}

void			Moveable::RequestMoveDown(size_t speed)
{
  const float s = speed * this->_app->GetFrameTime();
  this->SetMoveRequest(this->_x, this->_y + s);
}

void			Moveable::RequestMoveLeftUp(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x - s, this->_y - s);
}

void			Moveable::RequestMoveRightDown(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x + s, this->_y + s);
}

void			Moveable::RequestMoveLeftDown(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x - s, this->_y + s);
}

void			Moveable::RequestMoveRightUp(void)
{
  const float s = (this->_speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x + s, this->_y - s);
}

void			Moveable::RequestMoveLeftUp(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x - s, this->_y - s);
}

void			Moveable::RequestMoveRightDown(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x + s, this->_y + s);
}

void			Moveable::RequestMoveLeftDown(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x - s, this->_y + s);
}

void			Moveable::RequestMoveRightUp(size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime()) / 2;
  this->SetMoveRequest(this->_x + s, this->_y - s);
}

void   			Moveable::RequestMoveInDirection(float dx, float dy)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);

  this->SetMoveRequest(this->_x + (dx / ratio) * s,
		       this->_y + (dy / ratio) * s);
}

void	       		Moveable::RequestMoveInDirection(const RatiolizedVector2D & v)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  this->SetMoveRequest(this->_x + (v._x * s),
		       this->_y + (v._y * s));
}

void		       	Moveable::RequestMoveInDirection(const Point<float> & p)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);
  this->SetMoveRequest(this->_x + (p._x / ratio) * s,
		       this->_y + (p._y / ratio) * s);
}


void   			Moveable::RequestMoveTo(float dx, float dy)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);
  float x		= this->_x;
  float y		= this->_y;

  if (dx < x)
    {
      x += (dx / ratio) * s;
      if (x < dx) x = dx;
    }
  else if (dx > x)
    {
      x += (dx / ratio) * s;
      if (x > dx) x = dx;
    }

  if (dy < y)
    {
      y += (dy / ratio) * s;
      if (y < dy) y = dy;
    }
  else if (dy > y)
    {
      y += (dy / ratio) * s;
      if (y > dy) y = dy;
    }
  this->SetMoveRequest(x,y);
}

void		       	Moveable::RequestMoveTo(const Point<float> & p)
{
  const float s		= (this->_speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);
  float x		= this->_x;
  float y		= this->_y;

  if (p._x < x)
    {
      x += (p._x / ratio) * s;
      if (x < p._x) x = p._x;
    }
  else if (p._x > x)
    {
      x += (p._x / ratio) * s;
      if (x > p._x) x = p._x;
    }

  if (p._y < y)
    {
      y += (p._y / ratio) * s;
      if (y < p._y) y = p._y;
    }
  else if (p._y > y)
    {
      y += (p._y / ratio) * s;
      if (y > p._y) y = p._y;
    }

  this->SetMoveRequest(x,y);
}

void   			Moveable::RequestMoveInDirection(float dx, float dy, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);

  this->SetMoveRequest(this->_x + (dx / ratio) * s,
		       this->_y + (dy / ratio) * s);
}

void	       		Moveable::RequestMoveInDirection(const RatiolizedVector2D & v, size_t speed)
{
  const float s = (speed * this->_app->GetFrameTime());
  this->SetMoveRequest(this->_x + (v._x * s),
		       this->_y + (v._y * s));
}

void		       	Moveable::RequestMoveInDirection(const Point<float> & p, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);

  this->SetMoveRequest(this->_x + (p._x / ratio) * s,
		       this->_y + (p._y / ratio) * s);
}



void   			Moveable::RequestMoveTo(float dx, float dy, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(dx, dy);
  float x		= this->_x;
  float y		= this->_y;

  if (dx < x)
    {
      x += (dx / ratio) * s;
      if (x < dx) x = dx;
    }
  else if (dx > x)
    {
      x += (dx / ratio) * s;
      if (x > dx) x = dx;
    }

  if (dy < y)
    {
      y += (dy / ratio) * s;
      if (y < dy) y = dy;
    }
  else if (dy > y)
    {
      y += (dy / ratio) * s;
      if (y > dy) y = dy;
    }
  this->SetMoveRequest(x,y);
}

void		       	Moveable::RequestMoveTo(const Point<float> & p, size_t speed)
{
  const float s		= (speed * this->_app->GetFrameTime());
  const float ratio	= RatiolizedVector2D::GetRatio(p._x, p._y);
  float x		= this->_x;
  float y		= this->_y;

  if (p._x < x)
    {
      x += (p._x / ratio) * s;
      if (x < p._x) x = p._x;
    }
  else if (p._x > x)
    {
      x += (p._x / ratio) * s;
      if (x > p._x) x = p._x;
    }

  if (p._y < y)
    {
      y += (p._y / ratio) * s;
      if (y < p._y) y = p._y;
    }
  else if (p._y > y)
    {
      y += (p._y / ratio) * s;
      if (y > p._y) y = p._y;
    }

  this->SetMoveRequest(x,y);
}


//
// -- Commons
//

unsigned int		Moveable::GetSpeed(void) const
{
  return this->_speed;
}

sf::Window *		Moveable::GetApp(void) const
{
  return this->_app;
}

float			Moveable::GetFrameTime(void) const
{
  return this->_app->GetFrameTime();
}


void			Moveable::SetSpeed(unsigned int s)
{
  this->_speed	= s;
}

void			Moveable::CorrectPositionToMapSize(void)
{
  if	  (this->_x + this->_size._x > this->_app->GetWidth())
    this->_x = this->_app->GetWidth() - this->_size._x;
  else if (this->_x < 0)
    this->_x = 0;
  if	  (this->_y + this->_size._y > this->_app->GetHeight())
    this->_y = this->_app->GetHeight() - this->_size._y;
  else if (this->_y < 0)
    this->_y = 0;
}

// todo : allow, check, and notify map exit by entities
void				Moveable::ApplyMoveRequest(void)
{
  if (!(this->_moveRequest.IsActive())) return;
  this->_x = this->_moveRequest._x;
  this->_y = this->_moveRequest._y;
  this->CorrectPositionToMapSize();
  this->_lastMoveDirection = this->_moveRequest._direction;

  if (this->_moveRequest._direction == DirectionMoveRequest::LEFT)
    this->_directionX = false;
  else if (this->_moveRequest._direction == DirectionMoveRequest::RIGHT)
    this->_directionX = true;
  this->_moveRequest.Reset();
}

const DirectionMoveRequest &	Moveable::GetMoveRequest(void) const
{
  return this->_moveRequest;
}

DirectionMoveRequest &		Moveable::GetMoveRequest_unsafe(void)
{
  return this->_moveRequest;
}

void				Moveable::SetMoveRequest(const float & x,
							 const float & y)
{
  size_t direction = DirectionMoveRequest::NONE;

  if	  (x < this->_x) direction += DirectionMoveRequest::LEFT;
  else if (x > this->_x) direction += DirectionMoveRequest::RIGHT;
  if	  (y < this->_y) direction += DirectionMoveRequest::UP;
  else if (y > this->_y) direction += DirectionMoveRequest::DOWN;

  this->_moveRequest._x = x;
  this->_moveRequest._y = y;

  this->_moveRequest._direction = direction;
}
