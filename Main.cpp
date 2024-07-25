#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "windows.h"

//using namespace std;

class String {
public:
	void Print();
	int get_Size();
	void resize(int count);
	void resize(int count, char ch);
	void clear();
	bool empty();
	char font();
	char back();
	void insert(int index, const String str);
	void erase(int index, int count);
	void replase (int index, int count, const String str);
	int find(const String str);
	char& operator [](int index) const;
	String& operator =(const String &other);
	String& operator=(String&& other)noexcept;
	String operator +(const String& other);
	bool operator ==(const String& other);
	bool operator !=(const String& other);
	bool operator >(const String& other);
	bool operator <(const String& other);
	bool operator <=(const String& other);
	bool operator >=(const String& other);
	int compare(const String& other);
	void append(const String& other);
	friend std::istream& operator>>(std::istream& is, String& s);
	friend std::ostream& operator<<(std::ostream& out, const String& obj);
	String();
	String(const char* str);
	String(const String& other);
	~String();

private:
	char *str;
	int length;
};

void String::Print() {
	if(str != nullptr)
		std::cout << str << std::endl;
	else
		std::cout << " " << std::endl;
}

int String::get_Size() {
	return this->length;
}

void String::resize(int count) {
	if (count < this->length) {
		length = count;
		char* new_str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			new_str[i] = this->str[i];
		}
		new_str[length] = '\0';
		delete[] str;
		str = new_str;
	}
	else if (count > this->length) {
		throw "В методе resize, есди count больше размера строки, то нужно добавить второй аргумент символ";
	}
}

void String::resize(int count, char ch) {
	if (count < this->length) {
		length = count;
		char* new_str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			new_str[i] = this->str[i];
		}
		new_str[length] = '\0';
		delete[] str;
		str = new_str;
	}
	else if (count > this->length) {
		char* new_str = new char[count + 1];
		for (int i = 0; i < length; i++) {
			new_str[i] = this->str[i];
		}
		for (int i = length; i < count; i++) {
			new_str[i] = ch;
		}
		new_str[count] = '\0';
		delete[] str;
		str = new_str;
		length = count;
	}
}

void String::clear() {
	delete[] this->str;
	this->str = nullptr;
	length = 0;
}

bool String::empty() {
	return length != 0 ? true : false;
}

char String::font() {
	if (this->empty())
		return this->str[0];
	else
		throw "Строка пустая";
}

char String::back() {
	if (this->empty())
		return this->str[length - 1];
	else
		throw "Строка пустая";
}

void String::insert(int index, const String str) {
	if (index > this->length || index < 0) {
		throw "Индекс вышел за пределы массива";
	}
	char* new_mas = new char[str.length + this->length + 1];
	for (int i = 0; i < index; i++) {
		new_mas[i] = this->str[i];
	}
	for (int i = index, j = 0; j < str.length; i++, j++) {
		new_mas[i] = str[j];
	}
	for (int i = index + str.length, j = index; j < this->length; i++, j++) {
		new_mas[i] = this->str[j];
	}
	new_mas[str.length + this->length] = '\0';
	this->length = str.length + this->length;
	delete[] this->str;
	this->str = new_mas;
}

void String::erase(int index, int count) {
	if (index > this->length - count || index < 0) {
		throw "Индекс вышел за пределы массива";
	}
	if (index == 0 && this->length - count == 0) {
		delete[] this->str;
		this->length = 0;
	}
	else {
		char* new_mas = new char[this->length - count + 1];
		for (int i = 0; i < index; i++) {
			new_mas[i] = this->str[i];
		}
		for (int i = index + count, j = index; i < this->length; i++, j++) {
			new_mas[j] = this->str[i];
		}
		new_mas[this->length - count] = '\0';
		this->length = this->length - count;
		delete[] this->str;
		this->str = new_mas;
	}
}

void String::replase(int index, int count, const String str) {
	if (index > this->length - count || index < 0) {
		throw "Индекс вышел за пределы массива";
	}
	if (count > str.length) {
		throw "кол-во заменяемых символов больше строки str";
	}
	if (index == 0 && this->length - count == 0 && str.length == count) {
		delete[] this->str;
		this->str = str.str;
		this->length = str.length;
	}
	else {
		char* new_mas = new char[this->length + 1];
		for (int i = 0; i < index; i++) {
			new_mas[i] = this->str[i];
		}
		for (int i = index, j = 0; j < count; i++, j++) {
			new_mas[i] = str[j];
		}
		for (int i = index + count; i < this->length; i++) {
			new_mas[i] = this->str[i];
		}
		new_mas[this->length] = '\0';
		delete[] this->str;
		this->str = new_mas;
	}
}

int String::find(const String str) {
	for (int i = 0; i < this->length - str.length + 1; i++) {
		if (this->str[i] == str[0]) {
			for (int j = 0; j < str.length; j++) {
				if (this->str[i + j] != str[j]) {
					break;
				}
				return i;
			}
		}
	}
	return -1;
}

char& String::operator [](int index) const{
	if (index >= 0 && index < this->length) {
		return this->str[index];
	}
	else {
		throw "Выход за границы массива";
	}
}

bool String::operator ==(const String& other) {
	if (this->length != other.length) {
		return false;
	}
	for (int i = 0; i < this->length; i++) {
		if (this->str[i] != other[i]) {
			return false;
		}
	}
	return true;
}

bool String::operator !=(const String& other) {
	return !(this->operator==(other));
}

String& String::operator =(const String& other) {
	if (this->str != nullptr) {
		delete[] this->str;
	}
	this->str = new char[other.length + 1];

	for (int i = 0; i < other.length; i++) {
		this->str[i] = other[i];
	}
	this->length = other.length;
	this->str[length] = '\0';
	return *this;
}

String& String::operator=(String&& other)noexcept
{
	this->length = other.length;
	this->str = other.str;
	other.str = nullptr;
	return *this;
}

String String::operator +(const String& other) {

	String newStr;
	newStr.length = this->length + other.length;
	newStr.str = new char[newStr.length + 1];
	for (int i = 0; i < this->length; i++) {
		newStr.str[i] = this->str[i];
	}
	for (int i = this->length, j = 0; j < other.length; i++, j++) {
		newStr.str[i] = other.str[j];
	}
	newStr.str[newStr.length] = '\0';
	
	return newStr;
}

bool String::operator >(const String& other) {
	int count;
	bool istina = this->length > other.length;
	if (istina) {
		count = other.length;
	}
	else {
		count = this->length;
	}
	for (int i = 0; i < count; i++) {
		if (this->str[i] < other[i]) {
			return false;
		}
		else if (this->str[i] > other[i]) {
			return true;
		}
	}
	if (this->length > other.length) {
		return true;
	}
	else {
		return false;
	}
}

bool String::operator <(const String& other) {
	if (*this == other) {
		return false;
	}
	return !(*this > other);     
}

bool String::operator <=(const String& other) {
	return (*this < other || *this == other);
}
bool String::operator >=(const String& other) {
	return (*this > other || *this == other);
}

int String::compare(const String& other) {
	int count;
	bool istina = this->length > other.length;
	if (istina) {
		count = other.length;
	}
	else {
		count = this->length;
	}
	for (int i = 0; i < count; i++) {
		if (this->str[i] < other[i]) {
			return -1;
		}
		else if (this->str[i] > other[i]) {
			return 1;
		}
	}
	if (this->length > other.length) {
		return 1;
	}
	else if (this->length == other.length){
		return 0;
	}
	else {
		return -1;
	}
}

void String::append(const String& other) {
	String newStr = *this;
	newStr.length = length;
	delete[] this->str;
	length = this->length + other.length;
	str = new char[length + 1];
	for (int i = 0; i < newStr.length; i++) {
		str[i] = newStr.str[i];
	}
	for (int i = newStr.length, j = 0; j < other.length; i++, j++) {
		str[i] = other.str[j];
	}
	str[length] = '\0';
}

String::String() {
	str = nullptr;
	length = 0;
}

String::String(const char *str) {
	length = strlen(str);
	this->str = new char[length + 1];

	for (int i = 0; i < length; i++) {
  		this->str[i] = str[i];
	}
	this->str[length] = '\0';
}

String::String(const String &other) {
	length = other.length;
	this->str = new char[length + 1];

	for (int i = 0; i < length; i++) {
		this->str[i] = other[i];
	}
	this->str[length] = '\0';
}

String::~String() {
	delete[] this->str;
}

std::istream& operator>>(std::istream& is, String& s) {
	char buffer[1024];   
	is.getline(buffer, 1024);

	delete[] s.str;
	s.length = std::strlen(buffer);
	s.str = new char[s.length + 1];
	//std::strcpy(s.str, buffer);
	for (int i = 0; i < s.length + 1; i++) {
		s.str[i] = buffer[i];
	}
	return is;
}

std::ostream& operator<<(std::ostream& out, const String& obj)
{
	out << obj.str;
	return out;
}

int main() {
	//SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	String str = "Hello world! ";
	String str1 = "Hell0 world!";
	String str_new("sad");
	str_new[1] = 'P';
	str_new[0] = 'Q';
	String str2 = str1;
	str2 = str + str1;
	str2.Print();

	String s1 = "AQQ111";
	String s2 = "AQQ11";

	std::cout << "s1 > s2 " << s1.compare("AQQ11111") << std::endl;

	str1.resize(7);
	//str1.clear();
	str1.Print();
//	str1.append("QQQQ");
	str1.insert(5, " HEY");
	std::cout << str1 << std::endl;
	str1.erase(6, 2);
	std::cout << str1 << std::endl;
	str1.replase(6,3,"QQ1");
	std::cout << str1 << std::endl;
	std::cout << str1.find("1") << std::endl;
	//str_new.Print();
//	std::cin >> str_new;
//	std::cout << str_new << std::endl;
	std::vector<String> vec;
	vec.push_back("Привет");
	vec.push_back("Пока");
	vec.push_back("До свидание");
	vec.push_back("asdasd");

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	auto it = vec.begin();
	*it = "Dima";
	std::vector<String> vec1 = { String("One"),String("Two"),String("Three") };
	vec.insert(it,vec1.begin(), vec1.end());

	vec.swap(vec1);
	std::cout << "vec_____" << std::endl;
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
	std::cout << "vec1_____" << std::endl;
	for (auto el : vec1) {
		std::cout << el << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	it = vec.begin();
	vec.erase(it, it + 2);
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
	//std::cout << *it << std::endl;
	std::cout << "---------------------" << std::endl;
	vec.assign(5, "c++");
	for (auto element : vec) {
		std::cout << element << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	std::string line = "ADA";	std::string line1 = "AC";

	//line.clear();

	//int* big_mas = new int[1000000000];
	std::cout << (line > line1) << std::endl;
	std::cout << (int)'q' << std::endl;

	std::vector<int> qwe;
	int int_capacity = 0;
	for (int i = 0; i < 10000000; i++) {
		qwe.push_back(i);
		if (qwe.capacity() != int_capacity) {
			int_capacity = qwe.capacity();
			std::cout << i << ". значение capacity: " << int_capacity << std::endl;
		}
		//std::cout << i << ". значение: " << qwe[i] << std::endl;
		//std::cout << ". значение capacity: " << qwe.capacity() << std::endl;
	}
	std::cout << "---------------------" << std::endl;

	qwe.clear();
	qwe.shrink_to_fit();
	qwe.reserve(1000);
	std::cout << ". значение размера: " << qwe.size() << std::endl;
	std::cout << ". значение capacity: " << qwe.capacity() << std::endl;
   	return 0;
}

