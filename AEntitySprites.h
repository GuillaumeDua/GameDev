#ifndef __AENTITITY_SPRITES__
# define __AENTITITY_SPRITES__

# include <SFML/Graphics.hpp>
# include "/usr/include/boost/make_shared.hpp"
# include "/usr/include/boost/shared_ptr.hpp"

# include "./Geometry.h"

# include <vector>


# define DEBUG_AENTITYSPRITES_OFF

class	AEntitySprites
{
 public:

  static const size_t MAX_SPRITES_PER_ENTITY = 100;

  typedef std::vector<sf::Sprite *>			SpriteVector;
  typedef std::vector<sf::Sprite *>::iterator		SpriteVector_iterator;
  typedef std::vector<sf::Sprite *>::const_iterator	SpriteVector_const_iterator;

  // no cpy ctor 'cos of excessive cost

  AEntitySprites(const std::string & path, size_t w, size_t h);
  AEntitySprites(const sf::Image & image, size_t w, size_t h);
  ~AEntitySprites();

  bool	operator!();
  const sf::Image &		getImage(void) const;  
  const sf::Sprite &		getSprite(unsigned int index) const;
  const SpriteVector &		getSprites(void) const;
  SpriteVector &		getSprites_unsafe(void);

  static bool			SubImageIntoMultiSprites(AEntitySprites::SpriteVector & sm,
							 const sf::Image & image,
							 size_t w, size_t h);

  inline bool			spriteExist(unsigned int index) const
  {
    return (this->_sprites.size() - 1 < index) ? false : true;
  }

  inline const Point<size_t> &	getSpriteSize(void) const
  {
    return this->_spritesSize;
  }

 protected:

  bool				_isError;
  sf::Image			_image;
  SpriteVector			_sprites;
  Point<size_t>			_spritesSize;
};

#endif // __AENTITITY_SPRITES__
