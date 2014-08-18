#include "./MapLoader.h"

MapLoader::MapLoader(sf::Window * app)
  : ConfFileParser(),
    _isReady(false),
    _map(0x0),
    _app(app)
{}

MapLoader::MapLoader(const char * path, sf::Window * app)
  : ConfFileParser(path),
    _isReady(false),
    _map(0x0),
    _app(app)
{
  this->_isReady = this->Reload();
}

MapLoader::~MapLoader()
{
  this->Unload();
}

bool	MapLoader::Reload(void)
{
  if (!(this->IsLoadedConfValid()) ||
      !(this->Generate()))
    return false;
  return true;
}

bool	MapLoader::Reload(const char * path)
{
  this->Clear();
  this->Unload();
  if (!(this->LoadFromFile(path)) ||
      !(this->Reload()))
    return false;
  return true;
}

void	MapLoader::Unload()
{
  this->_isReady	= false;
  delete this->_map;
  this->_map		= 0x0;
}

bool	MapLoader::LoadSprites(void)
{
  if (!(this->_isLoad) ||
      this->_map->GetSprites().size() != 0)
    return false;

  ConfFileParser::KeyValue::iterator	it;
  MAP::Block::TYPE			t;

  for (it = this->_content["SPRITES"].begin(); it != this->_content["SPRITES"].end(); ++it)
    {
      t = Map::StringToBlockType(this->_content["KEYCODES"][it->first]);
      assert(t != MAP::Block::UNDEFINED_TYPE);
      this->_map->SetSprite(t,
			    boost::make_shared<AEntitySprites>(it->second, 32, 32));
      if (!(*(this->_map->GetSprite(t))))
	{
	  std::cerr << "Error while loading sprites : " << it->first << ", " << t << std::endl;
	  return false;
	}
    }
  return true;
}

bool	MapLoader::IsLoadedConfValid(void)
{
  if (!(this->_isLoad)) return false;
  if (this->_content.find("KEYCODES")		== this->_content.end()	||
      this->_content.find("SPRITES")		== this->_content.end()	||
      this->_content.find("MAP")		== this->_content.end()	||
      this->_content["MAP"].find("width")	== this->_content["MAP"].end()	||
      this->_content["MAP"].find("height")	== this->_content["MAP"].end()	||
      this->_content["MAP"].find("content")	== this->_content["MAP"].end()
      )
    return false;

  std::string				mask = "[]";
  ConfFileParser::KeyValue::iterator	it;

  for (it = this->_content["KEYCODES"].begin(); it != this->_content["KEYCODES"].end(); ++it)
    {
      if (it->first.length() != 1	||
	  it->first.at(0) < 20		||
	  it->first.at(0) > 122		||
	  it->first.find_first_of("[]{}()\\<>") != std::string::npos)
	return false;
      mask += it->first;
    }

  for (it = this->_content["SPRITES"].begin(); it != this->_content["SPRITES"].end(); ++it)
    if (this->_content["KEYCODES"].find(it->first) == this->_content["KEYCODES"].end())
      {
	std::cerr << "A sprites code matched no keycode : " << it->first << std::endl;
	return false;
      }

  size_t	fail_match;
  if ((fail_match = this->_content["MAP"]["content"].find_first_not_of(mask)) != std::string::npos)
    {
      std::cerr << "Unknow character in map : ["
		<< this->_content["MAP"]["content"][fail_match]
		<< "]" << std::endl;
      return false;
    }

  return true;
}

bool	MapLoader::Generate(void)
{
  if (this->_map != 0x0) delete this->_map;

  size_t		width;
  size_t		height;
  
  width		= TOOLS::StringToInt(this->_content["MAP"]["width"]);
  height	= TOOLS::StringToInt(this->_content["MAP"]["height"]);

  assert((width * height) < Map::MAX_BLOCK_PER_MAP);
  assert(this->_app != 0x0);

  this->_map = new Map(width, height, this->_app);

  size_t		str_it = 0;
  size_t		map_it = 0;
  MAP::Block::TYPE	type;
  std::string		map_token;

  while ((str_it = this->_content["MAP"]["content"].find("]", str_it)) != std::string::npos)
    {
      map_token = this->_content["MAP"]["content"][str_it - 1];
      type = Map::StringToBlockType(this->_content["KEYCODES"][map_token]);
      this->_map->SetBlock(type, map_it++);
      str_it++;
    }

  std::cout << "Map size : " << width << " * " << height << " == " << (width * height) << std::endl
	    << "Loaded   : " << map_it << std::endl;

  assert(width * height <=  map_it);

  this->LoadSprites();
  this->_map->ReloadElements();
  return true;
}

void	MapLoader::Dump(void) const
{
  static_cast<ConfFileParser>(*this).Dump();
  if (this->_map != 0x0)
    this->_map->Dump();
}


void	MapLoader::SetApp(sf::Window * app)
{
  this->_app = app;
}

void	MapLoader::ResetApp(void)
{
  this->_app = 0x0;
}

Map *	MapLoader::Get(void)
{
  
  return (this->_isReady ? this->_map : 0x0);
}
