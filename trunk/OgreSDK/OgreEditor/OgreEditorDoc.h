
// OgreEditorDoc.h : COgreEditorDoc ��Ľӿ�
//


#pragma once


class COgreEditorDoc : public CDocument
{
protected: // �������л�����
	COgreEditorDoc();
	DECLARE_DYNCREATE(COgreEditorDoc)

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
	virtual ~COgreEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


