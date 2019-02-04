#include "sdlgameobject.h"
#include "texturemanager.h"
#include "Game.h"  //如果放在sdlgameobject.h将会形成闭合环状！！

//CSDLGameObject::CSDLGameObject(const CLoaderParams* pParams) : CGameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0,0)
//{
//	m_width = pParams->getWidth();
//	m_height = pParams->getHeight();
//
//	m_textureID = pParams->getTextureID();
//
//	m_currentRow = 1;
//	m_currentFrame = 1;
//}

CSDLGameObject::CSDLGameObject() : CGameObject()
//,m_bulletFiringSpeed(0),
//m_bulletCounter(0),
//m_moveSpeed(0),
//m_dyingTime(0),
//m_dyingCounter(0),
//m_bPlayedDeathSound(false)
{

}

//void CSDLGameObject::load(const CLoaderParams *pParams)
void CSDLGameObject::load(std::unique_ptr<CLoaderParams> const &pParams)
{
	m_position = Vector2D((float)pParams->getX(), (float)pParams->getY());

	//m_velocity = Vector2D(0, 0);   
	//clw note
    //m_acceleration = Vector2D(0, 0);

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumFrames(); //应该有
}

void CSDLGameObject::update()
{
	//m_position += m_velocity;
}

void CSDLGameObject::draw()
{
	CTextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, CGame::Instance()->GetRenderer());
}

void CSDLGameObject::clean()
{

}

