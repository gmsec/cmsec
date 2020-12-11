#include "tools.h"
#include <mutex>
#include <filesystem>
#include <fstream>
#include <cassert>
#include<regex>
#include <codecvt>
#include <locale>
#include <map>
#ifdef _WIN32
#include <direct.h>
#pragma warning(disable:4996)
#else
#include <time.h>
#include <sys/stat.h> 
#endif // _WIN32







//#define MAX_WAIT_TIME 60
//using namespace boost::xpressive;//正则表达式库

std::mutex g_oMutex;
void MyTools::PrintToFile( std::string fname,std::vector<std::string> & prints,bool isClear)
{
	std::scoped_lock oLock(g_oMutex);//互斥锁
	//MessageBox(nullptr,fname.c_str(),"写文件",MB_OK);
	setlocale(LC_ALL, "chs");
	std::string path = fname; // GetModulePath(strF, fname);
	namespace fs = std::filesystem;
	if (!fs::exists(path.c_str())) { // 创建目录
		fs::create_directory(path.c_str());
	}

	std::ofstream ofs(path.c_str(), (isClear ? (std::ios_base::out | std::ios::trunc) : (std::ios_base::app | std::ios::ate)));
	if (ofs.is_open())//如果打开了
	{
		std::vector<std::string>::const_iterator it = prints.begin();
		while(it != prints.end())
		{
			ofs<<*it<<std::endl;
			it++;
		}
		ofs.close();
	}
	else//没有打开
		assert(false);
}

bool MyTools::ReadFromFile( std::string fname,std::vector<std::string> & reads, std::string strF)
{
	reads.clear();//清除老元素

	setlocale(LC_ALL, "chs");
	std::string path = fname;
	std::ifstream ifs(path.c_str(),std::ios::in);
	if (ifs.is_open())//如果打开了
	{
		std::string str;
		while(!ifs.eof())
		{
			std::getline(ifs,str);
			if (str.length() >0)//空行取消存取
				reads.push_back(str);
		}
		ifs.close();

		return true;
	}
	else//没有打开
		return false;

}


int MyTools::GetFilenames(const std::string& dir, std::vector<std::string>& filenames, bool isSubDir /*= true */, bool isImage /*= false*/)
{
	filenames.clear();
	std::filesystem::path path(dir);
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directories(path);//创建目录	
		//boost::filesystem::create_directory(path);//创建目录(不能创建数型目录)	
		return -1;
	}

	std::filesystem::directory_iterator end_iter;
	for (std::filesystem::directory_iterator iter(path); iter != end_iter; ++iter)
	{
		if (std::filesystem::is_regular_file(iter->status()))
		{
			std::string ext = ".JPEG.JPG.TIFF.TIF.BMP.GIF.PNG.jpeg.jpg.tiff.tif.bmp.gif.png";
			if (!isImage || ext.find(iter->path().extension().string()) != std::string::npos)
				filenames.push_back(iter->path().filename().string());
		}
		else if (std::filesystem::is_directory(iter->status()))
		{
			if (isSubDir)//查找子目录
			{
				GetFilenames(iter->path().string(), filenames, isSubDir, isImage);
			}
			else
			{
				//boost::filesystem::remove(iter->path());//删除文件
				// std::filesystem::remove_all(iter->path());//删除目录
			}
		}
	}

	return filenames.size();
}

bool MyTools::Delete_File(const std::string & strPath)
{
	std::filesystem::path path(strPath);
	if (std::filesystem::exists(path))
		std::filesystem::remove(path);//删除文件

	return true;
}

bool MyTools::FileIsExist(const std::string & strPath)
{
	std::filesystem::path path(strPath);
	return std::filesystem::exists(path);
}


int MyTools::GetFilesize(const std::string &filename)
{
	struct stat f_stat;
	if (stat(filename.c_str(), &f_stat) == -1)
	{
		return -1;
	}
	return f_stat.st_size;
}

bool MyTools::BuildDir(const std::string & strPath)
{
	size_t loc = strPath.rfind("/", strPath.length());
	if (loc != std::string::npos)
	{
		std::string dir(strPath.begin(), strPath.begin() + loc);
		std::filesystem::path path_file(dir);
		if (std::filesystem::exists(path_file) &&
			std::filesystem::is_directory(path_file))
		{
			return true;
		}
		else
		{
			namespace fs = std::filesystem;
			if (!fs::exists(dir.c_str())) { // 创建目录
				fs::create_directory(dir.c_str());
			}

			std::filesystem::path path_file1(dir);
			return std::filesystem::exists(path_file1) && std::filesystem::is_directory(path_file1);
		}
			
	}

	return true;
}

std::vector<std::string> MyTools::RegexAnalysis(const std::string & str, const std::string & strRegex)
{
	std::regex pattern(strRegex, std::regex::icase);//更新的正则表达式不会变的，故为了加快速度，icase表示大小写不敏感
	//迭代器声明
	std::string::const_iterator iter = str.begin();
	std::string::const_iterator iterEnd = str.end();
	std::smatch result;
	std::vector<std::string> ver;
	 //正则查找
	while (std::regex_search(iter, iterEnd, result, pattern))
	{
		ver.insert(ver.end(),result.begin(),result.end());
	    iter = result[0].second; //更新搜索起始位置
	}
	
	return ver;
}

std::string MyTools::FindFirstStr( std::string & strSrc,int n,bool isBlank )
{
	auto str = strSrc.substr(0,n);
	if (!isBlank)
	{
		if (isspace(str[0])) {
			str = str.substr(1);
		}
		if (str.length() > 0) {
			if (isspace(str[str.length() - 1])) {
				str = str.substr(0, str.length() - 1);
			}
		}
	}
	return str;
}

std::string MyTools::FindLastStr( std::string & strSrc,int n,bool isBlank )
{
	auto index = strSrc.length() - n;
	if (index < 0)// offset
		index = 0;

	auto str = strSrc.substr(index);
	if (!isBlank)
	{
		if (isspace(str[0])) {
			str = str.substr(1);
		}
		if (str.length() > 0) {
			if (isspace(str[str.length() - 1])) {
				str = str.substr(0, str.length() - 1);
			}
		}
	}
	return str;
}

void MyTools::TrimBlank(std::string & strSrc,bool isfirst /*= true*/, bool isEnd /*= true*/)
{
	if (isfirst && isspace(strSrc[0]))
		strSrc = strSrc.substr(1);
	if (isEnd && strSrc.length() > 0 && isspace(strSrc[strSrc.length() - 1])) {
		strSrc = strSrc.substr(0, strSrc.length() - 1);
	}
}

std::string MyTools::SplitString(std::string str, unsigned int nsplit /*= 4*/, const std::string addStr /*= ","*/)
{
	std::string strTemp(str.rbegin(),str.rend());
	std::string strResult = "";
	int n = 0;
	while(true)
	{
		n = (strTemp.length() > nsplit) ? nsplit:strTemp.length();
		strResult.append(FindFirstStr(strTemp, n, true));
		strTemp = FindLastStr(strTemp,strTemp.length() - n,true);
		if (strTemp.length() != 0)
			strResult.append(addStr);
		else
			break;
	}
	return std::string(strResult.rbegin(), strResult.rend());
}

std::vector<std::string> MyTools::SplitString(std::string str, const std::string splitStr /*= ","*/)
{
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(splitStr);
	std::sregex_token_iterator first{ str.begin(), str.end(), re, -1 }, last;
	return { first, last };

}

std::string MyTools::GetUtf8(const std::string & str)
{
	std::vector<wchar_t> buff(str.size());
#ifdef _MSC_VER
	std::locale loc("zh-CN");
#else
	std::locale loc("zh_CN.GB18030");
#endif
	wchar_t* pwszNext = nullptr;
	const char* pszNext = nullptr;
	mbstate_t state = {};
	int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
		(loc).in(state,str.data(), str.data() + str.size(), pszNext,
			buff.data(), buff.data() + buff.size(), pwszNext);
	if (std::codecvt_base::ok == res)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
		return cutf8.to_bytes(std::wstring(buff.data(), pwszNext));
	}
	return "";
	// 	return boost::locale::conv::between(str,"UTF-8","GBK");
}

std::string MyTools::GetGBK(const std::string & str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
	std::wstring wTemp = cutf8.from_bytes(str);
#ifdef _MSC_VER
	std::locale loc("zh-CN");
#else
	std::locale loc("zh_CN.GB18030");
#endif
	const wchar_t* pwszNext = nullptr;
	char* pszNext = nullptr;
	mbstate_t state = {};
	std::vector<char> buff(wTemp.size() * 2);
	int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
		(loc).out(state,
			wTemp.data(), wTemp.data() + wTemp.size(), pwszNext,
			buff.data(), buff.data() + buff.size(), pszNext);
	if (std::codecvt_base::ok == res)
	{
		return std::string(buff.data(), pszNext);
	}
	return "";

	//return boost::locale::conv::between(str, "GBK", "UTF-8");
}

std::string MyTools::GetGB2312(const std::string & str)
{
	return GetGBK(str);

	// return boost::locale::conv::between(str, "GBK", "UTF-8");
}

std::vector<std::string> MyTools::SplitStringUtf8(const std::string & str,unsigned int len)
{
	int size = str.length();
	std::string strTemp;
	std::vector<std::string> verStr;
	int n = 0;
	int n1 = 0;
	int i = 0;
	while (i<size)
	{
		if (str[i] > 0)//直接添加
		{
			strTemp.append(1,str[i]);
			i++;
			n1++;
		}
		else
		{
			strTemp.append(str.begin() + i, str.begin() + i + 3);
			i += 3;
			n++;
		}

		
		if ((n + (n1+1)/2 ) == len)
		{
			verStr.push_back(strTemp);
			strTemp.clear();
			n = 0;
			n1 = 0;
		}
	}

	if (strTemp.length() > 0)
		verStr.push_back(strTemp);

	return verStr;
}

void MyTools::replace_all(std::string & Input, const std::string & Search, const std::string & Format)
{
	// boost::replace_all(Input, Search, Format);
	std::string::size_type pos = Input.find(Search), t_size = Search.size(), r_size = Format.size();
	while (pos != std::string::npos) { // found   
		Input.replace(pos, t_size, Format);
		pos = Input.find(Search, pos + r_size);
	}
}

std::string MyTools::BuildString(const std::string & str0, const std::string & str1)
{
	std::string str = "";
	str.append(str0);
// 	int n = 5 - str0.length()/3;
// 	str.append(n,' ');

//	n = str1.length();
// 	if (n < 6)
// 		str.append("[");
	str.append("["+str1+"]");

	return str;
}


std::string MyTools::GetCurrentDate()
{
	std::string ret;
	time_t t = time(NULL);
	char date[64];
	struct tm tmTmp = {0};
#ifdef _WIN32
	localtime_s(&tmTmp, &t);
#else
	localtime_r(&t, &tmTmp);
#endif
	memset(date, 0, sizeof(date));
	strftime(date, sizeof(date), "%Y/%m/%d %H:%M:%S", &tmTmp);
	ret = date;
	return date;
}

std::string MyTools::GetCurrentDay()
{
	std::string ret;
	time_t t = time(NULL);
	struct tm tmTmp;
#ifdef _WIN32
	localtime_s(&tmTmp, &t);
#else
	localtime_r(&t, &tmTmp);
#endif
	char date[64];
	memset(date, 0, sizeof(date));
	strftime(date, sizeof(date), "%Y-%m-%d", &tmTmp);
	ret = date;
	return date;
}

void MyTools::PrintError(const std::string & strerror)
{
#ifdef _WIN32
	_mkdir("loginfo");
#else
	mkdir("loginfo", S_IRWXU);
#endif // _WIN32
	std::string path = "loginfo/" + MyTools::GetCurrentDay() + ".txt";
	std::vector<std::string> ver;
	ver.push_back(strerror + "\t[" + MyTools::GetCurrentDate() + "]");
	PrintToFile(path, ver, false);
}

std::string MyTools::HexToBin(const std::string &strHex)
{
	if (strHex.size() % 2 != 0)
	{
		return "";
	}

	std::string strBin;
	strBin.resize(strHex.size() / 2);
	for (size_t i = 0; i < strBin.size(); i++)
	{
		uint8_t cTemp = 0;
		for (size_t j = 0; j < 2; j++)
		{
			char cCur = strHex[2 * i + j];
			if (cCur >= '0' && cCur <= '9')
			{
				cTemp = (cTemp << 4) + (cCur - '0');
			}
			else if (cCur >= 'a' && cCur <= 'f')
			{
				cTemp = (cTemp << 4) + (cCur - 'a' + 10);
			}
			else if (cCur >= 'A' && cCur <= 'F')
			{
				cTemp = (cTemp << 4) + (cCur - 'A' + 10);
			}
			else
			{
				return "";
			}
		}
		strBin[i] = cTemp;
	}

	return strBin; 
}

std::string MyTools::BinToHex(const std::string &strBin, bool bIsUpper /*= false*/)
{
	std::string strHex;
	strHex.resize(strBin.size() * 2);
	for (size_t i = 0; i < strBin.size(); i++)
	{
		uint8_t cTemp = strBin[i];
		for (size_t j = 0; j < 2; j++)
		{
			uint8_t cCur = (cTemp & 0x0f);
			if (cCur < 10)
			{
				cCur += '0';
			}
			else
			{
				cCur += ((bIsUpper ? 'A' : 'a') - 10);
			}
			strHex[2 * i + 1 - j] = cCur;
			cTemp >>= 4;
		}
	}

	return strHex;
}

std::string MyTools::GetBigCamel(const std::string & name)
{
	if (name == "") {
		return "";
	}

	static std::vector<std::string> v = { "ACL", "API", "ASCII", "CPU", "CSS", "DNS", "EOF", "GUID", "HTML", "HTTP", "HTTPS", "ID", "IP", "JSON", "LHS", "QPS", "RAM", "RHS", "RPC", "SLA", "SMTP", "SQL", "SSH", "TCP", "TLS", "TTL", "UDP", "UI", "UID", "UUID", "URI", "URL", "UTF8", "VM", "XML", "XMPP", "XSRF", "XSS" };
	std::map<std::string, std::string> mp;
	for (const auto & k : v) {
		// std::string tmp = boost::to_lower_copy(k);
		std::string tmp = k;
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		std::string first(tmp.begin(), tmp.begin() + 1);
		// boost::to_upper(first);
		std::transform(first.begin(), first.end(), first.begin(), ::toupper);
		first.append(tmp.begin() + 1, tmp.end());

		mp[first] = k;
	}

	std::vector<std::string> temp = SplitString(name, "_");
	std::string s;
	for (auto & v : temp) {
		std::string vv = v;
		if (vv.length() > 0) {
			if ((vv[0] >= 'a' && vv[0] <= 'z')) { //首字母大写
				vv[0] -= 32;
			}
			s += vv;
		}
	}

	if (mp[s].length() > 0) {
		s = mp[s];
	}

	return s;

}
