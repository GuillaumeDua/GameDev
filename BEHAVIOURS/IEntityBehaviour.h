#ifndef __IENTITY_BEHAVIOUR__
# define __IENTITY_BEHAVIOUR__

# include "./../AEntity.h"

class IEntityBehaviour
{
 public:

  IEntityBehaviour(AEntity * thisEntity,
		   AEntity * bondAEntity = 0x0)
    {
      this->_this		= thisEntity;
      this->_bondAEntity	= bondAEntity;
    }

  virtual bool		OnBorderCollision(void)	= 0;
  virtual bool		OnCollision(void)	= 0;
  virtual bool		Routine(void)		= 0;

  void			SetBondAEntity(AEntity * e)
  {
    this->_bondAEntity = e;
  }

 protected:
  AEntity *		_bondAEntity;
  AEntity *		_this;
};


/* #define	GEN_BASIC_BEHAVIOUR_DEFINITION(name)		\ */
/* 							\ */
/*   class name : public IEntityBehaviour			\ */
/*   {							\ */
/*   public:						\ */
/* 							\ */
/*     name(AEntity *, AEntity *);				\ */
/* 							\ */
/*     bool		OnBorderCollision(void);	\ */
/*     bool		OnCollision(void);		\ */
/*     bool		Routine(void);			\ */
/* 							\ */
/*   protected:						\ */
/*   };							\ */



#endif // __IENTITY_BEHAVIOUR__
