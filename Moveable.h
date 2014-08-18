#ifndef __MOVEABLE__
# define __MOVEABLE__

# include <SFML/Graphics.hpp>
# include "/usr/include/boost/shared_ptr.hpp"
# include "./Geometry.h"
# include "./AGameObject.h"
# include "./Spec.h"

# define MOVEABLE_DEBUG_OFF
# define MOVEABLE_SAFETY_ON

# ifdef MOVEABLE_SAFETY_ON
#  include <cassert>
# endif


class	DirectionMoveRequest : public Point<float>
{
 public :
  DirectionMoveRequest(void)
    : Point(-1, -1),
    _direction(NONE)
    {}

  typedef size_t		INFO;

  static const size_t NONE	= 0;
  static const size_t LEFT	= 01;
  static const size_t RIGHT	= 02;
  static const size_t UP	= 10;
  static const size_t DOWN	= 20;
  static const size_t UP_LEFT	= 11;
  static const size_t UP_RIGHT	= 12;
  static const size_t DOWN_LEFT	= 21;
  static const size_t DOWN_RIGHT= 22;

  bool	IsActive(void) const
  {
    return (this->_x != -1);
  }

  const size_t	GetXDirection(void) const
  {
    return (this->_direction % 10);
  }


  const size_t	GetYDirection(void) const
  {
    return ((this->_direction / 10) * 10);
  }


  void	Reset(void)
  {
    this->_x = -1;
  }

  size_t	_direction;
};

class	Moveable : public AGameObject
{
 public:

  static const unsigned int DEFAULT_SPEED = 200;

  Moveable(sf::Window * app,
	   unsigned int s = Moveable::DEFAULT_SPEED,
	   float x = 0, float y = 0,
	   size_t sx = 0, size_t sy = 0);
  Moveable(sf::Window * app,
	   unsigned int s = Moveable::DEFAULT_SPEED,
	   Point<float> = Point<float>(0,0),
	   Point<size_t> = Point<size_t>(0,0));
  Moveable(const Moveable & m);

  //
  // -- Single axiales moves
  //

  void				MoveLeft(void);
  void				MoveRight(void);
  void				MoveUp(void);
  void				MoveDown(void);
  void				MoveLeft(size_t);
  void				MoveRight(size_t);
  void				MoveUp(size_t);
  void				MoveDown(size_t);

  //
  // -- Bi-axiales moves
  //

  void				MoveLeftUp(void);
  void				MoveRightDown(void);
  void				MoveLeftDown(void);
  void				MoveRightUp(void);
  void				MoveLeftUp(size_t);
  void				MoveRightDown(size_t);
  void				MoveLeftDown(size_t);
  void				MoveRightUp(size_t);

  //
  // -- Complexe moves
  //

  void				MoveInDirection(float dx, float dy);
  void				MoveInDirection(const RatiolizedVector2D & v);
  void				MoveInDirection(const Point<float> & p);
  void				MoveTo(float dx, float dy);
  void				MoveTo(const Point<float> & p);

  void				MoveInDirection(float dx, float dy, size_t);
  void				MoveInDirection(const RatiolizedVector2D & v, size_t);
  void				MoveInDirection(const Point<float> & p, size_t);
  void				MoveTo(float dx, float dy, size_t);
  void				MoveTo(const Point<float> & p, size_t);

  //
  // -- Single axiales moves requests
  //

  void				RequestMoveLeft(void);
  void				RequestMoveRight(void);
  void				RequestMoveUp(void);
  void				RequestMoveDown(void);
  void				RequestMoveLeft(size_t);
  void				RequestMoveRight(size_t);
  void				RequestMoveUp(size_t);
  void				RequestMoveDown(size_t);

  //
  // -- Bi-axiales moves requests
  //

  void				RequestMoveLeftUp(void);
  void				RequestMoveRightDown(void);
  void				RequestMoveLeftDown(void);
  void				RequestMoveRightUp(void);
  void				RequestMoveLeftUp(size_t);
  void				RequestMoveRightDown(size_t);
  void				RequestMoveLeftDown(size_t);
  void				RequestMoveRightUp(size_t);

  //
  // -- Complexe moves requests
  //

  void				RequestMoveInDirection(float dx, float dy);
  void				RequestMoveInDirection(const RatiolizedVector2D & v);
  void				RequestMoveInDirection(const Point<float> & p);
  void				RequestMoveTo(float dx, float dy);
  void				RequestMoveTo(const Point<float> & p);

  void				RequestMoveInDirection(float dx, float dy, size_t);
  void				RequestMoveInDirection(const RatiolizedVector2D & v, size_t);
  void				RequestMoveInDirection(const Point<float> & p, size_t);
  void				RequestMoveTo(float dx, float dy, size_t);
  void				RequestMoveTo(const Point<float> & p, size_t);


  //
  // -- Commons
  //

  unsigned int			GetSpeed(void) const;
  sf::Window *			GetApp(void) const;
  void				SetSpeed(unsigned int s);
  void				CorrectPositionToMapSize(void);

  //
  // -- Requests management
  //

  void				ApplyMoveRequest(void);
  const DirectionMoveRequest &	GetMoveRequest(void) const;
  DirectionMoveRequest &	GetMoveRequest_unsafe(void);
  void				SetMoveRequest(const float & x,
					       const float & y);

 protected:

  float				GetFrameTime(void) const;

  unsigned int			_speed;
  sf::Window *			_app;
  bool				_directionX;			// to flip on X axis : ( == false ? LEFT : RIGHT)
  DirectionMoveRequest		_moveRequest;
  DirectionMoveRequest::INFO	_lastMoveDirection;
};


#endif // __MOVEABLE__
