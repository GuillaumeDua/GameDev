#include "./GameSystem.h"

namespace GS
{
  // -- Public memebers

  GameSystem::GameSystem(const std::string & bg_path)
    : GameSystem_basic(bg_path),
      _map(0x0),
      _mapLoader(0x0)
  {
    BindedEvent::SetGameSystem(this);
    this->_quadTree = boost::make_shared<GS::QuadTree>();
  }

  GameSystem::~GameSystem()
  {
    EventMap_iterator		it;
    ElementsVector_iterator	e_it;

    std::cout << "GameSystem : dtor : deleting bind event : " << this->_bindKeyEventsMap.size() << std::endl;
    for (it = this->_bindKeyEventsMap.begin(); it != this->_bindKeyEventsMap.end(); ++it)
      delete (*it).second;

    std::cout << "GameSystem : dtor : deleting element " << this->_elements.size() << std::endl;
    for (e_it = this->_elements.begin(); e_it != this->_elements.end(); ++e_it)
      delete *e_it;

    if (this->_mapLoader != 0x0)	delete this->_mapLoader;
    else if (this->_map != 0x0)		delete this->_map;
  }

  void		GameSystem::RefreshQuadTreeEntities(void)
  {
    ElementsVector_iterator	it;

    this->_quadTree.get()->Clean();

    for (it = this->_elements.begin();
	 it != this->_elements.end();
	 ++it)
      {
	if ((*it)->Behave() == false)
	  (*it)->NotifyDelete();
	else
	  {
	    this->_quadTree.get()->AddAEntity(*it);
	    // this->_quadTree.get()->Debug(*it);
	    // (*it)->DrawIntoWindow(this->_mainWindow); // [todo] : change sprite-(s)
	  }
      }
  }

  void		GameSystem::CleanDeletedEntities(void)
  {
    ElementsVector_iterator	it;

    it = this->_elements.begin();
  b:
    for (;
	 it != this->_elements.end();
	 ++it)
      {

	if ((*it)->IsDeleteNotified())
	  {
   	    delete *it;
	    it = this->_elements.erase(it);
	    goto b;
	  }
      }
  }

    void		GameSystem::Refresh(void)
    {
      // if (this->_fps % COLLISION_CHECK_RATE == 0)
      //   this->_quadTree.get()->CheckCollisions();
      this->RefreshQuadTreeEntities();
      this->CleanDeletedEntities();
      this->ApplyMovesRequests();
      // this->DoGravityAction();
      this->_quadTree.get()->Draw(this->_mainWindow);
    }

  void		GameSystem::ApplyMovesRequests(void)
  {
    ElementsVector_iterator	it;
    const AEntity *		e;

    for (it = this->_elements.begin();
	 it != this->_elements.end();
	 ++it)
      {
	if ((*it)->GetMoveRequest().IsActive())
	  this->CorrectAEntityPosition(*it);
      }
  }

  void		GameSystem::CorrectAEntityPosition(AEntity * a)
  {
    const AEntity *	e;

    while ((e = this->_quadTree->IsEntityRayCastingCollision(*a)) != NULL)
      {
	if	(a->GetMoveRequest().GetYDirection() == DirectionMoveRequest::DOWN)
	  a->SetMoveRequest(a->GetPos()->_x, e->GetPos()->_y - a->GetSize()._y); 
	else if (a->GetMoveRequest().GetYDirection() == DirectionMoveRequest::UP)
	    a->SetMoveRequest(a->GetPos()->_x, e->GetPos()->_y + e->GetSize()._y); 
	else if	(a->GetMoveRequest().GetXDirection() == DirectionMoveRequest::LEFT)
	  a->SetMoveRequest(e->GetPos()->_x + e->GetSize()._x, a->GetPos()->_y); 
	else if (a->GetMoveRequest().GetXDirection() == DirectionMoveRequest::RIGHT)
	  a->SetMoveRequest(e->GetPos()->_x - a->GetSize()._x, a->GetPos()->_y); 
      }
    a->ApplyMoveRequest();
    // add to quadtree new entity/pos
  }
 
  void		GameSystem::DoGravityAction(void)
  {
    ElementsVector_iterator	it;

    for (it = this->_elements.begin();
	 it != this->_elements.end();
	 ++it)
      {

	if ((*it)->GetNeedGravityAction()  // typeid(**it) != typeid(MAP::Block)
	    )
	  {
	    (*it)->MoveDown(100);
	  }
      }
  }

  void		GameSystem::AddMapElementsToQuadTree(void)
  {
    assert(this->_map != 0x0);

    Map::ElementsVector::iterator	it;
    for (it = this->_map->GetElements().begin(); it != this->_map->GetElements().end(); ++it)
	this->_quadTree.get()->AddAEntity(*it);
  }

  void		GameSystem::AddMapElementsToGS(void)
  {
    assert(this->_map != 0x0);

    Map::ElementsVector::iterator	it;
    for (it = this->_map->GetElements().begin(); it != this->_map->GetElements().end(); ++it)
      this->_elements.push_back(*it);
    this->_map->Clear();
  }


  void		GameSystem::EventLoop(const sf::Event & e)
  {
    if (e.Type != sf::Event::KeyPressed)
      return ;
    EventMap_iterator	match = this->_bindKeyEventsMap.find(e.Key.Code);

    if (match != this->_bindKeyEventsMap.end())
      (*(match->second))();
#ifdef GS_DEBUG_ON
    else
      std::cout << "Unmapped event : " << e.Type << " -- " << e.Key.Code << std::endl;
#endif
  }

  void		GameSystem::AddElement(Entity * e)
  {
    this->_elements.push_back(e);
  }

  // -- Protected members :

  void		GameSystem::bindKeyEvents(sf::Key::Code e,
				       size_t entityIndex,
				       GameSystem::cb cb)
  {
    EventMap_iterator match;
    if ((match = this->_bindKeyEventsMap.find(e)) != this->_bindKeyEventsMap.end())
      delete (*match).second;
    this->_bindKeyEventsMap[e] = new BindedEvent(this->_elements.at(e), cb);
  }


  void		GameSystem::bindKeyEvents(sf::Key::Code e,
					  Entity * en,
					  GameSystem::cb cb)
  {
    EventMap_iterator match;
    if ((match = this->_bindKeyEventsMap.find(e)) != this->_bindKeyEventsMap.end())
      delete (*match).second;
    this->_bindKeyEventsMap[e] = new BindedEvent(en, cb);
  }


  void		GameSystem::bindKeyEvents(sf::Key::Code e,
				       const ElementsVector_iterator & it,
				       GameSystem::cb cb)
  {
    EventMap_iterator match;
    if ((match = this->_bindKeyEventsMap.find(e)) != this->_bindKeyEventsMap.end())
      delete (*match).second;
    this->_bindKeyEventsMap[e] = new BindedEvent(*it, cb);
  }

  // useless
  void		GameSystem::bindKeyEventsGroup(sf::Key::Code e,
					    ElementsVector & v,
					    GameSystem::cb cb)
  {
    ElementsVector_iterator it;
    for (it = v.begin(); it != v.end(); ++it)
      {
	this->bindKeyEvents(e, it, cb);
      }
  }


  void		GameSystem::SetMap(Map * m)
  {
    if (this->_map != 0x0) delete this->_map;
    this->_map = m;
    assert(this->_map != 0x0);
    this->AddMapElementsToGS();
  }

  void		GameSystem::LoadMap(const char * path)
  {
    if (this->_mapLoader != 0x0)	delete this->_mapLoader;
    else if (this->_map != 0x0)		delete this->_map;
    this->_mapLoader	= new MapLoader(path, this->_app);

    // this->_map		= this->_mapLoader->Get();
    this->SetMap(this->_mapLoader->Get());

    std::cout << "Got map : " << this->_map << std::endl;
  }

  void		GameSystem::SetCameraController(DisplayZone * camera)
  {
    this->_quadTree->SetCameraController(camera);
  }
}
