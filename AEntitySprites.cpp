#include "./AEntitySprites.h"


AEntitySprites::AEntitySprites(const std::string & path, size_t w, size_t h)
{
  if (!this->_image.LoadFromFile(path) ||
      !AEntitySprites::SubImageIntoMultiSprites(this->_sprites, this->_image, w, h))
    {
      this->_isError = true;
      return;
    }

  this->_spritesSize._x	= w;
  this->_spritesSize._y	= h;
  this->_isError       	= false;
}

AEntitySprites::AEntitySprites(const sf::Image & image, size_t w, size_t h)
{
  this->_image		= image;
  this->_spritesSize._x	= w;
  this->_spritesSize._y	= h;
  this->_isError	= false;

  if (!AEntitySprites::SubImageIntoMultiSprites(this->_sprites, this->_image, w, h))
    {
      this->_isError = true;
      return;
    }
}

AEntitySprites::~AEntitySprites()
{
  SpriteVector_iterator it;
  for (it = this->_sprites.begin(); it != this->_sprites.end(); ++it)
    delete *it;
}

bool						AEntitySprites::operator!()
{
  return this->_isError;
}

const sf::Image &				AEntitySprites::getImage(void) const
{
  return this->_image;
}

const sf::Sprite &				AEntitySprites::getSprite(unsigned int index) const
{
  return *(this->_sprites.at(index));
}

const AEntitySprites::SpriteVector &		AEntitySprites::getSprites(void) const
{
  return this->_sprites;
}

AEntitySprites::SpriteVector &			AEntitySprites::getSprites_unsafe(void)
{
  return this->_sprites;
}

bool						AEntitySprites::SubImageIntoMultiSprites(AEntitySprites::SpriteVector & sm,
											 const sf::Image & image,
											 size_t w, size_t h)
{
  if (image.GetWidth()  % w != 0 ||
      image.GetHeight() % h != 0 ||
      (((image.GetWidth()  / w) * (image.GetHeight() / h)) > MAX_SPRITES_PER_ENTITY))
    return false;

  size_t	x;
  size_t	y;

  for (y = 0; y < image.GetHeight(); y += h)
    {
      for (x = 0; x < image.GetWidth(); x += w)
	{
	  sm.push_back(new sf::Sprite(image));
	  sm.back()->SetSubRect(sf::IntRect(x, y, x + w, y + h));
#ifdef AENTITYSPRITES_DEBUG_ON
	  std::cout << "loading : " << x << "," << y << std::endl;
#endif
	}
    }

#ifdef AENTITYSPRITES_DEBUG_ON
  std::cout << "[AEntitySprites]::[SubImageIntoMultiSprites] : loaded sprites : " << sm.size() << std::endl;
#endif
  return true;
}
