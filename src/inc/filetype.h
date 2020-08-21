/******************************************************************************************
*				
*	Copyright (c)2002 , 广东步步高教育电子分公司
*	All rights reserved.
**
*	文件名称：filetype.h
*	文件标识：A600系统
*	摘    要：A600系统文件类型定义
**
*	修改历史：
*	版本    	日期    	 作者    	 改动内容和原因
*   ------		-------		---------	------------------------------
*	1.0    		2002.11.26   任新村      完成基本内容
*******************************************************************************************/
#ifndef		FILETYPE_H
#define		FILETYPE_H

#ifndef		DICTSYS_H
#include	"dictsys.h"
#endif


/******************************************************************************************
*					 公司申明 
*******************************************************************************************/
#define		STR_CORP_NAME			"BBK LTD."					

/******************************************************************************************
*					文件头中的文件类型定义，电脑端文件扩展名
*******************************************************************************************/
#define		FT_DICT					"DIC"						/* 词典类型 */
#define		FT_RECITE				"RCT"						/* 背诵 */
#define		FT_STUDY				"STD"						/* 学习 */
#define		FT_CALC					"CAC"						/* 计算 */
#define		FT_DATA					"DAT"						/* 资料,电子图书 */
#define		FT_MEMO					"MEM"						/* 名片记事类 */
#define		FT_TIME					"TIM"						/* 时间类 */
#define		FT_GAME					"GAM"						/* 游戏 */
#define		FT_DOWNLOAD				"DWN"						/* 下载 */
#define		FT_SYSTEM				"SYS"						/* 系统 */

#define		FT_TXT					"TXT"						/* 纯文本，非内部整理的格式 */
#define		FT_BMP					"BMP"						/* 静态位图 */
#define		FT_ANI					"ANI"						/* 动画，没声音 */
#define		FT_MOVIE				"MOV"						/* 动画，有声音 */
#define		FT_RING					"RNG"						/* 铃声 */

#define		FT_APP					"APP"						/* 其他应用程序类 */
/******************************************************************************************
*					版本号定义
*
*	注意：	版本号只是资料的版本标志，和系统没有直接的关系，也就是说，系统版本升级了，
* 某格式版本号的版本号可以还是以前的，同一个系统，可能支持不同版本的某类文件
*	
*******************************************************************************************/
#define		DICT_VER_A100				0x0010		/* 下载王目前所有资料的起始版本号 */

/******************************************************************************************
*					公共头结构
*******************************************************************************************/
#define		DOWN_COMM_HEAD_LEN			64
#define		DOWN_DATA_TITLE_LEN			32

typedef		struct	tagSysCommFileHead
{
	U8		strFileType[4];					/* 文件格式，为字符串格式 */
	U16		nVer;							/* 版本号 */
	U8		strTitle[DOWN_DATA_TITLE_LEN];	/* 标题 */
	U8		strCorpName[16];				/* 公司名称等声明 */
	U8		executable;						/* 可执行否，资料和词典也可以带程序 */
	U8		res[9];							/* 保留，填充 */
}TypeSysCommFileHead,*PtrSysCommFileHead;

/******************************************************************************************
*					下载程序结构
*******************************************************************************************/
typedef		struct		DownAppHeadTag				/* 下载程序头格式 */
{
	TypeSysCommFileHead		commHead;				/* 公共头 */
	U16						entry;					/* 入口地址 */
	U32						dataOffset;				/* 数据偏移地址 */
}TypeDownAppHead,*PtrDownAppHead;

/******************************************************************************************
*					词典端文件存储类型
******************************************************************************************/
#define		FTH_DICT		0x3b					/* 词典			*/
#define		FTH_RECITE		0x35					/* 背诵			*/
#define		FTH_STUDY		0x39					/* 学习			*/
#define		FTH_CALC		0x36					/* 计算			*/
#define		FTH_DATA		0x3e					/* 资料			*/
#define		FTH_MEMO		0x37					/* 名片			*/
#define		FTH_TIME		0x38					/* 时间			*/
#define		FTH_DOWNLOAD	0x33					/* 下载			*/
#define		FTH_GAME		0x3d					/* 游戏			*/
#define		FTH_SYSTEM		0x34					/* 系统			*/

#define		FTH_BOOK		0x3f					/* 电子图书		*/
#define		FTH_LOGO		0x3a					/* 开机画面		*/
#define		FTH_RING		0x11					/* 开机铃声		*/

#define		FTH_APP			0x3c					/* 应用程序		*/
#define		FTH_NULL		0xfe					/* 无此类程序		*/

#endif		/* FILETYPE_H */


