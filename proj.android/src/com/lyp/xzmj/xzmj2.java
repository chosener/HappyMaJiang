/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.lyp.xzmj;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import cn.cmgame.billing.api.BillingResult;
import cn.cmgame.billing.api.GameInterface;
import cn.cmgame.billing.api.GameInterface.GameExitCallback;
import cn.cmgame.billing.api.LoginResult;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.Toast;

public class xzmj2 extends Cocos2dxActivity{
	
	public static final int BILLING_1GOAL = 1;			//解锁卡
	public static final int BILLING_5GOAL   = 2;			//延时卡
	public static final int BILLING_10GOAL   = 3;			//提示卡

	private  static native void modifyfor1goal();
	private  static native void modifyfor5goal();
	private  static native void modifyfor10goal();
	
	private Context  mContext;
	private static xzmj2 instance = null;
	GameInterface.IPayCallback payCallback;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		instance = this;
		mContext = xzmj2.this;
		GameInterface.initializeApp(this);
		
	    // 监听登录结果，游戏根据自身业务逻辑，使用移动游戏SDK提供的登录结果
		
	    GameInterface.setLoginListener(this, new GameInterface.ILoginCallback(){
	    	@Override
	    	public void onResult(int i, String s, Object o) {
	    		System.out.println("Login.Result=" + s);
	    		if(i == LoginResult.SUCCESS_EXPLICIT || i==LoginResult.SUCCESS_IMPLICIT){
	    			Toast.makeText(xzmj2.this, "用户登录成功", Toast.LENGTH_SHORT).show();
	    		}
	    		if(i == LoginResult.FAILED_EXPLICIT || i==LoginResult.FAILED_IMPLICIT){
	    			Toast.makeText(xzmj2.this, "用户登录失败", Toast.LENGTH_SHORT).show();
	    		}
	    		if(i == LoginResult.UNKOWN){
	    			Toast.makeText(xzmj2.this, "没有登录", Toast.LENGTH_SHORT).show();
	    		}
	    	}
	    });
	
	    //    GameInterface.doBilling(xzmj2.this,true, true, billingIndex, null, payCallback);
	    payCallback = new GameInterface.IPayCallback() {
	        @Override
	        public void onResult(int resultCode, String billingIndex, Object obj) {
	        	String result = "";
	        	switch (resultCode) {
	            	case BillingResult.SUCCESS:
	            		callJniModify(billingIndex);
	            		result = "购买道具：[" + billingIndex + "] 成功！";
	            		break;
	            	case BillingResult.FAILED:
	            		result = "购买道具：[" + billingIndex + "] 失败！";
	            		break;
	            	default:
	            		result = "购买道具：[" + billingIndex + "] 取消！";
	            		break;
	        	}
	        	
	        	Toast.makeText(xzmj2.this, result, Toast.LENGTH_SHORT).show();
	        }
	    };
   
	}
    
    public void callJniModify(String billingIndex)
    {
    	if(billingIndex.equals("003")){
    		modifyfor1goal();
    	}else if(billingIndex.equals("004")){
    		modifyfor5goal();
    	}else if(billingIndex.equals("005")){
    		modifyfor10goal();
    	}
    }

    public Handler handler = new Handler() {
		public void handleMessage(Message msg) {
			if (msg.what == BILLING_1GOAL) {
				showBillingDialog(mContext, "003", payCallback);
			} else if (msg.what == BILLING_5GOAL) {
				showBillingDialog(mContext, "004", payCallback);
			} else if (msg.what == BILLING_10GOAL) {
				showBillingDialog(mContext, "005", payCallback);
			}
			
			super.handleMessage(msg);
		}
	};
	
	public void showBillingDialog(Context context, String billingIndex, GameInterface.IPayCallback payCallback) {
		
		instance.mGLSurfaceView.queueEvent(new Runnable() {
			public void run() {
				System.out.println("dsw pauseTimeProgess 111");
				//pauseTimeProgess();
			}
		});
		
		GameInterface.doBilling(xzmj2.this,true, true, billingIndex, null, payCallback);
	}

    public void exitGame() {

    	GameInterface.exit(this, new GameExitCallback() {
    		@Override
    		public void onConfirmExit() {
    			xzmj2.this.finish();
    		}
  		
    		@Override
    		public void onCancelExit() {
    			Toast.makeText(xzmj2.this, "取消", Toast.LENGTH_SHORT).show();			
    		}
  		});
  }
    
    public static Object getInstance() {
		return instance;
	}
    
    public void send_billing_for_get_1Goal() {
		
		System.out.println("you have enter send_billing_for_time_card");
		if (instance != null) {
			Message msg = new Message();
			msg.what = BILLING_1GOAL;
			instance.handler.sendMessage(msg);
		}
	}

	public void send_billing_for_get_5Goal() {
		
		System.out.println("you have enter send_billing_for_hint_card");
		if (instance != null) {
			Message msg = new Message();
			msg.what = BILLING_5GOAL;
			instance.handler.sendMessage(msg);
		}
	}

	public void send_billing_for_get_10Goal() {
		System.out.println("in send_billing_for_gifpack");
		if (instance != null) {
			Message msg = new Message();
			msg.what = BILLING_10GOAL;
			instance.handler.sendMessage(msg);
		}
	}
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// xzmj2 should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");

    }     
}
