#ifndef __MAP_LOADER__
# define __MAP_LOADER__

# include "./Map.h"
# include "../TOOLS/Tools.hpp"
# include "../TOOLS/ConfFileParser.h"
# include "../AEntitySprites.h"

class MapLoader : public ConfFileParser
{
 public:

  typedef std::map<std::string, AEntitySprites*> AEntitySpritesMap;

  MapLoader(sf::Window * app = 0x0);
  MapLoader(const char *, sf::Window * app = 0x0);
  ~MapLoader();
  
  bool			Reload(void);
  bool			Reload(const char *);
  void			Unload(void);
  void			Dump(void) const;

  void			SetApp(sf::Window * app);
  void			ResetApp(void);

  Map *			Get(void);

 protected:
  bool			LoadSprites(void);
  bool			Generate(void);
  bool			IsLoadedConfValid(void);

  bool			_isReady;
  Map *			_map;
  // AEntitySpritesMap	_sprites;
  sf::Window *		_app;
};

#endif // __MAP_LOADER__
