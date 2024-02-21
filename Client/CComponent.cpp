#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(CActor* _pOwner)
	: m_pOwner(_pOwner)
{
}

CComponent::~CComponent()
{
}
