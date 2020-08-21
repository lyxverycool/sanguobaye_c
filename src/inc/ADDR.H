/******************************************************************************************
*				
*	Copyright (c)2002 , �㶫�����߽������ӷֹ�˾
*	All rights reserved.
**
*	�ļ����ƣ�addr.h
*	�ļ���ʶ��A600ϵͳ
*	ժ    Ҫ�����õ�ͷ�ļ�
*   ע    �⣺���ļ�Ҫ�� dictsys.h ���汻����
**
*	�޸���ʷ��
*	�汾    	����    	 ����    	 �Ķ����ݺ�ԭ��
*   ------		-------		---------	------------------------------
*	1.0    		2002.7.26   ���´�      ��ɻ�������
*******************************************************************************************/
#ifndef		DICTADDR_H
#define		DICTADDR_H
/*******************************************************************************************/
#define		MEM_HEAP_START				0x2c00		/* ���׵�ַ */
#define		MEM_HEAP_SIZE				0x1400		/* �Ѵ�С */

/*******************************************************************************************/
#define		SYS_DATA_LOG_BANK			0x9				/* ���� bank ���߼� bank ��*/
#define		SYS_DATA_BANK_NUM			0x4				/* ���� bank �ĸ��� */
#define		SYS_DATA_BANK_ADDR			0x9000			/* ���� bank �ĵĵ�ַ*/

/*******************************************************************************************/
#if			(DICT_PHY_VER == VER_USR_DEBUG)
#define		SYS_PHY_START_ADDR		0xf80000		/* Ŀǰ 512K ������ĳ���ռ���ʼ��ַ */

#elif		(DICT_PHY_VER == VER_RXC_DEBUG)
#define		SYS_PHY_START_ADDR		0xf00000		/* Ŀǰ 1M ������ĳ���ռ���ʼ��ַ */

#elif		(DICT_PHY_VER == VER_RXC_DOWN)
#define		SYS_PHY_START_ADDR		0xf80000		/* Ŀǰ 512 ������ĳ���ռ���ʼ��ַ */

#elif		(DICT_PHY_VER == VER_RXC_RELEASE)
#define		SYS_PHY_START_ADDR		0xea0000  /*0xe00000*/		/* Ŀǰ 2M ������ĳ���ռ���ʼ��ַ */
#endif
/*********************************************************************************************/
#define			DATA_BANK_SIZE			0x4000
#define			SHELL_DATA_ADDR			0x30000
#define			APP_DATA_START_ADDR		0x130000
/*********************************************************************************************/
#if			(DICT_PHY_VER == VER_RXC_RELEASE )
#define	FONT_DATA_BASE_ADDR			0x80
#else
#define	FONT_DATA_BASE_ADDR			0x40
#endif

/*********************************************************************************************/
#define		STUDY_PHY_DATA_ADDR		0x894000		/* ѧϰ����������ַ */
#define		DATA_PHY_ADDR			0x7b0000		/* ���ϵ�ַ */

#define		DICT_SPL_DATA1			0x0400000		/* ����ʵ����� 1*/
#define		DICT_SPL_DATA2			0x0400000		/* ����ʵ����� 2*/

#endif