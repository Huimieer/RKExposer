#pragma once
#include <ntddk.h>
//
//������R0ͨ����صĺ�����Cm = Communication
//
#include "CommEx.h"

VOID CmDeleteComm(IN PDRIVER_OBJECT pDriverObj);

NTSTATUS CmSetupComm(PDRIVER_OBJECT pDriverObj);