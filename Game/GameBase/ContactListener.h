#pragma once
#include "Box2D.h"
#include "Character.h"
#include "Bubble.h"
#include "Enemies.h"
#include <string>
#include <cstring>
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
            EnemyHitWall(contact);
        }

        void EndContact(b2Contact* contact) {
            //check if fixture A was the foot sensor
            void* fixtureUserDataA = contact->GetFixtureA();
            void* fixtureUserDataB = contact->GetFixtureB();
            for (int i{ 0 }; i < m_Characters.size(); ++i)
            {
                if (fixtureUserDataA == m_Characters[i]->GetFootSensor() || fixtureUserDataB == m_Characters[i]->GetFootSensor())
                {
                    m_Characters[i]->DecrementFootCount();
                }
            }

            for (int i{ 0 }; i < m_Enemies.size(); ++i)
            {
                if (fixtureUserDataA == m_Enemies[i]->GetFootSensor() || fixtureUserDataB == m_Enemies[i]->GetFootSensor())
                {
                    m_Enemies[i]->DecrementFootCount();
                }
            }

        }
         void AddCharacter(Character * character) { m_Characters.push_back(character); }
        
         void AddEnemy(Enemy* e) { m_Enemies.push_back(e); }
         void ClearEnemies() { m_Enemies.clear(); }
    private:
        std::vector<Character*> m_Characters;
        std::vector<Enemy*> m_Enemies;
        void IsGrounded(b2Contact* contact)
        {
            //Check if grounded code
           //check if fixture A was the foot sensor
            auto fixtureUserDataA = contact->GetFixtureA();
            auto fixtureUserDataB = contact->GetFixtureB();

            for (int i{ 0 }; i < m_Characters.size(); ++i)
            {
                //&& fixtureUserDataB == &LVB::BubbleBobbleScene::keyPlatform)
                // && fixtureUserDataA == &LVB::BubbleBobbleScene::keyPlatform
                if ((fixtureUserDataA == m_Characters[i]->GetFootSensor() && fixtureUserDataB->GetFilterData().categoryBits == LVB::BubbleBobbleScene::PLATFORM) || (fixtureUserDataB == m_Characters[i]->GetFootSensor() && fixtureUserDataA->GetFilterData().categoryBits == LVB::BubbleBobbleScene::PLATFORM))
                {
                    m_Characters[i]->IncrementFootCount();
                }
            }

            for (int i{ 0 }; i < m_Enemies.size(); ++i)
            {
                if ((fixtureUserDataA == m_Enemies[i]->GetFootSensor() && fixtureUserDataB->GetFilterData().categoryBits == LVB::BubbleBobbleScene::PLATFORM) || (fixtureUserDataB == m_Enemies[i]->GetFootSensor() && fixtureUserDataA->GetFilterData().categoryBits == LVB::BubbleBobbleScene::PLATFORM))
                {
                    m_Enemies[i]->IncrementFootCount();
                }
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
                   for (int i{ 0 }; i < m_Characters.size(); ++i)
                   {
                       if (fixtureB == m_Characters[i]->GetBody())
                           bubble->Hit();
                   }
               }
               else
               {
                   for (int i{ 0 }; i < m_Characters.size(); ++i)
                   {
                       if (fixtureA == m_Characters[i]->GetBody())
                           bubble->Hit();
                   }
               }
           }
        }
        void EnemyHitWall(b2Contact* contact) 
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();
            void* fixtureUserDataA = fixtureA->GetUserData();
            void* fixtureUserDataB = fixtureB->GetUserData();
            for (int i{ 0 }; i < m_Enemies.size(); ++i)
            {
                if ((fixtureA == m_Enemies[i]->GetRigidBodyFixture() && fixtureB->GetFilterData().categoryBits == LVB::BubbleBobbleScene::BOUNDARY) || (fixtureB == m_Enemies[i]->GetRigidBodyFixture() && fixtureA->GetFilterData().categoryBits == LVB::BubbleBobbleScene::BOUNDARY))
                    m_Enemies[i]->HitWall();
            }
        }
	};
}