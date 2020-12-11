/********************************************************************
	����ʱ�䣺	2014/04/13 10: 01: 43
	�ļ�����		FileInfo.h
	���ߣ�		лС��
	
	���ܣ�		1. ������
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <vector>
#include <string>
//#include <direct.h>
//#include "OnLogDeal.h"

//ȫ�ֺ��� ��ʼ�� ����
class MyTools
{
public:
  /*
  fname:��ǰ��ִ��·�����ļ�����dataĿ¼���ļ���
  prints��Ҫ��ӡ��ֵ��һ��Ԫ�أ�std::string������Ҫ��ӡ��һ������
  isClear:�Ƿ��������
  strFl: ����ļ���
  */ 
  static void PrintToFile(std::string fname,std::vector<std::string> & prints,bool isClear=true);//��ӡ���

  /*
  fname: ��ǰ��ִ��·�����ļ�����dataĿ¼���ļ���
  reads�������洢��λ�ã�һ���ļ����ݴ浽һ��boost::string��
  strFl: ����ļ���
  */
  static bool ReadFromFile(std::string fname,std::vector<std::string> & reads, std::string strF = "");//��������
/*
	 ��ȡĿ¼�������ļ�����
	dir��Ŀ¼
	filenames���ļ��б�
	���Ƿ������Ŀ¼
	isImage:�Ƿ�ֻ����ͼƬ�ļ�
*/

  static int GetFilenames(const std::string& dir, std::vector<std::string>& filenames, bool isSubDir = true, bool isImage = false);

  //ɾ��һ���ļ�
  static bool Delete_File(const std::string & strPath);

  static bool FileIsExist(const std::string & strPath);//�ж��ļ��Ƿ����

  static int GetFilesize(const std::string &filename);//��ȡΪ�ļ���С

  static bool BuildDir(const std::string & strPath);//����Ŀ¼ ʹ��"/"


  //str ԭ���� strRegex��������ʽ
  static std::vector<std::string> RegexAnalysis(const std::string & str, const std::string & strRegex);//������ʽƥ��

  //ȡ�ò����ַ���
  static std::string FindFirstStr(std::string & strSrc,int n,bool isBlank = false);//isBlank �Ƿ����ո�
  static std::string FindLastStr(std::string & strSrc,int n,bool isBlank = false);

  //���˿ո�
  static void TrimBlank(std::string & strSrc,bool isfirst = true,bool isEnd = true);
  /*
  str��ԭ�ַ���
  nsplit����ֳ���
  addStr��������ַ���
  */
  //�и��ַ�������ӱ�����һ���µ��ַ���
  static std::string SplitString(std::string str, unsigned int nsplit = 4, const std::string addStr = ",");

  //�ָ��ַ���
  static std::vector<std::string> SplitString(std::string str,const std::string splitStr = ",");

  //�и��ַ��� �и�utf8�ַ���
  static std::vector<std::string> SplitStringUtf8(const std::string & str,unsigned int len);

  static void replace_all(std::string & Input, const std::string & Search, const std::string & Format);

  static std::string GetUtf8(const std::string & str);

  static std::string GetGBK(const std::string & str);

  static std::string GetGB2312(const std::string & str);

  static std::string BuildString(const std::string & str0,const std::string & str1);//�����ַ���


  static std::string GetCurrentDate(); // ��ȡ��ǰ��ʱ��

  static std::string GetCurrentDay(); // ��ȡ��ǰ������

  static void PrintError(const std::string & strerror);

  static std::string HexToBin(const std::string &strHex);//16����ת�������ַ���

  static std::string BinToHex(const std::string &strBin, bool bIsUpper = false);//�������ַ���ת16�����ַ���

  static std::string GetBigCamel(const std::string & str);//���շ���������
};

//�ڴ��� ����
#ifdef _WIN32
#define MEMORY_CHICK \
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);\
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;\
	_CrtSetDbgFlag(tmpFlag);
#else
#define MEMORY_CHICK 
#endif // _WIN32

#endif

