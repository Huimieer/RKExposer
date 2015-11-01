//
//ͷ�ļ�����
//
#include <ntddk.h>
#include "Comm.h"
#include "Utils.h"

//
//��������
//
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj);


//
//������ں���
//
NTSTATUS
DriverEntry(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString)
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    /*ע��ж�غ���*/
    pDriverObj->DriverUnload = DriverUnload;

    /*����ͨ��*/
    status = CmSetupComm(pDriverObj);
    if(!NT_SUCCESS(status))
        return status;


    return STATUS_SUCCESS;
}

//
//����ж�غ���
//
VOID
 DriverUnload(IN PDRIVER_OBJECT pDriverObj)
{	
    LogPrint("DriverUnload called\r\n");
    /*ɾ��ͨ��*/
    CmDeleteComm(pDriverObj);
}