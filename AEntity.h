#ifndef __AENTITY__
# define __AENTITY__

# include <SFML/Graphics.hpp>
# include "./AEntitySprites.h"
# include "./Collisionable.h"

#define	DEBUG_ENTITY_ON


//
//	Renderable entity.
//
//

class	AEntity : public Collisionable
{
 public:


  static const int SPRITE_NOT_SET = -1;

  AEntity(sf::Window * app,
	 boost::shared_ptr<AEntitySprites> const & v,
	 unsigned int s = AEntity::DEFAULT_SPEED,
	 float x = 0, float y = 0,
	 size_t sx = 0, size_t sy = 0);

  AEntity(sf::Window * app,
	 boost::shared_ptr<AEntitySprites> const & v,
	 unsigned int s = AEntity::DEFAULT_SPEED,
	 Point<float> = Point<float>(0,0),
	 Point<size_t> = Point<size_t>(0,0));

  AEntity(const AEntity & e);

#ifdef DEBUG_ENTITY_ON
  void							DumpPos(void);
#endif

  boost::shared_ptr<AEntitySprites> const &		getVisuals(void) const;
  bool							DrawIntoWindow(sf::RenderWindow & r,
								       int pic_index = SPRITE_NOT_SET);
  bool							DrawIntoWindow(sf::RenderWindow & r,
								       size_t x, size_t y,
								       int pic_index = SPRITE_NOT_SET);
  void							SetSpriteIndex(size_t s);
  const size_t &					GetSpriteIndex(void) const;


  virtual bool						Behave_e(void)			= 0;
  virtual bool						Behave(void);

 protected:
  // to change with a static, if the boost_shrd_ptr slow the system
  boost::shared_ptr<AEntitySprites>			_visuals;
  size_t						_currentSpriteIndex;
  // Animation
};


#endif // __AENTITY__
