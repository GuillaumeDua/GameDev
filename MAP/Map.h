#ifndef __MAP__
# define __MAP__

# define __VERBOSE__

# include <iostream>
# include <vector>
# include <map>
# include <unistd.h>
# include <cstring>
# include <cassert>
# include "./MapBlock.h"
# include "../BEHAVIOURS/MapBlockBehaviour.h"

# define MAP_COLLISION_CHECK_RATE 3

class	Map
{
 public:

  typedef std::vector<MAP::Block*>						ElementsVector;
  typedef std::map<MAP::Block::TYPE, boost::shared_ptr<AEntitySprites> >	ElementsSpritesMap;

  static MAP::Block::TYPE	StringToBlockType(const std::string & t)
  {
    if (t == "UNDEFINED_TYPE")	return MAP::Block::UNDEFINED_TYPE;
    if (t == "VOID")		return MAP::Block::VOID;
    if (t == "FIRE")		return MAP::Block::FIRE;
    if (t == "WATER")		return MAP::Block::WATER;
    if (t == "METAL")		return MAP::Block::METAL;
    if (t == "EARTH")		return MAP::Block::EARTH;
    if (t == "TREE")		return MAP::Block::TREE;
  }

  static std::string		BlockTypeToString(const MAP::Block::TYPE & t)
  {
    if (t == MAP::Block::UNDEFINED_TYPE)	return "UNDEFINED_TYPE";
    if (t == MAP::Block::VOID)			return "VOID";
    if (t == MAP::Block::FIRE)			return "FIRE";
    if (t == MAP::Block::WATER)			return "WATER";
    if (t == MAP::Block::METAL)			return "METAL";
    if (t == MAP::Block::EARTH)			return "EARTH";
    if (t == MAP::Block::TREE)			return "TREE";
    return "";
  }

  static const size_t	SCREEN_WIDTH_MAX_RESOLUTION	= 1024;
  static const size_t	SCREEN_HEIGHT_MAX_RESOLUTION	= 768;
# define GET_BLOCK_PER_PIXEL_AREA(x) (x/32)
  static const size_t	MAX_BLOCK_PER_MAP		= (GET_BLOCK_PER_PIXEL_AREA(SCREEN_WIDTH_MAX_RESOLUTION) * 
							   GET_BLOCK_PER_PIXEL_AREA(SCREEN_HEIGHT_MAX_RESOLUTION));

  Map(size_t, size_t, sf::Window * app = 0x0);
  ~Map();

  const MAP::Block::TYPE &			GetBlock(size_t)		const;
  const MAP::Block::TYPE &			GetBlock(size_t, size_t)	const;
  const MAP::Block::TYPE *			GetContent(void)		const;
  ElementsVector &				GetElements(void);
  boost::shared_ptr<AEntitySprites> &		GetSprite(const MAP::Block::TYPE &);
  const ElementsSpritesMap &			GetSprites(void)		const;

  void						SetElements(ElementsVector &);
  
  size_t					Size(void)			const;
  void						Dump(void)			const;

  void						SetBlock(MAP::Block::TYPE, size_t);
  void						SetBlock(MAP::Block::TYPE, size_t, size_t);
  void						SetSprite(const MAP::Block::TYPE &, boost::shared_ptr<AEntitySprites>);
  void						SetApp(sf::Window *);

  void						ReloadElements(void);

  void						Clear(void);			// no delete
 protected:
  void						CleanElements(void);
  void						CleanElementsSprites(void);

  size_t					_width;
  size_t					_height;
  MAP::Block::TYPE				_content[MAX_BLOCK_PER_MAP];	// to remove ?
  ElementsVector				_elements;
  ElementsSpritesMap				_elementsSprites;

  sf::Window *					_app;
};

#endif // __MAP
