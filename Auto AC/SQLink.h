#include "Htmlparse.h"

_ConnectionPtr pMyConnect;
string strqlk;
extern string StateAns;
extern string StateSapce;
extern string StateTime;
extern string CodeHtml;
extern char s[200];
extern vector <string> blogUrl;

void SQLinkInit()   
{
	CoInitialize(NULL);//��ʼ��Com��
	pMyConnect = NULL;//���Ǹ�����ָ�룬���ڶ���ָ������ݿ��԰ٶ�һ�£����������Ҳ������
	HRESULT hr = pMyConnect.CreateInstance(__uuidof(Connection));
	//������ָ��ʵ����
	if (FAILED(hr))
	{
		cout << "_ConnectionPtr����ָ��ʵ����ʧ�ܣ�" << endl;
		return ;
	}
	_bstr_t strConnect = "Driver={sql server};server=Tach-PC\\SQLEXPRESS;uid=tach1;pwd=123456;database=ProblemSolved";  //SQLSERVER
	//�������ӵ�SQL SERVER���ݿ�������ַ��������еĲ���Ҫ�Լ���
	try{
		pMyConnect->Open(strConnect, "", "", NULL);
	}//���ӵ����ݿ⣬Ҫ��׽�쳣
	catch (_com_error &e){
		cout << "�������ݿ��쳣��" << endl;
		cout << e.ErrorMessage() << endl;
	}

	_RecordsetPtr m_pRecordset;//��¼������ָ�룬����ִ��SQL��䲢��¼��ѯ���
	if (FAILED(m_pRecordset.CreateInstance(__uuidof(Recordset))))
	{
		cout << "��¼������ָ��ʵ����ʧ�ܣ�" << endl;
		return ;
	}

	char sSql[] = "SELECT* FROM Problem";//���������_variant_t�����ͣ�һ��COM�������ͣ�����_bstr_tҲ�ǣ�

	try{
			m_pRecordset->Open((_variant_t)sSql,
			pMyConnect.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic, adCmdText);//�����ݿ⣬ִ��SQL���
	}
	catch (_com_error &e)
	{

		cout << "ִ��������" << endl;
		cout << e.ErrorMessage() << endl;
	}

	//SQL���ִ����ϣ���ȡ��ѯ���
	/*try
	{
		m_pRecordset->MoveFirst(); //��¼��ָ���ƶ�����ѯ�������ǰ��
		while (m_pRecordset->EndOfFile == VARIANT_FALSE)
		{
			//����Ͷ�ȡemp���еĹ�Ա������
			char *sName = (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("probnum"))->Value);
			cout << (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("probnum"))->Value) << endl;
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		cout << "��ȡ�������" << endl;
		cout << e.ErrorMessage() << endl;
	}*/

}

void InsertProb(int i)
{
	//��������
	try{
	//pMyConnect.CreateInstance(__uuidof(Connection));

		char strsql[300] = "insert into Problem values(";
		strcat(strsql, s);
		strcat(strsql, ",'");
		strcat(strsql, blogUrl[i].c_str());
		strcat(strsql, "','");
		strcat(strsql, "hdu");
		strcat(strsql, "')");
		cout << strsql << endl;
		//char strsql[] = "insert into Problem values(1002,'34','hdu')";
		_variant_t RecordsAffected;
		pMyConnect->Execute(_bstr_t(strsql), &RecordsAffected, adCmdText);
	}
	catch (_com_error &e)
	{
		cout << "�������ݴ���" << endl;
		cout << e.ErrorMessage() << endl;
	}
	
}


void InsertState(int i)
{
	//��������
	try{

		char kk[10];
		_itoa(i+1, kk, 10);
	   strqlk = "";
	   strqlk = strqlk + "insert into CodeState values('" + blogUrl[i] + "',"+(string)kk+",'" + StateAns + "','" + CodeHtml + "','" + StateSapce + "','" + StateTime + "')";

		cout << strqlk << endl;
		//char strsql[] = "insert into Problem values(1002,'34','hdu')";
		_variant_t RecordsAffected;
		pMyConnect->Execute(_bstr_t(strqlk.c_str()), &RecordsAffected, adCmdText);
		//pMyConnect->Execute(_bstr_t(strsql), NULL, adCmdText);
		}
	catch (_com_error &e)
	{
		cout << "�������ݴ���" << endl;
		cout << e.ErrorMessage() << endl;
	}
	
}

