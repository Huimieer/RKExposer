#pragma  once


//typedef wchar_t         WCHAR;
//typedef unsigned char  BOOL, *PBOOL;
//typedef unsigned char  BYTE, *PBYTE;
//typedef unsigned long  DWORD, *PDWORD;
//typedef unsigned short WORD, *PWORD;
//
//typedef unsigned int    UINT;
//
//�Լ�����Ľṹ��
//
#define MAX_BUFFER_LENGTH       (260)

#pragma pack(push)
#pragma pack(1)
//-----------------------------------------------------------------------------
// ͨ������Ϣ������صĽṹ��
//-----------------------------------------------------------------------------

//
//Ӧ�ò����״̬
//
typedef enum USER_ACCESS_STATE{
    UAS_ACCESSIBLE  = 0,    //�ɷ���
    UAS_REFUSED     = 1,    //�ܾ�
    UAS_OTHER       = 100   //����
};
//
//�ں˲���״̬
//
typedef enum KERNEL_DETECT_STATE{
    KDS_NORMAL      = 0,
    KDS_HIDE        = 1
};

//
//���������Ϣ�ṹ��
//
typedef struct tagRKE_PROCESS_INFORMATION{
    wchar_t ImageName[MAX_BUFFER_LENGTH];           //����ӳ����
    unsigned long Eprocess;                         //���̶���
    unsigned long ProcessId;                        //����id
    unsigned long ParentId;                         //������id
    wchar_t ImagePath[MAX_BUFFER_LENGTH];           //����·��
    wchar_t FileManufacturer[MAX_BUFFER_LENGTH];    //�ļ�����
    KERNEL_DETECT_STATE KernelDetState;             //�ں�����Ľ������������ ����

}RKE_PROCESS_INFORMATION,*PRKE_PROCESS_INFORMATION;
#pragma pack(pop)