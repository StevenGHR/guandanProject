#pragma once
////////////自定义协议///////////////////

const int MSG_LOGOIN = 0x01; //登录
const int MSG_SEND = 0x11;   //发送消息
const int MSG_CLOSE = 0x02;  //退出
const int MSG_UPDATE = 0x21; //更信息
const int MSG_READY = 0x03;  //准备
const int MSG_HANDCARDS =0x31;  //手牌
const int MSG_CARDINFO = 0x04; //出牌信息
const int MSG_PASS = 0x41;    //过牌
const int MSG_PLAYERINFO = 0x05;//玩家信息
const int MSG_END = 0x51; //结束
const int MSG_USERNAME=0x06; //玩家呢称

#pragma pack(push,1)
typedef struct tagHeader{
	int type ;//协议类型

	//int number;//玩家编号
	int nContentLen; //将要发送内容的长度
}HEADER ,*LPHEADER;
#pragma pack(pop)
