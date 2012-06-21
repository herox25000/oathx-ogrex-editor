#ifndef _____OgrePropertySet_H
#define _____OgrePropertySet_H

namespace Ogre
{
	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-03-13
	*
	* \Author  : lp
	*
	* \Desc    : 属性事件，当某属性改变时发送改事件
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API PropertyEventArgs : public EventArgs
	{
	public:
		/** 构造函数
		 *
		 * \param pProperty		触发该事件的属性对象
		 * \return 
		 */
		PropertyEventArgs(Property* pProperty)
			:pProperty(pProperty)
		{

		}

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~PropertyEventArgs()
		{

		}
		
		// 属性
		Property*					pProperty;
	};
	
	// 属性列表
	typedef HashMap<String, Property*>		HashProperty;
	typedef MapIterator<HashProperty>		HashPropertyIter;

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-12
	*
	* \Author  : lp
	*
	* \Desc    : 属性事件表
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API PropertySet : public EventSet
	{
	public:
		// Namespace for global events
		static const String			EventNamespace;
		// add property
		static const String			EventAddProperty;
		// change value
		static const String			EventValueChanged;
		// del property
		static const String			EventDelProperty;
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		PropertySet();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~PropertySet();

		/** 添加一个新的属性
		 *
		 * \param name			属性名称
		 * \param Value			属性变量值
		 * \param describe		属性描述
		 * \param typeProperty	属性类型
		 * \param bWrite		是否可写入
		 * \param describe		属性表述
		 */
		virtual	void				addProperty(const String& name, Any anyValue, 
			 int typeProperty, bool bWrite=true, const String& describe="null");

		/** 删除指定属性
		 *
		 * \param name			属性名称
		 */
		virtual void				delProperty(const String& name);

		/** 获取属性对象
		 *
		 * \param name			属性名称
		 * \return 
		 */
		virtual Property*			getProperty(const String& name);

		/** 设置属性变量
		 *
		 * \param name			属性名称
		 * \param anyValue		属性变量值
		 */
		virtual	void				setPropertyValue(const String& name, const Any& anyValue);

		/** 获取属性变量值
		 *
		 * \param name			属性名称
		 * \return 
		 */
		virtual Any&				getPropertyValue(const String& name);

		/** 获取属性表引用
		 *
		 * \return 
		 */
		virtual HashProperty&		getHashProperty();

		/** 获取属性变量迭代器
		 *
		 * \return 
		 */
		virtual HashPropertyIter	getHashPropertyIter();

		/** 清空所有属性
		 *
		 */
		virtual	void				clearProperty();
	public:
		/** 获取属性变量值
		 *
		 * \param name		变量名称
		 * \param value		返回变量值
		 */
		template<typename T>
		void						getPropertyValue(const String& name, T& anyValue)
		{
			Property* pProperty = getProperty(name);
			if (pProperty != NULL)
			{
				try {
					anyValue = any_cast<T>(pProperty->getValue());
				}catch(Exception& e) {
					TKLogEvent(e.getFullDescription(), LML_CRITICAL);
				}
			}
			else
			{
				TKLogEvent("error: can't find property " + name);
			}
		}

		/** 设置属性变量值
		 *
		 * \param name		属性名称
		 * \param value		属性变量值
		 */
		template<typename T>
		void						setPropertyValue(const String& name, const T& anyValue)
		{
			Property* pProperty = getProperty(name);
			if (pProperty != NULL)
			{
				try {
					pProperty->setValue(Any(anyValue));
					
					PropertyEventArgs args(pProperty);
					fireEvent(EventValueChanged, args, EventNamespace);

				}catch(Exception& e) {
					TKLogEvent(e.getFullDescription(), LML_CRITICAL);
				}
			}
			else
			{
				TKLogEvent("error: can't find property " + name, LML_CRITICAL);
			}
		}
	protected:
		HashProperty				m_HashProperty;
	};
}

#endif