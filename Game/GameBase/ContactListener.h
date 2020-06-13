#pragma once
#include "Box2D.h"
#include "Character.h"
#include "Bubble.h"
//https://www.iforce2d.net/b2dtut/one-way-walls
//https://www.iforce2d.net/b2dtut/jumpability
//https://www.iforce2d.net/b2dtut/collision-filtering
namespace LVB
{
	class ContactListener : public b2ContactListener
	{
    public:
        void BeginContact(b2Contact* contact) {
           

            IsGrounded(contact);
            BubbleOverlap(contact);
          
        }

        void EndContact(b2Contact* contact) {
            //check if fixture A was the foot sensor
            void* fixtureUserData = contact->GetFixtureA()->GetUserData();
            if ((int)fixtureUserData == 3)
            {
                m_Parent->m_FootContactCount--;
            }
            //check if fixture B was the foot sensor
            fixtureUserData = contact->GetFixtureB()->GetUserData();
            if ((int)fixtureUserData == 3)
            {
                m_Parent->m_FootContactCount--;
            }

        }
         void SetCharacter(Character * character) { m_Parent = character; }
    private:
        Character* m_Parent;
      
        void IsGrounded(b2Contact* contact)
        {
            //Check if grounded code
           //check if fixture A was the foot sensor
            void* fixtureUserData = contact->GetFixtureA()->GetUserData();
            if ((int)fixtureUserData == 3)
            {
                m_Parent->m_FootContactCount++;
            }
            //check if fixture B was the foot sensor
            fixtureUserData = contact->GetFixtureB()->GetUserData();
            if ((int)fixtureUserData == 3)
            {
                m_Parent->m_FootContactCount++;
            }
        }
        void BubbleOverlap(b2Contact* contact)
        {
            b2Fixture* fixtureA = contact->GetFixtureA();
            b2Fixture* fixtureB = contact->GetFixtureB();

            bool sensorA = fixtureA->IsSensor();
            bool sensorB = fixtureB->IsSensor();
            if (!(sensorA ^ sensorB))
                return;
            Bubble* bubble{};
           if(sensorA)
               bubble = reinterpret_cast<Bubble*>(fixtureA->GetBody()->GetUserData());
           else
               bubble = reinterpret_cast<Bubble*>(fixtureB->GetBody()->GetUserData());
            
           if (bubble == nullptr)
               return;
           else
           {
               if (sensorA)
               {
                   if (m_Parent->GetBody()->GetUserData() == fixtureB->GetBody()->GetUserData())
                       bubble->Hit();
               }
               else
               {
                   if (m_Parent->GetBody()->GetUserData() == fixtureA->GetBody()->GetUserData())
                       bubble->Hit();
               }
           }
        }
	};
}