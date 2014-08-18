#ifndef __CONST_MOVE_BEHAVIOUR__
# define __CONST_MOVE_BEHAVIOUR__

# include "./IEntityBehaviour.h"

class ConstMoveBehaviour : public IEntityBehaviour
{
 public:

  ConstMoveBehaviour(AEntity *, const RatiolizedVector2D &);

  bool			OnBorderCollision(void);
  bool			OnCollision(void);
  bool			Routine(void);

 protected:
  // none-const because of boucing inherit, downstep.
  RatiolizedVector2D	_vector;
};

#endif // __CONST_MOVE_BEHAVIOUR__
