#include "./ControlableBehaviour.h"

ControlableBehaviour::ControlableBehaviour(AEntity * __this__, GS::GameSystem * gs)
  : IEntityBehaviour(__this__, 0x0),
    _gameSystem(gs)
{
  this->_this->SetType(AEntity::PLAYER);
}


bool		ControlableBehaviour::OnBorderCollision(void)
{
  std::cout << "#===> Out of Screen !" << std::endl;
  this->_this->CorrectPositionToMapSize();
  return true;
}

bool		ControlableBehaviour::OnCollision(void)
{
  // this->_this->SetPos(rand() % 400, rand() % 400);
  Collisionable::FACE	f;
  bool			isDownCollision = false;

  if (!(this->_this->GetCollisionStack().empty())) // useless secu
    {
      Collisionable::CollisionableVector::iterator	it;

      for (it = this->_this->GetCollisionStack().begin(); it != this->_this->GetCollisionStack().end(); ++it)
	{
	  if ((*it)->GetType() == Collisionable::MAP_BLOCK)
	    {
	      std::cout << "it works !" << std::endl;

	    }
	}
      this->_this->SetNeedGravityAction(!isDownCollision);
    }
  return true;
}

bool		ControlableBehaviour::Routine(void)
{
  const sf::Input & input = this->_gameSystem->GetInput();


  if (input.IsKeyDown(sf::Key::Left) ||
      input.IsKeyDown(sf::Key::Right) ||
      input.IsKeyDown(sf::Key::Down) ||
      input.IsKeyDown(sf::Key::Up))
    {
      this->_this->SetSpriteIndex(this->_this->GetSpriteIndex() == 7 ? 0 : this->_this->GetSpriteIndex() + 1);
    }

  if (input.IsKeyDown(sf::Key::Left))
    {
      if (input.IsKeyDown(sf::Key::Up))
	this->_this->RequestMoveLeftUp();
      else if (input.IsKeyDown(sf::Key::Down))
	this->_this->RequestMoveLeftDown();
      else this->_this->RequestMoveLeft();
    }
  else if (input.IsKeyDown(sf::Key::Right))
    {
      if (input.IsKeyDown(sf::Key::Up))
	this->_this->RequestMoveRightUp();
      else if (input.IsKeyDown(sf::Key::Down))
	this->_this->RequestMoveRightDown();
      else this->_this->RequestMoveRight();
    }
  else if (input.IsKeyDown(sf::Key::Up))
    this->_this->RequestMoveUp();
  else if (input.IsKeyDown(sf::Key::Down))
    this->_this->RequestMoveDown();

  if (!(this->_this->GetCollisionStack().empty()))
    this->_this->ResetCollision();

  return true;

}

