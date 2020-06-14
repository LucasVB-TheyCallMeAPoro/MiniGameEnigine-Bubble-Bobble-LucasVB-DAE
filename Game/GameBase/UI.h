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
namespace LVB {
	class GameScene;
	class GameObject;
}
class UI
{
public:
	enum ScreenPos
	{
		player1,
		player2
	};
	UI(Character* character,ScreenPos pos, LVB::GameScene* scene);
	void Render() const;
	void Update();
	void SetLevelNumber(int i);
private:
	ScoreListener m_ScoreListener;
	HealthListener m_HealthListener;
	LVB::GameObject* m_ScoreObject;
	LVB::GameObject* m_HealthObject;
	Character* m_Character;
	ScreenPos m_Pos;

	LVB::GameObject* m_LevelNumberObject;
};