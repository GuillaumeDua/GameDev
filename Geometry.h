#ifndef __GEOMETRY__
# define __GEOMETRY__

# include <unistd.h>
# include <cstdio>

template <typename T>
struct Point;

template <>
struct	Point<float>
{
  Point()
  {
    this->_x	= 0;
    this->_y	= 0;
  }

  Point(float x, float y)
  {
    this->_x	= x;
    this->_y	= y;
  }

  Point(const Point & p)
  {
    this->_x	= p.getX();
    this->_y	= p.getY();
  }

  inline float	getX(void) const
  {
    return this->_x;
  }

  inline float	getY(void) const
  {
    return this->_y;
  }

  float	_x;
  float	_y;
};

template <>
struct	Point<size_t>
{
  Point()
  {
    this->_x	= 0;
    this->_y	= 0;
  }

  Point(size_t x, size_t y)
  {
    this->_x	= x;
    this->_y	= y;
  }

  Point(const Point & p)
  {
    this->_x	= p.getX();
    this->_y	= p.getY();
  }

  inline size_t	getX(void) const
  {
    return this->_x;
  }

  inline size_t	getY(void) const
  {
    return this->_y;
  }

  size_t	_x;
  size_t	_y;
};


template <>
struct	Point<int>
{
  Point()
  {
    this->_x	= 0;
    this->_y	= 0;
  }

  Point(int x, int y)
  {
    this->_x	= x;
    this->_y	= y;
  }

  Point(const Point & p)
  {
    this->_x	= p.getX();
    this->_y	= p.getY();
  }

  inline int	getX(void) const
  {
    return this->_x;
  }

  inline int	getY(void) const
  {
    return this->_y;
  }

  int	_x;
  int	_y;
};


struct RatiolizedVector2D : public Point<float>
{
  static float	GetRatio(float x, float y)
  {
    return ((x < 0 ? x * -1.0 : x) +
	    (y < 0 ? y * -1.0 : y));
  }

  static float	GetRatio(const Point<float> & p)
  {
    return ((p._x < 0 ? p._x * -1.0 : p._x) +
	    (p._y < 0 ? p._y * -1.0 : p._y));
  }

  RatiolizedVector2D(float cX, float cY,
		     float dX, float dY);
  RatiolizedVector2D(const RatiolizedVector2D & v);
  RatiolizedVector2D(const Point<float> & p1,
		     const Point<float> & p2);

  void		SetVars(float cX, float cY,
			float dX, float dY);
  void		SetVars(const Point<float> & p1,
			const Point<float> & p2);

  void		Reverse(void);

};




#endif // __GEOMETRY__
