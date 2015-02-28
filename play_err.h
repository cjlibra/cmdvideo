#ifndef play_err_include_h
#define play_err_include_h

//错误码
#define ERR_HWPLAY_SUCCESS			(0x0)		//正确
#define ERR_HWPLAY_ORDER			(0x1)		//调用顺序错误
#define ERR_HWPLAY_INVALID_HANDLE	(0x2)		//无效的播放句柄
#define ERR_HWPLAY_INVALID_HEAD		(0x3)		//数据头错误
#define ERR_HWPLAY_NOT_SUPPORT		(0x4)		//不支持该操作
#define ERR_HWPLAY_STREAM_ONLY		(0x5)		//只有流播放才能进行该操作
#define ERR_HWPLAY_FILE_ONLY		(0x6)		//只有文件播放才能进行该操作
#define ERR_HWPLAY_NOT_ENOUGH_BUF	(0x7)		//没有可用空间
#define ERR_HWPLAY_INVALID_PARAM	(0x8)		//无效参数

#define ERR_HWPLAY_INTERNAL			(0xff)		//内部错误

#endif