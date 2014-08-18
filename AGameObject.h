#ifndef __AGAMEOBJECT__
# define __AGAMEOBJECT__

# include "./Geometry.h"

class	AGameObject : public Point<float>
{
 public:
  AGameObject(float, float, size_t, size_t);
  AGameObject(Point<float>, Point<size_t>);
  AGameObject(const AGameObject &);

  const Point<float> *		GetPos(void) const;
  const Point<size_t> &		GetSize(void) const;
  void				SetPos(float x, float y);
  void				SetPos(const Point<float> & p);
  void				SetPos(Point<float> * p);
  void				SetPos(const Point<float> * p);
  
  void				SetSize(size_t x, size_t y);

 protected:
  Point<size_t>		       	_size;
};


#endif // __AGAMEOBJECT__
