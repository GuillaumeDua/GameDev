//
// @Author	: Dua J. Guillaume `Guss`
// @Project	: SFML test
// @todo	: 
//

#ifndef __QUADTREE__
# define __QUADTREE__

# include "./Spec.h"
# include "./Geometry.h"
# include "./AEntity.h"
# include <vector>
# include "./TOOLS/Tools.hpp"
# include "./EntityProjection.h"
# include "DisplayZone.h"

# define QUADTREE_DEBUG_OFF

namespace GS
{
  namespace QUADTREE
  {
    namespace INDENT
    {
      static const size_t		MAX		= 5;	// 4^5 = 1024
      static const size_t		FIRST		= 0;
      static const size_t		CAMERA_MAX_LVL	= 3;
    }
  }

  class QuadTree : public AGameObject
  {
  public:

    typedef QuadTree			child_type;
    typedef std::vector<AEntity *>	AEntitySTDVector;

    // -- AABB
    static bool				ShouldBeContainedBy(const AEntity * e,
							    const QuadTree * lvl);
    static bool				ShouldBeContainedBy(const AEntity & e,
							    const Point<float> & pos,
							    const QuadTree * lvl);

    QuadTree(float x, float y, size_t sx, size_t sy, size_t indent, QuadTree * parent);
    QuadTree(size_t w = GS::SCREEN_WIDTH, size_t h = GS::SCREEN_HEIGHT);
    ~QuadTree();

    void				Debug(const AEntity *);
    void				CheckCollisions(void);
    void				CheckCollisions(AEntitySTDVector &);
    bool				IsCollision(AEntity *);
    const AEntity *			IsCollisionTest(const EntityProjection *) const;
    /* const AEntity *			IsEntityRayCastingCollision(const AEntity &, */
    /* 								    const Point<float> &); */
    const AEntity *			IsEntityRayCastingCollision(EntityProjection &);
    const AEntity *			IsEntityRayCastingCollision(AEntity &);

    void				AddAEntity(AEntity *);
    void				RemoveAEntity(AEntity *);
    void				Clean(void);
    void				Draw(sf::RenderWindow &);
    bool				IsContaining(const AEntity *);

    const AEntitySTDVector &		GetContent(void) const;
    AEntitySTDVector &			GetContent_unsafe(void);
    const size_t			getIndentLvl(void) const;
    const size_t			GetElementsNbr(void) const;


    void				SetCameraController(DisplayZone * e);
    void				AddCameraAEntity(void);
    void				DrawCamera(sf::RenderWindow & w);

  protected:

    void				AddCameraAEntity(DisplayZone * e);

    DisplayZone *			_camera_controller;

    QuadTree *				_parent;
    QuadTree::child_type *		_upLeft;
    QuadTree::child_type *		_upRight;
    QuadTree::child_type *		_downLeft;
    QuadTree::child_type *		_downRight;

    AEntitySTDVector			_content;
    size_t				_indent_lvl;

#ifdef QUADTREE_DEBUG_ON
    sf::Image *				_debugImage;
    sf::Sprite				_debugSprite;
#endif
  };
}
#endif // __QUADTREE__
