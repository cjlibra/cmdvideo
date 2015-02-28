#ifndef play_type_h
#define play_type_h

#ifndef WIN32
#include "hw_config.h"
#endif

enum{
	ZOOM_LEFT = 4,
	ZOOM_RIGHT = 6,
	ZOOM_UP = 8,
	ZOOM_DOWN = 2,
	ZOOM_STOP = 5,
};

enum{
	PLAY_LIVE = 0,
	PLAY_FILE = 1,
};

enum{
	FILE_BMP         = 0,
	FILE_JPG         = 1,
};

enum{
	MOTION_RESULT_SUCCESS = 0,
	MOTION_RESULT_NO_MORE_DATA = 1,
	MOTION_RESULT_INVALID_HANDLE = 2,
	MOTION_RESULT_INVALID_PARAM = 3,
};

typedef struct{
	int row;
	int col;
	int time;
	int frame_idx;
	char data[72];
}motion_node;

typedef struct{
	unsigned long time;//内部时标
	unsigned long time2;
	long sys_time;//系统时间时标(1970到现在的utc时间)
	int frame_idx;//帧序号(从1开始)
	long file_pos;//文件位置
	long i_file_pos;//i帧位置
	int frame_type;//帧类型 0:P帧 1:I帧
	int msec;//时间(ms)
}frame_info;

#endif
