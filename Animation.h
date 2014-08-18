#ifndef __ANIMATION__
# define __ANIMATION__

# include "AEntitySprites.h"


# include <SFML/Graphics.hpp>
# include "/usr/include/boost/make_shared.hpp"
# include "/usr/include/boost/shared_ptr.hpp"
# include <vector>

class Animation
{
 public:
  typedef std::vector<int>				AnimationVector;
  typedef std::vector<int>::iterator			AnimationVector_iterator;
  typedef std::vector<int>::const_iterator		AnimationVector_const_iterator;

  Animation(boost::shared_ptr<AEntitySprites> const & s, const AnimationVector & v);  
  Animation(boost::shared_ptr<AEntitySprites> const & s, const int * tab, const int * ss);
  Animation(boost::shared_ptr<AEntitySprites> const & s, const Animation & r);

  int					getCurrentIndex(void) const;
  const sf::Sprite &			getCurrentSprite(void) const;
  const AnimationVector &		getGenerator(void) const;
  void					Update(void);

 protected:
  AnimationVector			_gen;		// Animation generator
  int					_current;	// Current sprite index to display
  boost::shared_ptr<AEntitySprites>	_spritesStrip;
};

#endif // __ANIMATION__
