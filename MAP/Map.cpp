#include "./Map.h"

Map::Map(size_t w, size_t h, sf::Window * app)
  : _width(w),
    _height(h),
    _app(app)
{
  memset(this->_content, 0x0, MAX_BLOCK_PER_MAP);
  size_t max_width	= Map::SCREEN_WIDTH_MAX_RESOLUTION;
  size_t max_height	= Map::SCREEN_HEIGHT_MAX_RESOLUTION;
}

Map::~Map()
{
  this->CleanElements();
  this->CleanElementsSprites();
}

const MAP::Block::TYPE &		Map::GetBlock(size_t it) const
{
  assert(it < this->Size());
  return this->_content[it];
}

const MAP::Block::TYPE &		Map::GetBlock(size_t x, size_t y) const
{
  assert(x + (y * this->_width) < MAX_BLOCK_PER_MAP);
  return this->_content[x + (y * this->_width)];
}

const MAP::Block::TYPE *		Map::GetContent(void) const
{
  return this->_content;
}
  
size_t					Map::Size(void) const
{
  return (this->_width * this->_height);
}

void					Map::SetBlock(MAP::Block::TYPE t, size_t it)
{
  this->_content[it] = t;
}

void					Map::SetBlock(MAP::Block::TYPE t, size_t x, size_t y)
{
  this->_content[x + (y * this->_width)] = t;
}

void					Map::Dump(void) const
{
  std::cout << "Width  : " << this->_width << std::endl
	    << "Height : " << this->_height << std::endl
	    << "Map    : " << std::endl;

  size_t		it;
  size_t		tmp_it	 = -1;
  MAP::Block::TYPE	tmp_type = MAP::Block::UNDEFINED_TYPE;
  for (it = 0; it < this->Size(); ++it)
    {
      if (this->_content[it] != tmp_type)
	{
	  if (tmp_type != MAP::Block::UNDEFINED_TYPE && tmp_it != -1)
	    std::cout << "(" << tmp_it << " => " << it << ")\t"
		      << Map::BlockTypeToString(tmp_type) << std::endl;

	  tmp_type	= this->_content[it];
	  tmp_it	= it;
	}
    }
}

void					Map::SetElements(Map::ElementsVector & v)
{
  this->CleanElements();
  this->_elements = v;
}

void					Map::CleanElements(void)
{
  Map::ElementsVector::iterator it;

  std::cout << "Map::CleanElements : " << this->_elements.size() << std::endl;
  for (it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      delete *it;
      it = this->_elements.erase(it);
    }
}

void					Map::Clear(void)
{
  std::cout << "Map::Clear : before : " << this->_elements.size() << std::endl;
  this->_elements.clear();
  memset(this->_content, 0x0, MAX_BLOCK_PER_MAP);
  this->_width	= 0;
  this->_height	= 0;
  std::cout << "Map::Clear : after  : " << this->_elements.size() << std::endl;
}

void					Map::CleanElementsSprites(void)
{
  Map::ElementsSpritesMap::iterator	it;
  for (it = this->_elementsSprites.begin(); it != this->_elementsSprites.end(); ++it)
      it->second.reset();
  this->_elementsSprites.clear();
}

void					Map::ReloadElements(void)
{
  assert(this->_app != 0x0);
  assert(this->_elementsSprites.size() != 0);
  this->CleanElements();

#ifdef __VERBOSE__
  std::cout << "----------------------------------" << std::endl
	    << "#- Loaded element's sprites for : " << std::endl;
  Map::ElementsSpritesMap::iterator it_s;
  for (it_s = this->_elementsSprites.begin(); it_s != this->_elementsSprites.end(); ++it_s)
    std::cout << it_s->first << " => " << it_s->second << std::endl;
  std::cout << "----------------------------------" << std::endl;
#endif

  size_t	it;
  for (it = 0; it < this->Size(); ++it)
    {
      if (this->_content[it] != MAP::Block::VOID)
	{
	  if (this->_elementsSprites.find(this->_content[it]) == this->_elementsSprites.end())
	    {
	      std::cerr << "Invalid conf : a sprite is missing : keycode : "
			<< this->_content[it] << std::endl;
	      exit(EXIT_FAILURE);
	    }

	  this->_elements.push_back(new MAP::Block(this->_content[it],
						   this->_app,
						   this->_elementsSprites[this->_content[it]],
						   100,
						   (it % this->_width) * 32, (it / this->_width) * 32,
						   32, 32));
	  this->_elements.back()->SetBehaviour(boost::make_shared<MapBlockBehaviour>(this->_elements.back()));
	}
    }
  
  std::cout << "DEBUG : " << this->_elements.back() << std::endl;
  std::cout << "DEBUG : " << this->_elements.back()->IsDeleteNotified() << std::endl;
}

void					Map::SetSprite(const MAP::Block::TYPE & k, boost::shared_ptr<AEntitySprites> v)
{
  if (this->_elementsSprites.find(k) != this->_elementsSprites.end())
    {
      this->_elementsSprites[k].reset();
      this->_elementsSprites.erase(k);
    }
  this->_elementsSprites[k] = v;
}

boost::shared_ptr<AEntitySprites> &	Map::GetSprite(const MAP::Block::TYPE & k)
{
  return this->_elementsSprites[k];
}

const Map::ElementsSpritesMap &		Map::GetSprites(void) const
{
  return this->_elementsSprites;
}

Map::ElementsVector &			Map::GetElements(void)
{
  return this->_elements;
}

void					Map::SetApp(sf::Window * app)
{
  this->_app = app;
}
