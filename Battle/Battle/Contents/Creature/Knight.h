#pragma once
class Knight : public Player
{
public:
	Knight(string name, int hp, int atk);
	virtual ~Knight();

	// Player��(��) ���� ��ӵ�
	virtual void Attack(Creature* other) override;
	virtual void Attack(shared_ptr<Creature> other) override;

private:
};

