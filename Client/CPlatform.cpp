#include "pch.h"
#include "CPlatform.h"

#include "CEngine.h"

#include "CCollider.h"
#include "CRigidbody.h"

#include "CTimeMgr.h"

#include "CPlayer.h"



CPlatform::CPlatform()
	: _bEarth(false)
{
	SetName(L"Platform");
}

CPlatform::~CPlatform()
{
}

void CPlatform::tick()
{
	CActor::tick();
}

void CPlatform::render(HDC _dc)
{
	if (CDebug::GetInst()->IsDebugOn())
	{
		// 충돌라인을 그린다.
		// 필요한 펜을 가져온다.
		HPEN hPen = nullptr;

		if (!GetCollider())
		{
			hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_GREEN);
		}
		else
		{
			if (0 < GetCollider()->GetOverlapCount())
			{
				hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_RED);
			}
			else
			{
				hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_GREEN);
			}
		}

		// DC 의 기존 펜을 새로 가져온 것들로 대체한다
		HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);

		Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(GetLdot());
		Vec2 vPos2 = CCamera::GetInst()->GetRenderPos(GetRdot());

		MoveToEx(_dc, (int)vPos1.x, (int)vPos1.y, NULL);
		LineTo(_dc, (int)vPos2.x, (int)vPos2.y);

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

void CPlatform::BeginOverlap(CCollider* _pOther)
{
	_pOther->AddPlfCnt();
	if (!(_pOther->IsZeroPlfCnt()))
	{
		_pOther->GetOwner()->GetRigidbody()->SetGrnd(true);							// 땅 위에 있는 상태 설정
		_pOther->GetOwner()->GetRigidbody()->SetCurGrndDir(GetGradient());				// 현재 땅의 기울기 전달

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);
		if (pPlayer)
			pPlayer->SetPlatform(this);

		float fHeight = GetVerticalPos(_pOther->GetGrndPt()
			, GetLdot()
			, GetGradient()) - _pOther->GetOwner()->GetScale().y / 2.f - 2;

		Vec2 CurActPos = _pOther->GetOwner()->GetPos();

		_pOther->GetOwner()->SetPos(Vec2(_pOther->GetOwner()->GetPos().x, fHeight));

		CurActPos = _pOther->GetOwner()->GetPos();
	}
}

void CPlatform::OnOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());

	if (pPlayer)
	{
		if (pPlayer->GetLiftObj() != nullptr)
			return;
	}

	_pOther->GetOwner()->GetRigidbody()->SetCurGrndDir(GetGradient());
	float fHeight = GetVerticalPos(_pOther->GetGrndPt()
		, GetLdot()
		, GetGradient()) - _pOther->GetOwner()->GetScale().y / 2.f - 2;

	_pOther->GetOwner()->SetPos(Vec2(_pOther->GetOwner()->GetPos().x, fHeight));
}

void CPlatform::EndOverlap(CCollider* _pOther)
{
	_pOther->SubPlfCnt();
	if (_pOther->IsZeroPlfCnt())
	{
		_pOther->GetOwner()->GetRigidbody()->SetGrnd(false);
		_pOther->GetOwner()->GetRigidbody()->SetCurGrndDir(Vec2(1, 0));

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);
		if (pPlayer)
			pPlayer->SetPlatform(nullptr);
	}
}

void CPlatform::SetLineInfo()
{
	Vec2 Ld = GetLdot();
	Vec2 Rd = GetRdot();

	float _yScale = (Ld.y >= Rd.y) ? fabsf(Ld.y - Rd.y) : fabsf(Rd.y - Ld.y);
	float _yPos = (Ld.y >= Rd.y) ? (Rd.y + _yScale / 2.f) : (Ld.y + _yScale / 2.f);

	float _xScale = (Ld.x >= Rd.x) ? fabsf(Ld.x - Rd.x) : fabsf(Rd.x - Ld.x);
	float _xPos = (Ld.x >= Rd.x) ? (Rd.x + _xScale / 2.f) : (Ld.x + _xScale / 2.f);

	SetScale(Vec2(_xScale, _yScale));
	SetPos(Vec2(_xPos, _yPos));
}
