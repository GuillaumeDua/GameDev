#include "./AEntity.h"


#ifdef DEBUG_ENTITY_ON
void			AEntity::DumpPos(void)
  {
    std::cout << "[" << this << "]::[AEntity]::[DumpPos] : "
	      << this->_x << ","
	      << this->_y
	      << std::endl;
  }
#endif


AEntity::AEntity(sf::Window * app,
	       boost::shared_ptr<AEntitySprites> const & v,
	       unsigned int s,
	       float x, float y,
	       size_t sx, size_t sy)
  : Collisionable(app, s, x, y, sx, sy),
    _currentSpriteIndex(0)
{
  this->_visuals	= v;
}

AEntity::AEntity(sf::Window * app,
	       boost::shared_ptr<AEntitySprites> const & v,
	       unsigned int s,
	       Point<float> pos,
	       Point<size_t> size)
  : Collisionable(app, s, pos, size),
    _currentSpriteIndex(0)
{
  this->_visuals	= v;
}
  
AEntity::AEntity(const AEntity & e)
  : Collisionable(e)
{
  this->_visuals	= e.getVisuals();
}

inline boost::shared_ptr<AEntitySprites> const & AEntity::getVisuals(void) const
{
  return this->_visuals;
}

bool				AEntity::DrawIntoWindow(sf::RenderWindow & r, int pic_index)
{
  if (pic_index == AEntity::SPRITE_NOT_SET)
    pic_index = this->_currentSpriteIndex;

  if (!(this->_visuals->spriteExist(pic_index)))
    {
#ifdef DEBUG_ENTITY_ON
      std::cerr << "[AEntity]::[" << this << "] : sprite index doesn't exist : "
		<< pic_index << std::endl;
#endif
      return false;
    }

  this->_visuals->getSprites_unsafe()[pic_index]->SetPosition(this->_x, this->_y);
  this->_visuals->getSprites_unsafe()[pic_index]->FlipX(!(this->_directionX));
  r.Draw(*(this->_visuals.get()->getSprites_unsafe()[pic_index]));

  return true;
}

bool				AEntity::DrawIntoWindow(sf::RenderWindow & r, size_t x, size_t y, int pic_index)
{
  if (pic_index == AEntity::SPRITE_NOT_SET)
    pic_index = this->_currentSpriteIndex;

  if (!(this->_visuals->spriteExist(pic_index)))
    {
#ifdef DEBUG_ENTITY_ON
      std::cerr << "[AEntity]::[" << this << "] : sprite index doesn't exist : "
		<< pic_index << std::endl;
#endif
      return false;
    }

  this->_visuals->getSprites_unsafe()[pic_index]->SetPosition(x, y);
  this->_visuals->getSprites_unsafe()[pic_index]->FlipX(!(this->_directionX));
  r.Draw(*(this->_visuals.get()->getSprites_unsafe()[pic_index]));

  return true;
}


void				AEntity::SetSpriteIndex(size_t s)
{
  this->_currentSpriteIndex = s;
}

const size_t &			AEntity::GetSpriteIndex(void) const
{
  return this->_currentSpriteIndex;
}

bool				AEntity::Behave(void)
{
  return this->Behave_e();
}
