#include "./Map.h"

Map::Map(size_t w, size_t h)
  : _width(w),
    _height(h)
{
  memset(this->_content, 0x0, MAX_BLOCK_PER_MAP);
}

const Block::TYPE &	Map::GetBlock(size_t it) const
{
  assert(it < this->Size());
  return this->_content[it];
}

const Block::TYPE &	Map::GetBlock(size_t x, size_t y) const
{
  assert(x + (y * this->_width) < MAX_BLOCK_PER_MAP);
  return this->_content[x + (y * this->_width)];
}

const Block::TYPE *	Map::GetContent(void) const
{
  return this->_content;
}
  
size_t			Map::Size(void) const
{
  return (this->_width * this->_height);
}

void			Map::SetBlock(Block::TYPE t, size_t it)
{
  this->_content[it] = t;
}

void			Map::SetBlock(Block::TYPE t, size_t x, size_t y)
{
  this->_content[x + (y * this->_width)] = t;
}

void			Map::Dump(void) const
{
  std::cout << "Width  : " << this->_width << std::endl
	    << "Height : " << this->_height << std::endl
	    << "Map    : " << std::endl;

  size_t	it;
  size_t	tmp_it	 = -1;
  Block::TYPE	tmp_type = Block::UNDEFINED_TYPE;
  for (it = 0; it < this->Size(); ++it)
    {
      if (this->_content[it] != tmp_type)
	{
	  if (tmp_type != Block::UNDEFINED_TYPE && tmp_it != -1)
	    std::cout << "(" << tmp_it << " => " << it << ")\t"
		      << Map::BlockTypeToString(tmp_type) << std::endl;

	  tmp_type	= this->_content[it];
	  tmp_it	= it;
	}
    }
}
