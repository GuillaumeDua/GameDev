#ifndef __CONF_FILE_PARSER__
# define __CONF_FILE_PARSER__

# include <iostream>
# include <cstring>
# include <fstream>
# include <string>
# include <map>


class ConfFileParser
{
 public:

  typedef std::map<std::string, std::string>	KeyValue;
  typedef std::map<std::string, KeyValue>	ContentType;

  ConfFileParser(void);
  ConfFileParser(const char *);
  ~ConfFileParser();

  void		Clear(void);
  virtual void	Dump(void)			const;
  bool		LoadFromFile(const char *);

 protected:

  ContentType	_content;
  bool		_isLoad;
};

#endif // __CONF_FILE_PARSER__
