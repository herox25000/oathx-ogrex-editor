
// XavierDoc.h : CXavierDoc ��Ľӿ�
//


#pragma once


class CXavierDoc : public CDocument
{
protected: // �������л�����
	CXavierDoc();
	DECLARE_DYNCREATE(CXavierDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CXavierDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


