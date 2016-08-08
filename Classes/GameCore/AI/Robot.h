//
//  Robot.h
//  xzdd
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_Robot_h
#define xzdd_Robot_h

#include "../TypeDef.h"
#include "../GameLogical.h"

using namespace cocos2d;

//AI ������
class Robot
{
    CGameLogical * game;
    BYTE    chair;
    BYTE    AILevel;                //AI����
public:
    Robot();
    void Init(CGameLogical * g, BYTE c);
    
    //��Ҫ���÷���
    
    BYTE    selectedCard;           //ѡ���Ƶ�����
    BYTE    selectedCardIndex;      //ѡ���Ƶ����
    
	
	
	bool isLocked[3][15];//�Ƿ������������ͱ�ʾ���ܳ�
	BYTE outLevel[3][15]; //���Ƶȼ����ȼ�Խ�ߣ���ԽӦ�ó�
    
    BYTE ChoosingCommon(bool p, bool g, bool h);   //�Ծ���ѡ����������ѡ��
    
    BYTE ChoosingCommonAfterMo(bool ag, bool wg, bool h);    //AI���ƺ������ѡ��
    
    void ChoosingOutCard(); //AI����
    void SetAILevel(BYTE l);
    
	PAI_TYPE DingQue();
    
	void LogCard(BYTE nCard);
    
private:
	void DingQueAI(bool isDingQue, DING_QUE	* dingQue, BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard);//���ݶ�ȱ�߼�������	
    BYTE CountStandCardType(BYTE nChair, STAND_CARD * standCard);//������Ҳ�ͬ�ĵ���������
	PAI_TYPE FindDingQueCardType(BYTE nChair, STAND_CARD *standCard); //�ҳ�ȱ������	
    BYTE FindDingQueCard(BYTE nChair, PLAYER_DATA * playerData, PAI_TYPE cardType);//���������ҳ��Ѿ���ȱ��������
    BYTE CountShouCardType(BYTE nChair, PLAYER_DATA * playerData);//�����������������   	
    BYTE FindLeastShouCard(BYTE nChair, PLAYER_DATA * playerData);//�ҳ�����������������ٵ����ŵĵ�һ�ţ�ǰ��ʱ������������
	PAI_TYPE FindLeastShouCardType(BYTE nChair, PLAYER_DATA * playerData);//�ҳ�����������������ٵ�����,��ȱģʽ����
    BYTE FindLessShouCardExcludeStand(BYTE nChair, PLAYER_DATA * playerData, PAI_TYPE excludedCardType);//�ҳ�����������������ٵ����ŵĵ�һ��,ǰ���ǵ�������һ�ţ���������������	
    PAI_TYPE FindOnlyCardTypeInStand(BYTE nChair, STAND_CARD *standCard);//�ҳ������е�Ψһ���ͣ�ǰ����ֻ��һ��
	BYTE FindMin(BYTE b1, BYTE b2);//�����Сֵ 
	BYTE FindMax(BYTE b1, BYTE b2);//����ϴ�ֵ 
    
	//�����ĳ���AI, ���������ŵı�������˳�ӵı��������ӱ����������Ļ��߱��ŵ��ȳ�
    void BasicAI(BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard);	
	void FindShun(BYTE *buf, bool * isLocked);//��˳��,�ҵ�������
	void FindSanZhang(BYTE *buf, bool * isLocked);//����ͬ����,�ҵ�������
	void FindDui(BYTE *buf, bool * isLocked, BYTE * outLevel);//�Ҷ���,Ȼ������Ӧ�ȼ�
	void FindXiangJin(BYTE *buf, bool * isLocked, BYTE * outLevel, STAND_CARD *standCard);//�������,�������ں������Ȼ������Ӧ���Ƶȼ�   
    BYTE GetOutCardSelectedIndex(BYTE wantedCard, BYTE nChair, PLAYER_DATA * playerData);//�ҳ�Ҫ�����Ƶ�index
	BYTE GetOutCardSelectedContent(BYTE nChair, PLAYER_DATA * playerData);//�ҳ�Ҫ�����Ƶ�content
	BYTE FindCountOfOutCardFromTable(BYTE nCard);//��table�ҳ������ѳ�������
	BYTE FindCountOfOutCardFromStand(BYTE nCard, STAND_CARD * standCard);//�ӵ������ҳ������ѳ�������
	BYTE FindCountOfOutCardFromLeft(BYTE nCard);//���ƶ����ҳ������ѳ�������
    void DealWithOutXiangJinLevel(BYTE * outCardLevel, BYTE cardIndex, BYTE outCardCount, bool chengdui);//����������ѳ����ٸ����趨level	
    
	void TingHuAI(BYTE nChair, PLAYER_DATA * playerData, STAND_CARD *standCard);//���������߼�������	
    
    
};

#endif
