#ifndef __MAP_BLOCK_BEHAVIOUR__
# define __MAP_BLOCK_BEHAVIOUR__

# include "./IEntityBehaviour.h"

class MapBlockBehaviour : public IEntityBehaviour
{
 public:

  MapBlockBehaviour(AEntity *);

  bool			OnBorderCollision(void);
  bool			OnCollision(void);
  bool			Routine(void);

 protected:
};

#endif // __CONST_MOVE_BEHAVIOUR__
