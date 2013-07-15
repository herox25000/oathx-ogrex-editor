// STLMap.h: interface for the CSTLMap class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _STL_MAP
#define _STL_MAP

#pragma warning(disable : 4786)

#include <map>
#include <string>
using namespace std;

//mapģ��
template <class T1,class T2> class CSTLMap  
{
public:
	typedef typename map < T1, T2* >::iterator		Iterator; //ֵ���Ͷ���
	typedef typename map < T1, T2* >::value_type	ValueType; //ֵ����

	map < T1, T2* >		m_UserTypeMap; //����
	
	int GetSize() { return (int)m_UserTypeMap.size(); }; //�õ���С
	
	bool PutData( T1 key_value, T2* pData) //ѹ������
	//Iterator PutData( T1 key_value, T2* pData)
	{
		if( !pData ) return false;
		pair<Iterator, bool> temp_pair = m_UserTypeMap.insert( ValueType( key_value, pData ) );
		//Iterator temp_pair = m_UserTypeMap.insert( m_UserTypeMap.end(),  ValueType( key_value, pData ) );
		return temp_pair.second;
		//return temp_pair;
	};

	T2* GetData( T1 key_value ) //ȡ����
	{
		T2* pData = NULL;
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return NULL;
		else
			pData = (*iter).second;
		
		return pData;
	};

	T2* GetIData( T1 key_value ) //ȡֵ����
	{
		T2* pData = NULL;
		Iterator iter = m_UserTypeMap.begin();
		for( ; iter != m_UserTypeMap.end(); iter++ )
		{
			if( !stricmp( key_value.data(), (*iter).first.data()) )
			{
				pData = (*iter).second;
				break;
			}
		}
		return pData;
	};

	Iterator DeleteData( T1 key_value ) //ɾ������
	{
		if( m_UserTypeMap.empty() )
			return m_UserTypeMap.end();
		
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return m_UserTypeMap.end();
		else {
			T2* pData = NULL;
			pData = (*iter).second;

			iter = m_UserTypeMap.erase(iter);

			delete pData;
			pData = NULL;

			return iter;
		}
	};

	Iterator PopData( T1 key_value ) //ѹ�����ݣ���ɾ��
	{
		if( m_UserTypeMap.empty() )
			return m_UserTypeMap.end();
		
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return m_UserTypeMap.end();
		else {
			iter = m_UserTypeMap.erase(iter);
			return iter;
		}
	};

	void DeleteAllData() //ɾ����������
	{
		Iterator iter1 = m_UserTypeMap.begin(), iter2 = m_UserTypeMap.end();
		for(; iter1 != iter2; iter1++ )
			delete (*iter1).second;

		m_UserTypeMap.clear();
	};

	void Clear() //��գ�����ɾ��
	{
        m_UserTypeMap.clear();
	};

	bool IsExist( T1 key_value ) //�ж��Ƿ��д�����
	{
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return false;
		else
			return true;
	};

	bool IsEmpty() { return m_UserTypeMap.empty(); }; //�Ƿ�Ϊ��

	CSTLMap() { };
	virtual ~CSTLMap() {
		DeleteAllData();
	};
};

#endif