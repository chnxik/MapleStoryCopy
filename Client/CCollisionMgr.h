#pragma once

class CCollider;

union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};

	UINT_PTR id;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	WORD					m_matrix[(UINT)LAYER::END];
	map<UINT_PTR, bool>		m_mapPrevInfo;			// 이전 프레임에 두 충돌체의 충돌여부
	map<UINT_PTR, bool>     m_mapMntrn;		// 이전 프레임에 라인과의 충돌 여부

public:
	void LayerCheck(LAYER _left, LAYER _right);
	void CollisionClear(LAYER _LAYER);

	void Clear()				// 레벨 전환 시 CollisionMgr에 저장되어있는 레이어충돌 매트릭스를 0으로 초기화한다.
	{
		for (int i = 0; i < (UINT)LAYER::END; ++i)
		{
			m_matrix[i] = 0;
		}
	}

public:
	void tick();


private:
	void CollisionBtwLayer(LAYER _left, LAYER _right);
	bool CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight);
	

private:
	bool CheckMntrnTrgt(float _Tg, float _Pl)
	{
		if (_Pl > _Tg && _Tg > _Pl - 10)
			return true;

		return false;
	}

	bool CheckLineCollision(float _Tg, float _Pl)
	{
		if (_Pl + 10 > _Tg && _Tg >= _Pl - 3)
			return true;

		return false;
	}
};

