#include "pch.h"
#include "CFiledItem.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CItem.h"
#include "CTexture.h"
#include "CSound.h"

#include "CCollider.h"
#include "CRigidbody.h"

CFiledItem::CFiledItem(CItem* pItem)
	: m_pItem(pItem)
	, m_pTex(nullptr)
	, m_fAcc(0.f)
	, m_fMaxFiledTime(10.f)
	, m_fDir(1.f)
	, m_fOffset(0.f)
	, m_fMaxOffset(8.f)
	, m_bGetable(true)
	, m_fRatio(1.f)
	, m_bGet(false)
{
}

CFiledItem::~CFiledItem()
{
	if (!m_bGet)
		DEL(m_pItem);
}

void CFiledItem::tick()
{
	m_fAcc += DT;

	if (m_bGetable)
	{
		m_fOffset += m_fDir * 13 * DT;
		if (fabsf(m_fOffset) > m_fMaxOffset)
		{
			m_fDir *= -1.f;
			m_fOffset +=  m_fDir * (fabsf(m_fOffset) - m_fMaxOffset);
		}
	}

	if (11.f < m_fAcc)
		SetDead();

	CActor::tick();
}

void CFiledItem::render(HDC _dc)
{

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	vPos -= Vec2(16, 20);
	
	vPos.y += m_fOffset;

	float Opacity = 100.f;

	if (10.f < m_fAcc)
	{
		m_bGetable = false;
		Opacity *= (11.f - m_fAcc);
	}

	OpRender(_dc, m_pTex, vPos, (int)Opacity);

	CActor::render(_dc);
}

void CFiledItem::SetItemInfo()
{
	m_pTex = m_pItem->GetItemTex();

	CreateCollider();
	CreateRigidbody();

	SetScale(Vec2(32, 32));
	GetCollider()->SetScale(Vec2(32, 32));
	GetRigidbody()->SetGravityAccel(1000.f);
}

void CFiledItem::DropItem()
{
	GetRigidbody()->SetGrnd(false);
	GetRigidbody()->SetVelocity(Vec2(0.f, -400.f));
}

CItem* CFiledItem::GetItem()
{
	m_bGet = true;
	m_bGetable = false;
	m_fAcc = 10.f;
	GetRigidbody()->SetGrnd(false);
	GetRigidbody()->SetVelocity(Vec2(0.f, -300.f));

	return m_pItem;
}

