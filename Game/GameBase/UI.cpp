#include "UI.h"
#include "Character.h"
UI::UI(Character* character, ScreenPos pos)
	:m_HealthListener{}
	, m_ScoreListener{}
	,m_Character{character}
	,m_Pos{pos}
{
	m_Character->m_OnChangeScore.AddListener(&m_ScoreListener);
	m_Character->m_OnChangeHealth.AddListener(&m_HealthListener);
}

void UI::Render() const
{
	switch (m_Pos)
	{
	case UI::left:
		break;
	case UI::right:
		break;
	}
}
