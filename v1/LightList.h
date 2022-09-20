/**
This code is (c) 2006 of Riccardo Trocca  rtrocca@gmail.com
Use it at your own risk.
You are free to use it as you wish with no particular bounds.
I'd be really grateful if you can share bug-fixes and enhancements.
**/
#ifndef __LIGHT_LIST_H__
#define __LIGHT_LIST_H__

struct __LIGHTPOS { };
typedef __LIGHTPOS* LIGHTPOS;

template <class T> class CLightList
{
	struct CLightNode
	{
		CLightNode* pNext;
		CLightNode* pPrev;
		T* data;
	};
	public:
		CLightList(bool bSelfDestroy = true)
		{
			m_pRoot = NULL;
			m_pLast = NULL;
			m_nCount = 0;
			m_bSelfDestroy = bSelfDestroy;
		}
		~CLightList()
		{
			RemoveAll();
		}
		void SetSelfDestroy(bool bSelfDestroy)
		{
			m_bSelfDestroy = bSelfDestroy;
		}
		void RemoveAll()
		{
			CLightNode *pCur;
			CLightNode *pDel;
			pCur = m_pLast;
			pDel = m_pLast;
			while (pDel)
			{
				pCur = pDel->pPrev;
				if (m_bSelfDestroy)
					delete pDel->data;
				delete pDel;
				pDel = pCur;
			}
			m_pRoot = NULL;
			m_pLast = NULL;
			m_nCount = 0;
		}
		bool IsEmpty() {return m_nCount == 0;}
		int GetCount() {return m_nCount;}
		T *GetHead()
		{
			return m_pRoot->data;
		}
		LIGHTPOS GetHeadPos()
		{
			return (LIGHTPOS) m_pRoot;
		}
		LIGHTPOS GetTailPos()
		{
			return (LIGHTPOS) m_pLast;
		}
		T* GetPrev(LIGHTPOS &pos) const
		{
			CLightNode* pNode = (CLightNode*) pos;
			pos = (LIGHTPOS) pNode->pPrev;
			return pNode->data;
		}
		T* GetNext(LIGHTPOS &pos) const
		{
			CLightNode* pNode = (CLightNode*) pos;
			pos = (LIGHTPOS) pNode->pNext;
			return pNode->data;
		}

		T* GetAt(LIGHTPOS pos) const
		{
			CLightNode* pNode = (CLightNode*) pos;
			return pNode->data;
		}
		T* RemoveTail()
		{
			if (m_pLast)
			{
				T* pData = m_pLast->data;
				CLightNode* pNode = m_pLast->pPrev;
				delete m_pLast;
				m_pLast = NULL;
				m_nCount--;
				if (pNode)
				{
					pNode->pNext = NULL;
					m_pLast = pNode;
				}
				else
				{
					//empty list (now)
					m_pRoot = m_pLast;
				}

				return pData;
			}
			return NULL;
		}

		LIGHTPOS FindIndex(int nIndex) const
		{
			if (nIndex >= m_nCount || nIndex < 0)
				return NULL;  // went too far

			CLightNode* pNode = m_pRoot;
			while (nIndex--)
				pNode = pNode->pNext;

			return (LIGHTPOS) pNode;
		}
		LIGHTPOS FindElement(T* el) {

			CLightNode *it = m_pRoot;
			while(it) {
				if (it->data == el) return 	(LIGHTPOS) it;
				it = it->pNext;
			}
			return NULL;
		}


//		bool EndReached()
//		{
//			return (m_pIterator==NULL);
//		}
		void AddElement(T *pEl)
		{
			CLightNode *pNewEl = new CLightNode();
			pNewEl->data = pEl;
			m_nCount++;
			if (m_pRoot ==  NULL)
			{
				m_pRoot = pNewEl;
				m_pLast = pNewEl;
				pNewEl->pPrev = NULL;
				pNewEl->pNext = NULL;

			}
			else
			{
				pNewEl->pPrev = m_pLast;
				pNewEl->pNext = NULL;
				m_pLast->pNext = pNewEl;
				m_pLast = pNewEl;
			}
		}

		T* RemoveElement(LIGHTPOS &pos) {

			CLightNode* pNode = (CLightNode*) pos;
			T* data = pNode->data;
			CLightNode *pNextNode = pNode->pNext;
			CLightNode *pPrevNode = pNode->pPrev;
			if (pPrevNode) pPrevNode->pNext = pNode->pNext;
			if (pNextNode) pNextNode->pPrev = pNode->pPrev;
			if (m_pLast == pNode) m_pLast = pPrevNode;
      if (m_pRoot == pNode) m_pRoot = pNextNode;
      delete pNode;
      m_nCount--;

			return data;
		}

private:
	CLightNode *m_pRoot;
	CLightNode *m_pLast;
	bool m_bSelfDestroy;
	int m_nCount;
};
#endif
