#include "AnimationLoader.h"
#include <sstream>
#include <string>

Animation::Animation(void)
  : _isLoad(false)
{
  this->Clean();
}

Animation::Animation(const char * path)
{
  this->Clean();
  this->_isLoad  = this->LoadFromFile(path);
}

Animation::~Animation()
{}

void		Animation::Clean(void)
{
  memset(this->_content, 0, 255);
  this->_isLoad = false;
}

const char	Animation::GetNextSpriteIndex(const char & current) const
{
  assert(this->_isLoad);
  return this->_content[current];
}

bool		Animation::LoadFromFile(const char * path)
{
  std::ifstream		file(path);

  if (!(file.is_open())) return false;

  std::string		line;
  size_t		it;
  int			c;
  int			last;
  std::string		buf;

  while (file.good())
    {
      std::getline(file, line);

      last	= -1;
      buf	= "";

      for (it = 0; line[it] != '\0' && line[it] != '\n'; ++it)
	{
	  if (line[it] == ',')
	    {
	      if (!(std::istringstream(buf) >> c) || c > 255 || c < 0)
		return false;
	      else if (last != -1)
		{
		  std::cout << "last : [" << last << "] == [" << c << "]" << std::endl;
		  this->_content[last] = c;
		}
	      last = c;
	      buf = "";
	    }
	  else
	    buf += line[it];
	}

      if      (buf.empty());
      else if (!(std::istringstream(buf) >> c)) return false;
      else if (last != -1)
	{
	  std::cout << "last : [" << last << "] == [" << c << "]" << std::endl;
	  this->_content[last] = c;
	}
      last = c;
    }
  file.close();
  
  return true;  
}

const char *	Animation::GetContent(void) const
{
  return this->_content;
}
