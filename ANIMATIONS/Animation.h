#ifndef __ANIMATION__
# define __ANIMATION__

# include "../AEntitySprites.h"

# include <SFML/Graphics.hpp>
# include "/usr/include/boost/make_shared.hpp"
# include "/usr/include/boost/shared_ptr.hpp"
# include <vector>

class Animation
{
 public:
  typedef char						IndexType;
  typedef std::vector<IndexType>			AnimationVector;
  typedef std::vector<IndexType>::iterator		AnimationVector_iterator;
  typedef std::vector<IndexType>::const_iterator	AnimationVector_const_iterator;

  Animation(boost::shared_ptr<AEntitySprites> const & s, const AnimationVector & v);  
  Animation(boost::shared_ptr<AEntitySprites> const & s, const IndexType * tab);
  Animation(boost::shared_ptr<AEntitySprites> const & s, const Animation & r);

  IndexType						GetCurrentIndex(void) const;
  const sf::Sprite &					GetCurrentSprite(void) const;
  const sf::Sprite &					GetSprite(void);
  const AnimationVector &				GetMatrix(void) const;
  void							Update(void);

 protected:
  AnimationVector					_gen;		// Animation generator
  IndexType						_current;	// Current sprite index to display
  boost::shared_ptr<AEntitySprites>			_spritesStrip;
};

#endif // __ANIMATION__
