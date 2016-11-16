/**
	@file Process.h
	@brief 処理規定クラス
*/
#pragma once
#ifndef __PROSESS_H__
#define __PROSESS_H__

/**
	@class Process
	@brief 処理実行
*/
template< class TClass, class PRIORITY_TYPE >
class Process
{
public:
	/**
		@brief コンストラクター
		@param pszid [in] 識別子
		@param nPriority [in] プライオリティー
	*/
	Process(const char* id, PRIORITY_TYPE priority);

	/**
		@brief デストラクター
	*/
	virtual ~Process();

	/**
		@brief 終了
	*/
	void Terminate();
	
	/**
		@brief 自身と子に処理を行う
	*/
	void ProcessImpl(std::function<void(TClass*)> func);

	/**
		@brief 有効化
	*/
	void SetEnable();
	
	/**
		@brief 無効化
	*/
	void SetDisable();

	/*
		@brief 子の検索
		@param i_pName [in] 識別子
	*/
	TClass* FindChild(const char* identifier);

protected:
	/**
		@brief 有効化時のコールバック
	*/
	virtual void    OnEnable(){};

	/**
		@brief無効化時のコールバック
	*/
	virtual void    OnDisable(){};
	
	/**
		@brief 終了フラグ
	*/
	bool IsErase() { return _flgList[(uint8_t)FLG::ERASE]; }
	
	/**
		@brief 有効
	*/
	bool IsEnable() { return _flgList[(uint8_t)FLG::ENABLE]; }

private:
	/**
		@brief operator =
	*/
	Process& operator = ( const Process& ){};

	/*
		@brief 子の検索
		@param i_pName [in] 識別子
		@param i_pName [in] ハッシュ値
	*/
	TClass* FindChild(const char* identifier, std::size_t hash);

private:
	enum class FLG : uint8_t
	{
		ENABLE,			//!< 有効無効フラグ
		ERASE,			//!< 終了フラグ 

		MAX
	};

	std::vector<TClass*>				_child;				//!< 子
	std::bitset<(uint8_t)FLG::MAX>		_flgList;			//!< フラグ
	std::string							_identifierString;	//!< 識別子

	TClass*								_parent;			//!< 親
	const PRIORITY_TYPE					_priority;			//!< プライオリティー 
	std::size_t			 				_identifierHash;	//!< 識別子から生成されたID

	friend class ProcessManagerBase;
};


//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
Process<TClass, PRIORITY_TYPE>::Process(const char* id, PRIORITY_TYPE priority)
	:	_child			()
	,	_flgList			(0)
	,	_identifierString		(id)
	,	_parent			(nullptr)
	,	_priority			(priority)
	,	_identifierHash	(std::hash<std::string>()(id))
{
	_PRINT("ctor Process[%s]\n", _identifierString.c_str());
	_child.reserve(PROCESS_CHILD_MAX);
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
Process<TClass, PRIORITY_TYPE>::~Process()
{
	_PRINT("dtor Process[%s]\n", _identifierString.c_str());
	util::for_each( _child, [](Process* p){ SAFE_DELETE( p ); } );
	_child.clear();
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void Process<TClass, PRIORITY_TYPE>::ProcessImpl(std::function<void(TClass*)> func)
{
	func(reinterpret_cast<TClass*>(this));

	util::for_each( _child, [&](Process* p){ p->ProcessImpl(func); } );
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void Process<TClass, PRIORITY_TYPE>::SetEnable()
{
	_flgList[(uint8_t)FLG::ENABLE] = true;
	OnEnable();
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void Process<TClass, PRIORITY_TYPE>::SetDisable()
{
	_flgList[(uint8_t)FLG::ENABLE] = false;
	OnDisable();
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
TClass* Process<TClass, PRIORITY_TYPE>::FindChild(const char* identifier)
{
	return FindChild(identifier, std::hash<std::string>()(identifier));
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
TClass* Process<TClass, PRIORITY_TYPE>::FindChild(const char* identifier, std::size_t hash)
{
	if( _identifierHash == hash &&
		_identifierString.compare(identifier) == 0 )
	{
		return reinterpret_cast<TClass*>(this);
	}

	for each (auto var in _child)
	{
		Process* p = var->FindChild(identifier, hash);
		if( p ) return reinterpret_cast<TClass*>(p);
	}

	return nullptr;
}

//---------------------------------------------------------------------
template<class TClass, class PRIORITY_TYPE>
void Process<TClass, PRIORITY_TYPE>::Terminate()
{
	_flgList[(uint8_t)FLG::ERASE] = true;
}

#endif		//__PROSESS_H__

