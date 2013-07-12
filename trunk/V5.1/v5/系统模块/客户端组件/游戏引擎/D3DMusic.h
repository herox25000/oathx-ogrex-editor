#pragma once

#include "GameEngineHead.h"
#include "DirectShowBasic.h"


// ��������
typedef map< UINT_PTR ,CDXGraph* >				mapDXGraph;
class CMapDXGraph
{
protected:
	mapDXGraph									m_mapDXGraph;

public:
	CMapDXGraph(){}
	~CMapDXGraph(){}

public:
	mapDXGraph*	GetObject() { return &m_mapDXGraph; }
};

typedef map< UINT_PTR ,CGraphBuilderCB* >		mapGraphBuilderCB;
class CMapGraphBuilderCB
{
protected:
	mapGraphBuilderCB							m_mapGraphBuilderCB;

public:
	CMapGraphBuilderCB(){}
	~CMapGraphBuilderCB(){}

public:
	mapGraphBuilderCB*	GetObject() { return &m_mapGraphBuilderCB; }
};

typedef map< UINT_PTR ,CString >				mapKeyName;
class CMapKeyName
{
protected:
	mapKeyName									m_mapKeyName;

public:
	CMapKeyName(){}
	~CMapKeyName(){}

public:
	mapKeyName*	GetObject() { return &m_mapKeyName; }
};

// �����б�
typedef vector<CDXGraph*>						verGraph;
class CVerGraph
{
protected:
	verGraph									m_verGraph;

public:
	CVerGraph(){}
	~CVerGraph(){}

public:
	verGraph*	GetObject() { return &m_verGraph; }
};

typedef vector<CGraphBuilderCB*>				verGraphBuilderCB;
class CVerGraphBuilderCB
{
protected:
	verGraphBuilderCB							m_verGraphBuilderCB;

public:
	CVerGraphBuilderCB(){}
	~CVerGraphBuilderCB(){}

public:
	verGraphBuilderCB*	GetObject() { return &m_verGraphBuilderCB; }
};

//������
class GAME_ENGINE_CLASS CD3DMusic
{
	//ȫ��
private:
	static CD3DMusic*		pObject;						//����ָ��

	// ��������
private:
	bool						m_bBackTime;					//��������
	
	//------------------------------------------
	// ��������
private:
	CMapDXGraph*				m_mapDXGraph;
	CMapGraphBuilderCB*			m_mapGraphBuilderCB;
	CMapKeyName*				m_mapKeyName;


	//----------------------------------------------------------
	//�����б�
private:
	CVerGraph*					m_verBackGraph;
	CVerGraphBuilderCB*			m_verBackBuilder;
	bool						m_bPause;
	UINT_PTR					m_idEvent;
	UINT_PTR					m_iBackID;
	UINT_PTR					m_iBackMaxID;

private:
	CD3DMusic(void);
	~CD3DMusic(void);

	// ������
public:
	// ���ض���
	inline static CD3DMusic* _Object()
	{
		if ( pObject == NULL )
		{
			pObject = new CD3DMusic;
		}
		return pObject;
	}
	//ɾ������
	static void Delete()
	{
		if ( pObject != NULL )
		{
			delete pObject;
			pObject = NULL;
		}
	}

	// �ڲ�����
private:
	// ��ȡ·��
	CString			GetAppPath();
	// ע���ļ�
	BOOL			RegisterFilter(LPCTSTR  inFilterAx);
	// ɾ������
	void			mapErase(UINT idEvent);
	// ɾ������
	void			mapErase();
	// �������Żص�
	static void		CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );
	// �������Żص�
	static void		CALLBACK ListTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );

	// ���ź���
public:
	//------------------------------------------
	// ��������

	//************************************
	// Method:    ��������
	// FullName:  CD3DMusic::Start
	// Access:    public 
	// Returns:   bool
	// Parameter: LPCTSTR  filename	�ļ��� (���������Լ�����)
	//************************************
	bool Start(LPCTSTR filename);

	//************************************
	// Method:    ��ͣ����
	// FullName:  CD3DMusic::Pause
	// Access:    public 
	// Returns:   bool
	// Parameter: LPCTSTR  filename	�ļ��� (���ΪNULL ��ȫ����ͣ)
	//************************************
	bool Pause(LPCTSTR filename  = NULL);

	//************************************
	// Method:    ��������(��Ҫ�ȵ���Start�����Ժ����ʹ�� ������ͣ��ֹͣ������)
	// FullName:  CD3DMusic::Run
	// Access:    public 
	// Returns:   bool
	// Parameter: LPCTSTR  filename	�ļ��� (���ΪNULL ��ȫ��ֹͣ����ͣ����������)
	//************************************
	bool Run(LPCTSTR filename  = NULL);

	//************************************
	// Method:    ֹͣ����(ֹͣ�Լ��Ѵ���������ɾ��,��Ҫ�ٲ�������Ҫ����Start���벥��)
	// FullName:  CD3DMusic::Stop
	// Access:    public 
	// Returns:   bool
	// Parameter: LPCTSTR  filename �ļ��� (���ΪNULL ��ȫ��ֹͣ)
	//************************************
	bool Stop(LPCTSTR filename  = NULL);

	//************************************
	// Method:    ����������С
	// FullName:  CD3DMusic::ControlVolume
	// Access:    public 
	// Returns:   void
	// Parameter: int ibulk			������С(-10000 ~ 0)0���
	//************************************
	void ControlVolume(int ibulk);



	//----------------------------------------------------------
	//�����б�

	//************************************
	// Method:    �����Ŀ
	// FullName:  CD3DMusic::ListAdd
	// Access:    public 
	// Returns:   void
	// Parameter: LPCTSTR  filename  �ļ���
	//************************************
	void ListAdd(LPCTSTR filename);


	//************************************
	// Method:    ��ʼ��������
	// FullName:  CD3DMusic::Back_Start
	// Access:    public 
	// Returns:   void
	//************************************
	void ListStart();


	//************************************
	// Method:    ������б�������
	// FullName:  CD3DMusic::ListClear
	// Access:    public 
	// Returns:   void
	//************************************
	void ListClear();

	//************************************
	// Method:    ���ű�������(�ڱ�ֹͣ����ͣ��ʱ����ò���)
	// FullName:  CD3DMusic::ListRun
	// Access:    public 
	// Returns:   void
	//************************************
	void ListRun();


	//************************************
	// Method:    ��ͣ��������(ֻ�ܱ�Back_Run()��������)
	// FullName:  CD3DMusic::ListPause
	// Access:    public 
	// Returns:   void
	//************************************
	void ListPause();

	//************************************
	// Method:    ֹͣ��������(ֻ�ǰ�������0,������Back_Run()�ٴβ���)
	// FullName:  CD3DMusic::ListStop
	// Access:    public 
	// Returns:   void
	//************************************
	void ListStop();


	//************************************
	// Method:    ���Ʊ���������С
	// FullName:  CD3DMusic::ListVolume
	// Access:    public 
	// Returns:   void
	// Parameter: int ibulk			������С(-10000 ~ 0)0���
	//************************************
	void ListVolume(int ibulk);

};
