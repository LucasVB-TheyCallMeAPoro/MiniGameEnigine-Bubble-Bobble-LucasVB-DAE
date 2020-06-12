#pragma once
#include <Listener.h>


class HealthListener : public LVB::Listener<int>
{
public:
	int m_Health;
private:
	void OnNotify(int health) {m_Health = health; }
};

class ScoreListener : public LVB::Listener<int>
{
public: 
	int m_Score;
private:
	void OnNotify(int score) { m_Score = score; }
};

class Character;
class UI
{
public:
	enum ScreenPos
	{
		left,
		right
	};
	UI(Character* character,ScreenPos pos);
	void Render() const;
private:
	ScoreListener m_ScoreListener;
	HealthListener m_HealthListener;

	Character* m_Character;
	ScreenPos m_Pos;
};