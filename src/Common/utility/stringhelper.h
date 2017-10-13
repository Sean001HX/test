/********************************************************************
	purpose:	字符格式转换辅助类定义：窄字符->宽字符......
*********************************************************************/
#ifndef _HELPERS_STRING_HELPER_H
#define _HELPERS_STRING_HELPER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


#include <vector>
#include <string>


namespace CommonTools
{
    /*
    * UTF8 字符串转换成ASCII字符串 
    */
    std::string convert_UTF8_to_ascii(const char* str);

    // 
    std::string  string_trim(const std::string& str);
    std::wstring string_trim(const std::wstring& str);

	/**
	* @class QX_Wide_To_Ascii
	*
	* @brief A lightweight wchar* to char* string conversion class. Copied from ACE!
	*
	* The purpose of this class is to perform conversion from
	* wchar* to char* strings.  It is not intended for general
	* purpose use.
	*/
	class QX_Wide_To_Ascii
	{
	public:
		/// Ctor must take a wchar string.
		QX_Wide_To_Ascii (const wchar_t *s);

		/// Dtor will free up the memory.
		~QX_Wide_To_Ascii (void);

		/// Return the internal char* representation.
		char *char_rep (void);

		/// Converts an wchar_t string to ascii and returns a new string.
		static char *convert (const wchar_t *wstr);

	private:
		/// Internal pointer to the converted string.
		char *s_;

		/// Disallow these operation.
		QX_Wide_To_Ascii (void);
		QX_Wide_To_Ascii (QX_Wide_To_Ascii &);
		QX_Wide_To_Ascii& operator= (QX_Wide_To_Ascii &);
	};

	/**
	* @class QX_Ascii_To_Wide
	*
	* @brief A lightweight char* to wchar* string conversion class. Copied from ACE!
	*
	* The purpose of this class is to perform conversion from
	* char* to wchar* strings.  It is not intended for general
	* purpose use.
	*/
	class QX_Ascii_To_Wide
	{
	public:
		/// Ctor must take a wchar string.
		QX_Ascii_To_Wide (const char *s);

		/// Dtor will free up the memory.
		~QX_Ascii_To_Wide (void);

		/// Return the internal wchar* representation.
		wchar_t *wchar_rep (void);

		/// Converts an char string to unicode/wide and returns a new string.
		//static wchar_t *convert (const char *str);  //如果外部调用此函数会造成内存泄漏

	private:
		/// Converts an char string to unicode/wide and returns a new string.
		static wchar_t *convert (const char *str);

		/// Internal pointer to the converted string.
		wchar_t *s_;

		/// Disallow these operation.
		QX_Ascii_To_Wide (void);
		QX_Ascii_To_Wide (QX_Ascii_To_Wide &);
		QX_Ascii_To_Wide operator= (QX_Ascii_To_Wide &);
	};

	/**
	String manipulation routines
	*/
    class StringHelper
    {
       public:
		static std::string& ltrim(std::string& s);
		static std::string& rtrim(std::string& s);
        static std::string trim(const std::string& s);
        static bool startsWith(const std::string& s, const std::string& suffix);
        static bool endsWith(const std::string& s, const std::string& suffix);
        static bool equalsIgnoreCase(const std::string& s1, const char* upper, const char* lower);

        static int toInt(const std::string& s);
//        static __int64 toInt64(const std::string& s);

        static void toString(int i, std::string& s);
		static std::string toString(int i);
//        static void toString(__int64 i, std::string& s);
        static void toString(size_t i, std::string& s);

        static std::string toLowerCase(const std::string& s);
		static std::string toUpperCase(const std::string& s);

        static bool getline(std::string& buf, std::string& line);

#if UNICODE
		static std::wstring& ltrim(std::wstring& s);
		static std::wstring& rtrim(std::wstring& s);
        static std::wstring trim(const std::wstring& s);
        static bool startsWith(const std::wstring& s, const std::wstring& suffix);
        static bool endsWith(const std::wstring& s, const std::wstring& suffix);
        static bool equalsIgnoreCase(const std::wstring& s1,
              const wchar_t* upper, const wchar_t* lower);
        static int toInt(const std::wstring& s);
//        static __int64 toInt64(const std::wstring& s);
        static void toString(int i, std::wstring& s);
		static std::wstring toStringW(int i);
//        static void toString(__int64 i, std::wstring& s);
        static void toString(size_t i, std::wstring& s);
        static std::wstring toLowerCase(const std::wstring& s);
        static bool getline(std::wstring& buf, std::wstring& line);
#endif

	};

	class Unicode_To_UTF8
	{
	public:
		Unicode_To_UTF8 (const wchar_t *s);

		/// Dtor will free up the memory.
		~Unicode_To_UTF8 (void);

		/// Return the internal char* representation.
		char * utf8_rep (void);

	private:
		/// Internal pointer to the converted string.
		char * s_;

		/// Disallow these operation.
		Unicode_To_UTF8 (void);
		Unicode_To_UTF8 (Unicode_To_UTF8 &);
		Unicode_To_UTF8& operator= (Unicode_To_UTF8 &);
	};

//     class UTF8_To_Unicode
//     {
//     public:
//         UTF8_To_Unicode(const char* s);
// 
//         /// Dtor will free up the memory.
//         ~UTF8_To_Unicode(void);
// 
//         /// Return the internal char* representation.
//         wchar_t* unicode_rep(void);
// 
//     private:
//         /// Internal pointer to the converted string.
//         wchar_t* s_;
// 
//         /// Disallow these operation.
//         UTF8_To_Unicode(void);
//         UTF8_To_Unicode(UTF8_To_Unicode &);
//         UTF8_To_Unicode& operator= (UTF8_To_Unicode &);
//     };

	class Ansi_To_UTF8
	{
	public:
		Ansi_To_UTF8 (const char *s);

		/// Dtor will free up the memory.
		~Ansi_To_UTF8 (void);

		/// Return the internal char* representation.
		char * utf8_rep (void);

	private:
		/// Internal pointer to the converted string.
		Unicode_To_UTF8* s_;

		/// Disallow these operation.
		Ansi_To_UTF8 (void);
		Ansi_To_UTF8 (Ansi_To_UTF8 &);
		Ansi_To_UTF8& operator= (Ansi_To_UTF8 &);
	};

	class UTF8_To_TString
	{
	public:
		UTF8_To_TString (const char * utf8);

		/// Dtor will free up the memory.
		~UTF8_To_TString (void);

		/// Return the internal char* representation.
#ifdef UNICODE
		wchar_t * string_rep (void) { return s_; }
#else
		char * string_rep (void)	{ return s_; }
#endif

	private:
		/// Internal pointer to the converted string.
#ifdef UNICODE
		wchar_t * s_;
#else
		char* s_;
#endif
		/// Disallow these operation.
		UTF8_To_TString (void);
		UTF8_To_TString (UTF8_To_TString &);
		UTF8_To_TString& operator= (UTF8_To_TString &);
	};
}

#endif //_HELPERS_STRING_HELPER_H
