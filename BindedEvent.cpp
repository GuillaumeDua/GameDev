#include "./BindedEvent.h"

namespace GS
{
  GameSystem *	BindedEvent::_gs;
  
  BindedEvent::BindedEvent(Entity * e, void (GameSystem::* cb)(Entity *))
  {
    this->_target	= e;
    this->_callBack	= cb;
  }

  void	BindedEvent::operator()(void)
  {
    ((BindedEvent::_gs)->*(this->_callBack))(this->_target);
  }

  void	BindedEvent::SetGameSystem(GameSystem * gs)
  {
    BindedEvent::_gs	= gs;
  }
}
