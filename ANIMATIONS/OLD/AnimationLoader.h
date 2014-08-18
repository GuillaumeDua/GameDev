#ifndef __ANIMATION__
# define __ANIMATION__

# include <iostream>
# include <cstring>
# include <fstream>
# include <string>
# include <cassert>

class Animation
{
 public:

  Animation(void);
  Animation(const char *);
  ~Animation();

  bool		LoadFromFile(const char *);
  void		Clean(void);
  const char	GetNextSpriteIndex(const char &) const;
  const char *	GetContent(void) const;

 protected:
  char		_content[255];
  bool		_isLoad;
};


#endif // __ANIMATION__
