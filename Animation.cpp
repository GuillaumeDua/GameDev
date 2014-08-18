#include "Animation.h"


Animation::Animation(boost::shared_ptr<AEntitySprites> const & s, const AnimationVector & v)
  : _gen(v), _current(0), _spritesStrip(s)
{}
  
Animation::Animation(boost::shared_ptr<AEntitySprites> const & s, const int * tab, const int * ss)
  : _gen(tab, ss), _current(0), _spritesStrip(s)
{}
  
Animation::Animation(boost::shared_ptr<AEntitySprites> const & s, const Animation & r)
  : _gen(r.getGenerator()), _current(0), _spritesStrip(s)
{}

int					Animation::getCurrentIndex(void) const
{
  return this->_current;
}

const sf::Sprite &			Animation::getCurrentSprite(void) const
{
  this->_spritesStrip.get()->getSprite(this->_current);
}

const Animation::AnimationVector &	Animation::getGenerator(void) const
{
  return this->_gen;
}

void					Animation::Update(void)
{
  this->_current = this->_gen.at(this->_current);
}
