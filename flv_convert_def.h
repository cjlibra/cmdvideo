#ifndef flv_convert_dev_include_h
#define flv_convert_dev_include_h

#define HOWELL_FLV_CONVERT_API	extern "C"__declspec(dllexport)

typedef LONG FLV_CONVERT_HANDLE ;

HOWELL_FLV_CONVERT_API FLV_CONVERT_HANDLE __stdcall  flv_convert_start(const char* out_file,int frame_rate);

HOWELL_FLV_CONVERT_API BOOL __stdcall flv_convert_input(FLV_CONVERT_HANDLE handle,const char* buf,int len);

HOWELL_FLV_CONVERT_API BOOL __stdcall flv_convert_stop(FLV_CONVERT_HANDLE handle);


#endif