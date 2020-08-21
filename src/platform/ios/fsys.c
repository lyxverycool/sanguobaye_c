//
//  fsys.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#include "baye/stdsys.h"
#include "baye/comm.h"
#include "baye/enghead.h"
#include <stdio.h>

/***********************************************************************
 * 说明:     将当前文件系统的文件打开函数封装为标准的fopen函数
 * 输入参数: fname-文件名	mode-操作方式
 * 返回值  : 文件操作句柄
***********************************************************************/
FAR gam_FILE *gam_fopen(const U8 *fname,U8 pmode)
{
    U8 mode[3] = {pmode, 'b'};
    return (gam_FILE *)fopen((char*)fname, (char *)mode);
}
/***********************************************************************
 * 说明:     将当前文件系统的文件关闭函数封装为标准的fclose函数
 * 输入参数: fhandle-文件操作句柄
 * 返回值  : 0-操作成功		!0-错误代码
***********************************************************************/
FAR U8 gam_fclose(gam_FILE *fhandle)
{
    return fclose((FILE*)fhandle);
}
/***********************************************************************
 * 说明:     将当前文件系统的文件指针定位函数封装为标准的fseek函数
 * 输入参数: fhandle-操作句柄	offset-偏移	fromwhere-起始
 * 返回值  : 0-操作成功		!0-错误代码
***********************************************************************/
FAR U8 gam_fseek (gam_FILE *fhandle, U32 offset, U8 fromwhere)
{
    return fseek((FILE*)fhandle, offset, fromwhere);
}
/***********************************************************************
 * 说明:     将当前文件系统的文件读取函数封装为标准的fread函数
 * 输入参数: buf-缓冲	size-项长	count-项数	fhandle-句柄
 * 返回值  : 0-操作成功	!0-错误代码
***********************************************************************/
FAR U32 gam_fread(U8 *buf, U8 size, U16 count, gam_FILE *fhandle)
{
    return (U32)fread(buf, size, count, (FILE*)fhandle);
}
/***********************************************************************
 * 说明:     将当前文件系统的文件写入函数封装为标准的fwrite函数
 * 输入参数: fname-文件名		mode-操作方式
 * 返回值  : 0-操作成功		!0-错误代码
***********************************************************************/
FAR U32 gam_fwrite(U8 *buf, U32 size, U16 count, gam_FILE *fhandle)
{
    return (U32)fwrite(buf, size, count, (FILE*)fhandle);
}
/***********************************************************************
 * 说明:     将当前文件系统的文件指针查询函数封装为标准的ftell函数
 * 输入参数: fname-文件名	mode-操作方式
 * 返回值  : 资源项的数据长度
***********************************************************************/
FAR U32 gam_ftell(gam_FILE *fhandle)
{
    return (U32)ftell((FILE*)fhandle);
}
/***********************************************************************
 * 说明:     增强功能函数—按照页面方式将指定地址下的数据载入到常量页
 * 输入参数: bptr-常量页地址	addr-指定地址	fhandle-文件句柄
 * 返回值  : 被载入数据指针
***********************************************************************/
FAR U8 *gam_fload(U8 *bptr, U32 addr, gam_FILE *fhandle)
{
    return bptr + addr;
}
/***********************************************************************
 * 说明:     增强功能函数—修改文件名
 * 输入参数: fhandle-文件句柄	newname-新的文件名
 * 返回值  : 0-操作成功		!0-出错代码
***********************************************************************/
//FAR U8 gam_frename(gam_FILE *fhandle,U8 *newname)
//{
//	return 0;
//}
/***********************************************************************
 * 说明:     增强功能函数—文件删除
 * 输入参数: fhandle-文件句柄
 * 返回值  : 0-操作成功		!0-出错代码
***********************************************************************/
//FAR U8 gam_fdelete(gam_FILE *fhandle)
//{
//    return 0;
//}


FAR U8 *gam_freadall(gam_FILE *fhandle)
{
    U32 alloced = 1024*400;
    U8 buf[1024];
    U8 *rv = gam_malloc(alloced);
    U32 offset = 0;
    U32 cnt = 0;
    
    do {
        cnt = gam_fread(buf, 1, 1024, fhandle);
        if (offset + cnt > alloced) {
            alloced *= 2;
            rv = gam_realloc(rv, alloced);
        }
        memcpy(rv + offset, buf, cnt);
        offset += cnt;
    } while (cnt > 0);

    if (offset >= alloced) {
        rv = gam_realloc(rv, alloced+1);
    }
    rv[offset] = 0;
        
    return rv;
}

