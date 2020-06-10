#pragma once
#include "Box2D.h"
#include "Character.h"
namespace LVB
{
	class ContactListener : public b2ContactListener
	{
    public:
        void BeginContact(b2Contact* contact) {
            //check if fixture A was the foot sensor
            void* fixtureUserData = contact->GetFixtureA()->GetUserData();
            if ((int)fixtureUserData == 3)
                m_Parent->m_FootContactCount++;
            //check if fixture B was the foot sensor
            fixtureUserData = contact->GetFixtureB()->GetUserData();
            if ((int)fixtureUserData == 3)
                m_Parent->m_FootContactCount++;
        }

        void EndContact(b2Contact* contact) {
            //check if fixture A was the foot sensor
            void* fixtureUserData = contact->GetFixtureA()->GetUserData();
            if ((int)fixtureUserData == 3)
                m_Parent->m_FootContactCount--;
            //check if fixture B was the foot sensor
            fixtureUserData = contact->GetFixtureB()->GetUserData();
            if ((int)fixtureUserData == 3)
                m_Parent->m_FootContactCount--;
        }
         void SetCharacter(Character * character) { m_Parent = character; }

    private:
        Character* m_Parent;
	};
}