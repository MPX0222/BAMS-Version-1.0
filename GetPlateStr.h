#pragma once

// code by C


#include<stdio.h>
#include<ctype.h> //需要使用到判断字符的函数
#include<windows.h> //需要使用到系统提供的剪切板clipboard

int GetPlateString();

int GetPlateString() 
{
	char* pbuf = NULL;
	int i, count = 0;//count 表示单词的数量
	char word[30];//字符数组，保存单词

	HANDLE hclip;//剪切板句柄

	//打开剪切板，获取里面的数据

	if (OpenClipboard(NULL) == 0)
	{
		printf("打开剪切板失败！\n");
		return -1;
	}

	//剪切板当中的数据是不是文本类型的
	if (!IsClipboardFormatAvailable(CF_TEXT))
	{
		printf("剪切板当中的数据类型不匹配!\n");
		CloseClipboard();//关闭剪切板，不然其他程序无法正常0使用剪切板
		return -1;
	}

	//获取剪切板里面的数据
	hclip = GetClipboardData(CF_TEXT);
	pbuf = (char*)GlobalLock(hclip);//加锁，返回一个VOID类型的指针
	GlobalUnlock(hclip);//解锁

	//测试剪切板是否能使用

	//printf("%s\n",pbuf);

	//找出所有文件的单词

	while (1)
	{
		//清除前导的非字母和数字字符
		while (*pbuf && !isalnum(*pbuf))
			++pbuf;
		//如果到了字符串末尾就退出循环
		if (*pbuf == 0)
			break;
		i = 0;
		do {
			word[i] = *pbuf;//将读取到的字母或数字字符赋给word
			++pbuf;//将指针指向下一个字符处
			++i;
		} while (*pbuf && isalnum(*pbuf));

		word[i] = '\0';//添加字符串结束
		printf("%-30s", word);//在屏幕上打印出该单词
		++count;

		if (count % 2 == 0)//每一行只打印两个单词
			printf("\n");
	}

	printf("\n共有%d单词。\n", count);
	CloseClipboard();//关闭剪切板，不然其他程序无法正常0使用剪切板

	return 0;
}