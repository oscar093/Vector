/*
 * VectorItt.h
 *
 *  Created on: Dec 3, 2018
 *      Author: Oscar Arréhn Ågren
 */

#ifndef VECTORITT_H_
#define VECTORITT_H_
#include <iostream>


template<class T> class VectorItt {
public:
	typedef T value_type;
	typedef T& reference;
	typedef std::random_access_iterator_tag iterator_category;
	typedef signed int difference_type;
	typedef T* pointer;
	pointer ptr;

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
	template<class TT> friend bool operator==(const VectorItt& lhs, const VectorItt& rhs);
	template<class TT> friend bool operator!=(const VectorItt& lhs, const VectorItt& rhs);
	template<class TT> friend bool operator<(const VectorItt& lhs, const VectorItt& rhs);
	template<class TT> friend bool operator>(const VectorItt& lhs, const VectorItt& rhs);
	template<class TT> friend bool operator<=(const VectorItt& lhs, const VectorItt& rhs);
	template<class TT> friend bool operator>=(const VectorItt& lhs, const VectorItt& rhs);
};


/*****************************************************************************************/

template<class T>
VectorItt<T>::VectorItt() {
	ptr = nullptr;
}

template<class T>
VectorItt<T>::VectorItt(T* p){
	ptr = p;
}

template<class T>
VectorItt<T>::VectorItt(const VectorItt& other) {
	ptr = other.ptr;
}

template<class T>
VectorItt<T>& VectorItt<T>::operator= (const VectorItt& other){
	this->ptr = other.ptr;
	return *this;
}

template<class T>
T& VectorItt<T>::operator*(){
	return *ptr;
}

template<class T>
T* VectorItt<T>::operator ->(){
	return ptr;
}

template<class T>
T& VectorItt<T>::operator[](size_t i){
	return *(ptr + i);
}

template<class T>
VectorItt<T>& VectorItt<T>::operator++(){
	++ptr;
	return *this;
}

template<class T>
VectorItt<T>& VectorItt<T>::operator--(){
	--ptr;
	return *this;
}

template<class T>
VectorItt<T> VectorItt<T>::operator++(int){
	VectorItt<T> tmp = *this;
	++ptr;
	return tmp;
}

template<class T>
VectorItt<T> VectorItt<T>::operator--(int){
	VectorItt<T> tmp = *this;
	--ptr;
	return tmp;
}

template<class T>
VectorItt<T> VectorItt<T>::operator+(difference_type i) const{
	return VectorItt<T>(ptr + i);
}

template<class T>
VectorItt<T> VectorItt<T>::operator-(difference_type i) const{
	return VectorItt<T>(ptr - i);
}

template<class T>
typename VectorItt<T>::difference_type VectorItt<T>::operator-(const VectorItt& other) const{
	difference_type val = ptr - other.ptr;
	return val;
}

template<class T>
bool operator==(const VectorItt<T>& lhs, const VectorItt<T>& rhs){
	return lhs.ptr == rhs.ptr;
}

template<class T>
bool operator!=(const VectorItt<T>& lhs, const VectorItt<T>& rhs){
	return lhs.ptr != rhs.ptr;
}

template<class T>
bool operator<(const VectorItt<T>& lhs, const VectorItt<T>& rhs){
	return lhs.ptr < rhs.ptr;
}

template<class T>
bool operator>(const VectorItt<T>& lhs, const VectorItt<T>& rhs){
	return lhs.ptr > rhs.ptr;
}

template<class T>
bool operator<=(const VectorItt<T>& lhs, const VectorItt<T>& rhs){
	return lhs.ptr <= rhs.ptr;
}

template<class T>
bool operator>=(const VectorItt<T>& lhs, const VectorItt<T>& rhs){
	return lhs.ptr >= rhs.ptr;
}

template<class T>
VectorItt<T>::~VectorItt() {
	//Do nothing.
}


#endif /* VECTORITT_H_ */
