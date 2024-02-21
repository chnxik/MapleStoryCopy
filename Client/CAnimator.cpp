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

	// ���� �ִϸ��̼��� ���
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
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
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
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
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
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
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

	
	pAnim = new CAnimation(this);		// �ִϸ��̼� ��ü�� ������ ���������ش�.

	pAnim->init(CAnimationMgr::GetInst()->GetAniInfo(_strName));
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);	// ���� �ִϸ��̼� ��Ͽ��� �ִϸ��̼��̸����� Ž��

	if (iter == m_mapAnim.end())	// ���� ��� nullptr ��ȯ
		return nullptr;

	return iter->second;			// ������ �ִϸ��̼� ������ ��ȯ
}

void CAnimator::RePlay()
{
	if (nullptr == m_pCurAnim)
		return;

	m_pCurAnim->SetStop(false);
}