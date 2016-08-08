//
//  GameLogical.h
//  xzdd
//
//  Created by  on 12-2-27.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_GameLogical_h
#define xzdd_GameLogical_h

#include "MjDef.h"
#include "ServerFrameDefs.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 

#include "RuleDef.h"

#else 

#include "RuleGen/RuleDef.h"

#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MIN_GOLD_MUTIPLE 128
//���׺������ܺ� 12/10�� �����ڴ���Ļ����ϼӷֵġ�
const WORD SCORE_DADAHU_MORE = 20;           //���׺�����ķ֣�����10�֣�����ǵ�/���ڵ���ׯ�ң�Ϊ12�֣�
const WORD SCORE_DADAHU_BANKER_MORE = 10;
static BYTE CardIndex[3][10];

struct tagServerOption;

class CGameLogical
{	
private:
    ///cai
    BYTE m_nChairTA;
	BYTE m_nChairDianPao;				// ����������Ӻ�
	BYTE m_nCountHu;
	BYTE m_nCountFlee;
	BYTE m_nCountHuaZhu;
	BYTE m_nCountDajiao;
	bool m_bChairHu[PLAYER_COUNT];		// Ѫս�Ѻ����
    BYTE m_nGen[PLAYER_COUNT];
    
    bool m_bMaxFan;
    
    //	BYTE m_nDingQue[PLAYER_COUNT];		// ��ȱ״̬
	DING_QUE	m_sDingQue[PLAYER_COUNT];	// ��ȱ״̬
    

	BYTE m_nCountChangeBanker;			// ��ׯ����

    
	bool m_bSeen;                        //�Ƿ�ɼ�
	bool m_bTianRenHu;					// �����жϵ����˺�
	BYTE m_nDiHu[4];					// �жϵغ�
	bool m_bMenQing[4];					// �ж�����
	
	BYTE m_nEndReason;					// ��Ϸ����ԭ��
    
	QIANG_GANG m_sQiangGang;			// ��������
	GANG_PAO	m_sGangPao;				// �������
	bool m_bHaveGang;                   // ����ܿ�
    
	long m_wHuaZhuScore[4];				// ����
	long m_wDaJiaoScore[4];				// ����
	long m_wZimoFanScore[4];			// ����
	long m_wGangScore[4][4];			// ����
    long m_wGangScoreOne[4];			// ����
	long m_wTotalScore[4];				// �þֵķ���
    
    long m_wHuScore[4];					// ����
	long m_wGFXYScore[4];
    
    // 	DWORD m_dwUserID[4][10];			// ���ID, m_dwUserID[i][0] Ϊ��� 
    // 										// m_dwUserID[i][1]Ϊ�Թ�����Ŀ
    // 										// ����Ϊ�Թ���ID�������8���Թ���
    
	//������
	BYTE 		m_nTableCards[4][32];		// 4����ҵ�������
	STAND_CARD 	m_sStandCard[4];			// ��ҵ���

	PLAYER_DATA	m_sPlayer[4];				// ���˽������
	BYTE		m_nNumCheat[4];				// ���iթ������
	BYTE		m_nNumFan[4];				// Ӯ�ҵķ���
	long		m_wSetScore[4];				// �þֵ��������
	long		m_wSetLoseScore[4];			// �þֵ��������
	long		m_wSetGold[4];				// �þֵĽ����
	long		m_wSetTax[4];				// �þֵ�˰��
	BYTE		m_nHuTypeCurt[4];			// ���Եĺ��Ƶ�����(С��,���,�������)
	BYTE		m_nHuTypeDetailed[4];		// ��ϸ�ĺ�������(���, �غ�, ������.......)
	BYTE		m_nCardLast;				// ������
	
	//����
	BYTE        m_bFlee[PLAYER_COUNT];  
    BYTE        m_nSetCount;
    
    BYTE		m_nDajiaoFan[PLAYER_COUNT];
    
	//��������
	EAT_SUIT	m_sEat;						// ��ų�����Ϣ
	GangMine_SUIT	m_sCanGang;				// ��ſ��Ըܵ��Ƶ���Ϣ
	bool		m_bChooseBuf[4][4];			// 4����ҵĺ�,��,��,���ɺ���������
	BYTE		m_nNumCmdHu;				// ������ĸ���
	BYTE		m_chairHu[3];				// ��������������
	BYTE		m_chairSendCmd;				// ��ǰ����������

    
	// ���տͻ�������
	BYTE		m_nJiang[4];				// �жϺ��ƵĽ�,���ܺ�ʱ��Ϊ255;
	BYTE 		m_nHuList[4][30];			// �����б�, m_nHuCList[4][0]: �ɺ��Ƶĸ���
	BYTE		m_nHuGiveUp[4][10];			// ���ַ���������,m_nHuGiveUp[4][0]: ����
	BYTE		m_nEatBuf[3];				// �ͻ���ѡ��Ե�������
	
	// ��ͻ����޹�
	BYTE		m_nCardBuf[140];			// �ƵĻ�����
    
	// �����Ϸ
	BYTE m_bIsCasinoGame;	// �ǲ��ǽ����Ϸ
	BYTE m_bSupportNego;		// �Ƿ�֧��Э��
	int  m_nMinGold;		// ������Ϸ�������С���
	int  m_nAnte;			// ��ע
	int	 m_nDefAnte;        //����Ĭ�϶�ע
    
	//�������
	BYTE m_bIsMatchGame;
	BYTE m_bIsMatchOver;
    
	//����
    HU_CURT m_HuCurt[4];
    ///cai	bool m_bMissHu[4];      //����������ִ�
    
	///cai ��������
	BOOL m_bBloodyGame;		//��Ϸģʽ
	GuaFengXiaYu m_enGFXY;	//�η�����
	BOOL m_bFast;			//����
	BOOL m_bZimoFan;		//�����ӷ�
	BOOL m_b3Fan;			//�������
    
	//����
	Score_Struct m_Score[PLAYER_COUNT];
    
	BOOL m_bPreventCheatRoom;	//add by mxs 
    
private:	
	//--IServerFrame * m_pSite; 
	tagServerOption * m_pServerOption;
    
    /************************************************************************/
    /*                               ������                                 */
    /************************************************************************/
    
public:
    
    //��ʼ���ͷ���
	void InitData();
	void InitRawData();
	void DealAllCard();
	bool DealCard(BYTE nChair);
	
    //�����б�
	void InitHuList(BYTE chair);						// ��ʼ�������б�
	bool IsInHuList(BYTE chair, BYTE card);				// �ж���card�ڲ��ں����б���
    
    //���������
	void ListInsert(BYTE *buf, BYTE card);	// ������
	void ListDelete(BYTE *buf, BYTE card);		// ɾ����
	BYTE ListFind(BYTE *buf, BYTE card);		// �����ƣ����ظ���
	void ListSort(BYTE *buf, BYTE n);
    
	BYTE ListJudgePengPeng(BYTE * s, BYTE &nJiang);		//��"��"�����б��з���,�жϴ�����ȫ3��(return 1), 3+2��(return 2)������(return 0)
	BYTE ListJudgeNormal32(BYTE *s, BYTE &nJiang);		//�жϴ�����ȫ3��(return 1), 3+2��(return 2)������(return 0)
	bool ListJudgeDui(BYTE *s);						//�ж����б����ǲ���ֻ�ж�
    bool ListJudgeYaoJiu(BYTE *s);					//�ж��б����۾���
    //�жϸ�������
	bool Judge32(BYTE chair);					//�ж��ֳ����ܲ��ܹ���3 + 2
	bool IsShunInStandCards(BYTE chair);		//�жϵ�������û��˳
    
    //�жϲ�������
    ///cai	bool FindEat(BYTE chair);			//�ж���û�г���
	bool FindPeng(BYTE chair);			//�ж���û����
	bool FindAnGang(BYTE chair);		//�ж���û�а���
	bool FindWanGang(BYTE chair);	//�ж���û�б��˴���������
	bool FindMingGangCome(BYTE chair);	//�ж���û���Լ���������
	
    //�жϺ��ƺ���	
    ///cai
	bool JudgeQueYimen(BYTE nChair);
	bool JudgeHuaZhu(BYTE chair);
	void SceneStatusToPhasePlaying();
	void HandleDingQue(BYTE nChair, BYTE nCardType);
    
	bool JudgeHu(BYTE chair);
	BYTE JudgeFan(BYTE chair);
    
	BYTE JudgeHuType(BYTE chair);       //�жϳ���
//	BYTE JudgeYaoJiuHu(BYTE chair, bool bJudgeShiSanYao = false); //�ж�ô�� ����ʮ��ô����ô�ţ���ô�� 
	
	bool JudgePingHu(BYTE chair);		//�ж�ƽ  ��	1
	bool JudgePengPengHu(BYTE chair);   //�ж�������	3
///cai	bool JudgeHunYiSe(BYTE chair);		//�жϻ�һɫ	3
	bool JudgeQingYiSe(BYTE chair);		//�ж���һɫ	5
	bool JudgeZiYiSe(BYTE chair);		//�ж���һɫ	8
	
	bool JudgeQiQiaoDui(BYTE chair);	//�ж����ɶ�   ����
	BYTE JudgeGen(BYTE chair);			//�жϸ�
	bool JudgeYaoJiuHu(BYTE chair);		 //�ж�ô��
	bool Judge258(BYTE chair);		 //�жϽ�258
    
    BYTE JudgeDajiao(BYTE chair);
    
	void SetHuList(BYTE chair);    
    
    //�������
	void HandleChooseEat(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChoosePeng(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChooseAnGang(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChooseMingGangM(BYTE nChair, LPCVOID lpData, int nSize);
	void HandleChooseMingGangC(BYTE nChair, LPCVOID lpData, int nSize);	
    
	void HandleChooseResult();										 // �������ѡ��Ľ��
    
	void HandleHuZiMo(BYTE nChair, LPCVOID lpData, int nSize);		 //��������
	void HandleZhaHu(BYTE nChair);                                     //����թ��
	
	void HandleOutCard(BYTE nChair, LPCVOID lpData, int nSize);		 //�������
    void HandleOutCard(BYTE nChair, BYTE pos);                      //�������
    
	void HandleMatchNoStart();			//�������ʱ�䵽û�п�ʼ
    
    //����
	BYTE ChairTo(BYTE i, BYTE j);		// ���i��������j��λ��,��(0,3),����1(���¼�)
	BYTE AntiClock(BYTE chair);			// ����chair��ʱ��ת1�����
    
	PAI_TYPE GetCardType(BYTE nCard);	// �����Ƶ�����
	int GetCardValue(BYTE nCard);		// �����Ƶ�ֵ
	BYTE GetSanYuanNum(BYTE chair);     // �õ���Ԫ����Ŀ
	BYTE GetSiXiNum(BYTE chair, BYTE* pCardSiXi = NULL);		// �õ���ϲ����Ŀ
    
	bool Is258(BYTE card);				// �ж�card��value�ǲ���2,5,8֮һ
	bool IsYaoJiu(BYTE card);			// �Ƿ�ô����
	bool IsYaoQi(BYTE card);			// �Ƿ�ô7��    
    bool IsZiPai(BYTE card);			//�Ƿ�����
    bool IsFeng(BYTE card);				//�Ƿ����
	bool IsDragon(BYTE card);			//�Ƿ�����
	bool Is456(BYTE card);
	void ClearChooseBuf(BYTE nChair, bool bClearGang = true); //����������
    
	BOOL IsValidChair(BYTE nChair);
    
	void HandleSetOver();
    
    void WriteScore();
    
    //����Լ�д��
///paddy//	void ScoreNormalCalAndWrite(); //������д��
    void CalcHuScore(); //���������
	void CalcFleeScore(); //�������
    void CalcNoCardScore(); //�������
    
	void ScoreFleeNormalCal(); //��ͨ�������
	void ScoreFleeBloodCal(); //Ѫս�������
    
	bool ScoreFleeYBCal(Score_Struct score[PLAYER_COUNT]);//����������
	void ScoreFleeMatchCal(Score_Struct scores[PLAYER_COUNT]); //�����������
    
    void ScoreNoCardNormalCal(); //��ͨ�������
	void ScoreNoCardBloodCal(); //Ѫս�������
    
	bool ScoreOneHuCal(BYTE nWinChair, BYTE nLostChair = 255);
    
	void InformResultMsg();
	BOOL SendSysMsgToUser(BYTE nChair, LPCSTR lpszMsg);
    
    //������
//	BOOL CalSetCoinScore();
//	__inline bool IsYBGame()
//	{	
//		if ( m_pServerOption->dwMatchType > 0 )	//����Ǳ��������������ֹ��ҹ���
//			return FALSE;
//		return TRUE == m_pServerOption->bCasinoGame;
//	}
//	BOOL InforCoinNum(BYTE nSrcChair, BYTE nDestChair);
    
//	BOOL InformCoinChairToID(BYTE nSrcChair, DWORD dwUserID);
//	BOOL InformCoinChairToChair(BYTE nSrcChair, BYTE nDestChair, BOOL bIncludeLooker=TRUE);
    
    //�������
    void CalIsMatchStop();
	bool IsTooManyFlee(Score_Struct *pScore[PLAYER_COUNT],int nSetCount,long lFleeCounts[PLAYER_COUNT]);
    void BroadcastMatchScores(int nSetCount,Score_Struct *pScore[PLAYER_COUNT]);
//	__inline bool IsMatchServer()	{	return m_pServerOption->dwMatchType > 0;	}
    void SendOneByteMsg(char cmd ,BYTE data,DWORD dwUserID = INVALID_FRAME_USER_ID);
	
	
    //�ӿں���	
public:
	CGameLogical();
	virtual ~CGameLogical();
    
    // IGameLogicalSink
public:	
	virtual CHECK_START_MODE  OnGetCheckStartMode();
	virtual BOOL  OnGetChairScene(unsigned char nChair/*in*/,BOOL bSeenSecretData/*in*/,
                                         BOOL bNeedWholeScene/*in*/,int nUserCurrentVersion/*in*/,SCENE * pScene/*out*/,DWORD dwFlag = 0);
	virtual void  OnGetServerVersionScope(VERSION_STRUCT * version/*out*/);
	virtual LOOKON_OPTION  OnGetLookOnOption();
	virtual BOOL  OnInit(tagServerOption * pServerOption);
	virtual BOOL  OnSceneStatusToPlaying(int iNomi, int iDeNomi);
	virtual void  OnSceneStatusToFree(BOOL bFled[MAX_CHAIR],int nCondition = 0,DWORD dwReserved = 0);
	virtual void  OnGameMessage(unsigned char nChair/*in*/, 
                                       int nCmdID/*in*/, LPCVOID lpData/*in*/, int nSize/*in*/);
	virtual void  OnTimer(DWORD dwEventID);
	virtual void  OnTableStatusToPlaying();
//	virtual void  OnUserExit(int nChair,DWORD dwUserID,BOOL bIsPlayer,BOOL bLeftAtPlaying = FALSE);
	virtual void  OnUserEnter(int nChair,DWORD dwUserID,BOOL bIsPlayer);
	virtual void  OnPlayerOffline(int nChair,DWORD dwUserID);
	virtual void  OnPlayerReplay(int nChair,DWORD dwUserID);
	virtual bool  OnPlayerReady(int nChair,DWORD dwUserID);
	virtual void  OnSentence(int nWinIndex,DWORD dwReserved);
	virtual BOOL  OnIsCasinoGame(DWORD& dwMinCashNeeded);
//	virtual HRESULT  OnmeMatchStop(UINT uStopReason);
	virtual BOOL  OnIsOneScoreInOneSet();
//  virtual BOOL  OnIsPlayerNotEnoughGold(DWORD dwUserID,long lGold,BOOL& bNeedKick,BOOL & bCancelDefMsgBox);
	virtual BOOL  OnIsSupportGameConcept();
	virtual BOOL  OnGameStatusToPlaying();
	virtual BOOL  OnGameStatusToFree();
	virtual BOOL  OnGetOldScoreBuffer(LPSTR lpszBuffer,int& nSize);
	virtual void  Release();
//	virtual int  OnGetClientScoreType();
	virtual BOOL  OnIsSupportNegotiateDismiss(DWORD& dwLeastAdvocater/*out*/);
	virtual BOOL  OnGetMatchSetContext(LPSTR lpszBuffer/*out*/,int& nDataLen/*in/out*/);
	virtual int	 OnGetTableOpChair();
//	virtual BOOL  OnGetDefaultGameRule(LPVOID lpGameRule/*out*/,UINT& nDataLen/*in/out*/);
//    virtual BOOL  OnGetGameRule(LPVOID lpGameRule/*out*/,UINT& nDataLen/*in/out*/);
//    virtual void  OnGameRuleChanged(LPCVOID lpGameRule,UINT nLen);
    virtual void  OnSetGameRuleCanceled();
//  virtual void  OnClientVersion(DWORD dwUserID,int nChair,BOOL bIsPlayer,DWORD dwMainVersion,DWORD dwSubVersion) ;	
	virtual BOOL  OnGetCreateClientMethod(DWORD& dwMethodID,LPSTR lpszFileName);
//	virtual BOOL  OnCheckClientVersion(GameLogic_DownloadInfo & downloadInfo,DWORD dwMainVersion,DWORD dwSubVersion,LPCVOID lpExtInfo,UINT uLen);
    virtual BOOL  OnPlayerLookonStateChanged(int nChair,DWORD dwDestID,BOOL bEnable);
    
    
	virtual bool  OnIsNetChessAcademy();
	virtual bool  OnGetAcademyLevelScoreBuf(LPSTR lpszScoreBuf/*out*/,DWORD dwMaxLen);
	virtual bool  OnGetAcademyLevelDesc(LPSTR lpszDescBuf/*out*/,DWORD dwMaxLen);
	virtual void  OnWriteUBReturn(DWORD dwSequenceID,BOOL bSucceeded);
	virtual BOOL  OnMatchCheckStart();
//	virtual UINT  OnDispatch(DWORD dwReserved1 = 0,DWORD dwReserved2 = 0,DWORD dwReserved3 = 0);
    
    
    //����ʹ��
	typedef BYTE (CGameLogical::*TABuidFuc)();
#define MAX_TA_BULID_FUNC 20
	TABuidFuc BuildTA[MAX_TA_BULID_FUNC];
	int m_iTAFuncCount;
	BYTE	m_TArray[HOLD_CARD_NUM];
	char	m_szTALevel[16];
    
	BYTE	TAHunYaoJiu();		
	BYTE	TASanYuan();
	BYTE	TASiXi();
    
    BYTE    TAQingYiSe();		//1 ��һɫ������
    
	BYTE	TAYaoJiu();			//2 �۾�������
	BYTE	TAQiDui();			//3 �߶�������
    
	BYTE	TAQingPeng();		//4 ����������
	BYTE	TAJiangPeng();		//5 ����������
	BYTE	TALongQiDui();		//6 ���߶�������
    
	BYTE	TAQingQiDui();		//7 ���߶�������
	BYTE	TAQingYaJiu();		//8 ���۾�������
    
	BYTE	TAQingLongQiDui();	//9 �����߶�������
    
    bool	CheckTACard(BYTE ArrayBase[], const int iBaseCount);
    
	void ResetTACardBuf(BYTE nTACount);
	BOOL ReplaceCardFromBuf(BYTE* pBuf, int nLength, BYTE nPreCard, 
                            BYTE nByCard, BOOL bOnlyOnce = TRUE);
	void WashCard(BYTE nTACount = 0, BYTE nTAChair = 255);
	void DealAllCardEx(int iNomi, int iDeNomi);
    
	void DealAllCardBySet(int iNomi, int iDeNomi);  // ���ض���
    void DealAllCardTest(int iNomi, int iDeNomi);
    bool DealTestCard(BYTE nChair, BYTE nCard);
    void ResetCardBuf();
    bool DealAllotCard(BYTE nCard, BYTE nIndex);
    
    
    /************************************************************************/
    /*                               �¼Ӽ��޸�For Mobile                     */
    /************************************************************************/
    
    
public:
    void *  UIDelegate;
    //��ȡ����
    PLAYER_DATA *   GetPlayerData();
    BYTE        *   GetCardBuf();       //��ȡ�ƵĻ�����
    STAND_CARD 	*   GetStandCard();		//��ȡ��ҵ���
    bool        *   GetChooseBuf(BYTE chair);     //��ȡָ����������
    BYTE        *   GetTableCards(BYTE chair);    //��ȡ4����ҵ�������
    BYTE            m_nNumTableCards[4];		// 4����ҵ������Ƶ�����

    
    //��������
    Score_Struct *  GetScore();   // �þֵķ���
    HU_CURT     *   GetHuCurt();  //��ȡ����״̬
    BYTE        *   GetNumFan();  //��ȡ���� 
    long        *   GetGangScore(); // �η��������
    long        *   GetHuaZhuScore();
    long        *   GetDaJiaoScore();
    BYTE            GetEndReason();					// ��Ϸ����ԭ��
    long        *   GetSetWinScore();
    
    
    BOOL m_bDingQue;                //��ȱ
	DING_QUE	*   GetDingQue();	// ��ȱ״̬
    
    //private to public
    BYTE m_nChairBanker;				// ׯ�ҵ�λ�ã�
	BYTE m_nCountAllot;					// �����ڼ�����
	OUTED_CARD	m_sOutedCard;			// �մ������	
    SYSTEMPHASE m_sysPhase;				// ��ǰ�׶�״̬
    BYTE m_chairCurrentPlayer;			// ��ǰ������
    BYTE		m_currentCmd;			// ��ǰ������
    BYTE m_nMinFan;                     //�������
    
    BOOL OnInit(bool is_DingQue, bool is_3Fan, bool is_ZimoFan, GuaFengXiaYu is_enGFXY);
    
    BYTE            GetNumTableCards(BYTE chair);   //��ȡ��ҵ�����������
	BYTE        *   GetHuList(BYTE chair);          //��ȡ��ҵ�������
	
};

#endif