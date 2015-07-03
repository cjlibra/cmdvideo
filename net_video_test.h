#ifndef net_video_test_include_h
#define net_video_test_include_h

#include "play_def.h"
#pragma comment(lib,"play_sdk.lib")
#include "howellnetsdk.h"
#pragma comment(lib,"hwclient.lib")
#include "ts_convert_def.h"
#pragma comment(lib,"ts_convert.lib")
#include "flv_convert_def.h"
#pragma comment(lib,"flv_convert.lib")
#include "StdAfx.h"

#include "mysql.h"
#pragma comment(lib,"mysqlclient.lib")
 

typedef struct {
	long len;
	long type; //0-bbp frame,1-i frame,2-audio
	INT64 time_stamp;
	long tag;
	long sys_time;
	//long reserve[1];
}stream_head;

typedef struct 
{
	int type; //0 - extra_data backfocal_pos
	int len;
}extra_data_head;

typedef struct 
{
	int tm;
	int len;
	unsigned char buf[1024];
}rfid_data_t;

rfid_data_t g_rfid_data;

class net_video_test
{
public:
	rfid_data_t t_rfid_data;
	CString  ip;
	unsigned int channel;
	MYSQL *dbconn;
public:
	net_video_test(USER_HANDLE handle,int slot)
		:m_s_handle(INVALID_HANDLE),m_l_handle(handle),m_slot(slot)
		,m_p_handle(INVALID_HANDLE),m_bsaveing(false),m_hfile(INVALID_HANDLE_VALUE)
	{	
		 
		t_rfid_data.len  = 0;
		dbconn = open_db();
	}

	~net_video_test()
	{
		stop_preview();
		if (dbconn != NULL){
			mysql_close(dbconn); 
			mysql_library_end();

		}
	}

	bool is_preview()
	{
		return m_s_handle != INVALID_HANDLE && m_p_handle != INVALID_HANDLE;	
	}

	bool set_scale(const char* scale)
	{
		if(!is_preview())
		{
			return false;
		}
		
		hwplay_set_scale(m_p_handle,scale);
		return true;
	}

	bool start_nvr_preview(HWND hWnd)
	{
		if(is_preview())
		{
			return false;
		}
		
		m_hWnd = hWnd;
		
		m_last_stream_tm = time(NULL);

		m_s_handle = HW_NET_OpenVideoEx3(m_l_handle,m_slot,0,0,data_process,(long)this,1);

		if(m_s_handle == INVALID_HANDLE)
		{
			return false;
		}
		
		char head[40];
		int len = 40;
		BOOL ret = HW_NET_GetVideoHead(m_s_handle,head,40,&len);
		
		m_p_handle = hwplay_open_stream(head,len,1024 * 1024,PLAY_LIVE);
		if(m_p_handle == INVALID_HANDLE)
		{
			HW_NET_CloseVideo(m_s_handle);
			m_s_handle = INVALID_HANDLE;	
			return false;
		}
		
		if(hwplay_play(m_p_handle,m_hWnd))
		{
			//AfxMessageBox("play success");
		}
		else
		{
			printf("play failed");
		}
		//hwplay_set_max_framenum_in_buf(m_p_handle,2);
		hwplay_register_yuv_callback_ex(m_p_handle,yuv_fun,(long)this);
		
		HW_NET_SET_ForceIFrame(m_l_handle,m_slot);//强制I帧		
		
		return true;		
	}
	bool start_rfid(HWND hWnd)
	{
		m_hWnd = hWnd;
		 m_s_handle = HW_NET_OpenVideoEx3(m_l_handle,m_slot,0,0,data_process_rfid,(long)this,0);
		//m_s_handle = HW_NET_OpenVideoEx2(m_l_handle,m_slot,1,0,data_process_rfid,(long)this);
		if(m_s_handle == INVALID_HANDLE)
		{
			printf("INVALID_HANDLE\n");
			return false;
		}
		//hwplay_register_stream_callback(m_l_handle,hw_stream_callback,(long)this);
		return true;	
	}

	bool start_preview(HWND hWnd,int connect_mode,int is_sub = 0)
	{
		if(is_preview())
		{
			return false;
		}

		m_hWnd = hWnd;

		m_last_stream_tm = time(NULL);
#if 0
		if(is_sub == 0)
		{
			m_s_handle = HW_NET_OpenVideoEx(m_l_handle,m_slot,data_process,(long)this);
		}else{
			m_s_handle = HW_NET_OpenSubVideoEx(m_l_handle,m_slot,data_process,(long)this);
		}
#else
		m_s_handle = HW_NET_OpenVideoEx2(m_l_handle,m_slot,is_sub,connect_mode,data_process,(long)this);
#endif
		
		if(m_s_handle == INVALID_HANDLE)
		{
			return false;
		}

		char head[40];
		int len = 40;
		BOOL ret = HW_NET_GetVideoHead(m_s_handle,head,40,&len);
		 
		m_p_handle = hwplay_open_stream(head,len,1024 * 1024,PLAY_LIVE);
		
		if(m_p_handle == INVALID_HANDLE)
		{
			HW_NET_CloseVideo(m_s_handle);
			m_s_handle = INVALID_HANDLE;	
			return false;
		}
	 
		if(hwplay_play(m_p_handle,m_hWnd))
		{
			//AfxMessageBox("play success");
		}
		else
		{
			printf("play failed");
		} 
		 
		//hwplay_set_max_framenum_in_buf(m_p_handle,2);
		//hwplay_register_yuv_callback_ex(m_p_handle,yuv_fun,(long)this);

		hwplay_register_stream_callback(m_p_handle,hw_stream_callback,(long)this);
		
		HW_NET_SET_ForceIFrame(m_l_handle,m_slot);//强制I帧		

		return true;		
	}

	void stop_preview()
	{
		if(is_preview())
		{
			stop_save_to_file();

			hwplay_stop(m_p_handle);
			m_p_handle = INVALID_HANDLE;

			HW_NET_CloseVideo(m_s_handle);
			m_s_handle = INVALID_HANDLE;		
		}
	}

	bool is_zoom()
	{
		return is_preview() && hwplay_is_zoom(m_p_handle);
	}	

	bool register_draw(draw_callback* fun,long draw_user)
	{
		if(!is_preview())
		{
			return false;
		}

		return hwplay_register_draw_fun(m_p_handle,fun,draw_user) == TRUE;		
	}

	PLAY_HANDLE handle()
	{
		return m_p_handle;
	}

	HWND window_handle()
	{
		if(!is_preview())
		{
			return NULL;
		}

		return m_hWnd;
	}

	int remote_slot()
	{
		return m_slot;
	}

	USER_HANDLE user_handle()
	{
		return m_s_handle;
	}

	bool enable_color_adjust(bool benable)
	{
		if(!is_preview())
		{
			return false;
		}
		if(benable)
		{
			hwplay_start_color_adjust(m_p_handle);
		}else{
			hwplay_stop_color_adjust(m_p_handle);
		}

		return true;
	}

	bool enable_blacklighting(bool benable)
	{
		if(!is_preview())
		{
			return false;
		}
		if(benable)
		{
			hwplay_start_blacklighting(m_p_handle);
		}
		else
		{
			hwplay_stop_blacklighting(m_p_handle);
		}

		return true;
	}

	bool set_blacklighting_value(int value)
	{
		if(!is_preview())
		{
			return false;
		}
		hwplay_set_blacklighting_value(m_p_handle,value);

		return true;
	}

	bool get_blacklighting_value(int& value)
	{
		if(!is_preview())
		{
			return false;
		}
		
		hwplay_get_blacklighting_value(m_p_handle,&value);
		return true;
	}

	bool set_color(int bright,int contrast,int saturation,int hue)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_set_color_value(m_p_handle,bright,contrast,saturation,hue);
		return true;
	}

	bool get_color(int& bright,int& contrast,int& saturation,int&hue)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_get_color_value(m_p_handle,&bright,&contrast,&saturation,&hue);
		return true;
	}

	bool enable_sharpen(bool benable)
	{
		if(!is_preview())
		{
			return false;
		}

		if(benable)
		{
			hwplay_start_sharpen_adjust(m_p_handle);
		}
		else
		{
			hwplay_stop_sharpen_adjust(m_p_handle);
		}
		return  true;
	}

	bool set_sharpen_value(int value)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_set_sharpen_value(m_p_handle,value);
		return true;
	}

	bool get_sharpen_value(int& value)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_get_sharpen_value(m_p_handle,&value);
		return true;
	}

	bool set_max_yuv_buf(int buf)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_set_max_framenum_in_buf(m_p_handle,buf);	
		return true;
	}

	bool get_max_yuv_buf(int& buf)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_get_max_framenum_in_buf(m_p_handle,&buf);
		return true;
	}

	bool get_cur_yuv_buf(int& buf)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_get_framenum_in_buf(m_p_handle,&buf);
		return true;
	}

	bool set_volume(unsigned int volume)
	{
		if(!is_preview())
		{
			return false;
		}
		
		hwplay_set_audio_volume(m_p_handle,volume);
		return true;
	}

	bool save_to_bmp(const char* bmp)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_save_to_bmp(m_p_handle,bmp);
		return true;
	}

	bool save_to_jpg(const char* jpg,int quality)
	{
		if(!is_preview())
		{
			return false;
		}

		hwplay_save_to_jpg(m_p_handle,jpg,quality);
		return true;
	}

	bool save_to_file(const char* file_name)
	{
		if(!is_preview()
			|| m_bsaveing)
		{
			return false;
		}


#if SAVE_TS_FILE
		m_ts_convert_h = ts_convert_start(file_name,25);
		if(m_ts_convert_h != -1)
		{
			m_bsaveing = true;
		}		
		return m_bsaveing;
#else
#if SAVE_FLV_FILE
		m_flv_convert_h = flv_convert_start(file_name,25);
		if(m_flv_convert_h != -1)
		{
			m_bsaveing = true;
		}		
		return m_bsaveing;
#else		
		m_hfile = CreateFile(file_name,
			GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if(m_hfile == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		char head[40];
		int len = 40;
		BOOL ret = HW_NET_GetVideoHead(m_s_handle,head,40,&len);
		if(!ret)
		{
			CloseHandle(m_hfile);
			m_hfile = INVALID_HANDLE_VALUE;
			return false;
		}

		DWORD write_num;
		WriteFile(m_hfile,head,len,&write_num,NULL);
		m_bsaveing = true;
		return true;
#endif
#endif	
	}

	void stop_save_to_file()
	{
		if(m_bsaveing)
		{
			m_bsaveing = false;
#if SAVE_TS_FILE
			ts_convert_stop(m_ts_convert_h);
#else
#if SAVE_FLV_FILE
			flv_convert_stop(m_flv_convert_h);
#else
			CloseHandle(m_hfile);
			m_hfile = INVALID_HANDLE_VALUE;
#endif
#endif
		}
	}

	bool enable_audio_preview(bool benable)
	{
		if(!is_preview())
		{
			return false;
		}

		if(benable)
		{
			hwplay_open_sound(m_p_handle);

			hwplay_set_audio_volume(m_p_handle,0xffffffff);
		}else{
			hwplay_close_sound(m_p_handle);
		}		
		return true;
	}

	bool get_video_size(int& w,int& h)
	{
		if(!is_preview())
		{
			return false;
		}

		return hwplay_get_video_size(m_p_handle,&w,&h) ? true : false;
	}

	bool state_ok()
	{
		time_t cur = time(NULL);

		TRACE("cur %d,last %d\n",cur,m_last_stream_tm);
		return (cur - m_last_stream_tm) <= 3;
	}

private:
	REAL_HANDLE m_s_handle;
	USER_HANDLE m_l_handle;
	PLAY_HANDLE m_p_handle;
	int m_slot;
	HWND m_hWnd;
	HANDLE m_hfile;
	bool m_bsaveing;
	TS_CONVERT_HANDLE m_ts_convert_h;
	FLV_CONVERT_HANDLE m_flv_convert_h;
	time_t m_last_stream_tm;

private:
	static void CALLBACK data_process(REAL_HANDLE  s_handle,char* buf,int len,int video_type,long user)
	{		
		net_video_test* test = (net_video_test*)(user);
		test->m_last_stream_tm = time(NULL);
		if(video_type != HW_FRAME_VIDEO_HEAD)
		{							
			hwplay_input_data(test->m_p_handle,buf,len);

			if(test->m_bsaveing)
			{				
#if SAVE_TS_FILE
				ts_convert_input(test->m_ts_convert_h,buf,len);
#else
#if SAVE_FLV_FILE
				flv_convert_input(test->m_flv_convert_h,buf,len);
#else
				DWORD write_num;
				WriteFile(test->m_hfile,buf,len,&write_num,NULL);
#endif
#endif
			}
		}	
	}	

	static void CALLBACK yuv_fun(PLAY_HANDLE handle,
		const unsigned char* y,
		const unsigned char* u,
		const unsigned char* v,
		int y_stride,
		int uv_stride,
		int width,
		int height,
		INT64 time,
		long user)
	{
		TRACE("on yuv come,y_stride %d,uv_stride %d,width %d,height %d,time %x\n",
			y_stride,uv_stride,width,height,time);
	}


	static void CALLBACK data_process_rfid(REAL_HANDLE s_handle,char* buf,int len,int video_type,long user) 
    {  
        stream_head* head = (stream_head*)buf;
        char* extra_data = buf + sizeof(stream_head);
        int data_len = head->len - sizeof(stream_head);
        if(head->type == 8)
       {
           //这里调用hw_stream_callback()函数(以前该函数是播放库的回调，现在请手动调用就可以了)
		   hw_stream_callback( s_handle,	0, head->type, extra_data , data_len, user);
       }
    }


	static void CALLBACK hw_stream_callback(PLAY_HANDLE handle,
		INT64 stime,
		int type,

		char* buf,
		int len,
		long user)
	{	
		net_video_test *ptest = (net_video_test*) user;
		if(type == 8)
		{			
			//extra data	
			extra_data_head* extra_head = (extra_data_head*)buf;
			if(extra_head->type == 2)
			{
				//
				//extra_data* e = (extra_data*)(buf + sizeof(extra_data_head));
				//g_extra = *e;

				char* rfid_data = buf + sizeof(extra_data_head);
				int rfid_data_len = len - sizeof(extra_data_head);

				TRACE(">>>>>>>>>>>>>>>%d\n",rfid_data_len);

				g_rfid_data.len = rfid_data_len;				
				g_rfid_data.tm = time(NULL);
				memcpy(g_rfid_data.buf,rfid_data,rfid_data_len);
				ptest->t_rfid_data.len = rfid_data_len;				
				ptest->t_rfid_data.tm = g_rfid_data.tm;
				memcpy(ptest->t_rfid_data.buf,rfid_data,rfid_data_len);

				for (int i=0;i<rfid_data_len;i++){
				  printf("%02X ",*(unsigned  char *)(rfid_data+i));
				}
				printf("\n");
				fflush(stdout);
				
				ptest->insertdata(ptest->dbconn,rfid_data);
			}
		}
	}

public:
		int insertdata(MYSQL *dbconn ,char *rfid)
		{
			
			CString sql = "insert into monitorlog(begintime,endtime,cardid,readerid) select '?1' ,'?2', card.id,nrrelation.readerid from card inner join nrrelation  join nvr where nvr.ipaddress = '?3' and card.UID = '?4' and nrrelation.channelNum = ?5 and nvr.id = nrrelation.nvrid";
			time_t  t;  
			struct tm  *tp; 
			t=time(NULL); 
			tp=localtime(&t);  
			CString nowtime;
			CString onechar;
			CString rfidstr;
			
			nowtime.Format("%d-%02d-%02d %02d:%02d:%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,tp->tm_hour,tp->tm_min,tp->tm_sec);
			//printf("%d/%d/%d/n",tp->tm_mon+1,tp->tm_mday,tp->tm_year+1900);  
			//printf("%d:%d:%d/n",tp->tm_hour,tp->tm_min,tp->tm_sec); 
			
			printf(nowtime);
			for (int i=0;i<4;i++){
				onechar.Format("%02X",*((unsigned char *)(rfid+8+i)));
				rfidstr = rfidstr + onechar;

			}
			printf(rfidstr);
			CString tmpstr;
			tmpstr.Format("%d",channel);
			sql.Replace("?1",nowtime);
			sql.Replace("?2",nowtime);
			sql.Replace("?3",ip);
			sql.Replace("?4",rfidstr);
			sql.Replace("?5",tmpstr);
			printf(sql);

			if(mysql_query(dbconn,sql)){
				// printf(dbconn,"执行插入失败");
				//printf("error fail\n");
				printf("%s:\nError %u (%s)\n","执行插入失败",mysql_errno(dbconn),mysql_error(dbconn));
				dbconn = open_db();
				return -1;
			}else{
				unsigned int lines = (unsigned long)mysql_affected_rows(dbconn);
				if (lines > 0 ){
				    printf("插入成功,受影响行数:%lu\n",lines);
				}
				
			}
 
			return 0;


		}

		MYSQL * open_db(  )
		{
			static char *opt_host_name = "192.168.1.14";        /*服务器主机名称 默认为localhost*/
			static char *opt_user_name = "root";        /*数据库用户名 默认为当前登录名*/
			static char *opt_password = "anti410";        /*密码 默认为空*/
			static unsigned int opt_port_num = 0;            /*端口 使用内建值*/
			static char *opt_socket_name = NULL;    /*socket name (use build-in value)*/
			static char *opt_db_name = "rfvid";        /*数据库 名称 默认为空*/
			static unsigned int opt_flags = 0; 

			static MYSQL *conn;                        /*pointer to connection handler*/


			if( (conn = mysql_init(NULL))== NULL){
				fprintf(stderr,"mysql 初始化失败(可能是内存溢出)!\n");
				return NULL;
			}
			/*连接到数据库*/
			if(mysql_real_connect(conn,opt_host_name,opt_user_name,opt_password,
				opt_db_name,opt_port_num,opt_socket_name,opt_flags) == NULL){            
            
					fprintf(stderr,"mysql_real_connect 失败:\nError %u (%s)\n",
						mysql_errno(conn),mysql_error(conn));    

					mysql_close(conn);
					return NULL;
			}

			printf("db success\n");
			return conn;
			return 0;

		}


};
#endif