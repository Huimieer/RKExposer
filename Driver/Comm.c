#include "Comm.h"
#include "Utils.h"

//
//����ַ����������ڷַ�R3����������
//
NTSTATUS UserCmdDispatcher (IN PDEVICE_OBJECT DeviceObject,IN PIRP pIrp)
{
    NTSTATUS status				= STATUS_SUCCESS;
    PIO_STACK_LOCATION stack	= NULL;
    ULONG cbin					= 0;
    ULONG cbout					= 0;
    ULONG cmd					= 0;
    ULONG info					= 0;
    stack	= IoGetCurrentIrpStackLocation(pIrp);
    /*���뻺������С*/
    cbin    = stack->Parameters.DeviceIoControl.InputBufferLength;
    /*�����������С*/
    cbout   = stack->Parameters.DeviceIoControl.OutputBufferLength;
    //�õ�������
    cmd		= stack->Parameters.DeviceIoControl.IoControlCode;
    switch(cmd){
    case RKE_COMM_TEST:
        {

        }
        break;

    default:
        status  = STATUS_INVALID_VARIANT;
        break;
    }
    /*����irp���״̬*/
    pIrp->IoStatus.Status      = status;
    /*����irp����Ĳ�����*/
    pIrp->IoStatus.Information = info;
    //����irp����
    IoCompleteRequest(pIrp,IO_NO_INCREMENT);
    return status;
}

//
//ɾ��ͨ���豸
//
VOID CmDeleteComm(IN PDRIVER_OBJECT pDriverObj)
{
    PDEVICE_OBJECT		pDevObj			= NULL;
    UNICODE_STRING		uniSymLink   	= {0};

    pDevObj = pDriverObj->DeviceObject;
    if (pDevObj != NULL){
        /*ɾ����������*/
        RtlInitUnicodeString(&uniSymLink,COMM_SYMLINK_R0);
        IoDeleteSymbolicLink(&uniSymLink);

        /*ɾ���豸*/
        IoDeleteDevice(pDevObj);
        pDevObj = NULL;
        LogPrint("CmDeleteComm ok!\r\n");
    }

}

//
//����R3��R0��ͨ��
//
NTSTATUS CmSetupComm(PDRIVER_OBJECT pDriverObj)
{
    NTSTATUS			ntStatus		= STATUS_UNSUCCESSFUL;	
    UNICODE_STRING		uniDeviceName	= {0};
    UNICODE_STRING		uniSymLink  	= {0};
    PDEVICE_OBJECT		pDevObj			= NULL;

    /*�����豸*/
    RtlInitUnicodeString(&uniDeviceName,COMM_DEVICE_NAME_R0);
    ntStatus = IoCreateDevice(pDriverObj,
        0,
        &uniDeviceName,
        FILE_DEVICE_UNKNOWN,
        0,
        TRUE,
        &pDevObj);
    if (!NT_SUCCESS(ntStatus)){
        LogPrint("IoCreateDevice failed...\r\n");
        return ntStatus;
    }
    /*�����豸ͨ��ģʽ*/
    pDevObj->Flags |= DO_BUFFERED_IO;

    /*������������*/
    RtlInitUnicodeString(&uniSymLink,COMM_SYMLINK_R0);
    ntStatus = IoCreateSymbolicLink(&uniSymLink,&uniDeviceName);
    if(!NT_SUCCESS(ntStatus)){
        LogPrint("IoCreateSymbolicLink failed...\r\n");
        IoDeleteDevice(pDevObj);
        return ntStatus;
    }
    LogPrint("CmSetupComm ok!\r\n");
    /*�����ɹ���ע����ǲ���̣�����ֻע���� io control����ǲ*/
    pDriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL]    = UserCmdDispatcher;
    return STATUS_SUCCESS;
}