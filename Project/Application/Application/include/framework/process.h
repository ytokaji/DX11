/**
	@file process.h
	@brief 処理規定クラス
*/
#pragma once
#ifndef __PROSESS_H__
#define __PROSESS_H__

/**
	@class CProcess
	@brief 処理実行
*/
template< class TClass, class PRIORITY_TYPE >
class CProcess
{
public:
	/**
		@brief コンストラクター
		@param pszid [in] 識別子
		@param nPriority [in] プライオリティー
	*/
	CProcess(const char* i_pszid, PRIORITY_TYPE i_ePriority);

	/**
		@brief デストラクター
	*/
	virtual ~CProcess();

	/**
		@brief 終了
	*/
	void terminate();
	
	/**
		@brief 自身と子に処理を行う
	*/
	void process(std::function<void(TClass*)> i_func);

	/**
		@brief 有効化
	*/
	void setEnable();
	
	/**
		@brief 無効化
	*/
	void setDisable();

	/*
		@brief 子の検索
		@param i_pName [in] 識別子
	*/
	TClass* findChild(const char* i_pIdentifier);

protected:
	/**
		@brief 有効化時のコールバック
	*/
	virtual void    onEnable(){};

	/**
		@brief無効化時のコールバック
	*/
	virtual void    onDisable(){};
	
	/**
		@brief 終了フラグ
	*/
	bool isErase() { return m_bFlgList[FLG_ERASE]; }
	
	/**
		@brief 有効
	*/
	bool isEnable() { return m_bFlgList[FLG_ENABLE]; }

private:
	/**
		@brief operator =
	*/
	CProcess& operator = ( const CProcess& ){};

	/*
		@brief 子の検索
		@param i_pName [in] 識別子
		@param i_pName [in] ハッシュ値
	*/
	TClass* findChild(const char* i_pIdentifier, std::size_t i_nHash);

private:
	enum
	{
		FLG_ENABLE,			//!< 有効無効フラグ
		FLG_ERASE,			//!< 終了フラグ 

		FLG_MAX
	};

	std::vector<TClass*>		m_apChild;			//!< 子
	std::bitset<FLG_MAX>		m_bFlgList;			//!< フラグ
	std::string					m_strIdentifier;	//!< 識別子

	TClass*						m_pParent;			//!< 親
	const PRIORITY_TYPE			m_ePriority;		//!< プライオリティー 
	std::size_t			 		m_nIdentifierHash;	//!< 識別子から生成されたID

	friend class IProcessManager;
};


//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
CProcess<TClass, PRIORITY_TYPE>::CProcess(const char* i_pszid, PRIORITY_TYPE i_ePriority)
	:	m_apChild			()
	,	m_bFlgList			(0)
	,	m_strIdentifier		(i_pszid)
	,	m_pParent			(nullptr)
	,	m_ePriority			(i_ePriority)
	,	m_nIdentifierHash	(std::hash<std::string>()(i_pszid))
{
	_PRINT("ctor process[%s]\n", m_strIdentifier.c_str());
	m_apChild.reserve(PROCESS_CHILD_MAX);
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
CProcess<TClass, PRIORITY_TYPE>::~CProcess()
{
	_PRINT("dtor process[%s]\n", m_strIdentifier.c_str());
	util::for_each( m_apChild, [](CProcess* p){ SAFE_DELETE( p ); } );
	m_apChild.clear();
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void CProcess<TClass, PRIORITY_TYPE>::process(std::function<void(TClass*)> i_func)
{
	i_func(reinterpret_cast<TClass*>(this));

	util::for_each( m_apChild, [&](CProcess* p){ p->process(i_func); } );
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void CProcess<TClass, PRIORITY_TYPE>::setEnable()
{
	m_bFlgList[FLG_ENABLE] = true;
	onEnable();
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void CProcess<TClass, PRIORITY_TYPE>::setDisable()
{
	m_bFlgList[FLG_ENABLE] = false;
	onDisable();
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
TClass* CProcess<TClass, PRIORITY_TYPE>::findChild(const char* i_pIdentifier)
{
	return findChild(i_pIdentifier, std::hash<std::string>()(i_pIdentifier));
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
TClass* CProcess<TClass, PRIORITY_TYPE>::findChild(const char* i_pIdentifier, std::size_t i_nHash)
{
	if( m_nIdentifierHash == i_nHash &&
		m_strIdentifier.compare(i_pIdentifier) == 0 )
	{
		return reinterpret_cast<TClass*>(this);
	}

	for each (auto var in m_apChild)
	{
		CProcess* p = var->findChild(i_pIdentifier, i_nHash);
		if( p ) return reinterpret_cast<TClass*>(p);
	}

	return nullptr;
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void CProcess<TClass, PRIORITY_TYPE>::terminate()
{
	m_bFlgList[FLG_ERASE] = true;
}

#endif		//__PROSESS_H__

