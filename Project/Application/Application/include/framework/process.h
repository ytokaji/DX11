/**
	@file Process.h
	@brief �����K��N���X
*/
#pragma once
#ifndef __PROSESS_H__
#define __PROSESS_H__

/**
	@class Process
	@brief �������s
*/
template< class TClass, class PRIORITY_TYPE >
class Process
{
public:
	/**
		@brief �R���X�g���N�^�[
		@param pszid [in] ���ʎq
		@param nPriority [in] �v���C�I���e�B�[
	*/
	Process(const char* id, PRIORITY_TYPE priority);

	/**
		@brief �f�X�g���N�^�[
	*/
	virtual ~Process();

	/**
		@brief �I��
	*/
	void Terminate();
	
	/**
		@brief ���g�Ǝq�ɏ������s��
	*/
	void ProcessImpl(std::function<void(TClass*)> func);

	/**
		@brief �L����
	*/
	void SetEnable();
	
	/**
		@brief ������
	*/
	void SetDisable();

	/*
		@brief �q�̌���
		@param i_pName [in] ���ʎq
	*/
	TClass* FindChild(const char* identifier);

protected:
	/**
		@brief �L�������̃R�[���o�b�N
	*/
	virtual void    OnEnable(){};

	/**
		@brief���������̃R�[���o�b�N
	*/
	virtual void    OnDisable(){};
	
	/**
		@brief �I���t���O
	*/
	bool IsErase() { return _flgList[(uint8_t)FLG::ERASE]; }
	
	/**
		@brief �L��
	*/
	bool IsEnable() { return _flgList[(uint8_t)FLG::ENABLE]; }

private:
	/**
		@brief operator =
	*/
	Process& operator = ( const Process& ){};

	/*
		@brief �q�̌���
		@param i_pName [in] ���ʎq
		@param i_pName [in] �n�b�V���l
	*/
	TClass* FindChild(const char* identifier, std::size_t hash);

private:
	enum class FLG : uint8_t
	{
		ENABLE,			//!< �L�������t���O
		ERASE,			//!< �I���t���O 

		MAX
	};

	std::vector<TClass*>				_child;				//!< �q
	std::bitset<(uint8_t)FLG::MAX>		_flgList;			//!< �t���O
	std::string							_identifierString;	//!< ���ʎq

	TClass*								_parent;			//!< �e
	const PRIORITY_TYPE					_priority;			//!< �v���C�I���e�B�[ 
	std::size_t			 				_identifierHash;	//!< ���ʎq���琶�����ꂽID

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

