#include "Htmlparse.h"
#include "Socket.h"
#include "SQLink.h"
vector <string> blogUrl;
string allHtml;
string CodeHtml;
string ResCode;
SOCKET sock;
char host[200];
char othPath[300];
char buf[1024];
int ProblemID;
char s[200];
string StateAns;
string StateSapce;
string StateTime;

int main()
{
	
	SQLinkInit();  //�������ݿ�

	for (ProblemID = 1000; ProblemID < 5508; ProblemID++) //����ſ�ʼˢ��
	{
		strcpy(host, "www.haosou.com");
		strcpy(othPath, "/s?ie=utf-8&shb=1&src=360sou_newhome&q=hdu+");
		_itoa(ProblemID, s, 10);
		strcat(othPath, s);
		strcat(othPath, "+csdn");

		//cout << othPath << endl;
		
		SendRequst(host, othPath);
		int n;
		allHtml = "";
		while ((n = recv(sock, buf, sizeof(buf)-1, 0)) > 0)
		{
			buf[n] = '\0';
			allHtml += buf;
		}
		closesocket(sock);
		regexGetcom(allHtml);  //��ȡ������ַ

		for (int i = 0; i < min(blogUrl.size(),3); i++)
		{
			InsertProb(i);    //��Ϣ�������ݿ�
			cout << blogUrl[i] << endl;

			char tmp[400];
			strcpy(tmp, blogUrl[i].c_str());  ///////���ﲻ�ܸĳ�i����������
			if (analyUrl(tmp) == false)
			{
				cout << "analyUrl��������" << endl;
				return 0;
			}
			SendRequst(host, othPath);
			//freopen("out.txt", "w", stdout);
			allHtml = "";
			while ((n = recv(sock, buf, sizeof(buf)-1, 0)) > 0)
			{
				buf[n] = '\0';
				allHtml += buf;
			}
			closesocket(sock);
			GetCode(allHtml);

			CodeHtml = ReplaceDiv(CodeHtml);
			char  *p=U2G(CodeHtml.c_str()); //�����֣�UTF-8����תΪGB

			CodeHtml = string(p);
		   // cout << CodeHtml;
	
			strcpy(tmp, "http://acm.hdu.edu.cn/submit.php?action=submit");
			if (analyUrl(tmp) == false)
			{
				cout << "analyUrl��������" << endl;
				return 0;
			}

			ResCode = GetRescode((string)p);
			
			cout << ResCode;
			SendCode(host, othPath, ResCode);

			//freopen("out.txt", "w", stdout);

			while ((n = recv(sock, buf, sizeof(buf)-1, 0)) > 0)
			{
				buf[n] = '\0';
				cout << buf;
			}

            //��������
			//Sleep(4000);
			char temp[400];
			strcpy(temp,"http://acm.hdu.edu.cn/status.php");  ///////���ﲻ�ܸĳ�i����������
			if (analyUrl(temp) == false)
			{
				cout << "analyUrl��������" << endl;
				return 0;
			}
			SendRequst(host, othPath);
			//freopen("out.txt", "w", stdout);
			allHtml = "";
			while ((n = recv(sock, buf, sizeof(buf)-1, 0)) > 0)
			{
				buf[n] = '\0';
				allHtml += buf;
			}

			GetResult(allHtml, ProblemID);

		    InsertState(i);

			closesocket(sock);

			Sleep(3000);
			//if (StateAns=="Accepted")
			//break;    //��ʱ�����ύһ��
			
		}
	}
	return 0;
}


