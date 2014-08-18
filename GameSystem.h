#ifndef __GAME_SYSTEM__
# define __GAME_SYSTEM__

# include "./GameSystem_basic.h"
# include "./BindedEvent.h"
# include "./Entity.h"
# include "./QuadTree.h"
# include "./MAP/Map.h"
# include "./MAP/MapLoader.h"
# include <typeinfo>
# include <vector>
# include <map>

# define GS_DEBUG_OFF

namespace GS
{
  class	GameSystem : public GameSystem_basic
  {
  public:

    typedef std::vector<Entity *>					ElementsVector;
    typedef std::vector<Entity *>::iterator				ElementsVector_iterator;
    typedef std::vector<Entity *>::const_iterator			ElementsVector_const_iterator;
    typedef void (GameSystem::* cb)(Entity *);
    typedef std::map<sf::Key::Code, BindedEvent *>			EventMap;
    typedef std::map<sf::Key::Code, BindedEvent *>::iterator		EventMap_iterator;

    GameSystem(const std::string & bg_path);
    ~GameSystem();

    void					SetMap(Map *);
    void					LoadMap(const char *);

    void					Refresh(void);
    void					ApplyMovesRequests(void);
    void					AddMapElementsToQuadTree(void);
    void					AddMapElementsToGS(void);
    void					EventLoop(const sf::Event &);
    void					CorrectAEntityPosition(AEntity *);

    void					AddElement(Entity *);

    // -- Do it w/ const vector

    void					bindKeyEvents(sf::Key::Code e,
							      size_t entityIndex,
							      GameSystem::cb cb);

    void					bindKeyEvents(sf::Key::Code e,
							      Entity *,
							      GameSystem::cb cb);

    void					bindKeyEvents(sf::Key::Code e,
							      const ElementsVector_iterator & it,
							      GameSystem::cb cb);
    
    void					bindKeyEventsGroup(sf::Key::Code e,
								   ElementsVector & v,
								   GameSystem::cb cb);

    void					SetCameraController(DisplayZone *);

  protected:
    void					CleanDeletedEntities(void);
    void					RefreshQuadTreeEntities(void);
    void					DoGravityAction(void);
    
    MapLoader *					_mapLoader;
    Map *					_map;
    boost::shared_ptr<GS::QuadTree>		_quadTree;
    ElementsVector				_elements;
    EventMap					_bindKeyEventsMap;
  };
}

#endif // __GAME_SYSTEM__
