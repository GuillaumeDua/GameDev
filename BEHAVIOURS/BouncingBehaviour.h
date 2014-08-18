#ifndef __BOUNCING_BEHAVIOUR__
# define __BOUNCING_BEHAVIOUR__

# include "./ConstMoveBehaviour.h"

class BouncingBehaviour : public ConstMoveBehaviour
{
 public:

  BouncingBehaviour(AEntity *, const RatiolizedVector2D &);
  bool		OnBorderCollision(void);
  bool		OnCollision(void);
  bool		Routine(void);
							
 protected:						
};							


#endif // __BOUNCING_BEHAVIOUR__
