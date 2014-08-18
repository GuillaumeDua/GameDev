#include "./GameSystem_basic.h"

namespace GS
{
  GameSystem_basic::GameSystem_basic(const std::string & bg_path)
    : _mainWindow(sf::VideoMode(GS::SCREEN_WIDTH, GS::SCREEN_HEIGHT),
		  "Guss's SFML TEST"),
      _fps(.0f),
      _isInit(false),
      _isBreak(false),
      _isRunning(false)
  {
    this->_app = static_cast<sf::Window *>(&(this->_mainWindow));
    this->Init(bg_path);
  }
  
  bool		GameSystem_basic::Init(const std::string & bg_path)
  {
    if (this->_isInit) return true;

    if (!(BG.LoadFromFile(bg_path))	||
	BG.GetWidth()  != 640		||
	BG.GetHeight() != 480)
      {
	std::cerr << GS::Error::BG_LOADING << std::endl;
#ifdef DEBUG_GS_ON
	std::cerr << "Current size : " 
		  << BG.GetWidth() << " x " << BG.GetHeight()
		  << std::endl;
#endif
	return false;
      }
    
    BG_Sprite.SetImage(BG);

    this->_isInit = true;
    return true;
  };

  bool		GameSystem_basic::operator!(void)
  {
    return (this->_isInit == false);
  }

  bool		GameSystem_basic::Run(void)
  {
    if (this->_isRunning ||
	this->_isInit == false) return false;

    this->_isRunning = true;
    while (this->_isRunning)
      {
	this->Refresh_e();
      }
    this->_mainWindow.Close();
    return true;
  }

  bool			GameSystem_basic::Stop(void)
  {
    if (!(this->_isRunning))return false;
    this->_isRunning = false;
    return true;
  }

  void		GameSystem_basic::Refresh_e(void)
  {
    if (this->_fps % INPUT_CHECK_RATE == 0)
      while (this->_mainWindow.GetEvent(this->event))
	EventLoop_e(this->event);

    if (this->_isBreak)
      sf::Sleep(1);
    else
      {
	this->_mainWindow.Clear(sf::Color(0,0,0));
	this->_mainWindow.Draw(this->BG_Sprite);
	this->Refresh();
	this->_mainWindow.Display();

	sf::Sleep(GET_FPS(FPS_DEFAULT_VALUE));
	this->_fps += (this->_fps > RESET_FPS_VALUE ? this->_fps * -1 : GET_FPS(FPS_DEFAULT_VALUE));
      }
  }

  void		GameSystem_basic::EventLoop_e(const sf::Event & e)
  {
    if (e.Type == sf::Event::Closed ||
	(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Escape))
      {
	this->_isRunning = false;
	return;
      }
    this->EventLoop(e);
  }

  const sf::Input &	GameSystem_basic::GetInput(void)
  {
    return this->_app->GetInput();
  }

  void		GameSystem_basic::Break(Entity *)
  {
    this->_isBreak = true;
  }

  void		GameSystem_basic::UnBreak(Entity *)
  {
    this->_isBreak = false;
  }

  sf::Window *	GameSystem_basic::GetApp_unsafe(void)
  {
    return this->_app;
  }

}
