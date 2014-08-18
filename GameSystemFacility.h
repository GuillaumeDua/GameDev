#ifndef __GAME_SYSTEM_FACILITIE__
# define __GAME_SYSTEM_FACILITIE__

# include "./GameSystem.h"

/* -- Not instanciable : this classe is just a stack of cb, */
/*    used in binding event. */

namespace GS
{
  class GameSystemFacility : public GS::GameSystem
  {
  public:

    void	MoveEntityRight(Entity * e)
    {
      e->MoveRight();
    }

    void	MoveEntityLeft(Entity * e)
    {
      e->MoveLeft();
    }

    void	MoveEntityUp(Entity * e)
    {
      e->MoveUp();
    }

    void	MoveEntityDown(Entity * e)
    {
      e->MoveDown();
    }

  protected:
  };
}

#endif // __GAME_SYSTEM_FACILITIE__
