// cmdvideo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cmdvideo.h"

#include "net_video_test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
USER_HANDLE g_server_id = INVALID_HANDLE; 

static net_video_test* test = NULL;
static UINT64 g_recved_len = 0;


int actionvideo();
void CALLBACK  draw_fun(PLAY_HANDLE handle,HDC hDc,LONG nUser );
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);
	HW_NET_Init(5198);	

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			actionvideo();
			getchar();
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}


int actionvideo()
{
	
	char ip[255];
	long g_server_version;
	if( g_server_id == INVALID_HANDLE)
	{
		
		sprintf(ip,"%s","192.168.3.3");
		g_server_id = HW_NET_Login(ip,5198,"admin","12345");
		if(g_server_id != INVALID_HANDLE)
		{
		//	m_slots.ResetContent();	
			int g_window_count = HW_NET_GetWindowCount(g_server_id);			
			char str[255];
			
			for(int i = 0; i < g_window_count; i++)
			{
				sprintf(str,"通道%d",i + 1);
			 	//this->m_combochanctrl.AddString(str);
			}
		 	//this->m_combochanctrl.SetCurSel(0);
			
	 
			
			HW_NET_SET_GetDvrVersion(g_server_id,&g_server_version);
/*
			if(VERSION_IPCAM(g_server_version)){
				m_svr_type.AddString("ip camera");
			}else if(VERSION_NVR(g_server_version)){
				m_svr_type.AddString("nvr");
			}else if(VERSION_HIS(g_server_version)
				|| VERSION_HIS_RAILWAY(g_server_version)){
				m_svr_type.AddString("his");
			}
			m_svr_type.SetCurSel(0);
*/
			HW_NET_SET_RegisterAlarm(g_server_id,1);  //m_enable_alarm);

			//SetTimer(TIMER_HEARTBEAR,5000,NULL);

			//AfxMessageBox("登录成功!");
			SYSTEMTIME stTime;

            GetLocalTime(&stTime);
			HW_NET_SET_SetSystime(g_server_id, &stTime);
		 
		 
			if(g_server_id != INVALID_HANDLE)
			{
				test  = new net_video_test(g_server_id,0);
				
				test->start_preview(NULL,0);
			
				//test->register_draw(draw_fun,(long)test);
				//test[startvideocount ] ->enable_audio_preview(1);
			
			  
			}

		}
		else
		{
			CString tmpstr = "登录 ";
			printf(tmpstr+ip+" 失败!");
		}
	}


	return 0;
}


void CALLBACK  draw_fun(PLAY_HANDLE handle,HDC hDc,LONG nUser )
{
	 
	net_video_test *ntest = (net_video_test*) nUser;
		 	 
	//if(g_recved_len > 0)
	//{
	//	CString str;
	//	str.Format("%uKbps / %uKbps",(unsigned long)g_recved_len / 1024 * 8,(unsigned long)g_total_len / 1024 * 8);
		
	//}

	if(ntest->t_rfid_data.len > 0
		&& (time(NULL) - ntest->t_rfid_data.tm) < 3)
	{		
		
		CString str;
		for(int i = 0; i < ntest->t_rfid_data.len; i++)
		{
			CString tmp;
			tmp.Format("%02x",ntest->t_rfid_data.buf[i]);
			str = str + " " + tmp;
		}
		
		
		
		TRACE("this is rfid is %s\n",str);
		
	}


	
}