/********************************************************************
	purpose:	×Ö·û¸ñÊ½×ª»»¸¨ÖúÀàÊµÏÖ£ºÕ­×Ö·û->¿í×Ö·û......
*********************************************************************/
#include "stringhelper.h"
#include <algorithm>
#include <iterator>
#include <cctype>
#include <stdlib.h>
#include <tchar.h>

#if !defined (WIN32)
#  include /**/ <string.h>             // Need to see strlen()
#endif /* WIN32 */

#ifndef _WINDOWS_
#include "PointerDef.h"
#include <windows.h>				// for GetACP()...
#endif // _WINDOWS_

// These are always inlined
// FUZZ: disable check_for_inline


namespace CommonTools
{

	//////////////////////////////////////////////////////////////////////////
	//
//#if defined (UNICODE)

	QX_Wide_To_Ascii::~QX_Wide_To_Ascii (void)
	{
		delete [] this->s_;
	}

	char * QX_Wide_To_Ascii::char_rep (void)
	{
		return this->s_;
	}

	char * QX_Wide_To_Ascii::convert (const wchar_t *wstr)
	{
		// Short circuit null pointer case
		if (wstr == 0)
			return 0;

# if defined (WIN32)
		UINT cp = GetACP ();
		int len = ::WideCharToMultiByte (cp,
			0,
			wstr,
			-1,
			0,
			0,
			0,
			0);
# elif defined (ACE_LACKS_WCSLEN)
		const wchar_t *wtemp = wstr;
		while (wtemp != 0)
			++wtemp;

		int len = wtemp - wstr + 1;
# else  /* WIN32 */
		size_t len = ::wcslen (wstr) + 1;
# endif /* WIN32 */

		char *str = new char[len];

# if defined (WIN32)
		::WideCharToMultiByte (cp, 0, wstr, -1, str, len, 0, 0);
# elif defined (VXWORKS)
		::wcstombs (str, wstr, len);
# else /* WIN32 */
		for (size_t i = 0; i < len; i++)
		{
			wchar_t *t = const_cast <wchar_t *> (wstr);
			str[i] = static_cast<char> (*(t + i));
		}
# endif /* WIN32 */
		return str;
	}

	QX_Wide_To_Ascii::QX_Wide_To_Ascii (const wchar_t *s)
		: s_ (QX_Wide_To_Ascii::convert (s))
	{
	}

	QX_Ascii_To_Wide::~QX_Ascii_To_Wide (void)
	{
		delete[] this->s_;
	}

	wchar_t * QX_Ascii_To_Wide::wchar_rep (void)
	{
		return this->s_;
	}

	wchar_t * QX_Ascii_To_Wide::convert (const char *str)
	{
		// Short circuit null pointer case
		if (str == 0)
			return 0;

# if defined (WIN32)
		UINT cp = GetACP ();
		int len = ::MultiByteToWideChar (cp, 0, str, -1, 0, 0);
# else /* WIN32 */
		size_t len = strlen (str) + 1;
# endif /* WIN32 */

		wchar_t *wstr = new wchar_t[len];

# if defined (WIN32)
		::MultiByteToWideChar (cp, 0, str, -1, wstr, len);
# elif defined (VXWORKS)
		::mbstowcs (wstr, str, len);
# else /* WIN32 */
		for (size_t i = 0; i < len; i++)
		{
			char *t = const_cast<char *> (str);
			wstr[i] = static_cast<wchar_t> (*((unsigned char*)(t + i)));
		}
# endif /* WIN32 */
		return wstr;
	}

	QX_Ascii_To_Wide::QX_Ascii_To_Wide (const char *s)
		: s_ (QX_Ascii_To_Wide::convert (s))
	{
	}

//#endif /* UNICODE */

	//////////////////////////////////////////////////////////////////////////
	//
	std::string StringHelper::toLowerCase(const std::string& s)
	{
		std::string d;
		std::transform(s.begin(), s.end(), std::insert_iterator<std::string>(d, d.begin()), tolower);
		return d;
	}

	std::string StringHelper::toUpperCase(const std::string& s)
	{
		std::string d;
		std::transform(s.begin(), s.end(), std::insert_iterator<std::string>(d, d.begin()), toupper);
		return d;
	}

#if UNICODE
	std::wstring StringHelper::toLowerCase(const std::wstring& s)
	{
		std::wstring d;
#if defined(_MSC_VER)
		std::transform(s.begin(), s.end(),
			std::insert_iterator<std::wstring>(d, d.begin()),
			towlower);
#else
		std::transform(s.begin(), s.end(),
			std::insert_iterator<std::wstring>(d, d.begin()),
			(int(*)(int)) std::tolower);
#endif
		return d;
	}
#endif

	std::string StringHelper::trim(const std::string& s)
	{
		std::string::size_type pos = s.find_first_not_of(' ');
		if (pos == std::string::npos) {
			return std::string();
		}

		std::string::size_type n = s.find_last_not_of(' ') - pos + 1;
		return s.substr(pos, n);
	}

	std::string& ltrim(std::string& s)
	{
		const std::string drop = " ";
		// trim left
		return s.erase(0,s.find_first_not_of(drop));
	}

	std::string& rtrim(std::string& s)
	{
		const std::string drop = " ";
		// trim right
		return    s.erase(s.find_last_not_of(drop)+1);
	}

#if UNICODE
	std::wstring& ltrim(std::wstring& s)
	{
		const std::wstring drop = L" ";
		// trim left
		return s.erase(0,s.find_first_not_of(drop));
	}

	std::wstring& rtrim(std::wstring& s)
	{
		const std::wstring drop = L" ";
		// trim right
		return    s.erase(s.find_last_not_of(drop)+1);
	}

	std::wstring StringHelper::trim(const std::wstring& s)
	{
		std::wstring::size_type pos = s.find_first_not_of(_T(' '));
		if (pos == std::wstring::npos) {
			return std::wstring();
		}

		std::wstring::size_type n = s.find_last_not_of(_T(' ')) - pos + 1;
		return s.substr(pos, n);
	}
#endif

	bool StringHelper::startsWith(const std::string& s, const std::string& prefix)
	{
		return s.compare(0, prefix.length(), prefix) == 0;
	}

#if UNICODE
	bool StringHelper::startsWith(const std::wstring& s, const std::wstring& prefix)
	{
		return s.compare(0, prefix.length(), prefix) == 0;
	}
#endif

	bool StringHelper::endsWith(const std::string& s, const std::string& suffix)
	{
		if (suffix.length() <= s.length()) {
			return s.compare(s.length() - suffix.length(), suffix.length(), suffix) == 0;
		}
		return false;
	}

#if UNICODE
	bool StringHelper::endsWith(const std::wstring& s, const std::wstring& suffix)
	{
		if (suffix.length() <= s.length()) {
			return s.compare(s.length() - suffix.length(), suffix.length(), suffix) == 0;
		}
		return false;
	}
#endif

	bool StringHelper::equalsIgnoreCase(const std::string& s1, const char* upper, const char* lower) 
	{
		for (std::string::const_iterator iter = s1.begin(); iter != s1.end(); iter++, upper++, lower++) {
			if (*iter != *upper && *iter != * lower) 
				return false;
		}
		return (*upper == 0);
	}

#if UNICODE
	bool StringHelper::equalsIgnoreCase(const std::wstring& s1, const wchar_t* upper, const wchar_t* lower) 
	{
		for (std::wstring::const_iterator iter = s1.begin(); iter != s1.end(); iter++, upper++, lower++) {
			if (*iter != *upper && *iter != * lower) 
				return false;
		}
		return (*upper == 0);
	}
#endif

	bool StringHelper::getline(std::string& in, std::string& line) 
	{
		if (in.empty()) {
			return false;
		}

		size_t nl = in.find('\n');
		if (nl == std::string::npos) {
			line = in;
			in.erase(in.begin(), in.end());
		} else {
			//
			//  if the file has CR-LF then drop the carriage return false
			//
			if(nl > 0 && in[nl -1] == '\x0D') {
				line.assign(in, 0, nl - 1);
			} else {
				line.assign(in, 0, nl);
			}
			in.erase(in.begin(), in.begin() + nl + 1);
		}
		return true;
	}

#if UNICODE
	bool StringHelper::getline(std::wstring& in, std::wstring& line)
	{
		if (in.empty()) {
			return false;
		}

		size_t nl = in.find(_T('\n'));
		if (nl == std::wstring::npos) {
			line = in;
			in.erase(in.begin(), in.end());
		} else {
			//
			//  if the file has CR-LF then drop the carriage return false
			//
			if(nl > 0 && in[nl -1] == _T('\x0D')) {
				line.assign(in, 0, nl - 1);
			} else {
				line.assign(in, 0, nl);
			}
			in.erase(in.begin(), in.begin() + nl + 1);
		}
		return true;
	}
#endif

	int StringHelper::toInt(const std::string& s) 
	{
		return atoi(s.c_str());
	}

#if UNICODE
	int StringHelper::toInt(const std::wstring& s) 
	{
		QX_Wide_To_Ascii wta(s.c_str());
		return atoi(wta.char_rep());
	}
#endif

	//__int64 StringHelper::toInt64(const std::string& s) {
	//  return apr_atoi64(s.c_str());
	//}

	//#if UNICODE
	//__int64 StringHelper::toInt64(const std::wstring& s) {
	//  LOG4CXX_DECODE_WCHAR(logstr, s);
	//  LOG4CXX_ENCODE_CHAR(charstr, logstr);
	//  return apr_atoi64(charstr.c_str());
	//}
	//#endif

	void StringHelper::toString(int n, std::string& str)
	{
		char buf[64]={0};
		_itoa_s( n, buf, 64, 10 );
		str.append( buf );
	}

	std::string StringHelper::toString(int n)
	{
		char buf[64]={0};
		_itoa_s( n, buf, 64, 10 );
		return std::string(buf);
	}

#if UNICODE
	void StringHelper::toString(int n, std::wstring& str) 
	{
		char buf[64];
		_itoa_s( n, buf, 64, 10 );
		QX_Ascii_To_Wide atw(buf);
		str.append(atw.wchar_rep());
	}

	std::wstring StringHelper::toStringW(int n)
	{
		char buf[64];
		_itoa_s( n, buf, 64, 10 );
		QX_Ascii_To_Wide atw(buf);
		return std::wstring(atw.wchar_rep());
	}
#endif

	//void StringHelper::toString(__int64 n, std::string& s) {
	//  if (n >= INT_MIN && n <= INT_MAX) {
	//    s.append(apr_itoa((apr_pool_t*) pool.getAPRPool(), (int) n));
	//  } else {
	//    const __int64 BILLION = APR_INT64_C(1000000000);
	//    int billions = (int) (n / BILLION);
	//    s.append(apr_itoa((apr_pool_t*) pool.getAPRPool(), billions));
	//    int remain = (int) (n - billions * BILLION);
	//    if (remain < 0) remain *= -1;
	//    char* lower = apr_itoa((apr_pool_t*) pool.getAPRPool(), remain);
	//    int fill = 9 - strlen(lower);
	//    s.append(fill, LOG4CXX_STR('0'));
	//    s.append(lower);
	//  }
	//}

	//#if UNICODE
	//void StringHelper::toString(__int64 n, std::wstring& ws) {
	//    std::string s;
	//    toString(n, pool, s);
	//    LOG4CXX_DECODE_CHAR(ls, s);
	//    Transcoder::encode(ls, ws);
	//}
	//#endif

	void StringHelper::toString(size_t n, std::string& s) 
	{
		toString((int) n, s);
	}

#if UNICODE
	void StringHelper::toString(size_t n, std::wstring& ws) 
	{
		toString((int) n, ws);
	}
#endif

/////////////////////////////////////////////////////////////////////////////////////////

	Unicode_To_UTF8::Unicode_To_UTF8(const wchar_t *s) : s_(0)
	{
		int textlen;
		textlen = WideCharToMultiByte( CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL );
		s_ =(char *)malloc((textlen+1)*sizeof(char));
		memset(s_, 0, sizeof(char) * ( textlen + 1 ) );

		WideCharToMultiByte( CP_UTF8, 0, s, -1, s_, textlen, NULL, NULL );
	}

	/// Dtor will free up the memory.
	Unicode_To_UTF8::~Unicode_To_UTF8 (void)
	{
		if (s_)
			free(s_);
	}

	/// Return the internal char* representation.
	char * Unicode_To_UTF8::utf8_rep (void)
	{
		return s_;
	}

///////////////////////////////////////////////////////////////////////////////////////
	
	Ansi_To_UTF8::Ansi_To_UTF8(const char *s) : s_(0)
	{
		QX_Ascii_To_Wide toUnicode(s);
		s_ = new Unicode_To_UTF8( toUnicode.wchar_rep() );
	}

	/// Dtor will free up the memory.
	Ansi_To_UTF8::~Ansi_To_UTF8 (void)
	{
		if (s_)
			delete s_;
	}

	/// Return the internal char* representation.
	char * Ansi_To_UTF8::utf8_rep (void)
	{
		if (s_)
			return s_->utf8_rep();

		return NULL;
	}


///////////////////////////////////////////////////////////////////////////////////////

	UTF8_To_TString::UTF8_To_TString (const char * utf8) : s_(0)
	{
		int textlen ;
		wchar_t * result;
		textlen = MultiByteToWideChar( CP_UTF8, 0, utf8,-1, NULL,0 );
		result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
		memset(result,0,(textlen+1)*sizeof(wchar_t)); 
		MultiByteToWideChar(CP_UTF8, 0,utf8,-1,(LPWSTR)result,textlen );

#ifdef UNICODE
		s_ = result;
#else
		s_ = QX_Wide_To_Ascii::convert(result);
#endif
	}

	/// Dtor will free up the memory.
	UTF8_To_TString::~UTF8_To_TString (void)
	{
#ifdef UNICODE
		if ( s_ )
			free(s_);
#else
		if ( s_ )
			delete [] s_;
#endif
	}

    std::string convert_UTF8_to_ascii(const char* str)
    {
        int num= MultiByteToWideChar(CP_UTF8, NULL, str, -1, NULL, NULL);
        wchar_t *buffw2=new wchar_t[num];
        memset(buffw2,0,num*sizeof(wchar_t));
        MultiByteToWideChar(CP_UTF8,NULL,str,-1,buffw2,num);

        std::string szRet = QX_Wide_To_Ascii(buffw2).char_rep();

        delete[] buffw2;
        return szRet;
    }

    std::string string_trim(const std::string& str)
    {
        std::string::size_type pos = str.find_first_not_of(' ');
        if (pos == std::string::npos)
            return str;

        std::string::size_type pos2 = str.find_last_not_of(' ');
        if (pos2 != std::string::npos)
            return str.substr(pos, pos2 - pos + 1);

        return str.substr(pos);
    }

    std::wstring string_trim(const std::wstring& str)
    {
        std::wstring::size_type pos = str.find_first_not_of(L' ');
        if (pos == std::wstring::npos)
            return str;

        std::wstring::size_type pos2 = str.find_last_not_of(L' ');
        if (pos2 != std::wstring::npos)
            return str.substr(pos, pos2 - pos + 1);

        return str.substr(pos);
    }

//     UTF8_To_Unicode::UTF8_To_Unicode(const char* s) : s_(0)
//     {
//         int num = MultiByteToWideChar(CP_UTF8, NULL, s, -1, NULL, NULL);
//         MultiByteToWideChar(CP_UTF8, NULL, s, -1, s_, num);
//     }
// 
//     UTF8_To_Unicode::~UTF8_To_Unicode(void)
//     {
//         if (s_)
//             free(s_);
//     }
// 
//     wchar_t* UTF8_To_Unicode::unicode_rep(void)
//     {
//         return s_;
//     }

}