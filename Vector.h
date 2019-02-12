/*
 * Vector.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Oscar Arréhn Ågren
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
#include "VectorItt.h"

template <typename T>
class Vector {
	T* container = nullptr;
	size_t sze;
	size_t cpsty;
	void invar();
public:
	template<class TT> friend class VectorItt;
	using iterator = VectorItt<T>;
	Vector();
	virtual ~Vector();
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector(const char* other);
	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other);
	T& operator[](size_t i);
	T& at(size_t i);
	const T& operator[](size_t i) const;
	const T& at(size_t i) const;
	T* data() noexcept;
	const T* data() const noexcept;
	iterator begin() const;
	iterator end() const;
	size_t sizee() const noexcept;
	void reserve(size_t n);
	size_t capacity() const noexcept;
	void shrink_to_fit();
	void push_back(T c);
	void resize(size_t n);
	friend bool operator==(const Vector& lhs,
	               const Vector& other);
	friend bool operator!=(const Vector& lhs,
		               const Vector& other);
	friend bool operator<=(const Vector& lhs,
		               const Vector& other);
	friend bool operator>=(const Vector& lhs,
		               const Vector& other);
	friend bool operator>(const Vector& lhs,
		               const Vector& other);
	friend bool operator>(const Vector& lhs,
		               const Vector& other);

	friend std::ostream& operator<<(std::ostream& cout, const Vector& other){
			for (size_t i = 0; i < other.sizee(); ++i)
				cout << other[i];
			return cout;
	}
};

#endif /* VECTOR_H_ */
