#ifndef __MAP_LOADER__
# define __MAP_LOADER__

# include "./Map.h"
# include "./ConfFileParser.h"
# include "./Tools.h"
# include "../AEntitySprites.h"

class MapLoader : public ConfFileParser
{
 public:

  typedef std::map<std::string, AEntitySprites*> AEntitySpritesMap;

  MapLoader();
  MapLoader(const char *);
  ~MapLoader();
  
  bool			Reload(void);
  bool			Reload(const char *);
  void			Unload(void);
  void			Dump(void) const;

 protected:
  bool			LoadSprites(void);
  bool			Generate(void);
  bool			IsLoadedConfValid(void);

  bool			_isReady;
  Map *			_map;
  AEntitySpritesMap	_sprites;
};

#endif // __MAP_LOADER__
