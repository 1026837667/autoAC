
#define _CRT_SECURE_NO_WARNINGS   //vs 2013���ں���c���԰�ȫ�Ծ���  
#include <cstdio>  
#include <stdlib.h>
#include <iostream>  
#include <fstream>  
#include <string> 
#include <cstring>  
#include <regex>  
#include <vector> 
#include <ctime>
#include <queue>  
#include <algorithm>  
#include <winsock2.h> 
#include <windows.h>
#include <map> 
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
#pragma comment(lib, "ws2_32.lib")  

using namespace std;

void regexGetcom(string &allHtml);
bool analyUrl(char *url);
void GetCode(string &allHtml);
string ReplaceDiv(string &CodeHtml);

string ASCtoHex(int num);//ʮ����ת����ʮ������
string GetRescode(string &CodeHtml);

void GetResult(string &allHtml, int Prob);  //������state.php�еĽ�����ռ䣬ʱ��

char* U2G(const char* utf8);  //UTF-8��GB2312��ת��
char* G2U(const char* gb2312);  //GB2312��UTF-8��ת��


