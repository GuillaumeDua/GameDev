#ifndef __ENTITY__
# define __ENTITY__

# include "./AEntity.h"
# include "./AEntitySprites.h"
# include "./BEHAVIOURS/IEntityBehaviour.h"


class Entity : public AEntity
{
 public:

  Entity(sf::Window * app,
  	 boost::shared_ptr<AEntitySprites> const & v,
  	 unsigned int s = Entity::DEFAULT_SPEED,
  	 float x = 0, float y = 0,
  	 size_t sx = 0, size_t sy = 0);

  Entity(sf::Window * app,
  	 boost::shared_ptr<AEntitySprites> const & v,
  	 unsigned int s = Entity::DEFAULT_SPEED,
  	 Point<float> = Point<float>(0,0),
  	 Point<size_t> = Point<size_t>(0,0));

  Entity(const Entity &);


  virtual bool					Behave(void);
  virtual bool					Behave_e(void);

  void						SetBehaviour(boost::shared_ptr<IEntityBehaviour> const &);
  const boost::shared_ptr<IEntityBehaviour> &	GetBehaviour(void) const;
  bool						IsBehaviourSet(void) const;

  bool						NotifyDelete(void);
  bool						IsDeleteNotified(void) const;

 protected:
    volatile bool				_isDeleted;
    boost::shared_ptr<IEntityBehaviour>		_behaviour;
};


#endif // __ENTITY__
