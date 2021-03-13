#pragma once
#include "BigInt.h"

namespace overflow0x17
{
	/*Constructors*/
	BigInt::BigInt()
	{
		this->is_negative = false;
	}
	BigInt::BigInt(std::string str_as_number)
	{
		if (str_as_number.length() == 0) 
			this->is_negative = false;
		else {
			if (str_as_number[0] == '-') {
				str_as_number = str_as_number.substr(1);
				this->is_negative = true;
			}
			else 
				this->is_negative = false;
			

			for (long long i = str_as_number.length(); i > 0; i -= 9) {
				if (i < 9)
					this->digits.push_back(atoi(str_as_number.substr(0, i).c_str()));
				else
					this->digits.push_back(atoi(str_as_number.substr(i - 9, 9).c_str()));
			}

			this->remove_leading_zeros();
		}
	}
	BigInt::BigInt(signed int number)
	{
		if (number < 0) this->is_negative = true;
		else this->is_negative = false;
		this->digits.push_back(std::abs(number) % BigInt::BASE);
		number /= BigInt::BASE;
		if (number != 0) this->digits.push_back(std::abs(number));
	}
	BigInt::BigInt(unsigned int number)
	{   
		
		this->digits.push_back(number % BigInt::BASE);
		number /= BigInt::BASE;
		if (number != 0) this->digits.push_back(number);
	}
	BigInt::BigInt(signed short number)
	{
		if (number < 0) this->is_negative = true;
		else this->is_negative = false;
		this->digits.push_back(std::abs(number));
	}
	BigInt::BigInt(unsigned short  number)
	{
		this->is_negative = false;
		this->digits.push_back(number);
	}
	BigInt::BigInt(signed char number)
	{
		if (number < 0) this->is_negative = true;
		else this->is_negative = false;
		this->digits.push_back(std::abs(number));
	}
	BigInt::BigInt(unsigned char number)
	{
		this->is_negative = false;
		this->digits.push_back(number);
	}
	BigInt::BigInt(signed long number)
	{
		if (number < 0) this->is_negative = true;
		else this->is_negative = false;
		this->digits.push_back(std::abs(number) % BigInt::BASE);
		number /= BigInt::BASE;
		if (number != 0) this->digits.push_back(std::abs(number));
	}
	BigInt::BigInt(unsigned long number)
	{
		this->digits.push_back(number % BigInt::BASE);
		number /= BigInt::BASE;
		if (number != 0) this->digits.push_back(number);
	}
	BigInt::BigInt(signed long long number)
	{
		if (number < 0) { this->is_negative = true; number = -number; }
		else this->is_negative = false;
		do {
			this->digits.push_back(number % BigInt::BASE);
			number /= BigInt::BASE;
		} while (number != 0);
	}
	BigInt::BigInt(unsigned long long number)
	{
		this->is_negative = false;
		do {
			this->digits.push_back(number % BigInt::BASE);
			number /= BigInt::BASE;
		} while (number != 0);
	}
	/*ostream operator && operator std::sttring()*/
	std::ostream& operator <<(std::ostream& out, const BigInt& big_int)
	{
		if (big_int.digits.empty()) out << 0;
		else {
			if (big_int.is_negative) out << '-';
			out << big_int.digits.back();
			char old_fill = out.fill('0');
			for (long long i = static_cast<long long>(big_int.digits.size()) - 2; i >= 0; --i) out << std::setw(9) << big_int.digits[i];
			out.fill(old_fill);
		}

		return out;
	}
	BigInt::operator std::string() const
	{
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

	/*Unary operators*/
	const BigInt BigInt::operator+() const
	{
		return BigInt(*this);
	}
	const BigInt BigInt::operator-() const
	{
		BigInt big_int(*this);
		big_int.is_negative = !big_int.is_negative;
		return big_int;
	}
	const BigInt BigInt::operator++()
	{
		return (*this += 1);
	}
	const BigInt BigInt::operator++(int)
	{
		*this += 1;
		return *this - 1;
	}
	const BigInt BigInt::operator--()
	{
		return (*this -= 1);
	}
	const BigInt BigInt::operator--(int)
	{
		*this -= 1;
		return *this + 1;
	}
	/*Binary operators*/

	bool operator == (const BigInt& first, const BigInt& second)
	{
		if (first.is_negative != second.is_negative) return false;
		if (first.digits.empty()) {
			if (second.digits.empty() || (second.digits.size() == 1 && second.digits[0] == 0)) return true;
			else return false;
		}
		if (second.digits.empty())
		{
			if (first.digits.empty() || (first.digits.size() == 1 && first.digits[0] == 0)) return true;
			else return false;
		}
		if (first.digits.size() != second.digits.size()) return false;
		for (size_t i = 0; i < first.digits.size(); ++i)
			if (first.digits.at(i) != second.digits.at(i)) return false;

		return  true;
	}
	bool operator !=(const BigInt& first, const BigInt& second)
	{
		return !(first == second);
	}
	bool operator > (const BigInt& first, const BigInt& second)
	{
		return !(first <= second);
	}
	bool operator < (const BigInt& first, const BigInt& second)
	{
		if (first == second)return false;
		if (first.is_negative) {
			if (second.is_negative) return ((-second) < (-first));
			else return true;
		}
		else if (second.is_negative) return false;
		else
		{
			if (first.digits.size() != second.digits.size()) return first.digits.size() < second.digits.size();
			else
			{
				for (long long i = first.digits.size() - 1; i >= 0; --i)
					if (first.digits[i] != second.digits[i]) return first.digits[i] < second.digits[i];

				return false;
			}
		}
	}
	bool operator >= (const BigInt& first, const BigInt& second)
	{
		return !(first < second);
	}
	bool operator <= (const BigInt& first, const BigInt& second)
	{
		return (first < second || first == second);
	}
	/*Other binary operators*/
	const BigInt operator+(BigInt first, const BigInt& second)
	{
		if (first.is_negative) {
			if (second.is_negative) return -(-first + (-second));
			else return second - (-first);
		}
		else if (second.is_negative) return first - (-second);
		int carry = 0;
		for (size_t i = 0; i < std::max(first.digits.size(), second.digits.size()) || carry != 0; ++i) {
			if (i == first.digits.size()) first.digits.push_back(0);
			first.digits[i] += carry + (i < second.digits.size() ? second.digits[i] : 0);
			carry = first.digits[i] >= BigInt::BASE;
			if (carry != 0) first.digits[i] -= BigInt::BASE;
		}

		return first;
	}
	const BigInt operator-(BigInt first, const BigInt& second)
	{
		if (second.is_negative) return first + (-second);
		else if (first.is_negative) return -(-first + second);
		else if (first < second) return -(second - first);
		int carry = 0;
		for (size_t i = 0; i < second.digits.size() || carry != 0; ++i) {
			first.digits[i] -= carry + (i < second.digits.size() ? second.digits[i] : 0);
			carry = first.digits[i] < 0;
			if (carry != 0) first.digits[i] += BigInt::BASE;
		}

		first.remove_leading_zeros();
		return first;
	}
	const BigInt operator*(const BigInt& first, const BigInt& second)
	{
		BigInt result;
		result.digits.resize(first.digits.size() + second.digits.size());
		for (size_t i = 0; i < first.digits.size(); ++i) {
			int carry = 0;
			for (size_t j = 0; j < second.digits.size() || carry != 0; ++j) {
				long long cur = result.digits[i + j] +
					first.digits[i] * 1LL * (j < second.digits.size() ? second.digits[j] : 0) + carry;
				result.digits[i + j] = static_cast<int>(cur % BigInt::BASE);
				carry = static_cast<int>(cur / BigInt::BASE);
			}
		}

		result.is_negative = first.is_negative != second.is_negative;
		result.remove_leading_zeros();
		return result;
	}
	const BigInt operator/ (const BigInt& first, const BigInt& second)
	{
		if (second == 0) throw BigInt::divide_by_zero();
		BigInt b = second;
		b.is_negative = false;
		BigInt result, current;
		result.digits.resize(first.digits.size());
		for (long long i = static_cast<long long>(first.digits.size()) - 1; i >= 0; --i) {
			current.shift_right();
			current.digits[0] = first.digits[i];
			current.remove_leading_zeros();
			int x = 0, l = 0, r = BigInt::BASE;
			while (l <= r) {
				int m = (l + r) / 2;
				BigInt t = b * m;
				if (t <= current) {
					x = m;
					l = m + 1;
				}
				else r = m - 1;
			}

			result.digits[i] = x;
			current = current - b * x;
		}

		result.is_negative = first.is_negative != second.is_negative;
		result.remove_leading_zeros();
		return result;
	}
	const BigInt operator%(const BigInt& first,const BigInt& second)
	{
		BigInt result = first - (first / second) * second;
		if (result.is_negative) result += second;
		return result;
	}

	BigInt& BigInt::operator+=(const BigInt& other)
	{
		return *this = (*this + other);
	}
	BigInt& BigInt::operator-=(const BigInt& other)
	{
		return *this = (*this - other);
	}
	BigInt& BigInt::operator*=(const BigInt& other)
	{
		return *this = (*this * other);
	}
	BigInt& BigInt::operator/=(const BigInt& other)
	{
		return *this = (*this / other);
	}
	BigInt& BigInt::operator%=(const BigInt& other)
	{
		return *this = (*this % other);
	}
	/*Some usefull functions*/
	bool BigInt::odd() const
	{
		if (this->digits.size() == 0) return false;
		return this->digits[0] & 1;
	}
	bool BigInt::even() const
	{
		return !this->odd();
	}
	const BigInt BigInt::pow(BigInt value) const
	{
		BigInt a(*this), result(1);
		while (value != 0) {
			if (value.odd()) result *= a;
			a *= a;
			value /= 2;
		}

		return result;
	}
	void BigInt::remove_leading_zeros()
	{
		while (this->digits.size() > 1 && this->digits.back() == 0) {
			this->digits.pop_back();
		}

		if (this->digits.size() == 1 && this->digits[0] == 0) this->is_negative = false;
	}
	void BigInt::shift_right()
	{
		if (this->digits.size() == 0) {
			this->digits.push_back(0);
			return;
		}
		this->digits.push_back(this->digits[this->digits.size() - 1]);
		for (size_t i = this->digits.size() - 2; i > 0; --i) 
			this->digits[i] = this->digits[i - 1];
		this->digits[0] = 0;
	}
}
	














