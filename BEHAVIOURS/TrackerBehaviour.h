#ifndef __ENTITY_BEHAVIOUR_TRACKER__
# define __ENTITY_BEHAVIOUR_TRACKER__

# include "./IEntityBehaviour.h"

class TrackerBehaviour : public IEntityBehaviour
{
 public:

  TrackerBehaviour(AEntity *, AEntity *);

  bool		OnBorderCollision(void);
  bool		OnCollision(void);
  bool		Routine(void);

 protected:
};


#endif // __ENTITY_BEHAVIOUR_TRACKER__
