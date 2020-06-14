#pragma once
#include "Box2D.h"
#include "Character.h"
#include "Bubble.h"
#include "Pickup.h"
#include "Enemies.h"
#include "Boulder.h"
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
            EnemyHitPlayer(contact);
            PlayerHitPickUp(contact);
            BoulderHitPlayer(contact);
        }

        void EndContact(b2Contact* contact) {
            //check if fixture A was the foot sensor
           auto fixtureUserDataA = contact->GetFixtureA();
           auto fixtureUserDataB = contact->GetFixtureB();
            for (int i{ 0 }; i < m_Characters.size(); ++i)
            {
                if (fixtureUserDataA == m_Characters[i]->GetFootSensor() || fixtureUserDataB == m_Characters[i]->GetFootSensor())
                {
                    m_Characters[i]->DecrementFootCount();
                }
            }

            for (int i{ 0 }; i < m_Enemies.size(); ++i)
            {
                if (m_Enemies[i] == nullptr)
                    continue;
               
                if (fixtureUserDataA == m_Enemies[i]->GetFootSensor() || fixtureUserDataB == m_Enemies[i]->GetFootSensor())
                {
                    m_Enemies[i]->DecrementFootCount();
                }
    
            }


        }
         void AddCharacter(Character * character) { m_Characters.push_back(character); }
        
         void AddEnemy(Enemy* e) { m_Enemies.push_back(e); }
         void RemoveEnemy(Enemy* e)
         {
            
             auto it = std::find(m_Enemies.begin(), m_Enemies.end(), e);
             *it = nullptr;
         }
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
                if (m_Enemies[i] == nullptr)
                    continue;
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

            if (fixtureA->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BUBBLE && fixtureB->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BUBBLE)
                return;

            Bubble* bubble{};

           if(fixtureA->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BUBBLE)
               bubble = reinterpret_cast<Bubble*>(fixtureB->GetBody()->GetUserData());
           else
               bubble = reinterpret_cast<Bubble*>(fixtureA->GetBody()->GetUserData());
            
           if (bubble == nullptr)
               return;
           else
           {
               if (fixtureB->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BUBBLE)
               {
                   for (int i{ 0 }; i < m_Characters.size(); ++i)
                   {
                       if (fixtureB == m_Characters[i]->GetBody())
                       {
                           bubble->Hit();
                           for (int j{ 0 }; j < m_Enemies.size(); ++j)
                           {
                               if (m_Enemies[j]->GetState() == Enemy::State::InBubble)
                                   m_Enemies[j]->Kill();
                           }
                       }
                           
                   }
                   for (int i{ 0 }; i < m_Enemies.size(); ++i)
                   {

                       if (fixtureB->GetUserData() == m_Enemies[i])
                           m_Enemies[i]->HitByBubble(bubble->GetTransform()->GetPosition(), bubble->GetSpeed(), bubble->GetLifeTime() - bubble->GetTimer());

                   }

                   
               }
               else
               {
                   for (int i{ 0 }; i < m_Characters.size(); ++i)
                   {

                       if (fixtureA->GetFilterData().categoryBits == m_Characters[i]->GetBody()->GetFilterData().categoryBits)
                       {
                           bubble->Hit();
                           for (int j{ 0 }; j < m_Enemies.size(); ++j)
                           {
                               if (m_Enemies[j]->GetState() == Enemy::State::InBubble)
                                   m_Enemies[j]->Kill();
                           }
                       }
                   }
                   for (int i{ 0 }; i < m_Enemies.size(); ++i)
                   {
                      
                       if (fixtureA->GetUserData() == m_Enemies[i])
                           m_Enemies[i]->HitByBubble(bubble->GetTransform()->GetPosition(), bubble->GetSpeed(),bubble->GetLifeTime() - bubble->GetTimer());

                   }
               }
           }
        }
        void EnemyHitWall(b2Contact* contact) 
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();
            for (int i{ 0 }; i < m_Enemies.size(); ++i)
            {
                if (m_Enemies[i] == nullptr)
                    continue;
                if ((fixtureA == m_Enemies[i]->GetRigidBodyFixture() && fixtureB->GetFilterData().categoryBits == LVB::BubbleBobbleScene::BOUNDARY) || (fixtureB == m_Enemies[i]->GetRigidBodyFixture() && fixtureA->GetFilterData().categoryBits == LVB::BubbleBobbleScene::BOUNDARY))
                    m_Enemies[i]->HitWall();
            }
        }
        void EnemyHitPlayer(b2Contact* contact)
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();

            for (int i{ 0 }; i < m_Enemies.size(); ++i)
            {
                if (m_Enemies[i] == nullptr)
                    continue;
                for (int j{ 0 }; j < m_Characters.size(); ++j)
                {
                    if ((fixtureA == m_Enemies[i]->GetRigidBodyFixture() && fixtureB == m_Characters[j]->GetBody()) || (fixtureB == m_Enemies[i]->GetRigidBodyFixture() && fixtureA == m_Characters[j]->GetBody()))
                    {
                        m_Characters[j]->TakeDamage();
                    }
                }
            }
        }
        void PlayerHitPickUp(b2Contact* contact)
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();

            if (fixtureA->GetFilterData().categoryBits != LVB::BubbleBobbleScene::PICKUP && fixtureB->GetFilterData().categoryBits != LVB::BubbleBobbleScene::PICKUP)
                return;

            PickUp* pickUp{};
            if (fixtureA->GetFilterData().categoryBits != LVB::BubbleBobbleScene::PICKUP)
                pickUp = reinterpret_cast<PickUp*>(fixtureB->GetBody()->GetUserData());
            else
                pickUp = reinterpret_cast<PickUp*>(fixtureA->GetBody()->GetUserData());

            if (pickUp == nullptr)
                return;

            if (fixtureA->GetFilterData().categoryBits == LVB::BubbleBobbleScene::PICKUP)
            {
                for (int i{ 0 }; i < m_Characters.size(); ++i)
                {
                    if (fixtureB == m_Characters[i]->GetBody())
                        pickUp->PickedUp(m_Characters[i]);
                }
            }
            else
            {
                for (int i{ 0 }; i < m_Characters.size(); ++i)
                {
                    if (fixtureA == m_Characters[i]->GetBody())
                        pickUp->PickedUp(m_Characters[i]);
                }
            }
        }
        void BoulderHitPlayer(b2Contact* contact)
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();

            if (fixtureA->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BOULDER && fixtureB->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BOULDER)
                return;

            Boulder* boulder{};
            if (fixtureA->GetFilterData().categoryBits != LVB::BubbleBobbleScene::BOULDER)
                boulder = reinterpret_cast<Boulder*>(fixtureB->GetBody()->GetUserData());
            else
                boulder = reinterpret_cast<Boulder*>(fixtureA->GetBody()->GetUserData());

            if (boulder == nullptr)
                return;

            if (fixtureA->GetFilterData().categoryBits == LVB::BubbleBobbleScene::BOULDER)
            {
                for (int i{ 0 }; i < m_Characters.size(); ++i)
                {
                    if (fixtureB == m_Characters[i]->GetBody())
                        boulder->Hit(m_Characters[i]);
                }
            }
            else
            {
                for (int i{ 0 }; i < m_Characters.size(); ++i)
                {
                    if (fixtureA == m_Characters[i]->GetBody())
                        boulder->Hit(m_Characters[i]);
                }
            }
        }
	};
}