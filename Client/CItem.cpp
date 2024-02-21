#include "pch.h"
#include "CItem.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"


CItem::CItem()
	: m_eItemtype(ITEM_TYPE::END)
	, m_pItemTex(nullptr)
	, m_pUseSound(nullptr)
	, m_iQuantity(1)
{
}

CItem::~CItem()
{
}

void CItem::tick()
{
	CActor::tick();
}