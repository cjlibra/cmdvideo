#ifndef _protocol_type_include_h
#define _protocol_type_include_h

#define MAX_DATA_LEN			4096
#define MAX_USER				256
#define MAX_MANAGER_USER		5
#define MAX_SLOT				256
#define	MAX_NAME_LEN			32
#define	MAX_PASS_LEN			16
#define IP_LENGTH				32
#define	MAX_DAVINCI_USER		16
#define MAX_FILES				2000
#define HW_MAX_ALARM_IN			16
#define HW_MAX_ALARM_OUT		16
#define HW_MAX_DISKNUM			8
#define HW_MAX_DSPNUM			32
#define HW_MAX_SERIALID			32

#define VERSION_TEMPEST(x) ((x) >= 20000 && (x) <=29999)
#define VERSION_DAVI(x) ((x) >= 10000 && (x) <=19999)
#define VERSION_HOWELL_LINUX(x)((x) >= 30000 && (x) <= 39999)
#define VERSION_HIS(x) ((x) >= 40000 && (x) <= 49999)
#define VERSION_NVR(x) (((x) >= 50000 && (x) <= 59999) || ((x) >= 100000 && (x) <= 109999))
#define VERSION_IPCAM(x) ((x) >= 60000 && (x) <= 69999)
#define VERSION_IPCAM_A5(x) ((x) >= 65000 && (x) <= 69999)
#define VERSION_MIXED_NVR(x)((x) >= 70000 && (x) <= 79999)//混和型nvr
#define VERSION_HIS_RAILWAY(x) ((x) >= 80000 && (x) <= 89999)

#define OLD_NET_VERSION_DVR(x) ((x) < 90000)
#define VERSION_DECODER(x) ((x) >= 120000 && (x) <= 130000)


#define HWHI_HANDLE_BEG			4000		//his
// #define HWNVR_HANDLE_BEG		5000		//nvr
// #define HWIPC_HANDLE_BEG		6000		//ip cam

/*Video Data Type*/
#define HW_FRAME_VIDEO_HEAD	            1
#define HW_FRAME_VIDEO_I                3
#define HW_FRAME_VIDEO_P                4
#define HW_FRAME_VIDEO_BP               5
#define HW_FRAME_AUDIO                  2
#define HW_FRAME_VIDEO_SUB_HEAD         7
#define HW_FRAME_VIDEO_SUB_I            8
#define HW_FRAME_VIDEO_SUB_P            9
#define HW_FRAME_VIDEO_SUB_BP          10

#define HW_FRAME_VIDEO_BBP             11
#define HW_FRAME_VIDEO_SUB_BBP         12
#define HW_FRAME_MOTION_FRAME          13
#define HW_FRAME_VIDEO_B               14
#define HW_FRAME_VIDEO_SUB_B           15

#define HW_FRAME_VIDEO_MJPEG		   16
#define HW_FRAME_VIDEO_SUB_MJPEG       17

#define HW_FRAME_FOCUS				   20
#define HW_FRAME_VIDEO_ANALYZE		   21
#define HW_FRAME_EXTRA_DATA			   22
#define HW_FRAME_SUB_EXTRA_DATA		   23

//查找回放文件返回值
#define HWNET_FILE_SUCCESS		1000
#define HWNET_NOFILE			1001
#define HWNET_ISFINDING			1002
#define HWNET_NOMOREFILES		1003
#define HWNET_FILE_EXCEPTION	1004

struct tServerInfo{
	int slotCount;			//通道总数
	int sverVersion;		//服务器版本
	int netVersion;			//网络版本
	int reserver[32];		
};

/*osd struct*/
struct tOsdDate
{
	int slot;				//从0开始
	int isEnable;			//是否显示
	int left;				//0-703
	int top;				//0-575
	int type;				//		无效
	int isShowWeek;			//是否显示星期
};

/*video color struct*/
struct tVideoColor
{
	int slot;
	int brightness/*0-255*/;
	int contrast/*0-127*/;
	int saturation/*0-127*/;
	int hue/*0-255*/;
};

/*osd channel struct*/
struct tOsdChannel
{
	int slot;
	int isEnable;		//是否显示
	int left;			//0-703
	int top;			//0-575
	char name[32];		//通道名称
};

/*encode quality struct*/
struct tVideoQuality
{
	int slot;
	int encodeType; /*0-CIF, 1-D1 2-720p,3-1080p,4-1280*960,5-1024*768,0xff-qcif*/
	int qualityLev;/* 0-最好,1-次好，2-较好，3一般*/
	int maxBps;		//0-不限,1-较小 2-大 3-较大 4-最大，CIF(2000,400,600,800,1000),D1(4000,800,1000,1400,1600),720p(8000,2000,2500,3000,4000)
	
	int vbr;		//0-cbr 1-vbr
	int framerate;  //0-全帧率 1-24 实际帧率
	int reserved;
	//int iQuality;
	//int pQuality;
	//int bQuality;
};

/*user log password*/
struct tLogin
{	
	int type;	//暂时未使用
	char logName[32];
	char logPassword[32];	
	int clientUserID;
	int reserved[32];
};

/*work sheet  2 in 1  davinci & linux*/
#define MAX_SEGMENT 3
#define MAX_DAY     7
#ifndef _WINDOWS 
typedef struct _HWSYSTEMTIME {
		short wYear;
   short wMonth;
   short wDayOfWeek;
   short wDay;
   short wHour;
   short wMinute;
   short wSecond;
   short wMilliseconds;
}HWSYSTEMTIME;
#endif
struct tSegment{
	int isSet;
	SYSTEMTIME beg;
	SYSTEMTIME end;
	int recType;//0-Real ,1-Motion
};
struct tDaySheet{
	int isSet;		//暂时未使用
	struct tSegment segment[MAX_SEGMENT];
};
struct tSlotSheet{	
	struct tDaySheet sameSheet;//each day is same,暂时未使用
	struct tDaySheet eachDaySheet[MAX_DAY];
};
struct tWorkSheet{
	int sheetNO;		//1:手动，即不启用工作表
	int slotNo;
	struct tSlotSheet slotSheet;
};

/*motion*/
struct tMotion{
	int slot;
	int lev ;		/*0最高-5最低，6关闭*/
	int	recDelay;	//0-6:10s,20s,30s,1m,2m,5m,10m
	int data[18];	//从低位往高位为0-21
};

/*mask*/
#define MAX_MASK_RECT 4
struct tMask{
	int slot;
	int count;		//遮挡个数，不大于4个
	int lev;		//暂时未使用
	RECT rt[MAX_MASK_RECT];
};

/*rec file*/
struct tRecFile{
	int slot;
	SYSTEMTIME beg;
	SYSTEMTIME end;
	int type;/*0=all 1=normal file 2=mot file 3=alarm 4=mot&&alarm 5=ipcam lost 6=analyze metadata*/
};

/*rec data*/
struct tRecData{
	int slot;
	int type;/*0=head  1=video data*/
	int dataLen;
	char buf[2048];
};

/*video standard*/
struct tVideoStandard{
	int slot;
	int videoStandard;/*0 - pal,1-ntfs*/
};

/*video status*/
struct tVideoStatus{
	int slot;
	int recStatus;/*0- not rec, 1- rec*/
	int signalStatus;/*0 - no signal, 1- signal*/
	int motionStatus;/*0- no motion alarm, 1- motion alarm*/
};

/*alarm */
struct tAlarmData{
	//报警的视频通道
	//如果为硬盘报警则为硬盘序号
	//如果报警类型为HW_ALARM_MONITOR,0--参数设置(get) 1--参数保存(set)  2--回放
	int value;			
	int status;	    
	int reserved[32];
};

/*center information*/
struct tCenter{
	char ip[32];
	int port;
	int listenType;/*0 - udp ,1 - tcp*/
	int reserved[32];
};

/*stream type*/
struct tStreamType{
	int slot;
	int type;/*1- video, 2-audio,3-both*/
};

struct tAlarmMotionData
{
	unsigned int slot; //视频窗口号，从0开始
	long tmSec;        //时间，从1970年1月1号经过的秒数
	unsigned int tmMSec;//毫秒，0-1000
	unsigned int data[18];//存放运动帧信息
	unsigned int reserved[4];//保留
};

typedef enum
{
//---------------record_type-------------------------
  CONTINUOUS        = 1 << 0,
  MOTION            = 1 << 1,
  TRIGGER_INPUT_0   = 1 << 2,
  TRIGGER_INPUT_1   = 1 << 3,
  TRIGGER_INPUT_2   = 1 << 4,
  TRIGGER_INPUT_3   = 1 << 5,
  TRIGGER_INPUT_4   = 1 << 6,
  TRIGGER_INPUT_5   = 1 << 7,
  TRIGGER_INPUT_6   = 1 << 8,
  TRIGGER_INPUT_7   = 1 << 9,
  TRIGGER           = 1 << 10,
//---------------record_mode-------------------------
  DAILY             = 1 << 11,
  WEEKLY            = 1 << 12,
  ONCE              = 1 << 13
}RecrtdTypeFlags;


/*work sheet */
#define MAX_TEMPEST_SCHEDULE_COUNT 1000
typedef struct
{
  SYSTEMTIME beg;
  SYSTEMTIME end;
  unsigned int frame_rate;
  unsigned int record_type;   //CONTINUOUS MOTION TRIGGER,see RecrtdTypeFlags
  unsigned int record_mode;   //WEEKLY DAILY ONCE,see RecrtdTypeFlags
}record_schedule_item_t;

struct tTempestWorkSheet
{
	int slot;	
	record_schedule_item_t *sch_list; 
	int sch_count;	
};

/*user*/

/* privileges */
enum{
  USER_PRIVILEGS_GUEST,
  USER_PRIVILEGS_ADMIN,
  USER_PRIVILEGS_CUSTOM,
};
/* access flag */
enum{
  USER_ACCESS_PLAYBACK =   (1 << 0),
  USER_ACCESS_PTZ      =   (1 << 1),
  USER_ACCESS_LOGS     =   (1 << 2),
  USER_ACCESS_SCHEDULE =   (1 << 3),
  USER_ACCESS_QUALITY  =   (1 << 4),
  USER_ACCESS_MOTION   =   (1 << 5),
  USER_ACCESS_NETWORK  =   (1 << 6),
  USER_ACCESS_DELETE   =   (1 << 7),
  USER_ACCESS_TIME     =   (1 << 8),
  USER_ACCESS_ADMIN    =   (1 << 9),
  USER_ACCESS_UPGRADE  =   (1 << 10),
  USER_ACCESS_ALARM    =   (1 << 11),
  USER_ACCESS_POS      =   (1 << 20),
};

#define USER_GUEST_PGUEST_ACCESS_FLAG USER_ACCESS_PLAYBACK
#define USER_GUEST_PADMIN_ACCESS_FLAG (0xffffffff-USER_ACCESS_UPGRADE-USER_ACCESS_ADMIN-USER_ACCESS_TIME-USER_ACCESS_DELETE-USER_ACCESS_NETWORK)

typedef struct  {
  char email[50];
  char user[50];
  int num;
  int numLeft;
  int min_time;
  unsigned char motion[16];
  unsigned char input[8];
  unsigned char motion_snap;
  unsigned char input_snap;
  unsigned char net;
  unsigned char dis;
  unsigned char emailTimeRange[4];
}email_user_t;


typedef struct  {
  char name[50];
  char pass[50];
  char email[100];

  /* for encrypt */
  int encPass[50];
  int passLen;
  int passTm;

  /*
  unsigned int admin;
  unsigned int flags;
  */
  int privilege;
  unsigned int flags;
  unsigned int loggedIn;

  unsigned int access_cameras;
  unsigned int access_sound;
  unsigned int access_flags;

  //email_user_t  emailUser;
}user_t;

struct tTempestUsers{
	int userCount;
	user_t *user_item;
};


/*ptz*/
struct tPtzControl{
	int slot;
	int controlType;/*0-direct 1- len 2-AUTO zoom in,3-preset*/
	int cmd;/*direct: 7-left up
		             8-up
					 9-right up
					 4-left
					 5-stop
					 6-right
					 1-left down
					 2-down
					 3-right down

			len:     1-iris open
			         2-iris close
					 3-len tele
					 4-len wide
					 5-focus far
					 6-focus near
					 7-stop
			AUTO zoom in:
					 1-auto zoom in
			preset:
					 1-set
					 2-clear
					 3-goto
			*/
	int presetno;			//预置点号或方向移动的速度（0-64）
	RECT rect;			//点击放大，相对于704×576
};

struct tRegisterAlarm{
	int bRegister;
	int listenPort;
	/*long lUserID;*/
	long reserved[4];
};

typedef enum{
	ALARM_DO_NOTHING = 0,
	ALARM_TO_MONITOR = (1<<0),
	ALARM_WITH_AUDIO = (1<<1),
	ALARM_TO_CENTER =  (1<<2),
	ALARM_TO_OUT =  (1<<3),
	ALARM_TO_RECORD = (1<<4),
	ALARM_TO_SNAP = (1<<5),
}AlarmHandleType;

typedef struct 
{ 
	int type;   /*处理方式,处理方式的"或"结果,参照AlarmHandleType*/
	byte byRelAlarmOut[HW_MAX_ALARM_OUT];  /*  报警触发的输出通道,报警触发的输出,为1 表示触发该输出 */ 
	byte byRelRecord[MAX_SLOT];// 联动录象	, 报警触发的录象通道,为1表示触发该通道 //移动侦测可以不支持
	byte byRelSnap[MAX_SLOT];// 联动抓图			
}tHandle; 
typedef struct
{
	byte byStartHour; //0-23
	byte byStartMin; //0-59
	byte byStopHour; //0-23
	byte byStopMin; //0-59
}HW_NET_SCHEDTIME;

struct tAlarmInCfg{
	int alarmin_no;//报警器序号 
	int type;//报警器类型 0-常开 1-常闭
	tHandle handle;//报警联动处理
	HW_NET_SCHEDTIME schedule[MAX_DAY][MAX_SEGMENT];//报警处理的时间段，在这些时间段里才处理报警
	int reserved[32];
};

struct tAlarminDefend{
	int alarmin_no;//报警器序号 
	int type;//0-定时  1-手动不妨 2-手动撤防
	int reserved[32];
};

struct tAlarmOutState{
	byte state[HW_MAX_ALARM_OUT]; //报警输出状态 0:无效 1：有效
	int reserved[32];
};

struct tAlarmOutCfg{
	int alarmout_no;//0xff-全部，否则表明报警输出
	byte state;//1- 有效，0- 无效
	int reserved[32];
};

//遮挡报警
struct tAlarmMask{
	int slot;
	int enabled;//是否启用
	tHandle handle;
	int reserved[32];
};

//串口设备设置
struct tRs232Cfg{
	int rs232_no;//当slot小于本地通道数的时候,为本地串口号，否则为该网络通道对应的串口号
	int rate; /*  波特率(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;*/ 
	byte data_bit; //0-5位 1-6位 2-7位 3-8位
	byte stop_bit; //0-1位 1-2位
	byte parity; //0-无校验 1-奇校验 2-偶校验
	byte flow_control;//0-无 1-软流控 2-硬流控
	int work_mode; //工作模式 0-云台 1-报警接收 2-透明通道
	int annunciator_type;/*0-Howell 1-VISTA 120 ... */	
	int reserved[32];
};

typedef enum
{
	PELCO_D		= 0,
	PELCO_P		,
	ALEC		,
	YANAN		
}ProtocolType;

//ptz云台设置,只有在串口的work_mode=0(云台)时有效
struct tPtzRs232Cfg{
	int slot;
	int rs232_no;//当slot小于本地通道数的时候,为本地串口号，否则为该网络通道对应的串口号
	int rate; /*  波特率(bps)，0－50，1－75，2－110，3－150，4－300，5－600，6－1200，7－2400，8－4800，9－9600，10－19200， 11－38400，12－57600，13－76800，14－115.2k;*/ 
	byte data_bit; //0-5位 1-6位 2-7位 3-8位
	byte stop_bit; //0-1位 1-2位
	byte parity; //0-无校验 1-奇校验 2-偶校验
	byte flow_control;//0-无 1-软流控 2-硬流控
	int protocol;//协议类型，参照ProtocolType
	int address; //地址 0-255
	int reserve[32];
};

//透明通道发送,只有在串口的work_mode=2(透明通道)时有效
struct tRs232Send
{
	int rs232_no;//当slot小于本地通道数的时候,为本地串口号，否则为该网络通道对应的串口号
	int protocol;//协议类型，参照protocolType,如果=0xffffffff,表明其他协议，只要直接转发即可。
	int len;//数据长度
	byte data[256];
	int reserve[32];
};

struct tVideoLostCfg{
	int slot;
	tHandle handle;
	HW_NET_SCHEDTIME schedule[MAX_DAY][MAX_SEGMENT];//视频丢失处理的时间段，只有在这些时间段才处理
	int reserve[32];
};

struct tVoice{
	int type; //0-单向（中心到主机)  1-双向
	int slot;
	int reserve[31];
};

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#define  HW_MOTION_MAX_ROWS 128
#define  HW_MOTION_MAX_COLS 128
typedef struct{
	int slot;
	int rows;//0-HW_MOTION_MAX_ROWS
	int cols;//0-HW_MOTION_MAX_COLS
	int reserved[32];
}tMotionRowCols;

typedef struct 
{
	int slot;
	int lev ;		/*0最高-5最低，6关闭*/
	int	recDelay;	//0-6:10s,20s,30s,1m,2m,5m,10m	
	char data[HW_MOTION_MAX_ROWS * HW_MOTION_MAX_COLS / 8];
	tHandle handle;
	int reserved[32];
}tMotionEx;

typedef struct //主动上传
{
	unsigned int slot; //视频窗口号，从0开始
	long tmSec;        //时间，从1970年1月1号经过的秒数
	unsigned int tmMSec;//毫秒，0-1000	
	char data[HW_MOTION_MAX_ROWS * HW_MOTION_MAX_COLS / 8];
	int reserved[32];
}tAlarmMotionDataEx;

#define  MAX_SMARTSEARCH_RECT 5
typedef struct{
	tRecFile recFile;
	int rt_count;
	RECT rt[MAX_SMARTSEARCH_RECT]; //按照704 * 576
	int direction;//0-全部  4-左 6-右  8-上 2-下
	int reserved[32];
}tSmartSearchEx;

//硬盘信息获取
typedef struct{	
	INT64 volume; //硬盘容量
	INT64 free;//可用容量
	int state;//硬盘状态 0- 正常 1-休眠 2-不正常
	int nindex; //对应的SATA口
	int reserved[31];
}tEachHarddiskInfo;

#define  MAX_HARD_DISK_COUNT 16
typedef struct{
	tEachHarddiskInfo disk[MAX_HARD_DISK_COUNT];
	int reserved[32];
}tHarddiskInfo;

/*****************		lzs		****************/
/*network setting*/
struct tNetworkSetInfo {
	int		port;
	char	sDvrIp[IP_LENGTH];				//dvr ip地址
	char	sDvrMaskIp[IP_LENGTH];			//dvr子网掩码
	char	gateway[IP_LENGTH];
	int		byMACAddr[6];					//服务器的物理地址
	char	dns[IP_LENGTH];
	char	sMultiCastIP[IP_LENGTH];		 //多播组地址
	int		dwPPPOE;						//0-不启用,1-启用
	char	sPPPoEUser[MAX_NAME_LEN];		//PPPoE用户名
	char	sPPPoEPassword[MAX_PASS_LEN];	// PPPoE密码
	char	sPPPoEIP[IP_LENGTH];			//PPPoE IP地址(只读)
	int		reserve[32];
};

/*	log	*/
//!!!!主类型0表示全部，1异常，2操作，3报警，dvr主机中没有“全部”，0异常，1操作，2报警
/* 报警 */
//主类型
#define MAJOR_ALARM				0x3
//次类型
#define MINOR_ALARM_IN			0x0		/* 报警输入 */
#define MINOR_ALARM_OUT			0x1		/* 报警输出 */
#define MINOR_MOTDET_START		0x2		/* 移动侦测报警开始 */
#define MINOR_MOTDET_STOP		0x3		/* 移动侦测报警结束 */
#define MINOR_HIDE_ALARM_START	0x4		/* 遮挡报警开始 */
#define MINOR_HIDE_ALARM_STOP	0x5		/* 遮挡报警结束 */
#define MINOR_ALARM_UNKOWN		0x6		/* 未知 */

/* 异常 */
//主类型
#define MAJOR_EXCEPTION			0x1
//次类型
#define MINOR_VI_LOST			0x7		/* 信号丢失 */
#define MINOR_ILLEGAL_ACCESS	0x8		/* 非法访问 */
#define MINOR_HD_FULL			0x9		/* 硬盘满 */
#define MINOR_HD_ERROR			0xA		/* 硬盘错误 */
#define MINOR_DCD_LOST			0xB		/* MODEM 掉线 */
#define MINOR_IP_CONFLICT		0xC		/* IP地址冲突 */
#define MINOR_EXCEPTION_UNKOWN	0xD		/* 未知 */

/* 操作 */
//主类型
#define MAJOR_OPERATION			0x2
//次类型
#define MINOR_START_DVR			0xE		/* 开机 */
#define MINOR_STOP_DVR			0xF		/* 关机 */
#define MINOR_STOP_ABNORMAL		0x10	/* 非法关机 */
// #define	MINOR_REBOOT_DVR		0x44	/* 重启 */	//lzs

#define MINOR_LOCAL_LOGIN		0x11	/* 本地登陆 */
#define MINOR_LOCAL_LOGOUT		0x12	/* 本地注销登陆 */
#define MINOR_LOCAL_CFG_PARM	0x13	/* 本地配置参数 */
#define MINOR_LOCAL_PLAYBYFILE	0x14	/* 本地按文件回放 */
#define MINOR_LOCAL_PLAYBYTIME	0x15	/* 本地按时间回放 */
#define MINOR_LOCAL_START_REC	0x16	/* 本地开始录像 */
#define MINOR_LOCAL_STOP_REC	0x17	/* 本地停止录像 */
#define MINOR_LOCAL_PTZCTRL		0x18	/* 本地云台控制 */
#define MINOR_LOCAL_PREVIEW		0x19	/* 本地预览 */
#define MINOR_LOCAL_MODIFY_TIME	0x1A	/* 本地修改时间 */
#define MINOR_LOCAL_UPGRADE		0x1B	/* 本地升级 */
// #define MINOR_LOCAL_COPYFILE	0x5b	/* 本地备份文件 */

#define MINOR_REMOTE_LOGIN		0x1C	/* 远程登录 */
#define MINOR_REMOTE_LOGOUT		0x1D	/* 远程注销登陆 */
#define MINOR_REMOTE_START_REC	0x1E	/* 远程开始录像 */
#define MINOR_REMOTE_STOP_REC	0x1F	/* 远程停止录像 */
#define MINOR_START_TRANS_CHAN	0x20	/* 开始透明传输 */
#define MINOR_STOP_TRANS_CHAN	0x21	/* 停止透明传输 */
#define MINOR_REMOTE_GET_PARM	0x22	/* 远程获得参数 */
#define MINOR_REMOTE_CFG_PARM	0x23	/* 远程配置参数 */
#define MINOR_REMOTE_GET_STATUS 0x24	/* 远程获得状态 */
#define MINOR_REMOTE_ARM		0x25	/* 远程布防 */
#define MINOR_REMOTE_DISARM		0x26	/* 远程撤防 */
#define MINOR_REMOTE_REBOOT		0x27	/* 远程重启 */
#define MINOR_START_VT			0x28	/* 开始语音对讲 */
#define MINOR_STOP_VT			0x29	/* 停止语音对讲 */
#define MINOR_REMOTE_UPGRADE	0x2A	/* 远程升级 */
#define MINOR_REMOTE_PLAYBYFILE	0x2B	/* 远程按文件回放 */
#define MINOR_REMOTE_PLAYBYTIME	0x2C	/* 远程按时间回放 */
#define MINOR_REMOTE_PTZCTRL	0x2D	/* 远程云台控制 */
#define MINOR_OPERAION_UNKOWN	0x2E	/* 未知 */


/*参数*/
#define	PARAM_VIDEO_OUT			0x0		/*视频输出*/
#define PARAM_IMAGE				0x1		/*图像*/
#define PARAM_ENCODE			0x2		/*编码*/
#define PARAM_NETWORK			0x3		/*网络*/
#define PARAM_ALARM				0x4		/*报警*/
#define PARAM_EXCEPTION			0x5		/*异常*/
#define PARAM_DECODE			0x6		/*解码*/
#define PARAM_RS232				0x7		/*RS232*/
#define PARAM_PREVIEW			0x8		/*预览*/
#define PARAM_SECURITY			0x9		/*安全*/
#define PARAM_DATETIME			0xA		/*日期时间*/
#define PARAM_FRAMETYPE			0xB		/*帧格式*/
#define PARAM_UNKOWN			0xC		/*未知*/


struct tLogInfo {
	SYSTEMTIME	beg;	//开始时间或日志记录时间
	SYSTEMTIME	end;
	int		slot;
	int		majorType;			//参见上述定义
	int		minorType;			//参见上述定义
	char	local_operator[MAX_NAME_LEN];		//本地操作员
	char	remote_ipaddr[IP_LENGTH];			//远程操作ip
	char	remote_operator[MAX_NAME_LEN];		//远程操作员
	int		paramType;			//操作参数
	int		disknumber;			//硬盘号
	int		nAlarmInPort;		//报警输入端口
	int		nAlarmOutPort;		//报警输出端口
	char	reserve[32];
};

/*	davinci user	*/
struct Davinci_user_t {
	char	username[MAX_NAME_LEN];
	char	password[MAX_PASS_LEN];
	int		privilege;
	char	reserve[32];
};
struct tDavinciUser {
	int		user_count;
	Davinci_user_t *user;
};

/*	smart search	*/
struct tSmartSearch {
	tRecFile	recFile;
	char		searchRect[72];		//智能搜索范围,按位取,1-该区域需要在搜索范围内
};

/* alarm state */
struct tAlarmState {
	int		alarm_in_state[HW_MAX_ALARM_IN];		//报警输入状态
	int		alarm_out_state[HW_MAX_ALARM_OUT];		//报警输出状态
	int		rec_state[MAX_SLOT];					//录像状态 0-不录，1-录像
	int		signal_state[MAX_SLOT];					//视频信号状态 0-无 1-有
	int		disk_state[HW_MAX_DISKNUM];				//硬盘状态	0-正常 1-无硬盘 2-硬盘坏 3-硬盘未格式化 4-硬盘满 
	int		motion_state[MAX_SLOT];					//移动侦测 0-没有移动侦测报警 1-有
	int 	dsp_state[HW_MAX_DSPNUM];				//dsp状态  0-异常 1-正常
	char	reserve[32];
};

/* devcie configuration */
struct tDevConfig {
	char	devName[MAX_NAME_LEN];				//设备名称
	char	devSerialID[HW_MAX_SERIALID];		//设备序列号
	int		window_count;		//窗口数
	int		alarm_in_count;		//报警输入数
	int		alarm_out_count;	//报警输出数		
	int		disk_count;			//硬盘数
	int		dsp_count;			//dsp数
	int		rs232_count;		//串口数
	char	channelname[MAX_SLOT][32]; // 通道名称

	int		net_channel_count;  //网络通道数
	char	reserve[28];
};

/* upgrade file header */
struct tUpgradeFileHeader {
	char	fileName[260];	
	long	fileSize;		//单位字节
	char	md5[33];		//md5 code, 32 byte，33为结束符'\0'
	char	reserve[31];
};


/* error definition */
#define HW_NET_NOERROR 					0  //没有错误
#define HW_NET_PASSWORD_ERROR 			1  //用户名密码错误
#define HW_NET_NOENOUGHPRI 				2  //权限不足
#define HW_NET_NOINIT 					3  //没有初始化
#define HW_NET_CHANNEL_ERROR 			4  //通道号错误
#define HW_NET_OVER_MAXLINK 			5  //连接到DVR的客户端个数超过最大
#define HW_NET_VERSIONNOMATCH			6  //版本不匹配
#define HW_NET_NETWORK_FAIL_CONNECT		7  //连接服务器失败
#define HW_NET_NETWORK_SEND_ERROR		8  //向服务器发送失败
#define HW_NET_NETWORK_RECV_ERROR		9  //从服务器接收数据失败
#define HW_NET_NETWORK_RECV_TIMEOUT		10 //从服务器接收数据超时
#define HW_NET_NETWORK_ERRORDATA		11 //传送的数据有误
#define HW_NET_ORDER_ERROR				12 //调用次序错误
#define HW_NET_OPERNOPERMIT				13 //无此权限
#define HW_NET_COMMANDTIMEOUT			14 //DVR命令执行超时
#define HW_NET_ERRORSERIALPORT			15 //串口号错误
#define HW_NET_ERRORALARMPORT			16 //报警端口错误
#define HW_NET_PARAMETER_ERROR 			17  //参数错误
#define HW_NET_CHAN_EXCEPTION			18	//服务器通道处于错误状态
#define HW_NET_NODISK					19	//没有硬盘
#define HW_NET_ERRORDISKNUM				20	//硬盘号错误
#define HW_NET_DISK_FULL				21	//服务器硬盘满
#define HW_NET_DISK_ERROR				22	//服务器硬盘出错
#define HW_NET_NOSUPPORT				23	//服务器不支持
#define HW_NET_BUSY						24	//服务器忙
#define HW_NET_MODIFY_FAIL				25	//服务器修改不成功
#define HW_NET_PASSWORD_FORMAT_ERROR	26	//密码输入格式不正确
#define HW_NET_DISK_FORMATING			27	//硬盘正在格式化，不能启动操作
#define HW_NET_DVRNORESOURCE			28	//DVR资源不足
#define	HW_NET_DVROPRATEFAILED			29  //DVR操作失败
#define HW_NET_OPENHOSTSOUND_FAIL 		30  //打开PC声音失败
#define HW_NET_DVRVOICEOPENED 			31  //服务器语音对讲被占用
#define	HW_NET_TIMEINPUTERROR			32  //时间输入不正确
#define	HW_NET_NOSPECFILE				33  //回放时服务器没有指定的文件
#define HW_NET_CREATEFILE_ERROR			34	//创建文件出错
#define	HW_NET_FILEOPENFAIL				35  //打开文件出错
#define	HW_NET_OPERNOTFINISH			36  //上次的操作还没有完成
#define	HW_NET_GETPLAYTIMEFAIL			37  //获取当前播放的时间出错
#define	HW_NET_PLAYFAIL					38  //播放出错
#define HW_NET_FILEFORMAT_ERROR			39  //文件格式不正确
#define HW_NET_DIR_ERROR				40	//路径错误
#define HW_NET_ALLOC_RESOUCE_ERROR		41  //资源分配错误
#define HW_NET_AUDIO_MODE_ERROR			42	//声卡模式错误
#define HW_NET_NOENOUGH_BUF				43	//缓冲区太小
#define HW_NET_CREATESOCKET_ERROR		44	//创建SOCKET出错
#define HW_NET_SETSOCKET_ERROR			45	//设置SOCKET出错
#define HW_NET_MAX_NUM					46	//个数达到最大
#define HW_NET_USERNOTEXIST				47	//用户不存在
#define HW_NET_WRITEFLASHERROR			48  //写FLASH出错
#define HW_NET_UPGRADEFAIL				49  //DVR升级失败
#define HW_NET_CARDHAVEINIT				50  //解码卡已经初始化过
#define HW_NET_PLAYERFAILED				51	//播放器中错误
#define HW_NET_MAX_USERNUM				52  //用户数达到最大
#define HW_NET_GETLOCALIPANDMACFAIL		53  //获得客户端的IP地址或物理地址失败
#define HW_NET_NOENCODEING				54	//该通道没有编码
#define HW_NET_IPMISMATCH				55	//IP地址不匹配
#define HW_NET_MACMISMATCH				56	//MAC地址不匹配
#define HW_NET_UPGRADELANGMISMATCH		57	//升级文件语言不匹配
#define HW_NET_DDRAWDEVICENOSUPPORT		58	//本地显卡不支持
#define HW_NET_UPGRADEOCCUPIED			59	//服务器升级资源被占用
#define HW_NET_VOICE_EXIST				60 //语音对讲已经存在
#define HW_NET_MAX_LIVE_NUM				61 //预览个数达到最大

//ipcam 通道设置
struct tChannelSet{
	int		slot;
	char username[32];	// 用户名
	char password[32];	// 密码
	char ipaddress[32];	// IP地址
	char macaddress[32];	// MAC地址
	int nport; 		// 端口号
	int nchannelnum;	// 连接的通道号
};

/*
说明：
针对不同的ntype有效值不同。
ntype为0即howell协议的IPC设备：
username：用户名
password：密码
ipaddress：IP地址
nport：端口号
nchannelnum：连接的通道号

ntype为1即ONVIF设备

ntype为2即RTSP协议的IPC设备：
ipaddress：主码流的RTSP的URL(rtsp://[username[:password]@]ip_address[:rtsp_port]/server_URL[?param1=val1[&param2=val2]...[&paramN=valN]])
profilename：子码流的RTSP的URL
busingtcp：以TCP/UDP连接获得流
*/
struct tChannelSetEx{
	int		slot;
	int     ntype;           // 0--howell device, 1--onvif device, 2--RTSP
	char    username[128];	// 用户名
	char    password[128];	// 密码
	char    ipaddress[256];	// IP地址  //serviceaddress
	char    profilename[128];   //profilename
	int     nport; 		    // 端口号
	int     nchannelnum;	// 连接的通道号
	int     busingtcp; //bStreamUsingTcp
};

typedef enum {
	IPCAM_ESHUTTER_1_SEC=0, /* 1 sec */
	IPCAM_ESHUTTER_2_SEC,
	IPCAM_ESHUTTER_3_SEC,
	IPCAM_ESHUTTER_4_SEC,
	IPCAM_ESHUTTER_5_SEC,
	IPCAM_ESHUTTER_7_SEC,
	IPCAM_ESHUTTER_10_SEC, /* 1/10 sec */
	IPCAM_ESHUTTER_12_SEC, /* 1/12 sec */
	IPCAM_ESHUTTER_15_SEC,
	IPCAM_ESHUTTER_20_SEC,
	IPCAM_ESHUTTER_25_SEC,
	IPCAM_ESHUTTER_30_SEC,
	IPCAM_ESHUTTER_50_SEC,
	IPCAM_ESHUTTER_60_SEC,
	IPCAM_ESHUTTER_100_SEC0,
	IPCAM_ESHUTTER_120_SEC,
	IPCAM_ESHUTTER_240_SEC,
	IPCAM_ESHUTTER_480_SEC,
	IPCAM_ESHUTTER_960_SEC,
	IPCAM_ESHUTTER_1024_SEC,
	IPCAM_ESHUTTER_COUNT,
}HW_IPCAM_ESHUTTER_E;

typedef enum {
	HW_WB_INCANDESCENT=0,
	HW_WB_D4000,
	HW_WB_D5000,
	HW_WB_SUNNY,
	HW_WB_CLOUDY,
	HW_WB_FLASH,
	HW_WB_FLUORESCENT_WARM,
	HW_WB_FLUORESCENT_COLD,
	HW_WB_COUNT,
}HW_IPCAM_WB_E;

struct tIPCam_feature{
	int		slot;
	int		bae;		//是否自动曝光
	int		eshutter;//参照HW_IPCAM_ESHUTTER_E
	int		agcgain;//0-30
	int		blackwhitemode;		//彩转灰
	int		badj;		//自动调节
	int		blacklevel;		//黑电平[-128,128]，badj无效时该参数有效

	int     bAutoWB; //自动白平衡
	int     wb_mode; //白平衡模式
	int     rgb_gain[3];//rgb增益 0-16384

	int		noisefilter;		//噪声抑制0-5，5最大，badj无效时该参数有效
	int		sharp;				//锐度0-5，5最大，badj无效时该参数有效
	
	int		luma;				//流明
	
	int		reserved[13];
};

//强光抑制,当前只有enable和max_luma_night 有用
struct tBlackMaskBLC{
	int slot;

	int enable;
	
	/* 夜间的luma最大值,小于该值则启用逆光抑制 */
	int max_luma_night;
	
	/* 调整后，原高亮block的y值应该在此范围内  */
	int block_y_max;
	int block_y_min;
	
	/* 调整后如果y值小于该值，说明亮光过去，需要恢复自动曝光 */
	int block_y_night_normal;
	
	int mode; //0: 固定增益 1:固定快门 2:自动
	int fixedAgc;
	int fixedEshutter;
	
	int max_eshutter;
	int min_eshutter;
	int max_agc;
	int min_agc;
	
	/* 
	* 区域选择，3x3共9个区域。 用位表示选择或不选择
	* 如 (1<<0|1<<3) 即选择了第1个区域和第4个区域
	*/
	int area_map; 
	
	/* 设置掩码 */
	/* 0: nothing to set */
	/* 1<<0: enable */
	/* 1<<1: area_map */
	/* 1<<2: max_luma_night */
	/* 1<<3: block_y_max */
	/* 1<<4: block_y_min */
	/* 1<<5: block_y_night_normal */
	/* 1<<6: mode */
	/* 1<<7: fixedAgc */
	/* 1<<8: fixedEshutter */
	/* 1<<9: max_eshutter */
	/* 1<<10: min_eshutter */
	/* 1<<11: max_agc */
	/* 1<<12: min_agc */
	int set_mask;
	
	char reserve[32];
	
};



//通道状态，为NVR准备
struct tChannelStatus{
	byte status[MAX_SLOT]; //0-未连接 1-连接
	int reserved[32];
};

//通道类型，为NVR设备提供
struct tChannelType{
	int		slot;
	int		slottype;	//实际通道版本号
	int		reserved[32];
};

#define  HW_MEDIA_TAG 0x48574D49
typedef enum{
	VDEC_H264 = 0,	
	ADEC_G711U = 1,
	ADEC_HISG711A = 2,
	VDEC_HISH264 = 3,
	ADEC_HISG711U = 4,
	ADEC_HISADPCM = 5,
	VDEC_MJPEG = 6,
}HW_DEC_TYPE;
typedef struct 				
{
	unsigned int    media_fourcc;			// "HKMI": 0x484B4D49 Hikvision Media Information,"HWMI":0x48574D49
	long dvr_version;
	long vdec_code;
	long adec_code; 

	unsigned char au_bits; // 8,16...
	unsigned char au_sample;//Kbps 8,16,64
	unsigned char au_channel;//1,2
	unsigned char hd_ver;//版本，如果为1,必须正确填写w,h,fr

	unsigned char fr;//实际帧率
	char reserve[3];
	unsigned short w;//视频宽
	unsigned short h;//视频高	

	unsigned int    reserved[3];            // 保留
}HW_MEDIAINFO;


//文件信息
struct tRecFileInfo{
	int		slot;
	SYSTEMTIME beg;
	SYSTEMTIME end;
	int		fileformattype;	//文件编码格式类型，参见HW_DEVICE_TYPE
	int video_dec;
	int audio_dec;

	int ext_flag;//如果为1,下面的media_info必须有效
	HW_MEDIAINFO media_info;

	int		reserved[19];
};

struct tSubChannelSet{
	int slot;
	int used; //是否启用子码流，0-不启用 1-启用,当不启用，下面参数无效

	int encodeType; /*0-CIF,1-D1,2-720p 3-1080p,0xff-qcif*/
	int qualityLev;/* 0-最好,1-次好，2-较好，3一般*/
	int maxBps;		//0-不限,1-较小 2-大 3-较大 4-最大，CIF(2000,400,600,800,1000),D1(4000,800,1000,1400,1600),qcif(600,100,200,300,400)
	int vbr;		//0-cbr 1-vbr
	int framerate;  //0-全帧率 1-24 实际帧率

	int reserve[256];
};

/*数据迁移*/
struct tLostDataTransfer{
	int slot;
	
	int enable;
	
	/* 录像码流类型 0:主码流 1:次码流*/
	int stream; 
	
	/* 录像帧数,0: 满帧率 ,1-24实际帧率*/
	int framerate; 
	
	/* 是否循环覆盖,现在保留，不起作用 */
	int b_loop_write;
	
	char reserve[32];
	
};

typedef enum{
	WIN_D1 = 0,
	WIN_720p = 1,
	WIN_1080p = 2
}DECODER_WIN_FORMAT;
typedef struct{
	int win_idx;//窗口序号
	char ip[32];
	int slot;
	int port;
	int stream_type;//设备的最大编码能力0-d1 1-720p 2- 1080p
	int reserv3[32];
}net_win_video_t;

typedef struct {
	char mode;	//0: day	1:night
	char reserve[32];
} net_test_filter_t;

typedef struct  
{
	int enable;
	int reserve[32];
}net_raid_t;

typedef struct 
{
	int id;              //array id
	int total_space;      //MB
	int free_space;         
	int backup_space; 
	int total_pids;            
	int bga;   //0 : none  1: rebuilding 2:migration 3
	int state; //0 正常，1-损坏
	int rebuild_pos;
	int reserve[31];
}net_raid_state_t;

typedef struct  
{
	int slot;
	int is_sub;
	char buf[128];
	int len;
}net_head_t;

// 录像硬盘信息
struct tDisksInfo{
	int disk_counts; // 用于录像的硬盘数目
	int file_counts[64]; // 每个硬盘的最大录像文件数
	int badfile_counts[64]; // 每个硬盘有坏块文件数
	int  bwritten[64]; // 正在向里面写数据	
	int reserved[64];
};

typedef struct {
    char ip[IP_LENGTH];
    int cycle;			/* 1~300s */
    char reserve[32];
} NetSnmpCfg;

typedef struct{
	int enable;
	int port;
	char ip[32];
	int reserve[32];
}net_udp_info;

typedef struct{
	int port;
	char ip[32];
	int slot;
	int is_sub;
	int reserve[32];
}udp_live_info_t;

struct tAutoFocus{
	int slot;
	char custom_focus;	/*1 指定区域，0不指定区域*/
	//块为8 * 5
	char x;//0-7
	char y;//0-4
	char w;//1-8
	char h;//1-5
	char reserve[32];
};

/* 设备ID设置 */
struct tSerialID {
	char serial_id[32];
	char reserve[32];
};

typedef struct 
{
	int slot;
	int enable;
	int scene_changed_threso; //场景变化阀值1-100
	int scene_occluded_threso;//场景遮挡阀值1-100
	int focus_changed_threso;//焦距变化阀值1-100
	char reserve[32];
}net_analyze_t;

typedef struct  
{
	int slot;//通道
	int stream;//0:主码流 1:子码流
	int enable;//1:启用 0:不启用
	int left;//(0-703)
	int top;//(0-575)
	int color;//0:白色 1:红色 2:黑色 3:蓝色 4:绿色 5:黄色 6:青色
	int outline;//0:不勾边 1:勾边
	int font_size;//字体大小
	int aplha;//透明值,255不透明,0全透明
	int show_week;//1:显示日期 0:不显示日期
	int mode;//0: YYYY-MM-DD HH:MM:SS 1:MM-DD-YYYY HH:MM:SS
	int reserve[4];
}net_custom_osd_date_t;

typedef struct  
{
	int slot;//通道
	int stream;//0:主码流 1:子码流
	int enable;//1:启用 0:不启用
	int left;//(0-703)
	int top;//(0-575)
	int color;//0:白色 1:红色 2:黑色 3:蓝色 4:绿色 5:黄色 6:青色
	int outline;//0:不勾边 1:勾边
	int font_size;//字体大小
	int aplha;//透明值,255不透明,0全透明
	char name[512];//名称,支持换行，如果需要显示多行用&来控制，如"row1:123&row2:456"就会显示两行.
	int reserve[4];//保留，必须为0
}net_custom_osd_name_t;

typedef struct
{
	int slot;//通道
	int enable_noise_filter;//1:启动噪声抑制  0:不启动噪声抑制
	int noise_filter_value;//噪声抑制值(当前无效）
	int enable_echo_cancel;//1:启动回声抑制  0:不启动回声抑制(当前无效)
	int echo_delay;//回声抑制延时,单位ms(当前无效)
	int reserve[4];//保留，必须为0
}net_audio_enhance_t;

typedef struct  
{
	int control_mode;//0-手动 1-自动
	int sense;//灵敏度(1-3)在自动模式下起作用
	int blackwhite;//0-彩色 1-黑白,在手动模式下起作用
	int slot;//通道号
	char reserve[56];//保留
}net_blackwhite_t;

typedef struct  
{
	int flag;
	char is_flip;
	char enable_lowest_shutter;
	char shutter;
	char noise_filter_auto;
	char noise_filter_level;
	char sharp_auto;
	char sharp_level;
	char envinrenment;
	char enable_uppest_agc;
	char agc_upper_limit;
	char gama;
	char reserve[53];
}net_ipcam_misc_t;

typedef struct  
{
	int gpio;//gpio 号
	int value;//0:低 1:高
	char reserve[32];
}net_gpio_ctrl_t;

typedef struct  
{
	int slot;
	int mode;//0-NVR断线启动录像 1-实时录像 2-不录像 3-移动侦测录像
	int stream;
	int reserve[4];
}net_record_ctrl_t;

typedef struct  
{
	int slot;
	int clock_wise;//0-不翻转 1-翻转90度
	int reserve[4];
}net_encode_rotate_t;

typedef struct  
{
	unsigned char vout_id;//模拟输出id,当前为0
	unsigned char enable;//1-启动 0-停止
	unsigned char reserve[64];
}net_vout_t;

struct tChannelSetEx2{
	int	 slot;
	int     ntype;     // 0--howell device, 1--onvif device, 2--RTSP	3--GBIN
	char    username[32];	// 0--用户名	// 1--用户名
	char    password[32];	// 0--密码    	// 1--密码
	char    ipaddress[128];	// 0--IP地址	// 1--serviceaddress	// 2--RTSP主码流URL	// 3--国标摄像机ID
	char    profilename[128]; // 2--RTSP子码流URL	// 3--GB中心ID
	int     nport;   // 0--端口号
	int     nchannelnum;	// 0--连接的通道号
	int     busingtcp; // 1--是否采用TCP连接	// 2--是否采用TCP连接

	char name[128]; // 3--通道名称
	int extend_len; // 3--扩展数据
	char extend[1576]; // 3--扩展数据
};

struct tSlotByID{
	char gbid[128];
	int slot;
};

typedef struct  
{	
	//如果为1,表明通道号有效，如果想要测试ipc经过NVR到客户端的网速，需要设置该值
	int flag;
	
	//通道号
	int slot;

	//0: TCP 1:UDP
	int connect_mode;

	//0:服务端至客户端  1:客户端至服务端 2:双向
	int check_mode;

	//0:以最大速度发送  其他为发送间隔，单位毫秒(0-1000)
	int send_interval;

	//每次发送的包长(TCP:1-128K UDP:1-1400)
	int intervl_data_len;

	//保留必须为0
	int reserve[4];
}net_diagnostics_cfg_t;

typedef struct  
{
	//总的包个数
	unsigned long long total_packets;

	//收到的包个数
	unsigned long long total_recv_packets;

	//丢失的包个数
	unsigned long long total_lost_packets;

	//错误的包个数
	unsigned long long total_error_packets;

	//持续时间，单位为豪秒
	unsigned long long duration;

	//速率kbps
	unsigned int bps;

	//保留必须为0
	int reserve[16];
}net_diagnostics_status_t;

typedef struct
{
	//0xffffffff:获取设备本身的能力值
	//0-256:设备通道的能力值
	int slot;

	//第0位为1:支持 rtsp/udp
	//第1位为1:支持 rtsp/tcp
	//第2位为1:支持 rtsp/http/tcp
	int rtsp_capability_flag;

	//第0位为1:支持浩维协议校时
	//第1位为1:支持NTP校时
	int sync_time_capability_flag;

	//第0位为1:支持上下控制
	//第1位为1:支持左右控制
	//第2位为1:支持zoom控制
	//第3位为1:支持自动聚焦
	//第4位为1:支持预置点
	int ptz_capability_flag;

	//第0位为1:支持snmp
	//第1位为1:支持ipv6
	//第2位为1:支持PPPOE
	//第3位为1:支持老版本搜索协议
	//第4位为1:支持新版本搜索协议
	//第5位为1:支持WEB
	//第6位为1:支持WIFI
	int net_capability_flag;

	//第0位为1:支持SD卡储存
	//第1位为1:支持硬盘储存
	//第2位为1:支持RAID
	int storage_capabilicity_flag;

	//第0位为1:支持ONVIF
	//第1位为1:支持GB28181
	int protocol_capability_flag;

	//第0位为1:支持温度检测
	//第1位为1:支持电压检测
	int diagnostics_capability_flag;

	//第0位为1:支持H264
	//第1位为1:支持MJPEG
	int video_encode_capability_flag;

	//第0位为1:支持G711U
	//第1位为1:支持G711A
	//第2位为1:支持AAC
	int audio_encode_capability_flag;

	//0:普通IPC
	//1:后焦IPC
	//2:球机
	//3:一体机
	//4:半球
	//100:NVR
	int device_type;

	//0:不支持日夜切换
	//1:支持日夜切换
	//2:支持日夜切换且可以设置灵敏度
	//3:支持日夜切换，由外设控制
	int daynight_capability_flag;

	//最大通道数
	int max_slot;

	//每个通道的子码流数目
	int max_sub_streams;

	//保留必须为0
	int reserve[32];
}net_capability_t;

struct tSubSystemInfo
{

	char bySubSystemType;//子系统 1-编码子系统 （此参数只能获取)
	char byChan;//子系统通道数目，编码子系统为编码通道数目
	char bySlotNum;//槽位号，次参数只能获取 从1开始 （此参数只 能获取）
	char byState;//子系统状态 0-正常，1-异常... （此参数只能获取)
	char sSubSystemIP[IP_LENGTH];    //IP地址（可修改）
	char sSubSystemIPMask[IP_LENGTH];   //子网掩码 （可修改）
	char sSubSystemGateway[IP_LENGTH];  //网关地址 （可修改）
	short wSubSystemPort;   //子系统端口号（可修改）
	char byMACAddr[6];    //物理地址(只能获取)
	char sUsername[MAX_NAME_LEN];    //子系统用户名 （此参数只能获取）
	char sPassword[MAX_PASS_LEN];    //子系统密码 （此参数只能获取）
	char sSerialNumber[HW_MAX_SERIALID];    //序列号（此参数只能获取）
	char sSubSystemName[MAX_NAME_LEN];  //子系统名称 （可修改）
	char byRes[128];     //保留
};
#define MAX_SUBSYSTEM_NUM 64
struct tAllSubSystemInfo
{
	int dwSubSystemNum;
	struct tSubSystemInfo struSubSystemInfo[MAX_SUBSYSTEM_NUM];
	char byRes[16];
};

struct tIVMSize
{
	int width;
	int height;
};
struct tIVMPointD
{
	double x;
	double y;
};
struct tIVMCameraParam
{
	struct tIVMSize size; //图像尺寸
	struct tIVMPointD focus;   //焦距
	struct tIVMPointD center;  //中心
	double k[8];     //径向畸变系数k1
	double p[2];     //切向畸变系数p1
	char byRes[128];
};

typedef struct  
{
	int slot;
	int state;
	int reserve[4];
}net_lamp_state_t;

typedef struct
{
	int id;
	int attenuation;
	int type;
	int range_beg;
	int range_end;
	int reserve[4];
}net_rfid_info_t;

typedef struct
{
	int slot;
	char buf[255];
	int len; 
	char reserve[4];
}net_rfid_alarm_t;

#endif
