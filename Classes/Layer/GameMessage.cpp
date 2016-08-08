//
//  GameMessage.cpp
//  xzdd
//
//  Created by  on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameMessage.h"
#include "ParentLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CommonFunction.h"
#include "IOSCommon.h"

#else
#include "../Common/CommonFunction.h"
#endif

using namespace cocos2d;

bool GameMessage::init()
{
	//////////////////////////////
	// 1. super init first
	ccColor4B c = {0,0,0,150};
	if (!CCLayerColor::initWithColor(c) )
	{
		return false;
	}
	selectedGK = 0;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//加入背景
	bjSprite = new CCSprite();
	if (CommonFunction::isIpad()) {
		bjSprite->initWithFile(CONS_Image_BG_Message_Ipad);
	}else {
		bjSprite->initWithFile(CONS_Image_BG_Message);
	}

	bjSprite->setAnchorPoint(ccp(0.5, 0.5));
	bjSprite->setPosition(ccp(size.width * 0.5, size.height * 0.5));
	this->addChild(bjSprite,1,1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if(IOSCommon::IsIpad3())
	{
		bjSprite->setAnchorPoint(ccp(0.5f,0.5f));
		bjSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
		bjSprite->setScale(2.0f);
	}
#endif


	// 加入一个 label
	label = CCLabelTTF::create(CONS_MESSAGE_ReGK,"Thonburi", CommonFunction::GetValueByDev(13));
	label->setPosition( ccp(size.width*0.5,size.height*0.55) );
	this->addChild(label, 2,2);

	// 加入菜单    - 取消
	CCSprite * ci1 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Cancel);
	CCSprite * ci12 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Cancel_2);

	pCancel = CCMenuItemSprite::create(ci1,ci12,NULL,this,
		menu_selector(GameMessage::menuCancelCallback));
	pCancel->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.62,
		CCDirector::sharedDirector()->getWinSize().height*0.31) ); 

	// 加入菜单    - 确认
	CCSprite * ci2 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Confirm);
	CCSprite * ci22 = CCSprite::createWithSpriteFrameName(CONS_Image_Menu_Confirm_2);

	pConfirm = CCMenuItemSprite::create(ci2,ci22,NULL,this,
		menu_selector(GameMessage::menuConfirmCallback));
	pConfirm->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width*0.75,
		CCDirector::sharedDirector()->getWinSize().height*0.31) ); 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if(IOSCommon::IsIpad3())
	{
		pConfirm->setScale(2.0f);
		pCancel->setScale(2.0f);
	}
#endif
	CCMenu* pMenu = CCMenu::create(pCancel,pConfirm,NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 3,3);

	this->setVisible(false);

	return true;
}
void GameMessage::onExit()
{
	bjSprite->release();
	CCLayerColor::onExit();
}

void GameMessage::SetMessageType(MessageType mType, int nStatus)
{
	type = mType;
	char str[128];
	switch (type) {
	case MT_ReGK:
		label->setString(UTEXT(CONS_MESSAGE_ReGK));
		break;
	case MT_ContinueGK:
		{
			GUANKA_STATS gkStats = CommonFunction::GetGuanKaStats(selectedGK);
			char str[500];
			sprintf(str,CONS_STRING_DQJD,
				gkStats.nSet,
				gkStats.nScore,
				gkStats.nFan,
				gkStats.nJiPin);
			label->setString(UTEXT(str));
			break;
		}
	case MT_RunAway:
		{
			label->setString(UTEXT(CONS_MESSAGE_RunAway));
		}
		break;
	case MT_NO_COIN:
		{
			sprintf(str, CONS_MESSAGE_NO_COIN, COIN_NUM_PAY);

			label->setString(UTEXT(str));
		}
		break;
	case MT_SINGLE_FLEE:
		{
			if (nStatus == StatusJipinHu)
			{
				sprintf(str, CONS_MESSAGE_SINGLE_FLEE_JIPIN, COIN_NUM_FLEE_JIPIN);
			}
			else
			{
				sprintf(str, CONS_MESSAGE_SINGLE_FLEE, COIN_NUM_FLEE);
			}
			label->setString(UTEXT(str));
		}
		break;
	case MT_ADD_COIN:
		{
			sprintf(str, CONS_MESSAGE_ADD_COIN, COIN_NUM_PAY);
			label->setString(UTEXT(str));
		}
		break;
	case MT_OPEN_GUANKA:
		{
			if (nStatus == 0)
			{
				sprintf(str, CONS_MESSAGE_OPEN_GUANKA);
			}
			else if (nStatus == 1)
			{
				sprintf(str, CONS_MESSAGE_OPEN_GUANKA_PASS);
			}
			else if(nStatus == 2)
			{
				sprintf(str,CONS_MSG_DELOCK_OPEN_GK);
			}
			label->setString(UTEXT(str));
		}
		break;
	case MT_PAY_COIN_MSG:
		{
			if (nStatus == 1)
			{
				int nCoin = GetIntegerToXML(UD_SINGLE_COIN);

				setVisibleCancel(false);
				sprintf(str, CONS_MESSAGE_PAY_COIN_OK, nCoin);
				label->setString(UTEXT(str));

				CommonFunction::SubmitCoin(nCoin);
			}
		}
		break;
	case MT_PAY_GK_MSG:
		{
			if (nStatus == 1)
			{
				setVisibleCancel(false);
				sprintf(str, CONS_MESSAGE_PAY_GK_OK);
				label->setString(UTEXT(str));
			}
		}
		break;

	case MT_UNPASS_MSG:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_UNPASS);
			label->setString(UTEXT(str));
		}
		break;
	case MT_RECEIVE_COIN:
		{
            //领取金币
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_RECEIVE);
			label->setString(UTEXT(str));
		}
		break;
	case MT_BUY_TOW_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_TOW);
			label->setString(UTEXT(str));
		}
		break;
	case MT_BUY_FOUR_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_FOUR);
			label->setString(UTEXT(str));
		}
		break;
	case MT_BUY_SIX_COIN:
		{
			setVisibleCancel(false);
			sprintf(str, CONS_MESSAGE_SIX);
			label->setString(UTEXT(str));
		}
		break;
	default:
		break;
	}
	this->setVisible(true);
}

//#pragma mark -----------------------菜单动作----------------------

void GameMessage::menuCancelCallback(CCObject* pSender)
{
	CCLOG("click cancel btn");
	((ParentLayer *) this->getParent())->onCancel(type);
}

void GameMessage::menuConfirmCallback(CCObject* pSender)
{
    CCLOG("click confirm btn");
	if ( MT_RECEIVE_COIN == type || MT_BUY_TOW_COIN == type || MT_BUY_FOUR_COIN == type || MT_BUY_SIX_COIN == type)
		this->removeFromParent();
	else
		((ParentLayer *) this->getParent())->onConfirm(type);
}

void GameMessage::setVisibleCancel(bool bVisible)
{
	pCancel->setVisible(bVisible);
}
