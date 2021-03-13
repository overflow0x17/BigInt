#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
namespace overflow0x17
{
	class BigInt
	{
	public:
		/*class-helperfor exceptions*/
		class divide_by_zero : public std::exception {};
	/*constructors*/
		BigInt();
		BigInt(std::string);
		BigInt(signed int);
		BigInt(unsigned int);
		BigInt(signed short);
		BigInt(unsigned short);
		BigInt(signed char);
		BigInt(unsigned char);
		BigInt(signed long);
		BigInt(unsigned long);
		BigInt(signed long long);
		BigInt(unsigned long long);
	/*ostream operator*/
		friend std::ostream& operator <<(std::ostream& out, const BigInt&);
		operator std::string() const;
	/*unary operators*/
		const BigInt operator +() const ;
	    const BigInt operator -() const ;
		const BigInt operator ++();
		const BigInt operator ++(int);
		const BigInt operator --();
		const BigInt operator --(int);
	/*binary operators*/
		friend bool operator == (const BigInt&, const BigInt&);
		friend bool operator != (const BigInt&, const BigInt&);
		friend bool operator > (const BigInt&, const BigInt&);
		friend bool operator < (const BigInt&, const BigInt&);
		friend bool operator >= (const BigInt&, const BigInt&);
		friend bool operator <= (const BigInt&, const BigInt&);
		friend const BigInt operator+(BigInt, const BigInt&);
		friend const BigInt operator-(BigInt, const BigInt&);
		friend const BigInt operator*(const BigInt&, const BigInt&);
		friend const BigInt operator/(const BigInt&, const BigInt&);
		friend const BigInt operator%(const BigInt&, const BigInt&);
		BigInt& operator +=(const BigInt&);
		BigInt& operator -=(const BigInt&);
		BigInt& operator *=(const BigInt&);
		BigInt& operator /=(const BigInt&);
		BigInt& operator %=(const BigInt&);
	/*some usefull functions*/
		bool odd() const;
		bool even() const;
		const BigInt pow(BigInt) const;

	private:
		static const int BASE = 1000000000;
		std::vector<int> digits;
		bool is_negative;
		void remove_leading_zeros();
		void shift_right();
	};
}