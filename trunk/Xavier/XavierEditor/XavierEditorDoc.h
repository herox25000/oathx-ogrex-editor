
// XavierEditorDoc.h : CXavierEditorDoc ��Ľӿ�
//


#pragma once


class CXavierEditorDoc : public CDocument
{
protected: // �������л�����
	CXavierEditorDoc();
	DECLARE_DYNCREATE(CXavierEditorDoc)

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
	virtual ~CXavierEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


