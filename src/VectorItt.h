/*
 * VectorItt.h
 *
 *  Created on: Nov 21, 2018
 *      Author: xps
 */

#ifndef VECTORITT_H_
#define VECTORITT_H_

#include <iostream>

template<class T> class VectorItt {

	typedef T value_type;
	typedef T& reference;
	typedef std::random_access_iterator_tag iterator_category;
	typedef signed int difference_type;
	typedef T* pointer;

public:
	VectorItt();
	virtual ~VectorItt();
	VectorItt(T* p);
	VectorItt(const VectorItt& other);
	VectorItt& operator=(const VectorItt& other);
	T& operator*();
	T* operator->();
	T& operator[](size_t i);
	VectorItt& operator++();
	VectorItt& operator--();
	VectorItt operator++(int);
	VectorItt operator--(int);
	VectorItt operator+(difference_type i) const;
	VectorItt operator-(difference_type i) const;
	difference_type operator-(const VectorItt& other) const;
	friend bool operator==(const VectorItt& lhs, const VectorItt& rhs);
	friend bool operator!=(const VectorItt& lhs, const VectorItt& rhs);
	friend bool operator<(const VectorItt& lhs, const VectorItt& rhs);
	friend bool operator>(const VectorItt& lhs, const VectorItt& rhs);
	friend bool operator<=(const VectorItt& lhs, const VectorItt& rhs);
	friend bool operator>=(const VectorItt& lhs, const VectorItt& rhs);
};

#endif /* VECTORITT_H_ */
