#ifndef __CONTROLABLE_BAHVIOUR__
# define __CONTROLABLE_BAHVIOUR__

#include "./IEntityBehaviour.h"
#include "./../GameSystem.h"
#include "./../MAP/MapBlock.h"

class ControlableBehaviour : public IEntityBehaviour
{
 public:

  ControlableBehaviour(AEntity *, GS::GameSystem *);

  bool				OnBorderCollision(void);
  bool				OnCollision(void);
  bool				Routine(void);

 protected:

  GS::GameSystem *		_gameSystem;
};


#endif // __CONTROLABLE_BAHVIOUR__
