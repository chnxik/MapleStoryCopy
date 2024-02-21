#include "pch.h"
#include "CLine.h"

#include "CTimeMgr.h"
#include "CCamera.h"

#include "CCollider.h"
#include "CRigidbody.h"


#include "CEngine.h"


CLine::CLine()
	: m_Tool(TOOL_TYPE::NONE)
	, m_Line{}
{
}

CLine::~CLine()
{
}

void CLine::tick()
{
	CActor::tick();
}

void CLine::DrawCmplt()
{
	if (m_Line.Ldx > m_Line.Rdx)
	{
		short xtmp;
		short ytmp;

		xtmp = m_Line.Ldx;
		m_Line.Ldx = m_Line.Rdx;
		m_Line.Rdx = xtmp;

		ytmp = m_Line.Ldy;
		m_Line.Ldy = m_Line.Rdy;
		m_Line.Rdy = ytmp;
	}

	SetLineInfo();

	if (!GetCollider())
		CreateCollider();

	GetCollider()->SetScale(GetScale());
}

void CLine::SetLineInfo()
{
	Vec2 Ld = GetLdot();
	Vec2 Rd = GetRdot();

	float _yPos = (Ld.y >= Rd.y) ? Rd.y : Ld.y;
	float _yScale = (Ld.y >= Rd.y) ? fabsf(Ld.y - Rd.y) : fabsf(Rd.y - Ld.y);

	SetPos(CCamera::GetInst()->GetRealPos(Vec2(Ld.x + (Rd.x / 2), _yPos)));
	SetScale(Vec2(Rd.x - Ld.x, _yScale));
}

void CLine::BeginOverlap(CCollider* _pOther)
{
}

void CLine::OnOverlap(CCollider* _pOther)
{
}

void CLine::EndOverlap(CCollider* _pOther)
{
}