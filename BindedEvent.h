#ifndef __BINDED_EVENT__
# define __BINDED_EVENT__

# include "./Entity.h"

namespace GS
{
  class	GameSystem;

  class	BindedEvent
  {
  public:

    BindedEvent(Entity * e, void (GameSystem::* cb)(Entity *));
    void		operator()(void);
    static void		SetGameSystem(GameSystem * gs);

  protected:
    Entity *		_target;
    void (GameSystem::*	_callBack)(Entity *);
    static GameSystem *	_gs;
  };
}

#endif // __BINDED_EVENT__
