#pragma once
#include <ntddk.h>

//
//�����������
//
#define  _RKE_DEBUG_

#ifdef _RKE_DEBUG_
#define  LogPrint DbgPrint
#else
#define  LogPrint 
#endif
