#include "Version.h"

/*ȫ�ֱ�����־windows�汾��*/
WIN_VER_DETAIL gWinVersion;

/*��ؽṹӲ���룬�汾��ͬ�ṹƫ��Ҳ��ͬ*/
STRUCT_OFFSET gStructOffset;

WIN_VER_DETAIL GetWindowsVersion()
{
	RTL_OSVERSIONINFOEXW	osverinfo;

	if (gWinVersion)
		return gWinVersion;

	RtlZeroMemory(&osverinfo,sizeof(RTL_OSVERSIONINFOEXW));
	osverinfo.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW); 
	if (RtlGetVersion((RTL_OSVERSIONINFOW*)&osverinfo) != STATUS_SUCCESS){
		return WINDOWS_VERSION_NONE;
	}

	if (osverinfo.dwMajorVersion == 5 && osverinfo.dwMinorVersion == 0){
		gWinVersion = WINDOWS_VERSION_2K;
	} 
	else if (osverinfo.dwMajorVersion == 5 && osverinfo.dwMinorVersion == 1){
		gWinVersion = WINDOWS_VERSION_XP;
	} 
	else if (osverinfo.dwMajorVersion == 5 && osverinfo.dwMinorVersion == 2){
		if (osverinfo.wServicePackMajor == 0)
			gWinVersion = WINDOWS_VERSION_2K3;
		else
			gWinVersion = WINDOWS_VERSION_2K3_SP1_SP2;
	} 
	else if (osverinfo.dwMajorVersion == 6 && osverinfo.dwMinorVersion == 0){
		gWinVersion = WINDOWS_VERSION_2K3_SP1_SP2;
	}
	else if (osverinfo.dwMajorVersion == 6 && 
			 osverinfo.dwMinorVersion == 1 && 
			 osverinfo.dwBuildNumber == 7000){
		gWinVersion = WINDOWS_VERSION_7_7000;
	}
	else if (osverinfo.dwMajorVersion == 6 && 
		osverinfo.dwMinorVersion == 1 && 
		osverinfo.dwBuildNumber >= 7600){
		gWinVersion = WINDOWS_VERSION_7_7600_UP;
	}
	return gWinVersion;
}

//
//��ʼ���ṹ��ƫ�ƣ�һЩ��Ҫ�Ľṹ����ݰ汾��ͬ���ƫ��Ҳ��ͬ
//
VOID InitStructOffset()
{
	RtlZeroMemory(&gStructOffset,sizeof(STRUCT_OFFSET));

	/*��ȡϵͳ�汾��*/
	GetWindowsVersion();

	switch(gWinVersion){
	case WINDOWS_VERSION_XP:
		{
			gStructOffset.EProcessActiveProcessLinks	= 0x88;
			gStructOffset.EProcessDebugPort				= 0xbc;
			gStructOffset.EProcessImageFileName			= 0x174;
			gStructOffset.EProcessObjectTable			= 0xc4;
			gStructOffset.EProcessThreadListHead		= 0x190;
			gStructOffset.EProcessUniqueProcessId		= 0x84;
			gStructOffset.EProcessVadRoot				= 0x11c;

            /*  */
            gStructOffset.FileObjectSize                = 0x70;
		}
		break;
	case WINDOWS_VERSION_7_7000:
	case WINDOWS_VERSION_7_7600_UP:
		{
			//
            gStructOffset.FileObjectSize                = 0x80;
		}
		break;
	}
}
