#ifndef __TOOLS__
# define __TOOLS__

# include <iostream>
# include <sstream>
# include <vector>

class TOOLS
{
public:

  template <typename T>
  static void	RemoveValueFromVector(std::vector<T> & v, const T & value)
  {
    typename std::vector<T>::iterator	it = v.begin();

  b:
    for (; it != v.end(); ++it)
      {
	if (*it == value)
	  {
	    it = v.erase(it);
	    goto b;
	  }
      }
  }

  static int	StringToInt(const std::string & str)
  {
    int n;
    if (!(std::istringstream(str) >> n)) n = 0;
    return n;
  }

  template <typename T>
  static const std::string IntToString(T data)
  {
    std::ostringstream oss;
    oss << data;
    return oss.str();
  }

};

#endif // __TOOLS__
