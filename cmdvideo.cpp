// cmdvideo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "cmdvideo.h"

#include "net_video_test.h"

 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;


int attenuateRfid(CString ip , int value);
int actionvideo(CString ip , unsigned int chan);
int selnvr() ;
void CALLBACK  draw_fun(PLAY_HANDLE handle,HDC hDc,LONG nUser );
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);
	HW_NET_Init(5198);	

	if (argc <= 2 && argc != 1) {
		printf("usage:cmd ip attenuation\n");
		return 1;

	}
	
	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			if (argc == 1){
               selnvr();
			   getchar();
			   getchar();
			   return 0;

			}
			if ( atoi(argv[2]) < 0){
			    actionvideo(argv[1] , atoi(argv[3]));
				while (1){
				  Sleep(60*1000*60*24);
				}
			}
			else{
                attenuateRfid(argv[1] , atoi(argv[2]));
				printf("����ֵΪ%d\n",atoi(argv[2]));
			}
			
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

int attenuateRfid(CString ip , int value)
{
	USER_HANDLE g_server_id = INVALID_HANDLE; 

   net_video_test* test = NULL;
   UINT64 g_recved_len = 0;
	long g_server_version;
	if( g_server_id == INVALID_HANDLE)
	{
		
		//sprintf(ip,"%s","192.168.3.2");
		g_server_id = HW_NET_Login(ip,5198,"admin","12345");
		if(g_server_id != INVALID_HANDLE)
		{
		//	m_slots.ResetContent();	
			int g_window_count = HW_NET_GetWindowCount(g_server_id);			
			char str[255];
			
			for(int i = 0; i < g_window_count; i++)
			{
				sprintf(str,"ͨ��%d",i + 1);
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

			//AfxMessageBox("��¼�ɹ�!");
			SYSTEMTIME stTime;

            GetLocalTime(&stTime);
			HW_NET_SET_SetSystime(g_server_id, &stTime);
		 
		 
			if(g_server_id != INVALID_HANDLE)
			{
				net_rfid_info_t net_rfid_info;
				memset(&net_rfid_info,0,sizeof(net_rfid_info));
				net_rfid_info.attenuation = value;

				if(!HW_NET_SET_SetRfidConfig(g_server_id,&net_rfid_info))
				{
					printf("����RFID����ʧ��!\n");
					return FALSE;
				}

	                printf("����RFID���óɹ�!\n");

			
			  
			}

		}
		else
		{
			CString tmpstr = "��¼ ";
			printf(tmpstr+ip+" ʧ��!");
			exit(1);
		}
	}

	return TRUE;


}

int actionvideo(CString ip , unsigned int chan)
{
	
//	char ip[255];
	USER_HANDLE g_server_id = INVALID_HANDLE; 

    net_video_test* test = NULL;
    UINT64 g_recved_len = 0;
	long g_server_version;
	if( g_server_id == INVALID_HANDLE)
	{
		
		//sprintf(ip,"%s","192.168.3.2");
		g_server_id = HW_NET_Login(ip,5198,"admin","12345");
		if(g_server_id != INVALID_HANDLE)
		{
		//	m_slots.ResetContent();	
			int g_window_count = HW_NET_GetWindowCount(g_server_id);			
			char str[255];
			
			for(int i = 0; i < g_window_count; i++)
			{
				sprintf(str,"ͨ��%d",i + 1);
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

			//AfxMessageBox("��¼�ɹ�!");
			SYSTEMTIME stTime;

            GetLocalTime(&stTime);
			HW_NET_SET_SetSystime(g_server_id, &stTime);
		 
		 
			if(g_server_id != INVALID_HANDLE)
			{
				test  = new net_video_test(g_server_id,chan);
				test->ip = ip;
				test->channel = chan;
				
				//test->start_preview(NULL,0,1);
				if (false == test->start_rfid(NULL)) exit(1);
			
				//test->register_draw(draw_fun,(long)test);
				//test[startvideocount ] ->enable_audio_preview(1);
			
			  
			}

		}
		else
		{
			CString tmpstr = "��¼ ";
			printf(tmpstr+ip+" ʧ��!");
			//exit(1);
			return -1;
		}
	}


	return 0;
}


int selnvr() 
{
	static char *opt_host_name = "192.168.1.14";        /*�������������� Ĭ��Ϊlocalhost*/
	static char *opt_user_name = "root";        /*���ݿ��û��� Ĭ��Ϊ��ǰ��¼��*/
	static char *opt_password = "anti410";        /*���� Ĭ��Ϊ��*/
	static unsigned int opt_port_num = 0;            /*�˿� ʹ���ڽ�ֵ*/
	static char *opt_socket_name = NULL;    /*socket name (use build-in value)*/
	static char *opt_db_name = "rfvid";        /*���ݿ� ���� Ĭ��Ϊ��*/
	static unsigned int opt_flags = 0; 

	MYSQL *conn;                        /*pointer to connection handler*/
	MYSQL_RES *results;
    MYSQL_ROW record;

	if( (conn = mysql_init(NULL))== NULL){
		fprintf(stderr,"mysql ��ʼ��ʧ��(�������ڴ����)!\n");
		return -1;
	}
	/*���ӵ����ݿ�*/
	if(mysql_real_connect(conn,opt_host_name,opt_user_name,opt_password,
		opt_db_name,opt_port_num,opt_socket_name,opt_flags) == NULL){            
            
			fprintf(stderr,"mysql_real_connect ʧ��:\nError %u (%s)\n",
				mysql_errno(conn),mysql_error(conn));    

			mysql_close(conn);
			return -1;
	}

	printf("db success\n");


	char *selsql="select  nvr.ipaddress , nrrelation.channelNum from nvr inner join nrrelation where nvr.id = nrrelation.nvrid and nrrelation.state = 0";
	if(mysql_query(conn,selsql)){
		        printf("�޷���ѯ���ݿ�\n");
				return -1;
	}
	results = mysql_store_result(conn);
 
	while((record = mysql_fetch_row(results))) {
		printf("%s - %s \n", record[0], record[1]);
		actionvideo(record[0] ,atoi(record[1]));
	}
 
	mysql_free_result(results);
	mysql_close(conn);
	mysql_server_end();
 
	return 0;


}

