#include <iostream>
#include <cstdlib>

#define FPS_DEFAULT_VALUE	60.0f
#define GET_FPS(x)		(1.0f/x)

#include "./GameSystem.h"
#include "./Entity.h"
#include "./BehavioursPack.h"
#include "./GameSystemFacility.h"

#include "./MAP/MapLoader.h"

namespace GS_im
{

  static const size_t		sprites_img_w	= 640;
  static const size_t		sprites_img_h	= 448;
  static const unsigned int	x_sprites	= 10;
  static const unsigned int	y_sprites	= 7;
  static const size_t		w_sprite	= sprites_img_w / x_sprites;
  static const size_t		h_sprite	= sprites_img_h / y_sprites;
}

class Test : public GS::GameSystem
{
public :
  typedef void (Test::* cb)(Entity *);

  Test(const std::string & p) : GS::GameSystem(p)
  {
    this->InitEntities();
  }

  ~Test()
  {}

  void	InitEntities(void)
  {
    boost::shared_ptr<AEntitySprites> sprites = boost::make_shared<AEntitySprites>("./PICS/char_sprites.png",
										   GS_im::w_sprite,
										   GS_im::h_sprite);
    if (!(*sprites))
      {
	std::cerr << "Error loading/splitting sprites" << std::endl;
	exit(EXIT_FAILURE);      
      }

    GameSystem::ElementsVector	v;
    RatiolizedVector2D		r(.0f, .0f, 400.0f, 400.0f);
    RatiolizedVector2D		r1(.0f, .0f, -400.0f, 400.0f);
    RatiolizedVector2D		r2(.0f, .0f, 200.0f, 400.0f);
    RatiolizedVector2D		r3(.0f, .0f, 100.0f, 400.0f);
    RatiolizedVector2D		r5(.0f, .0f, 0.0f, 0.0f);

    v.push_back(new Entity(this->_app, sprites,
    			   200, 300, 50, 64, 64));
    // v.push_back(new Entity(this->_app, sprites,
    // 			   200, 300, 120, 64, 64));

    this->AddElement(*(v.begin() + 0));
    // this->AddElement(*(v.begin() + 1));

    // (*(v.begin() + 0))->SetBehaviour(boost::make_shared<TrackerBehaviour>(*(v.begin() + 0), *(v.begin() + 1)));
    (*(v.begin() + 0))->SetBehaviour(boost::make_shared<ControlableBehaviour>(*(v.begin() + 0), this));


    std::cout << "Controlable : " << *(v.begin() + 0) << std::endl;
    // std::cout << "Tracker : " << *(v.begin() + 1) << std::endl;


    // this->bindKeyEventsGroup(sf::Key::Right, v, &GameSystem::Break);
    // this->bindKeyEventsGroup(sf::Key::Left, v, &GameSystem::UnBreak);

    this->SetCameraController(new DisplayZone(this->_app, boost::make_shared<AEntitySprites>("./PICS/grey_bg.png",
											     GS::SCREEN_WIDTH,
											     GS::SCREEN_HEIGHT),
					      0, 0));

  }

protected:
};

int	main(void)
{
  Test	m("./PICS/grey_bg.png");

  m.LoadMap("./MAP/map3.map");
  // m.LoadMap("./MAP/mapDEBUG.map");
  m.Run();

  return EXIT_SUCCESS;
}
