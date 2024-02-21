#include "pch.h"
#include "CLadder.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidbody.h"

#include "CEngine.h"
#include "CPlayer.h"
#include "CPlayerState.h"


CLadder::CLadder()
{
	SetName(L"ladder");
}

CLadder::~CLadder()
{
}

void CLadder::tick()
{

	CActor::tick();
}

void CLadder::render(HDC _dc)
{
	if (CDebug::GetInst()->IsDebugOn())
	{
		// �浹������ �׸���.
		// �ʿ��� ���� �����´�.
		HPEN hPen = nullptr;

		if (!GetCollider())
		{
			hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_PURPLE);
		}
		else
		{
			if (0 < GetCollider()->GetOverlapCount())
			{
				hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_RED);
			}
			else
			{
				hPen = CEngine::GetInst()->GetPen(PEN_TYPE::BOLD_PURPLE);
			}
		}


		// DC �� ���� ���� ���� ������ �͵�� ��ü�Ѵ�
		HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);

		Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(GetLdot());
		Vec2 vPos2 = CCamera::GetInst()->GetRenderPos(GetRdot());

		MoveToEx(_dc, (int)vPos1.x, (int)vPos1.y, NULL);
		LineTo(_dc, (int)vPos2.x, (int)vPos2.y);

		// DC �� GDI ������Ʈ���� ������ ������ �ǵ�����.
		SelectObject(_dc, hOriginPen);

		if (CDebug::GetInst()->IsDebugTextOn())
		{
			RECT rt = { (LONG)(vPos1.x),
						(LONG)(vPos1.y - 15),
						(LONG)(vPos1.x + 100),
						(LONG)(vPos1.y + 50)};	// ���ڰ� ���� �簢��

			wchar_t szBuff[256] = {};
			swprintf_s(szBuff, L"%s", GetName().c_str());

			SetBkMode(_dc, OPAQUE);				// ���� ��� ���� ����
			DrawText(_dc, szBuff, -1, &rt, DT_LEFT);	// ���� ���
		}
	}
}

void CLadder::SetLineInfo()
{
	Vec2 Ld = GetLdot();
	Vec2 Rd = GetRdot();

	float _yScale = (Ld.y >= Rd.y) ? fabsf(Ld.y - Rd.y) : fabsf(Rd.y - Ld.y);
	float _yPos = (Ld.y >= Rd.y) ? (Rd.y + _yScale / 2.f) : (Ld.y + _yScale / 2.f);

	SetScale(Vec2(2.f, _yScale));
	SetPos(Vec2(Ld.x, _yPos));
}

void CLadder::BeginOverlap(CCollider* _pOther)
{
}

void CLadder::OnOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (pPlayer)
	{
		if (pPlayer->GetLiftObj() == nullptr)
		{
			if (ISHOLD(KEY::UP) && (_pOther->GetGrndPt().y >= GetLdot().y + 20.f))
			{
				pPlayer->SetLiftObj(this);
				pPlayer->ChangeState(CHANGESTATE(CPlayerState)::ladder);
				pPlayer->SetPos(Vec2(GetCenterx(), pPlayer->GetPos().y));
			}
			if (ISHOLD(KEY::DOWN) && (_pOther->GetGrndPt().y < GetLdot().y + 20.f))
			{
				pPlayer->SetLiftObj(this);
				pPlayer->ChangeState(CHANGESTATE(CPlayerState)::ladder);
				pPlayer->SetPos(Vec2(GetCenterx(), pPlayer->GetPos().y + 10.f));
			}
		}
	}
}

void CLadder::EndOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());

	if (pPlayer)
		pPlayer->SetLiftObj(nullptr);
}