#include "pch.h"
#include "CWall.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"

CWall::CWall()
	: m_bOnlyMob(false)
	, m_eWallDir(eDir::NONE)
{
	SetName(L"Wall");
}

CWall::~CWall()
{
}

void CWall::tick()
{

	CActor::tick();
}

void CWall::render(HDC _dc)
{
	if (CDebug::GetInst()->IsDebugOn())
	{
		// 충돌라인을 그린다.
		// 필요한 펜을 가져온다.
		HPEN hPen = nullptr;

		if (!GetCollider())
		{
			hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_BLUE);
		}
		else
		{
			if (0 < GetCollider()->GetOverlapCount())
			{
				hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_RED);
			}
			else
			{
				hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_BLUE);
			}
		}

		// DC 의 기존 펜을 새로 가져온 것들로 대체한다
		HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);

		Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(GetLdot());
		Vec2 vPos2 = CCamera::GetInst()->GetRenderPos(GetRdot());

		MoveToEx(_dc, (int)vPos1.x, (int)vPos1.y, NULL);
		LineTo(_dc, (int)vPos2.x, (int)vPos2.y);

		switch (m_eWallDir)
		{
		case eDir::LEFT:
		{
			MoveToEx(_dc, (int)vPos1.x, (int)(vPos1.y + GetScale().y / 2.f), NULL);
			LineTo(_dc, (int)(vPos2.x + 15.f), (int)(vPos1.y + GetScale().y / 2.f));
		}
		break;
		case eDir::RIGHT:
		{
			MoveToEx(_dc, (int)vPos1.x, (int)(vPos1.y + GetScale().y / 2.f), NULL);
			LineTo(_dc, (int)(vPos2.x - 15.f), (int)(vPos1.y + GetScale().y / 2.f));
		}
		break;
		}

		// DC 의 GDI 오브젝트들을 기존의 펜으로 되돌린다.
		SelectObject(_dc, hOriginPen);

		if (CDebug::GetInst()->IsDebugTextOn())
		{
			RECT rt = { (LONG)(vPos1.x),
						(LONG)(vPos1.y - 15),
						(LONG)(vPos1.x + 100),
						(LONG)(vPos1.y + 50) };	// 문자가 써질 사각형

			wchar_t szBuff[256] = {};
			swprintf_s(szBuff, L"%s", GetName().c_str());

			SetBkMode(_dc, OPAQUE);				// 문자 배경 투명 설정
			DrawText(_dc, szBuff, -1, &rt, DT_LEFT);	// 문자 출력
		}
	}
}

void CWall::SetLineInfo()
{
	Vec2 Ld = GetLdot();
	Vec2 Rd = GetRdot();

	float _yScale = (Ld.y >= Rd.y) ? fabsf(Ld.y - Rd.y) : fabsf(Rd.y - Ld.y);
	float _yPos = (Ld.y >= Rd.y) ? (Rd.y + _yScale /2.f) : (Ld.y + _yScale / 2.f);

	SetScale(Vec2(5.f, _yScale));
	SetPos(Vec2(Ld.x, _yPos));
}


void CWall::BeginOverlap(CCollider* _pOther)
{
}

void CWall::OnOverlap(CCollider* _pOther)
{
	// 부딪혔을때 Velocity가 -면  오른쪽좌표로, + 면 왼쪽좌표로 벽 x좌표 에 scale.x / 2.f 만큼 x좌표지정.
	Vec2 vVelocity = _pOther->GetOwner()->GetRigidbody()->GetVelocity();
	Vec2 vOtherGrndPt = _pOther->GetGrndPt();
	Vec2 vWallGrndPt = GetCollider()->GetGrndPt();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (pPlayer)
	{
		if (m_bOnlyMob)
			return;
	}

	switch (m_eWallDir)
	{
	case eDir::LEFT:
	{
		if (0 > vVelocity.x && CheckCollisionWall(vOtherGrndPt)) // 왼쪽 벽
		{
			_pOther->GetOwner()->GetRigidbody()->SetVelocity(Vec2(0.f, vVelocity.y));
			_pOther->GetOwner()->SetPos(Vec2(GetPos().x + _pOther->GetScale().x / 2.f + GetScale().x / 2.f , _pOther->GetOwner()->GetPos().y));
		}
	}
	break;
	case eDir::RIGHT:
	{
		if (0 < vVelocity.x && CheckCollisionWall(vOtherGrndPt)) // 오른쪽 벽
		{
			_pOther->GetOwner()->GetRigidbody()->SetVelocity(Vec2(0.f, vVelocity.y));
			_pOther->GetOwner()->SetPos(Vec2(GetPos().x - _pOther->GetScale().x / 2.f - GetScale().x / 2.f , _pOther->GetOwner()->GetPos().y));
		}
	}
	break;
	}
}

void CWall::EndOverlap(CCollider* _pOther)
{
}

bool CWall::CheckCollisionWall(Vec2 _OtherPos)
{
	Vec2 vOtherPos = _OtherPos;

	Vec2 vWallPos = GetPos();
	Vec2 vWallScale = GetScale();

	if ((vOtherPos.y < (vWallPos.y + vWallScale.y) ||
		(vOtherPos.y > vWallPos.y)) &&
		(vOtherPos.x > (vWallPos.x - vWallScale.x / 2.f) ||
		vOtherPos.x < (vWallPos.x + vWallScale.x / 2.f)))
		return true;

	return false;
}
