package com.lyp.xzmj;

import android.app.Application;

public class cmgameApplication extends Application {

	public void onCreate() {
		try {
			 System.loadLibrary("megjb");
		} catch(Exception e){
			System.out.println(e.getMessage());
		}
	}
}
