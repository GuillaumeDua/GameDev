#ifndef __ANIMATION_LOADER__
# define __ANIMATION_LOADER__

# include <iostream>
# include <cstring>
# include <fstream>
# include <string>
# include <cassert>
//# include "./Animation.h"
# include "../TOOLS/ConfFileParser.h"

class AnimationLoader : public ConfFileParser
{
 public:

  AnimationLoader(void);
  AnimationLoader(const char *);
  ~AnimationLoader();

  bool		Generate(void);
  void		Clean(void);
  const char	GetNextSpriteIndex(const char &) const;
  const char *	GetContent(void) const;
  void		Dump(void) const;

 protected:
  char		_animationMatrix[255];
  bool		_isReady;
};


#endif // __ANIMATION_LOADER__
