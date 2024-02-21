#include "pch.h"
#include "CLogoLevel.h"

#include "CEngine.h"

#include "CBackgrnd.h"
#include "CTitle.h"

CLogoLevel::CLogoLevel()
{
}

CLogoLevel::~CLogoLevel()
{
}

void CLogoLevel::init()
{
	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos /= 2.f;
	vPos -= Vec2(456 / 2.f,285.f - 285.f/3.f);

	CTitle* m_Logo = new CTitle;
	m_Logo->SetPos(vPos);
	Instantiate(m_Logo, LAYER::BACKGROUND);
}

void CLogoLevel::Enter(UINT _iPortalNo)
{
	init();
}

void CLogoLevel::Exit()
{
	DeleteAllActor();
}

void CLogoLevel::CreateUI()
{
}
