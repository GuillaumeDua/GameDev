#ifndef __COLLISIONABLE__
# define __COLLISIONABLE__

# include "./Moveable.h"
# include <vector>

class	Collisionable : public Moveable
{
 public:

  enum FACE
  {
    NONE,
    LEFT,
    RIGHT,
    DOWN,
    UP
  };

  enum TYPE
  {
    UNDEFINED = 0,
    MAP_BLOCK,
    AI,
    PLAYER,
    DISPLAY_ZONE,	// Display zone		: The area of the map that is displayed
    CALCULATED_ZONE	// Calculated zone	: The area of the map where collisions and behaviours are effectives
  };

  struct CollisionNotification;

  typedef std::vector<Collisionable *>		CollisionableVector;

  Collisionable(sf::Window * app,
		unsigned int s = Collisionable::DEFAULT_SPEED,
		float x = 0, float y = 0,
		size_t sx = 0, size_t sy = 0);
  Collisionable(sf::Window * app,
		unsigned int s = Collisionable::DEFAULT_SPEED,
		Point<float> = Point<float>(0,0),
		Point<size_t> = Point<size_t>(0,0));
  Collisionable(const Collisionable & m);

  virtual ~Collisionable();


  bool			GetHasCollision(void) const;
  bool			GetHasBorderCollision(void) const;
  bool			GetNeedGravityAction(void) const;
  void			SetNeedGravityAction(const bool & v);

  CollisionableVector &	GetCollisionStack(void);

  bool			IsCollision(void);
  bool			IsCollision(const Collisionable &);
  bool			IsCollisionRealTime(const Moveable &);
  bool			IsCollisionRealTime(const Moveable &, const Point<float> &);
  bool			IsBorderCollision(void);
  bool			IsOutOfScreen(void);
  void			NotifyCollision(Collisionable *);
  /* FACE			GetCollisionFace(const Collisionable &)		__attribute__((deprecated)); */
  /* void			CorrectPos(const Collisionable &)		__attribute__((deprecated)); */
  /* void			CorrectPos(const Collisionable &, const FACE &)	__attribute__((deprecated)); */

  // Simili-protected
  void			ResetCollision(void);
  void			ResetCollision(const Collisionable *);
  void			ResetBorderCollision(void);


  const TYPE &		GetType(void) const;
  void			SetType(const TYPE &);

 protected:
  virtual void		DestroyAnimation(void);

  volatile bool		_hasBorderCollision;
  CollisionableVector	_collisionStack;
  bool			_needGravityAction;
  TYPE			_type;
};

#endif // __COLLISIONABLE__
