#ifndef play_include_h
#define play_include_h

#include "play_err.h"
#include "play_type.h"

#ifdef WIN32
#define HOWELL_PLAY_API	extern "C"__declspec(dllexport)
#else
#define HOWELL_PLAY_API extern "C" 
#endif

typedef unsigned long PLAY_HANDLE;
typedef unsigned long MOTION_HANDLE;

typedef void (CALLBACK draw_callback)(PLAY_HANDLE handle,
									  HDC hDc,
									  LONG nUser);
typedef void (CALLBACK yuv_callback)(PLAY_HANDLE handle, 
									 const unsigned char* yuv,
									 int len,
									 int width,
									 int height,
									 INT64 time,
									 long user);

typedef void (CALLBACK yuv_callback_ex)(PLAY_HANDLE handle,
									 const unsigned char* y,
									 const unsigned char* u,
									 const unsigned char* v,
									 int y_stride,
									 int uv_stride,
									 int width,
									 int height,
									 INT64 time,
									 long user);

typedef void (CALLBACK stream_callback)(PLAY_HANDLE handle,
										INT64 time,
										int type,
										char* buf,
										int len,
										long user);



#ifndef INVALID_HANDLE
#define  INVALID_HANDLE (-1)
#endif

//分配句柄
//hwplay_open_stream使用流方式播放。
//hwplay_open_local_file播放本地文件
HOWELL_PLAY_API PLAY_HANDLE __stdcall hwplay_open_stream(const char* head,int head_len,int buf_len,int open_mode);
HOWELL_PLAY_API PLAY_HANDLE __stdcall hwplay_open_local_file(const char* file_name);

//开始(结束)播放,必须在hwplay_open_stream或hwplay_open_local_file之后调用
HOWELL_PLAY_API BOOL __stdcall hwplay_play(PLAY_HANDLE handle, HWND hWnd);
HOWELL_PLAY_API BOOL __stdcall hwplay_stop(PLAY_HANDLE handle);

//如没有特殊说明,必须在hwplay_play()之后调用

//通用接口
HOWELL_PLAY_API BOOL __stdcall hwplay_open_sound(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_close_sound(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_is_sound_open(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_refresh(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_save_to_bmp(PLAY_HANDLE handle,const char* bmp_path);
HOWELL_PLAY_API BOOL __stdcall hwplay_save_to_jpg(PLAY_HANDLE handle,const char* jpg_path,int quality);
HOWELL_PLAY_API BOOL __stdcall hwplay_save_to_jpg_buf(PLAY_HANDLE handle,char* buf,int len,int* ret_len,int quality);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_yuv_source_data(PLAY_HANDLE handle,int left,int top,int w,int h,char* dst_buf,int buf_len);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_video_size(PLAY_HANDLE handle,int* w, int* h);
HOWELL_PLAY_API BOOL __stdcall hwplay_register_draw_fun(PLAY_HANDLE handle,draw_callback* fun,long user_data);
HOWELL_PLAY_API BOOL __stdcall hwplay_register_yuv_callback_ex(PLAY_HANDLE handle,yuv_callback_ex* fun,long user_data);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_played_msec(PLAY_HANDLE handle,int* msec);
HOWELL_PLAY_API BOOL __stdcall hwplay_throw_b(PLAY_HANDLE handle,int throw_num);
HOWELL_PLAY_API BOOL __stdcall hwplay_throw_p(PLAY_HANDLE handle,BOOL bthrow);
HOWELL_PLAY_API BOOL __stdcall hwplay_auto_adjust_size(PLAY_HANDLE handle,BOOL bauto);
HOWELL_PLAY_API BOOL __stdcall hwplay_zoom_rect(PLAY_HANDLE handle,BOOL benable,RECT* dst,RECT* src);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_framenum_in_buf(PLAY_HANDLE handle,int* frame_num);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_max_framenum_in_buf(PLAY_HANDLE handle,int* max_frame_num);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_max_framenum_in_buf(PLAY_HANDLE handle,int max_frame_num);

//文件方式专用接口
HOWELL_PLAY_API BOOL __stdcall hwplay_pause(PLAY_HANDLE handle,BOOL bpause);
HOWELL_PLAY_API BOOL __stdcall hwplay_is_pause(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_speed(PLAY_HANDLE handle,float* speed);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_speed(PLAY_HANDLE handle,float speed);
HOWELL_PLAY_API BOOL __stdcall hwplay_step_froward(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_step_back(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_pos(PLAY_HANDLE handle,int* pos);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_pos(PLAY_HANDLE handle,int pos);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_total_msec(PLAY_HANDLE handle,int* totalmsec);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_current_frame(PLAY_HANDLE handle,int* frame_num);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_total_frame(PLAY_HANDLE handle,int* frame_num);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_frame(PLAY_HANDLE handle,int frame_num);

//流方式专用接口
HOWELL_PLAY_API BOOL __stdcall hwplay_input_data(PLAY_HANDLE handle, const char* buf,int len);
HOWELL_PLAY_API BOOL __stdcall hwplay_clear_stream_buf(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_stream_buf_len(PLAY_HANDLE handle, int* buf_len);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_stream_buf_remain(PLAY_HANDLE handle,int* buf_remain);
HOWELL_PLAY_API BOOL __stdcall hwplay_realloc_stream_buf_len(PLAY_HANDLE handle, int new_buf_len);
HOWELL_PLAY_API BOOL __stdcall hwplay_clear_framenum_in_buf(PLAY_HANDLE handle);

//切割,合并文件接口
HOWELL_PLAY_API BOOL __stdcall hwplay_start_cut_file(const char* src_file,int beg_frame,int end_frame,const char* dst_file);
HOWELL_PLAY_API BOOL __stdcall hwplay_start_cut_file_by_time(const char* src_file,int beg_sec,int end_sec,const char* dst_file);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_cut_pos(int* pos);
HOWELL_PLAY_API BOOL __stdcall hwplay_stop_cut_file();
HOWELL_PLAY_API BOOL __stdcall hwplay_start_join_file(const char* src_file,const char* dst_file);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_join_pos(int* pos);
HOWELL_PLAY_API BOOL __stdcall hwplay_stop_join_file();

//智能搜索支持
HOWELL_PLAY_API MOTION_HANDLE __stdcall hwplay_start_motion_search(PLAY_HANDLE handle,RECT search_rt);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_next_motion(MOTION_HANDLE handle,motion_node* mt_node,int* err_code);
HOWELL_PLAY_API BOOL __stdcall hwplay_stop_motion_search(MOTION_HANDLE handle);

//osd
HOWELL_PLAY_API BOOL __stdcall hwplay_get_osd(PLAY_HANDLE handle, SYSTEMTIME* sys);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_osd(PLAY_HANDLE handle,SYSTEMTIME sys);
HOWELL_PLAY_API BOOL __stdcall hwplay_get_frame_osd(PLAY_HANDLE handle,int frame,SYSTEMTIME* sys);

//播放模式
HOWELL_PLAY_API BOOL  __stdcall hwplay_init_draw(BOOL used3d);

//图像处理
//色彩调节,参数范围(0-100)
HOWELL_PLAY_API BOOL  __stdcall hwplay_start_color_adjust(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_color_value(PLAY_HANDLE handle,int bright,int contrast,int saturation,int hue);
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_color_value(PLAY_HANDLE handle,int* bright,int* contrast,int* saturation,int* hue);
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_color_default_value(PLAY_HANDLE handle,int* bright,int* contrast,int* saturation,int* hue);
HOWELL_PLAY_API BOOL  __stdcall hwplay_stop_color_adjust(PLAY_HANDLE handle);
//黑白模式
HOWELL_PLAY_API BOOL  __stdcall hwplay_start_balck_mode(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL  __stdcall hwplay_stop_black_mode(PLAY_HANDLE handle);
//锐度调节,参数范围(0-100)
HOWELL_PLAY_API BOOL  __stdcall hwplay_start_sharpen_adjust(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_sharpen_value(PLAY_HANDLE handle,int sharpen);
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_sharpen_value(PLAY_HANDLE handle,int* sharpen);
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_sharpen_default_value(PLAY_HANDLE handle,int* sharpen);
HOWELL_PLAY_API BOOL  __stdcall hwplay_stop_sharpen_adjust(PLAY_HANDLE handle);
//梯度调节
HOWELL_PLAY_API BOOL  __stdcall hwplay_start_gradient_adjust(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_gradient_mode(PLAY_HANDLE handle,BOOL bcolor,BOOL bcartoon);
HOWELL_PLAY_API BOOL  __stdcall hwplay_stop_gradient_adjust(PLAY_HANDLE handle);
//逆光处理 参数范围(0-100)
HOWELL_PLAY_API BOOL  __stdcall hwplay_start_blacklighting(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_blacklighting_value(PLAY_HANDLE handle,int value);
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_blacklighting_value(PLAY_HANDLE handle,int* value);
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_default_blacklighting_value(PLAY_HANDLE handle,int* value);
HOWELL_PLAY_API BOOL  __stdcall hwplay_stop_blacklighting(PLAY_HANDLE handle);

//显示比例 (因为视频编码尺寸不一定与实际显示的匹配，所以让用户来自己选择
//比如ipcam 子码流虽然是704 * 576的，但是实际却需要以16:9来显示。
//scale = "16:9" or scale = "4:3" or scale = "unknown"(显示整个窗口)
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_scale(PLAY_HANDLE handle,const char* scale);

//获取/设置yuv最大输出缓存帧数
//当前值支持1-100
//默认值 流方式下:PLAY_LIVE-1;PLAY_FILE-25  文件方式:25
HOWELL_PLAY_API BOOL __stdcall hwplay_get_max_framenum_out_buf(PLAY_HANDLE handle,int* max_frame_num);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_max_framenum_out_buf(PLAY_HANDLE handle,int max_frame_num);

//定位到毫秒
HOWELL_PLAY_API BOOL __stdcall hwplay_set_played_msec(PLAY_HANDLE handle,int msec);

//获取帧率
HOWELL_PLAY_API BOOL __stdcall hwplay_get_framerate(PLAY_HANDLE handle,int* framerate);

//声音
//范围为0-0xffffffff,低16位为左声道,高16位为右声道
//调整的是波形的音量
HOWELL_PLAY_API BOOL __stdcall hwplay_get_audio_volume(PLAY_HANDLE handle,unsigned int* volume);
HOWELL_PLAY_API BOOL __stdcall hwplay_set_audio_volume(PLAY_HANDLE handle,unsigned int volume);

//文件结束消息通知
//消息中的WPARAM为 PLAY_HANDLE。
//必须在hwplay_open_local_file()之后,hwplay_play()之前调用，
//否则，如果文件过小，将无法收到消息
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_file_end_msg(PLAY_HANDLE handle,HWND hWnd,unsigned int msg);

//主动判断文件是否播放完毕
//与hwplay_set_file_end_msg功能类似
HOWELL_PLAY_API BOOL  __stdcall hwplay_is_file_end(PLAY_HANDLE handle);

//帧索引结束消息通知
//消息中的WPARAM为 PLAY_HANDLE,LPARAM为帧索引建立花费的时间(ms)
//帧索引在调用hwplay_open_local_file()时开始建立，如果调用 hwplay_set_idx_end_msg时,
//帧索引已经完成，会马上收到消息，且耗费时间为0
HOWELL_PLAY_API BOOL  __stdcall hwplay_set_idx_end_msg(PLAY_HANDLE handle,HWND hWnd,unsigned int msg);

//主动判断帧索引是否建立完毕
//与hwplay_set_idx_end_msg功能类似
HOWELL_PLAY_API BOOL  __stdcall hwplay_is_idx_end(PLAY_HANDLE handle);

//画中画支持(内部测试)
//最多支持5个区域
//如果area_idx=0,表明在hwplay_play()中显示的窗口进行设置，忽略hwnd
//src表示yuv数据的坐标,如果src=NULL,表示显示整个原始图像
//dst表示显示窗口的坐标，如果dst=NULL,表示在整个窗口中显示
//如果enable=FALSE,hwnd,src,dst将不做判断
HOWELL_PLAY_API BOOL  __stdcall hwplay_enable_area(PLAY_HANDLE handle,int area_idx,BOOL enable,HWND hwnd,RECT* src,RECT* dst);


//获取指定帧的信息(可以用来切割文件,参考play_demo)
//如果mode==0,value表示帧序号(从1开始)
//如果mode==1,value表示时间(ms)
HOWELL_PLAY_API BOOL  __stdcall hwplay_get_frame_info(PLAY_HANDLE handle,int mode,unsigned int value,frame_info* fr);

//编码数据回调
HOWELL_PLAY_API BOOL  __stdcall hwplay_register_stream_callback(PLAY_HANDLE handle,stream_callback* fun,long user);

//原始数据回调
typedef void (CALLBACK source_callback)(PLAY_HANDLE handle,
										int type,//0-音频,1-视频
										const char* buf,//数据缓存,如果是视频，则为YV12数据，如果是音频则为pcm数据
										int len,//数据长度
										unsigned long timestamp,//时标,单位为毫秒
										long sys_tm,//osd 时间(1970到现在的UTC时间)
										int w,//视频宽
										int h,//视频高
										int framerate,//视频帧率
										int au_sample,//音频采样率
										int au_channel,//音频通道数
										int au_bits,//音频位宽
										long user);
HOWELL_PLAY_API BOOL  __stdcall hwplay_register_source_data_callback(PLAY_HANDLE handle,source_callback* fun,long user);

//获取错误
HOWELL_PLAY_API int	  __stdcall hwplay_get_last_error();

//-------------------------------------------无效函数-----------------------------------------------//
HOWELL_PLAY_API PLAY_HANDLE __stdcall hwplay_open_net_file(const char*ip,short port,const char* log_name,const char* log_psw,int slot,SYSTEMTIME beg,SYSTEMTIME end);
HOWELL_PLAY_API PLAY_HANDLE __stdcall hwplay_open_net_live(const char*ip,short port,const char* log_name,const char* log_psw,int slot,int is_sub);
HOWELL_PLAY_API BOOL __stdcall hwplay_register_yuv_callback(PLAY_HANDLE handle,yuv_callback* fun,long user_data);
HOWELL_PLAY_API BOOL __stdcall hwplay_zoom(PLAY_HANDLE handle,BOOL bzoom);
HOWELL_PLAY_API BOOL __stdcall hwplay_is_zoom(PLAY_HANDLE handle);
HOWELL_PLAY_API BOOL __stdcall hwplay_control_zoom(PLAY_HANDLE handle,int command);
HOWELL_PLAY_API BOOL __stdcall hwplay_save_hwnd_to_file(PLAY_HANDLE handle,const char* file_name,int file_type,RECT* rt);
HOWELL_PLAY_API BOOL __stdcall hwplay_save_src_to_file(PLAY_HANDLE handle,const char* file_name,int file_type,RECT* rt);
HOWELL_PLAY_API BOOL __stdcall hwplay_wait_sync(PLAY_HANDLE handle,BOOL bwait);
//---------------------------------------------------------------------------------------------------//


#endif
