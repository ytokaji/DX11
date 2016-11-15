/**
	@file util.h
	@brief ���낢��ȂƂ���Ŏg������
*/

#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include "define_type.h"
#include <algorithm>

namespace util
{
	/**
		@brief for_each �̈������ȗ�������e���v���[�g�֐�
	*/
	template <typename T_container, typename T_function>
	T_function for_each(T_container& rcontainer, T_function function)
	{
		return for_each(rcontainer.begin(), rcontainer.end(), function);
	}
}

#endif		//__UTIL_H__