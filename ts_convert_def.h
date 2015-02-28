#ifndef ts_convert_dev_include_h
#define ts_convert_dev_include_h

#define HOWELL_TS_CONVERT_API	extern "C"__declspec(dllexport)

typedef LONG TS_CONVERT_HANDLE ;

HOWELL_TS_CONVERT_API TS_CONVERT_HANDLE __stdcall  ts_convert_start(const char* out_file,int frame_rate);

HOWELL_TS_CONVERT_API BOOL __stdcall ts_convert_input(TS_CONVERT_HANDLE handle,const char* buf,int len);

HOWELL_TS_CONVERT_API BOOL __stdcall ts_convert_stop(TS_CONVERT_HANDLE handle);


#endif