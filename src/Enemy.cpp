#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>

Enemy::Enemy(Properties* props): Character(props)
{
    m_RigiBody = new RigidBody();
    m_RigiBody->SetGravity(6.5);
    m_Collider = new Collider();

    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("assets/animation.aml");
    m_Animation->SetCurrentSeq("boss_appear");
}

void Enemy::Draw()
{
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 1, 1, m_Flip);
}

void Enemy::Update(float dt)
{

    // X-Axis movements
    m_RigiBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigiBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 20);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;

    // Y-Axis movements
    m_RigiBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigiBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 20);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->Y = m_LastSafePosition.Y;

    m_Animation->Update(dt);

    if(m_Animation->IsEnded()){
        m_Animation->SetCurrentSeq("boss_idle");
        m_Animation->SetRepeat(true);
    }
}


void Enemy::Clean(){

}



