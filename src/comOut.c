/***********************************************************************
 *Copyright (c)2005 , 东莞步步高教育电子分公司
 *All rights reserved.
 **
 文件名称：	comOut.c
 *文件标识：	步步高电子词典的游戏引擎模块
 *摘要：		封装引擎对系统显示程序调用的入口
 **
 *移植性声明:
 *	1、符合标准：《游戏设计标准V1.0》
 *	2、兼容模式：本程序和界面无关，无兼容模式。
 *	3、使用本封装程序的引擎要移植到其他环境中，系统的显示部分只需在此修改
 *修改历史：
 *	版本    日期     作者     改动内容和原因
 *   ----------------------------------------------------
 *	1.0    2005.5.16  高国军     基本的功能完成
 ***********************************************************************/
/* 声明本文件可以直接调用系统底层函数宏 */
#define		_BE_CHANGED_
#include "baye/stdsys.h"
#include "baye/comm.h"
#include "baye/enghead.h"
#include "touch.h"
#include "baye/script.h"

/* 当前所在文件 */
#define		IN_FILE		21

/*本体函数声明*/
/*------------------------------------------*/
U32	CountHZMAddrOff(U16 Hz);
void	GamResumeSet();
void	GamAscii(PT x,PT y,U8 asc);
void	GamChinese(PT x,PT y,U16 Hz);
void	GetExcHZMCode(U16 Hz,U8 *hzmCode);

/***********************************************************************
 * 说明:     游戏系统信息框(不保存背景)
 * 输入参数: buf-信息内容	delay-延时(秒)
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamMsgBox(const U8 *buf,U8 delay)
{
    U8	h,s;
    U8	slen;

    c_Sx = WK_SX + 5;
    c_Ex = WK_EX - 4;
    slen = gam_strlen(buf);
    h = (WK_EX - WK_SX) / ASC_WID - 2;
    s = slen / h + 1;
    if(s > (WK_EY - WK_SY) / ASC_HGT - 1)
    {
        c_Sy = WK_SY+5;
        c_Ey = WK_EY-5;
    }
    else
    {
        s *= ASC_HGT;
        c_Sy = (WK_EY - WK_SY - s) >> 1;
        c_Sy += WK_SY;
        c_Ey = c_Sy + s;
    }
    gam_clrlcd(c_Sx-3,c_Sy-3,c_Ex+3,c_Ey+2);
    gam_rect(c_Sx-3,c_Sy-3,c_Ex+3,c_Ey+2);
    GamStrShowS(c_Sx,c_Sy,buf);
    if(delay == 0)
        return;
    GamDelay(delay*100, 2);
}
/***********************************************************************
 * 说明:     显示虚拟屏幕到屏幕
 * 输入参数: vscr-虚拟屏幕指针
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamShowFrame(U8 *vscr)
{
    gam_copyscr(vscr);
}

FAR void GamPicShow(PT x,PT y,PT wid,PT hgt,U8 *pic)
{
    wid-=1;
    hgt-=1;
    SysPicture(x,y,x+wid,y+hgt,pic,0, 1);
}

/***********************************************************************
 * 说明:     显示图片到屏幕
 * 输入参数: x,y-显示坐标	wid,hgt-图片尺寸	pic-图片数据
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamPicShowS(PT x,PT y,PT wid,PT hgt,U8 *pic)
{
    gam_selectscr(NULL);
    GamPicShow(x, y, wid, hgt, pic);
}
/***********************************************************************
 * 说明:     显示图片到虚拟屏幕
 * 输入参数: x,y-显示坐标	wid,hgt-图片尺寸	pic-图片数据
 *	   : vscr-虚拟屏幕指针
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamPicShowV(PT x,PT y,PT wid,PT hgt,U8 *pic,U8 *vscr)
{
    gam_selectscr(vscr);
    GamPicShow(x, y, wid, hgt, pic);
}


FAR void GamMPicShow(PT x,PT y,PT wid,PT hgt,U8 *pic)
{
    U16 pLen = (wid+7) / 8 * hgt;
    SysPicture(x,y,x+wid-1,y+hgt-1,pic,1, 1);
    SysPicture(x,y,x+wid-1,y+hgt-1,pic+pLen,2, 1);
}
/***********************************************************************
 * 说明:     显示mask图片到屏幕
 * 输入参数: x,y-显示坐标	wid,hgt-图片尺寸	pic-图片数据
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamMPicShowS(PT x,PT y,PT wid,PT hgt,U8 *pic)
{
    gam_selectscr(NULL);
    GamMPicShow(x, y, wid, hgt, pic);
}

/***********************************************************************
 * 说明:     显示mask图片到虚拟屏幕
 * 输入参数: x,y-显示坐标	wid,hgt-图片尺寸	pic-图片数据
 *	   : vscr-虚拟屏幕指针
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamMPicShowV(PT x,PT y,PT wid,PT hgt,U8 *pic,U8 *vscr)
{
    gam_selectscr(vscr);
    GamMPicShow(x, y, wid, hgt, pic);
}
/***********************************************************************
 * 说明:     显示图片到屏幕(功能扩展——可显示图片上面的部分)
 * 输入参数: x,y-显示坐标	wid,hgt-图片尺寸	idx-图片序号(从0开始)
 *	  : pic-图片数据(包括图片头)
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamPicShowEx(PT x,PT y,PT wid,PT hgt, U16 idx, U8 *pic)
{
    U8	mask;
    U8	pwid,phgt;
    U16	pLen;

    pwid = ((PictureHeadType *)pic)->wid;
    phgt = ((PictureHeadType *)pic)->hig;
    mask = ((PictureHeadType *)pic)->mask & 0x01;
    pLen = pwid >> 3;
    if(pwid&0x07) pLen += 1;
    pLen *= phgt;
    pic += pLen * idx + PICHEAD_LEN;
    if(HV_MASK == mask)
        GamMPicShow(x, y, wid, hgt, pic);
    else
        GamPicShow(x,y,wid,hgt,pic);
}

/***********************************************************************
 * 说明:     显示12字符串到屏幕
 * 输入参数: x,y-显示坐标	str-数据缓冲
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR U32 GamStrShowS(PT x,PT y,const U8 *str)
{
    gam_selectscr(NULL);
    return GamStrShow(x, y, str);
}
/***********************************************************************
 * 说明:     显示12字符串到虚拟屏幕
 * 输入参数: x,y-显示坐标	str-数据缓冲	vscr-虚拟屏幕
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR U32 GamStrShowV(PT x,PT y,U8 *str,U8 *vscr)
{
    gam_selectscr(vscr);
    return GamStrShow(x,y,str);
}
/***********************************************************************
 * 说明:     初始化游戏引擎所在的机型环境
 * 输入参数: 无
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamResumeSet()
{
    /*恢复字符串显示区域*/
    if(c_ReFlag)
    {
        c_Sx = WK_SX;
        c_Sy = WK_SY;
        c_Ex = WK_EX;
        c_Ey = WK_EY;
    }
}
/***********************************************************************
 * 说明:     显示12字符串
 * 输入参数: 无
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U32 GamStrShow(PT x,PT y,const U8 *buf)
{
    U16	i,wid;
    U16	hzCode;

    if (y+HZ_HGT > c_Ey) return 0;

    for(i=0; buf[i] != '\0'; i++)
    {
        hzCode=buf[i];

        if(hzCode=='\n')
        {
            x=c_Sx;
            y+=HZ_HGT;
            if(y>c_Ey) break;
            continue;
        }
        if(hzCode<0x80)
            wid=ASC_WID-1;
        else
            wid=HZ_WID-1;
        if(x+wid>c_Ex)
            x+=wid;
        if(x>c_Ex)
        {
            x=c_Sx;
            if(x + wid > c_Ex) break;
            y+=HZ_HGT;
            if(y + HZ_HGT>c_Ey) break;
        }
        if(hzCode<0x80)
        {
            GamAscii(x,y,hzCode);
            x+=6;
        }
        else
        {
            i+=1;
            hzCode<<=8;
            hzCode+=buf[i];
            GamChinese(x,y,hzCode);
            x+=12;
        }
    }
    GamResumeSet();
    return i;
}
/***********************************************************************
 * 说明:     显示12*12点阵GB2312汉字
 * 输入参数: x,y	->显示坐标	Hz	->要显示的汉字内码
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2004.6.2        基本完成
 ***********************************************************************/
void GamChinese(PT x,PT y,U16 Hz)
{
    U8 zmCode[24];

    GetExcHZMCode(Hz,zmCode);
    SysPicture(x,y,x+HZ_WID-1,y+HZ_HGT-1,zmCode, 0, 2);
}
/***********************************************************************
 * 说明:     显示12*12点阵GB2312AscII
 * 输入参数: x,y	->显示坐标	asc	->要显示的AscII
 * 返回值  :
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2004.6.2        基本完成
 ***********************************************************************/
void GamAscii(PT x,PT y,U8 asc)
{
    U16 ascCode;
    U8  i,zmCode[24];

    if(asc <= ' ')
        gam_memset(zmCode,0,24);
    else
    {
        ascCode=GAM_FONT_ASC_QU;
        ascCode<<=8;
        ascCode+=asc-0x21+0xA1;		/* 汉字字模从'!'开始*/

        GetExcHZMCode(ascCode,zmCode);
        for(i=0;i<12;i++)
            zmCode[i]=zmCode[i<<1];
    }
    SysPicture(x,y,x+ASC_WID-1,y+ASC_HGT-1,zmCode,0, 2);
}
/***********************************************************************
 * 说明:     获取扩充后的汉字字模数据(18->24)
 * 输入参数: Hz	->汉字内码	hzmCode	->扩充后的数据buf
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2004.6.2        基本完成
 ***********************************************************************/
void GetExcHZMCode(U16 Hz,U8 *hzmCode)
{
    /*字模页号偏移 是否跨bank */
    U8  buf[18];
    U8  i,j,k;
    U32 hzmAddr;

    /* 当前要显示的汉字不是2312GB中的汉字，调试模式下显示黑块，释放模式下显示白块 */
    if((U8)(Hz>>8) < 0xA1)
    {
        I32 index = -1;
        IF_HAS_HOOK("fontImageForChar") {
            U16 code = Hz;
            BIND_U16(&code);
            BIND_U32(&index);
            CALL_HOOK_S();
        }
        if (index >= 0) {
            PictureHeadType* head = (PictureHeadType*)ResLoadToCon(MAIN_SPE,2,g_CBnkPtr);
            if (index < head->count) {
                U32 len = (head->wid + 7) / 8 * head->hig;
                U8 *data = (U8*)(&head[1]);
                gam_memcpy(hzmCode, &data[len * index], len);
                return;
            }
        }
        
#if	GAM_VER==GAM_DEBUG_MODE
        gam_memset(hzmCode,0xFF,24);
        return;
#else
        gam_memset(hzmCode,0,24);
        return;
#endif
    }
    else
    {
        hzmAddr=CountHZMAddrOff(Hz);
        memset(buf, 18, 2);
        gam_fseek(g_FontFp,hzmAddr,SEEK_SET);
        gam_fread(buf,1,18,g_FontFp);
    }

    /*转换数据*/
    for(i=0;i<6;i++)
    {
        j = i * 4;
        k = i * 3;
        hzmCode[j]=buf[k];
        hzmCode[j+1]=buf[k+1]&0xf0;
        hzmCode[j+2]=(buf[k+1]&0x0f)<<4;
        hzmCode[j+2]+=(buf[k+2]&0xf0)>>4;
        hzmCode[j+3]=(buf[k+2]&0x0f)<<4;
    }
}
/***********************************************************************
 * 说明:     计算要显示的汉字字模地址偏移
 * 输入参数: Hz	->汉字内码
 * 返回值  : 该汉字字模在字库中的地址偏移
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2004.6.2        基本完成
 ***********************************************************************/
U32 CountHZMAddrOff(U16 Hz)
{
    /*计算公式:(94*(HCode-0xA1)+(LCode-0xA1))*18 */
    U32 hCode, lCode;
    hCode = Hz >> 8;
    lCode = Hz & 0xff;
    return (94*(hCode - 0xA1) + (lCode-0xA1)) * 18;
}

/******************************************************************************
 * 函数名:GamAsciiS
 * 说  明:封装函数，显示12*12点阵GB2312AscII到屏幕
 *
 * 入口参数：x,y	->显示坐标	asc	->要显示的AscII
 *
 * 出口参数：无
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-23 16:13	基本功能完成
 ******************************************************************************/
FAR void GamAsciiS(PT x,PT y,U8 asc)
{
    GamAscii(x,y,asc);
}

FAR void GamClearScreenV(PT l, PT t, PT r, PT b, U8*scr) {
    gam_selectscr(scr);
    SysLcdPartClear(l, t, r, b);
}

FAR void gam_clrlcd(PT x1,PT y1,PT x2,PT y2)
{
    gam_selectscr(NULL);
    SysLcdPartClear(x1, y1, x2, y2);
}

FAR void gam_clslcd(void)
{
    gam_selectscr(NULL);
    SysLcdPartClear(0,0,SCR_WID-1,SCR_HGT-1);
}

FAR void gam_revlcd(PT x1,PT y1,PT x2,PT y2)
{
    gam_selectscr(NULL);
    SysLcdReverse(x1, y1, x2, y2);
}

FAR void gam_putpixel(PT x,PT y,U8 data)
{
    gam_selectscr(NULL);
    SysPutPixel(x, y, data);
}

FAR void gam_line(PT x1,PT y1,PT x2,PT y2)
{
    gam_selectscr(NULL);
    SysLine(x1, y1, x2, y2);
}

FAR void gam_rect(PT x1,PT y1,PT x2,PT y2)
{
    gam_selectscr(NULL);
    SysRect(x1, y1, x2, y2);
}

FAR void gam_rectc(PT x1,PT y1,PT x2,PT y2)
{
    gam_selectscr(NULL);
    SysRectClear(x1, y1, x2, y2);
}

FAR void gam_usescr(U8 scr)
{
    gam_selectscr(scr ? g_VisScr : NULL);
}
