#include "AnimationLoader.h"
#include <sstream>

AnimationLoader::AnimationLoader(void)
  : ConfFileParser(),
    _isReady(false)
{
  this->Clean();
}

AnimationLoader::AnimationLoader(const char * path)
  : ConfFileParser(path)
{
  this->Clean();
  this->_isReady  = this->Generate();
}

AnimationLoader::~AnimationLoader()
{}

void		AnimationLoader::Dump(void) const
{
  static_cast<ConfFileParser>(*this).Dump();

  for (size_t it = 0; it < 255; ++it)
    {
      if (it % 10 == 0) std::cout << std::endl;
      std::cout << "[" << static_cast<int>(this->_animationMatrix[it]) << "]";
    }
}

void		AnimationLoader::Clean(void)
{
  memset(this->_animationMatrix, 0, 255);
  this->_isReady = false;
}

const char	AnimationLoader::GetNextSpriteIndex(const char & current) const
{
  assert(this->_isReady);
  return this->_animationMatrix[current];
}

bool		AnimationLoader::Generate(void)
{
  assert(this->_isLoad);

  ConfFileParser::ContentType::const_iterator	it;
  ConfFileParser::KeyValue::const_iterator	value_it;

  int		last;
  int		c;
  size_t	str_it;
  std::string	buf;

  for (it = this->_content.begin(); it != this->_content.end(); ++it)
    {
      std::cout << std::endl << it->first << std::endl;
      last = -1;
      for (value_it = it->second.begin(); value_it != it->second.end(); ++value_it)
	{
	  for (str_it = 0; str_it < value_it->second.length(); ++str_it)
	    {
	      if (value_it->second[str_it] == ',')
		{
		  if (!(std::istringstream(buf) >> c) || c > 255 || c < 0)
		    return false;
		  else if (last != -1)
		    {
		      std::cout << "last : [" << last << "] == [" << c << "]" << std::endl;
		      this->_animationMatrix[last] = c;
		    }
		  last = c;
		  buf = "";
		}
	      else
		buf += value_it->second[str_it];
	    }
	  if (buf.empty());
	  else if (!(std::istringstream(buf) >> c) || c > 255 || c < 0)
	    return false;
	  else if (last != -1)
	    {
	      std::cout << "last : [" << last << "] == [" << c << "]" << std::endl;
	      this->_animationMatrix[last] = c;
	    }
	  last	= c;
	  buf	= "";
	}
    }

  return true;  
}

const char *	AnimationLoader::GetContent(void) const
{
  return this->_animationMatrix;
}
