#pragma once
////////////�Զ���Э��///////////////////

const int MSG_LOGOIN = 0x01; //��¼
const int MSG_SEND = 0x11;   //������Ϣ
const int MSG_CLOSE = 0x02;  //�˳�
const int MSG_UPDATE = 0x21; //����Ϣ
const int MSG_READY = 0x03;  //׼��
const int MSG_HANDCARDS =0x31;  //����
const int MSG_CARDINFO = 0x04; //������Ϣ
const int MSG_PASS = 0x41;    //����
const int MSG_PLAYERINFO = 0x05;//�����Ϣ
const int MSG_END = 0x51; //����
const int MSG_USERNAME=0x06; //����س�

#pragma pack(push,1)
typedef struct tagHeader{
	int type ;//Э������

	//int number;//��ұ��
	int nContentLen; //��Ҫ�������ݵĳ���
}HEADER ,*LPHEADER;
#pragma pack(pop)
