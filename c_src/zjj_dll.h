#ifndef __ZJJ_DLL_H__
#define __ZJJ_DLL_H__

/*  To use this exported function of dll, include this header
 *  in your project.
 */


#ifdef __cplusplus
extern "C"
{
#endif
typedef enum{PRO_NULL,PRO645_97,PRO645_07,PRO645_188}PRO_TYPE;

typedef struct{
    char *meterADDR;
    char *collector2;
    char *collector1;
    char *info;
    int info_datalen;
    char *route1;
    char *route2;
    char *isBCD;
    unsigned char subSEQ;
}INPUT_STRU;

typedef struct{
    char *data;
    char *frame;
    char *error;
    int data_len;
    int frame_len;
    int err_len;
}OUTPUT_STRU;

int  data_pack(INPUT_STRU *in, OUTPUT_STRU *out);
int  data_result(INPUT_STRU *in, OUTPUT_STRU *out);
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__

