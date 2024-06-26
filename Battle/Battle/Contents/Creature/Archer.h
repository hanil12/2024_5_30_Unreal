#pragma once
class Archer : public Player
{
public:
	Archer(string name, int hp, int atk);
	virtual ~Archer();

	virtual void Attack(Creature* other) override;
	virtual void Attack(shared_ptr<Creature> other) override;
private:

};

