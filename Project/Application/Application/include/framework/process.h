/**
	@file process.h
	@brief �����K��N���X
*/
#pragma once
#ifndef __PROSESS_H__
#define __PROSESS_H__

/**
	@class CProcess
	@brief �������s
*/
template< class TClass, class PRIORITY_TYPE >
class CProcess
{
public:
	/**
		@brief �R���X�g���N�^�[
		@param pszid [in] ���ʎq
		@param nPriority [in] �v���C�I���e�B�[
	*/
	CProcess(const char* i_pszid, PRIORITY_TYPE i_ePriority);

	/**
		@brief �f�X�g���N�^�[
	*/
	virtual ~CProcess();

	/**
		@brief �I��
	*/
	void terminate();
	
	/**
		@brief ���g�Ǝq�ɏ������s��
	*/
	void process(std::function<void(TClass*)> i_func);

	/**
		@brief �L����
	*/
	void setEnable();
	
	/**
		@brief ������
	*/
	void setDisable();

	/*
		@brief �q�̌���
		@param i_pName [in] ���ʎq
	*/
	TClass* findChild(const char* i_pIdentifier);

protected:
	/**
		@brief �L�������̃R�[���o�b�N
	*/
	virtual void    onEnable(){};

	/**
		@brief���������̃R�[���o�b�N
	*/
	virtual void    onDisable(){};
	
	/**
		@brief �I���t���O
	*/
	bool isErase() { return m_bFlgList[FLG_ERASE]; }
	
	/**
		@brief �L��
	*/
	bool isEnable() { return m_bFlgList[FLG_ENABLE]; }

private:
	/**
		@brief operator =
	*/
	CProcess& operator = ( const CProcess& ){};

	/*
		@brief �q�̌���
		@param i_pName [in] ���ʎq
		@param i_pName [in] �n�b�V���l
	*/
	TClass* findChild(const char* i_pIdentifier, std::size_t i_nHash);

private:
	enum
	{
		FLG_ENABLE,			//!< �L�������t���O
		FLG_ERASE,			//!< �I���t���O 

		FLG_MAX
	};

	std::vector<TClass*>		m_apChild;			//!< �q
	std::bitset<FLG_MAX>		m_bFlgList;			//!< �t���O
	std::string					m_strIdentifier;	//!< ���ʎq

	TClass*						m_pParent;			//!< �e
	const PRIORITY_TYPE			m_ePriority;		//!< �v���C�I���e�B�[ 
	std::size_t			 		m_nIdentifierHash;	//!< ���ʎq���琶�����ꂽID

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

