#include "Animation.h"


Animation::Animation(boost::shared_ptr<AEntitySprites> const & s, const AnimationVector & v)
  : _gen(v),
    _current(0),
    _spritesStrip(s)
{}
  
Animation::Animation(boost::shared_ptr<AEntitySprites> const & s, const Animation::IndexType * tab)
  : _gen(tab, tab + sizeof(tab) / sizeof(Animation::IndexType)),
    _current(0),
    _spritesStrip(s)
{}
  
Animation::Animation(boost::shared_ptr<AEntitySprites> const & s, const Animation & r)
  : _gen(r.GetMatrix()),
    _current(0),
    _spritesStrip(s)
{}

Animation::IndexType			Animation::GetCurrentIndex(void) const
{
  return this->_current;
}

const sf::Sprite &			Animation::GetCurrentSprite(void) const
{
  return this->_spritesStrip.get()->getSprite(this->_current);
}

const sf::Sprite &			Animation::GetSprite(void)
{
  return this->_spritesStrip.get()->getSprite(this->_current++);
}


const Animation::AnimationVector &	Animation::GetMatrix(void) const
{
  return this->_gen;
}

void					Animation::Update(void)
{
  this->_current = this->_gen.at(this->_current);
}

