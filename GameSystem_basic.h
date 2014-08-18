#ifndef __GAME_SYSTEM_BASIC__
# define __GAME_SYSTEM_BASIC__

# include <iostream>
# include <SFML/Graphics.hpp>

# define FPS_DEFAULT_VALUE	60.0f
# define RESET_FPS_VALUE	FPS_DEFAULT_VALUE * 100.0f
# define INPUT_CHECK_RATE	10
# define COLLISION_CHECK_RATE	2
# define GET_FPS(x)		(1.0f/x)

# define DEBUG_GS_ON

# include "./Spec.h"
# include "./Entity.h"

namespace GS
{
  namespace Error
  {
    static const std::string & BG_LOADING = "Error loading background picture : invalid path or image dimensions.\nIt must be a 640x480 png picture";
  }

  class	GameSystem_basic
  {
  public:

    GameSystem_basic(const std::string & bg_path);
 
    bool		Init(const std::string & bg_path);
    bool		operator!(void);
    bool		Run(void);
    bool		Stop(void);

    void		Break(Entity *);
    void		UnBreak(Entity *);

    const sf::Input &	GetInput(void);
    sf::Window *	GetApp_unsafe(void);

  protected:

    void		Refresh_e(void);
    virtual void	Refresh(void) = 0;
    void		EventLoop_e(const sf::Event & e);
    virtual void	EventLoop(const sf::Event & e) = 0;


    sf::RenderWindow	_mainWindow;
    sf::Window *	_app;		// Just a convinient scoped-alias to _mainWindow
    sf::Event		event;

    sf::Image		BG;
    sf::Sprite		BG_Sprite;

    bool		_isInit;
    volatile bool      	_isRunning;
    volatile bool	_isBreak;
    size_t		_fps;		// FPS counter, recursively reset
  };
}

#endif // __GAME_SYSTEM_BASIC__
