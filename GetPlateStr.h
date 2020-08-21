#pragma once

// code by C


#include<stdio.h>
#include<ctype.h> //��Ҫʹ�õ��ж��ַ��ĺ���
#include<windows.h> //��Ҫʹ�õ�ϵͳ�ṩ�ļ��а�clipboard

int GetPlateString();

int GetPlateString() 
{
	char* pbuf = NULL;
	int i, count = 0;//count ��ʾ���ʵ�����
	char word[30];//�ַ����飬���浥��

	HANDLE hclip;//���а���

	//�򿪼��а壬��ȡ���������

	if (OpenClipboard(NULL) == 0)
	{
		printf("�򿪼��а�ʧ�ܣ�\n");
		return -1;
	}

	//���а嵱�е������ǲ����ı����͵�
	if (!IsClipboardFormatAvailable(CF_TEXT))
	{
		printf("���а嵱�е��������Ͳ�ƥ��!\n");
		CloseClipboard();//�رռ��а壬��Ȼ���������޷�����0ʹ�ü��а�
		return -1;
	}

	//��ȡ���а����������
	hclip = GetClipboardData(CF_TEXT);
	pbuf = (char*)GlobalLock(hclip);//����������һ��VOID���͵�ָ��
	GlobalUnlock(hclip);//����

	//���Լ��а��Ƿ���ʹ��

	//printf("%s\n",pbuf);

	//�ҳ������ļ��ĵ���

	while (1)
	{
		//���ǰ���ķ���ĸ�������ַ�
		while (*pbuf && !isalnum(*pbuf))
			++pbuf;
		//��������ַ���ĩβ���˳�ѭ��
		if (*pbuf == 0)
			break;
		i = 0;
		do {
			word[i] = *pbuf;//����ȡ������ĸ�������ַ�����word
			++pbuf;//��ָ��ָ����һ���ַ���
			++i;
		} while (*pbuf && isalnum(*pbuf));

		word[i] = '\0';//����ַ�������
		printf("%-30s", word);//����Ļ�ϴ�ӡ���õ���
		++count;

		if (count % 2 == 0)//ÿһ��ֻ��ӡ��������
			printf("\n");
	}

	printf("\n����%d���ʡ�\n", count);
	CloseClipboard();//�رռ��а壬��Ȼ���������޷�����0ʹ�ü��а�

	return 0;
}