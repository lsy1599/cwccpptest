#ifndef __STRINGUTIL__
#define __STRINGUTIL__

#include <iostream>
#include <string>
#include <algorithm>

namespace cwc{
	using namespace std;
	struct StringUtil{
		/**
		 * 字串轉小寫
		 *
		 * @param	
		 * @example
		 *	string str = "Chui-Wen Chiu";
		 *	cout << str << endl;
		 *	cwc::StringUtil::toUpperCase(str);
		 *	cout << str << endl;
		 */
		static void toLowerCase(std::string& str){
			std::transform(str.begin(), str.end(), str.begin(), tolower);
		}

		/**
		 * 字串轉大寫
		 *
		 * @param	
		 * @example
		 *	string str = "Chui-Wen Chiu";
		 *	cout << str << endl;
		 *	cwc::StringUtil::toUpperCase(str);
		 *	cout << str << endl;
		 */
		static void toUpperCase(std::string& str){
			std::transform(str.begin(), str.end(), str.begin(), toupper);
		}

		/**
		 * 去除兩側空白字元
		 *
		 * @param	
		 * @example
		 *	string str = "  Chui-Wen Chiu  ";     
		 *	cout << "-->" << str << "<--" << endl;
		 *	cwc::StringUtil::trim(str);          
		 *	cout << "-->" << str << "<--" << endl;
		 */
		static void trim(std::string& str){
			lTrim(str);
			rTrim(str);
		}

		/**
		 * 去除左側空白字元
		 *
		 * @param	
		 * @example
		 *	string str = "  Chui-Wen Chiu  ";     
		 *	cout << "-->" << str << "<--" << endl;
		 *	cwc::StringUtil::lTrim(str);          
		 *	cout << "-->" << str << "<--" << endl;
		 */
		static void lTrim(std::string& str){
			std::string::iterator i;
			for (i = str.begin(); i != str.end(); i++) {
				if (!isspace(*i)) {
					break;
				}
			}
			if (i == str.end()) {
				str.clear();
			} else {
				str.erase(str.begin(), i);
			}
		}


		/**
		 * 去除右側空白字元
		 *
		 * @param	
		 * @example
		 *	string str = "  Chui-Wen Chiu  ";     
		 *	cout << "-->" << str << "<--" << endl;
		 *	cwc::StringUtil::rTrim(str);          
		 *	cout << "-->" << str << "<--" << endl;
		 */
		static void rTrim(std::string& str){
			string::iterator i;
			for (i = str.end() - 1; ;i--) {
				if (!isspace(*i)) {
					str.erase(i + 1, str.end());
					break;
				}
				if (i == str.begin()) {
					str.clear();
					break;
				}
			}
		}

		static string repeat(const string& str, int n) {
			string s;
			for (int i = 0; i < n; i++) {
				s += str;
			}
			return s;
		}

		static string repeat(char c, int n) {
			return string(n, c);
		}

		/**
		 * 匹配字串開頭是否相符
		 *
		 */
		static bool startWith(const string& str, const string& substr){
			return str.find(substr) == 0;
		}

		/**
		 * 匹配字串結尾是否相符
		 *
		 */
		static bool endWith(const string& str, const string& substr){
			return str.rfind(substr) == (str.length() - substr.length());
		}

		/**
		 * 字串解析出指定型別資料
		 *
		 */
		//template<class T> parseString(const std::string& str) {
		//	T value;
		//	std::istringstream iss(str);
		//	iss >> value;
		//	return value;
		//}

		/**
		 * 字串解析出 bool
		 *
		 */
		template<bool>
		bool parseString(const std::string& str) {
			bool value;
			std::istringstream iss(str);
			iss >> boolalpha >> value;
			return value;
		}

		/**
		 * 解析 16 進位字串
		 *
		 */
		//template<class T> parseHexString(const std::string& str) {
		//	T value;
		//	std::istringstream iss(str);
		//	iss >> hex >> value;
		//	return value;
		//}

		template<class T> std::string toString(const T& value) {
			std::ostringstream oss;
			oss << value;
			return oss.str();
		}

		//string toString(const bool& value) {
		//	ostringstream oss;
		//	oss << boolalpha << value;
		//	return oss.str();
		//}

		template<class T> std::string toHexString(const T& value, int width) {
			std::ostringstream oss;
			oss << hex;
			if (width > 0) {
				oss << setw(width) << setfill('0');
			}
			oss << value;
			return oss.str();
		}



	};
}

#endif
