#include "./ConfFileParser.h"

ConfFileParser::ConfFileParser() :
  _isLoad(false)
{}

ConfFileParser::ConfFileParser(const char * path)
{
  this->_isLoad = this->LoadFromFile(path);
}

ConfFileParser::~ConfFileParser()
{
  this->Clear();
}

void	ConfFileParser::Clear()
{
  ConfFileParser::ContentType::iterator it;

  for (it = this->_content.begin(); it != this->_content.end(); ++it)
    it->second.clear();
  this->_content.clear();
}

bool	ConfFileParser::LoadFromFile(const char * path)
{
  std::ifstream		file(path);

  if (!(file.is_open())) return false;

  std::string		line;
  std::string		buff;
  size_t		token;
  size_t		key_token	= std::string::npos;
  size_t		endl_token	= std::string::npos;
  std::string		entry;

  while (file.good())
    {
      std::getline(file, line);
 
      if (line.empty())
	{
	  if ((token = buff.find(':')) == std::string::npos)
	    {
	      std::cerr << "Bad formated file" << std::endl;
	      return false;
	    }
	  entry = buff.substr(0, token);
	  if (entry.empty())
	    {
	      std::cerr << "Bad formated file" << std::endl;
	      return false;
	    }
	  
	  token += 1;
	  while ((token = buff.find('=', token)) != std::string::npos)
	    {
	      if ((key_token = buff.rfind('\n', token)) == std::string::npos ||
		  (endl_token = buff.find('\n', token)) == std::string::npos
		  )
		  return false;
	      token += 1;
	      this->_content[entry][buff.substr(key_token + 1, token - (key_token + 1) - 1)] = buff.substr(token, endl_token - token);
	    }
	  buff.clear();
	}
      else
	{
	  buff += line + '\n';
	  while ((token = buff.find("\\\n")) != std::string::npos)
	    buff.replace(token, 2, "");
	}
    }
  return true;
}

void		ConfFileParser::Dump(void) const
{
  std::cout << "Content size : " << this->_content.size() << std::endl
	    << "---------------" << std::endl;;

  ConfFileParser::ContentType::const_iterator	it;
  ConfFileParser::KeyValue::const_iterator	value_it;


  for (it = this->_content.begin(); it != this->_content.end(); ++it)
    {
      std::cout << std::endl << it->first << std::endl;
      for (value_it = it->second.begin(); value_it != it->second.end(); ++value_it)
	std::cout << value_it->first << " => " << value_it->second << std::endl;
    }
}
