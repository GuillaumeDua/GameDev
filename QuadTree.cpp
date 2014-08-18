#include "./QuadTree.h"

namespace GS
{
  QuadTree::QuadTree(float x, float y,
		     size_t sx, size_t sy,
		     size_t indent,
		     QuadTree * parent)
    : AGameObject(x, y, sx, sy),
      _camera_controller(0x0)
  {
    this->_parent	= parent;
    this->_indent_lvl	= indent;

#ifdef QUADTREE_DEBUG_ON
    this->_debugImage = 0x0;
#endif

    if (indent == GS::QUADTREE::INDENT::MAX)
      {
#ifdef QUADTREE_DEBUG_ON
	// this->_debugImage = new sf::Image(20,15);
	// if (!(this->_debugImage->LoadFromFile("./PICS/debug_cell_sprite.png")))
	this->_debugImage = new sf::Image(80,60);
	if (!(this->_debugImage->LoadFromFile("./PICS/debug_sprite_2.png")))
	  {
	    std::cerr << "Error loading debug sprites"  << std::endl;
	    return;
	  }

	this->_debugSprite.SetImage(*(this->_debugImage));
#endif
	return;
      }
    if (indent == GS::QUADTREE::INDENT::FIRST)
      this->_parent = NULL;

    this->_upLeft	= new GS::QuadTree::child_type(this->_x, this->_y,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
    this->_upRight	= new GS::QuadTree::child_type(this->_x + this->_size._x / 2.0f, this->_y,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
    this->_downLeft	= new GS::QuadTree::child_type(this->_x, this->_y + this->_size._y / 2.0f,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
    this->_downRight	= new GS::QuadTree::child_type(this->_x + this->_size._x / 2.0f, this->_y + this->_size._y / 2.0f,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
  }
  
  // --Default constructor
  QuadTree::QuadTree(size_t w, size_t h) :
    AGameObject(Point<float>(.0f, .0f),
		Point<size_t>(w, h)),
    _camera_controller(0x0)
  {

#ifdef QUADTREE_DEBUG_ON
    this->_debugImage = 0x0;
#endif

    this->_indent_lvl	= GS::QUADTREE::INDENT::FIRST;
    this->_parent	= NULL;

    this->_upLeft	= new GS::QuadTree::child_type(this->_x, this->_y,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
    this->_upRight	= new GS::QuadTree::child_type(this->_x + this->_size._x / 2.0f, this->_y,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
    this->_downLeft	= new GS::QuadTree::child_type(this->_x, this->_y + this->_size._y / 2.0f,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
    this->_downRight	= new GS::QuadTree::child_type(this->_x + this->_size._x / 2.0f, this->_y + this->_size._y / 2.0f,
						       this->_size._x / 2.0f, this->_size._y / 2.0f,
						       this->_indent_lvl + 1, this);
  }


  QuadTree::~QuadTree()
  {
    if (this->_indent_lvl == GS::QUADTREE::INDENT::MAX) return;
    delete this->_upRight;
    delete this->_upLeft;
    delete this->_downRight;
    delete this->_downLeft;


#ifdef QUADTREE_DEBUG_ON
    if (this->_debugImage != 0x0) delete this->_debugImage;
#endif
  }



  bool					QuadTree::ShouldBeContainedBy(const AEntity * e,
								      const QuadTree * lvl)
  {
    if ((e->GetPos()->_x >= lvl->_x + lvl->_size._x)
	||	(e->GetPos()->_y >= lvl->_y + lvl->_size._y)
	||	(e->GetPos()->_x + e->GetSize()._x <= lvl->_x)
	||	(e->GetPos()->_y + e->GetSize()._y <= lvl->_y))
      return false;
    return true; 
  }

  bool					QuadTree::ShouldBeContainedBy(const AEntity & e,
								      const Point<float> & pos,
								      const QuadTree * lvl)

  {
    if ((pos._x >= lvl->_x + lvl->_size._x)
	||	(pos._y >= lvl->_y + lvl->_size._y)
	||	(pos._x + e.GetSize()._x <= lvl->_x)
	||	(pos._y + e.GetSize()._y <= lvl->_y))
      return false;
    return true;       
  }

  void						QuadTree::Debug(const AEntity * e)
  {
    GS::QuadTree::AEntitySTDVector::const_iterator it;
    for (it = this->GetContent().begin(); it != this->GetContent().end(); ++it)
      {
	if ((*it) == e)
	  std::cout << e << " is contained in : " << this << " (" << this->_indent_lvl << ")" << std::endl;
      }

    if (this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      return;

    if (QuadTree::ShouldBeContainedBy(e, this->_upLeft))
      this->_upLeft->Debug(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_upRight))
      this->_upRight->Debug(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_downLeft))
      this->_downLeft->Debug(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_downRight))
      this->_downRight->Debug(e);
  }


  void						QuadTree::CheckCollisions(void)
  {
    if (this->_indent_lvl != 0) return;
      
    QuadTree::AEntitySTDVector::iterator	it;

    for (it = this->_content.begin(); it != this->_content.end(); ++it)
      this->IsCollision(*it);
  }


  void						QuadTree::CheckCollisions(QuadTree::AEntitySTDVector & v)
  {
    if (this->_indent_lvl != 0) return;
      
    AEntitySTDVector::iterator	it;

    for (it = v.begin(); it != v.end(); ++it)
      this->IsCollision(*it);
  }


  //
  // -- Check and notify every Entities collision in the whole Quadtree
  //
  bool						QuadTree::IsCollision(AEntity * e)
  {
    bool	ret = false;

    if (this->getIndentLvl() == GS::QUADTREE::INDENT::MAX)
      {
	GS::QuadTree::AEntitySTDVector::const_iterator it;
	for (it = this->GetContent().begin(); it != this->GetContent().end(); ++it)
	  {
	    if ((*it) != e && (*it)->IsCollisionRealTime(*e))
	      {
		e->NotifyCollision(*it);
		(*it)->NotifyCollision(e);
		//#ifndef QUADTREE_DEBUG_ON
		std::cout << "collision between : " << *it << " and " << e << std::endl;
		//#endif
		ret = true;
	      }
	  }
	return ret;
      }

    if (this->_upLeft->IsContaining(e) && (this->_upLeft->GetContent().size() != 1))
      return this->_upLeft->IsCollision(e);
    if (this->_upRight->IsContaining(e) && (this->_upRight->GetContent().size() != 1))
      return this->_upRight->IsCollision(e);
    if (this->_downLeft->IsContaining(e) && (this->_downLeft->GetContent().size() != 1))
      return this->_downLeft->IsCollision(e);
    if (this->_downRight->IsContaining(e) && (this->_downRight->GetContent().size() != 1))
      return this->_downRight->IsCollision(e);

    return false;
  }

  // RayCasting project : Test Collision
  const AEntity *				QuadTree::IsCollisionTest(const EntityProjection * e) const
  {
    if (this->getIndentLvl() == GS::QUADTREE::INDENT::MAX)
      {
	GS::QuadTree::AEntitySTDVector::const_iterator it;
	for (it = this->_content.begin(); it != this->_content.end(); ++it)
	  {
	    if ((*it) != e->GetOrigin() &&
		(*it) != e)
	      std::cout << e << " (" << e->GetOrigin() << ") -- " << *it << std::endl;
	    if ((*it) != e->GetOrigin() &&
		(*it) != e &&
		(*it)->IsCollisionRealTime(*e))
	      return *it;
	  }
	return NULL;
      }

    // if (this->_upLeft->IsContaining(e) && (this->_upLeft->GetContent().size() != 1))
    //   return this->_upLeft->IsCollisionTest(e);
    // if (this->_upRight->IsContaining(e) && (this->_upRight->GetContent().size() != 1))
    //   return this->_upRight->IsCollisionTest(e);
    // if (this->_downLeft->IsContaining(e) && (this->_downLeft->GetContent().size() != 1))
    //   return this->_downLeft->IsCollisionTest(e);
    // if (this->_downRight->IsContaining(e) && (this->_downRight->GetContent().size() != 1))
    //   return this->_downRight->IsCollisionTest(e);

    const AEntity * p;

    if (this->_upLeft->IsContaining(e)			&&
	(this->_upLeft->GetContent().size() != 1)	&&
	(p = this->_upLeft->IsCollisionTest(e)) != NULL)
      return p;
    if (this->_upRight->IsContaining(e)			&&
	(this->_upRight->GetContent().size() != 1)	&& 
	(p = this->_upRight->IsCollisionTest(e)) != NULL)
      return p;
    if (this->_downLeft->IsContaining(e)		&&
	(this->_downLeft->GetContent().size() != 1)	&& 
	(p = this->_downLeft->IsCollisionTest(e)) != NULL)
      return p;
    if (this->_downRight ->IsContaining(e)		&&
	(this->_downRight->GetContent().size() != 1)	&& 
	(p = this->_downRight->IsCollisionTest(e)) != NULL)
      return p;

    return NULL;
  }

  void						QuadTree::AddAEntity(AEntity * e)
  {
    if (this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      {
	this->_content.push_back(e);
	return;
      }

    if (QuadTree::ShouldBeContainedBy(e, this->_upLeft))
      this->_upLeft->AddAEntity(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_upRight))
      this->_upRight->AddAEntity(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_downLeft))
      this->_downLeft->AddAEntity(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_downRight))
      this->_downRight->AddAEntity(e);

    if (QuadTree::ShouldBeContainedBy(e, this))
      this->_content.push_back(e);
  }

  void						QuadTree::RemoveAEntity(AEntity * e)
  {
    if (this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      {
	TOOLS::RemoveValueFromVector<AEntity *>(this->_content, e);
	return;
      }

    if (this->_upLeft->IsContaining(e))
      this->_upLeft->RemoveAEntity(e);
    if (this->_upRight->IsContaining(e))
      this->_upRight->RemoveAEntity(e);
    if (this->_downLeft->IsContaining(e))
      this->_downLeft->RemoveAEntity(e);
    if (this->_downRight->IsContaining(e))
      this->_downRight->RemoveAEntity(e);

    if (this->IsContaining(e))
      TOOLS::RemoveValueFromVector<AEntity *>(this->_content, e);
  }

  void						QuadTree::Clean(void)
  {
    if (this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      {
	this->_content.clear();
	return;
      }

    this->_upLeft->Clean();
    this->_upRight->Clean();
    this->_downLeft->Clean();
    this->_downRight->Clean();

    if (this->_content.empty() == false)
      this->_content.clear();
  }

#ifdef QUADTREE_DEBUG_ON
  // todo  :
  // error : cannot draw objects that are larger than a smaller step
  void						QuadTree::Draw(sf::RenderWindow & w)
  {
    if (this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      {
	QuadTree::AEntitySTDVector::iterator	it;
	std::ostringstream			ss;

	if (!(this->_content.empty()))
	  {
	    ss << this->_content.size();

	    for (it = this->_content.begin(); it != this->_content.end(); ++it)
	      ss << std::endl << TOOLS::IntToString((*it));

	    this->_debugSprite.SetPosition(this->_x, this->_y);
	    w.Draw(this->_debugSprite);
	  }

	for (it = this->_content.begin(); it != this->_content.end(); ++it)
	  {
	    (*it)->DrawIntoWindow(w);
	  }

	if (!(this->_content.empty()))
	  {
	    sf::String	text(ss.str());

	    text.SetSize(10);
	    text.SetPosition(this->_x + 2, this->_y + 2);
	    w.Draw(text);
	  }
	return;
      }

    this->_upLeft->Draw(w);
    this->_upRight->Draw(w);
    this->_downLeft->Draw(w);
    this->_downRight->Draw(w);
  }
#endif

#ifndef QUADTREE_DEBUG_ON
  void						QuadTree::Draw(sf::RenderWindow & w)
  {
    QuadTree::AEntitySTDVector::iterator it;
    for (it = this->_content.begin(); it != this->_content.end(); ++it)
      (*it)->DrawIntoWindow(w);
    return;
  }
#endif
    
  bool						QuadTree::IsContaining(const AEntity * e)
  {
    QuadTree::AEntitySTDVector::iterator	it;
    for (it = this->_content.begin(); it != this->_content.end(); ++it)
      if (*it == e) return true;
    return false;
  }

  void						QuadTree::SetCameraController(DisplayZone * e)
  {
    assert(e != 0x0);
    this->_camera_controller = e;
  }

  void						QuadTree::AddCameraAEntity(DisplayZone * e)
  {
    assert(e != 0x0);

    if (this->_indent_lvl == GS::QUADTREE::INDENT::CAMERA_MAX_LVL ||
  	this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      {
  	this->_content.push_back(static_cast<AEntity*>(e));
  	return;
      }

    if (QuadTree::ShouldBeContainedBy(e, this->_upLeft))
      this->_upLeft->AddCameraAEntity(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_upRight))
      this->_upRight->AddCameraAEntity(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_downLeft))
      this->_downLeft->AddCameraAEntity(e);
    if (QuadTree::ShouldBeContainedBy(e, this->_downRight))
      this->_downRight->AddCameraAEntity(e);

    if (QuadTree::ShouldBeContainedBy(e, this))
      this->_content.push_back(e);
  }

  void						QuadTree::AddCameraAEntity(void)
  {
    assert(this->_camera_controller != 0x0);
    if (this->_indent_lvl == GS::QUADTREE::INDENT::CAMERA_MAX_LVL ||
	this->_indent_lvl == GS::QUADTREE::INDENT::MAX)
      {
	this->_content.push_back(this->_camera_controller);
	return;
      }

    if (QuadTree::ShouldBeContainedBy(this->_camera_controller, this->_upLeft))
      this->_upLeft->AddCameraAEntity(this->_camera_controller);
    if (QuadTree::ShouldBeContainedBy(this->_camera_controller, this->_upRight))
      this->_upRight->AddCameraAEntity(this->_camera_controller);
    if (QuadTree::ShouldBeContainedBy(this->_camera_controller, this->_downLeft))
      this->_downLeft->AddCameraAEntity(this->_camera_controller);
    if (QuadTree::ShouldBeContainedBy(this->_camera_controller, this->_downRight))
      this->_downRight->AddCameraAEntity(this->_camera_controller);

    if (QuadTree::ShouldBeContainedBy(this->_camera_controller, this))
      this->_content.push_back(this->_camera_controller);
  }

  const QuadTree::AEntitySTDVector &		QuadTree::GetContent(void) const
  {
    return this->_content;
  }


  QuadTree::AEntitySTDVector &			QuadTree::GetContent_unsafe(void)
  {
    return this->_content;
  }

  const size_t					QuadTree::getIndentLvl(void) const
  {
    return this->_indent_lvl;
  }
    
  const size_t					QuadTree::GetElementsNbr(void) const
  {
    return this->_content.size();
  }

  const AEntity *				QuadTree::IsEntityRayCastingCollision(EntityProjection & p)
  {
    const AEntity * ret;

    this->AddAEntity(&p);
    ret = this->IsCollisionTest(&p);
    if (ret != NULL)
      std::cout << "#==> Collision : " << p.GetOrigin() << " -- " << ret << std::endl;
    this->RemoveAEntity(&p);
    return ret;
  }

  const AEntity *				QuadTree::IsEntityRayCastingCollision(AEntity & e)
  {
    EntityProjection	p(e);
    return this->IsEntityRayCastingCollision(p);
  }

  void						QuadTree::DrawCamera(sf::RenderWindow & w)
  {
    if (!this->IsContaining(this->_camera_controller))
      return;
    this->Draw(w);

    this->_upRight->DrawCamera(w);
    this->_upLeft->DrawCamera(w);
    this->_downRight->DrawCamera(w);
    this->_downLeft->DrawCamera(w);
  }

}
