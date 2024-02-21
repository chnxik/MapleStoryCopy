#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CAnimationMgr.h"

CAnimator::CAnimator(CActor* _pOwner)
	: CComponent(_pOwner)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{

}

CAnimator::CAnimator(const CAnimator& _other)
	: CComponent(_other)
	, m_pCurAnim(_other.m_pCurAnim)
	, m_bRepeat(_other.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _other.m_mapAnim.begin();
	for (; iter != _other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->Reset();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	// 같은 애니메이션을 재생
	if (nullptr != m_pCurAnim)
	{
		Play(_other.m_pCurAnim->GetName(), m_bRepeat);
	}

}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		delete iter->second;
	}
}

void CAnimator::tick()
{
}

void CAnimator::final_tick()
{
	if (nullptr == m_pCurAnim)
		return;

	if (m_pCurAnim->GetName() == L"selectcell")
		int a = 0;

	if (m_pCurAnim->IsFinish() && m_bRepeat)
	{
		m_pCurAnim->Reset();
	}

	m_pCurAnim->tick();
}

void CAnimator::render(HDC _dc)
{
	if (nullptr == m_pCurAnim)
		return;

	m_pCurAnim->render(_dc);
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		ShowCursor(true);
		MessageBox(nullptr, L"해당 Animation 없음", L"Animation 재생 오류", MB_OK);
		ShowCursor(false);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset();
	m_pCurAnim->SetFlashing(false);
	m_pCurAnim->SetOpacity(100);
	m_bRepeat = _bRepeat;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat, UINT _iOpacity)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		ShowCursor(true);
		MessageBox(nullptr, L"해당 Animation 없음", L"Animation 재생 오류", MB_OK);
		ShowCursor(false);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset();
	m_pCurAnim->SetFlashing(false);
	m_pCurAnim->SetOpacity(_iOpacity);
	m_bRepeat = _bRepeat;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat, UINT _iOpacity, bool _bFlashing)
{
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		ShowCursor(true);
		MessageBox(nullptr, L"해당 Animation 없음", L"Animation 재생 오류", MB_OK);
		ShowCursor(false);
		return;
	}

	m_pCurAnim = pAnim;
	m_pCurAnim->Reset();
	m_pCurAnim->SetFlashing(true);
	m_pCurAnim->SetOpacityLimit(_iOpacity);
	m_pCurAnim->SetOpacity(100);
	m_bRepeat = _bRepeat;
}

void CAnimator::Stop()
{
	if (nullptr == m_pCurAnim)
		return;

	m_pCurAnim->SetStop(true);
}

void CAnimator::CreateAnimation(const wstring& _strName)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	
	pAnim = new CAnimation(this);		// 애니메이션 객체를 생성해 연결지어준다.

	pAnim->init(CAnimationMgr::GetInst()->GetAniInfo(_strName));
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);	// 보유 애니메이션 목록에서 애니메이션이름으로 탐색

	if (iter == m_mapAnim.end())	// 없을 경우 nullptr 반환
		return nullptr;

	return iter->second;			// 있으면 애니메이션 포인터 반환
}

void CAnimator::RePlay()
{
	if (nullptr == m_pCurAnim)
		return;

	m_pCurAnim->SetStop(false);
}