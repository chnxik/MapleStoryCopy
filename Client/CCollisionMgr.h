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
	map<UINT_PTR, bool>		m_mapPrevInfo;			// ���� �����ӿ� �� �浹ü�� �浹����
	map<UINT_PTR, bool>     m_mapMntrn;		// ���� �����ӿ� ���ΰ��� �浹 ����

public:
	void LayerCheck(LAYER _left, LAYER _right);
	void CollisionClear(LAYER _LAYER);

	void Clear()				// ���� ��ȯ �� CollisionMgr�� ����Ǿ��ִ� ���̾��浹 ��Ʈ������ 0���� �ʱ�ȭ�Ѵ�.
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

