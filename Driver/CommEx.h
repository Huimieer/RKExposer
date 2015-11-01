#pragma once

//
//���.h�ļ�R3��R0��Ҫ����
//

//-----------------------------------------------------------------------------
// R3��R0��ʹ�õķ���������
//-----------------------------------------------------------------------------
#define COMM_DEVICE_NAME_R0			L"\\Device\\RkExposerDevice"            //R0�豸��
#define COMM_SYMLINK_R0				L"\\??\\RkExposer"                      //R0����������
#define COMM_SYMLINK_R3				L"\\\\.\\RkExposer"                     //R3���������������ڴ��豸��ȡ���

//-----------------------------------------------------------------------------
// ����R3��R0��ͨ������ͨ��DeviceIoControl������
//-----------------------------------------------------------------------------
#define FILE_DEVICE_UNKNOWN             0x00000022
#define METHOD_BUFFERED                 0
#define FILE_ANY_ACCESS                 0

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
    )
#define  CTRL_BASE 0xa00	// ����0x800
#define CTRL_EXPRESSION(i)   CTL_CODE(FILE_DEVICE_UNKNOWN,(CTRL_BASE+i),METHOD_BUFFERED,FILE_ANY_ACCESS)
//�ж��ǲ��ǿ�����
//#define CTRL_SUCCESS(code) (((code) &  0x88880000) == 0x88880000)

//
//����һϵ�п����룬����R3��R0ͨ�ţ������뿪ʼ�� "RKE"��ʼ
//
#define RKE_COMM_TEST		                    CTRL_EXPRESSION(0)			//����ͨ��
#define RKE_ENUM_PROCESS_INFORMATION            CTRL_EXPRESSION(1)          //ö�ٽ�����Ϣ����
#define RKE_ENUM_THREAD_INFORMATION             CTRL_EXPRESSION(2)          //ö���߳���Ϣ����

