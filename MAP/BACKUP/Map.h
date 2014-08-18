#ifndef __MAP__
# define __MAP__

# include <iostream>
# include <unistd.h>
# include <cstring>
# include <cassert>

class Block
{
 public:

  enum TYPE
  {
    UNDEFINED_TYPE	= 42,
    VOID,
    FIRE,
    WATER,
    METAL,
    EARTH,
    TREE
  };

 protected:
  TYPE	_type;
};


class	Map
{
 public:

  static Block::TYPE	StringToBlockType(const std::string & t)
  {
    if (t == "UNDEFINED_TYPE")	return Block::UNDEFINED_TYPE;
    if (t == "VOID")		return Block::VOID;
    if (t == "FIRE")		return Block::FIRE;
    if (t == "WATER")		return Block::WATER;
    if (t == "METAL")		return Block::METAL;
    if (t == "EARTH")		return Block::EARTH;
    if (t == "TREE")		return Block::TREE;
  }

  static std::string	BlockTypeToString(const Block::TYPE & t)
  {
    if (t == Block::UNDEFINED_TYPE)	return "UNDEFINED_TYPE";
    if (t == Block::VOID)		return "VOID";
    if (t == Block::FIRE)		return "FIRE";
    if (t == Block::WATER)		return "WATER";
    if (t == Block::METAL)		return "METAL";
    if (t == Block::EARTH)		return "EARTH";
    if (t == Block::TREE)		return "TREE";
    return "";
  }

  static const size_t	SCREEN_WIDTH_MAX_RESOLUTION	= 1024;
  static const size_t	SCREEN_HEIGHT_MAX_RESOLUTION	= 768;
# define GET_BLOCK_PER_PIXEL_AREA(x) (x/32)
  static const size_t	MAX_BLOCK_PER_MAP		= (GET_BLOCK_PER_PIXEL_AREA(SCREEN_WIDTH_MAX_RESOLUTION) * 
							   GET_BLOCK_PER_PIXEL_AREA(SCREEN_HEIGHT_MAX_RESOLUTION));

  Map(size_t, size_t);

  const Block::TYPE &	GetBlock(size_t)		const;
  const Block::TYPE &	GetBlock(size_t, size_t)	const;
  const Block::TYPE *	GetContent(void)		const;
  
  size_t		Size(void)			const;
  void			Dump(void)			const;

  void			SetBlock(Block::TYPE, size_t);
  void			SetBlock(Block::TYPE, size_t, size_t);

 protected:
  size_t		_width;
  size_t		_height;
  Block::TYPE		_content[MAX_BLOCK_PER_MAP];
};

#endif // __MAP
