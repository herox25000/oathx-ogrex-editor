
// EditorDoc.h : CEditorDoc ��Ľӿ�
//


#pragma once


class CEditorDoc : public CDocument
{
protected: // �������л�����
	CEditorDoc();
	DECLARE_DYNCREATE(CEditorDoc)

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
	virtual ~CEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


