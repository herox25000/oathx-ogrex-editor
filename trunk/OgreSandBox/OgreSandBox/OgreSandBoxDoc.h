
// OgreSandBoxDoc.h : COgreSandBoxDoc ��Ľӿ�
//


#pragma once


class COgreSandBoxDoc : public CDocument
{
protected: // �������л�����
	COgreSandBoxDoc();
	DECLARE_DYNCREATE(COgreSandBoxDoc)

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
	virtual ~COgreSandBoxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


