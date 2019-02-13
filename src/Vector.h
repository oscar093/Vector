/*
 * Vector.h
 *
 *  Created on: Dec 5, 2018
 *      Author: Oscar Arréhn Ågren
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
#include <cstring>
#include <cassert>
#include "VectorItt.h"

template <typename T>
class Vector {
	T* container = nullptr;
	size_t sze;
	size_t cpsty;

public:

	void invar();
	template<class TT> friend class VectorItt;
	using iterator = VectorItt<T>;
	Vector();
	virtual ~Vector();
	Vector(const Vector& other);
	Vector(Vector&& other);
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

	template <typename TT>
	friend bool operator==(const Vector<TT>& lhs, const Vector<TT>& other){
		if(other.sizee() != lhs.sizee()){
			return false;
		}
		for (unsigned int i = 0; i < lhs.sizee(); ++i) {
			if (lhs[i] != other[i]) {
				return false;
			}
		}
		return true;
	}

	template <typename TT>
	friend bool operator!=(const Vector<TT>& lhs, const Vector<TT>& other){
		return !(lhs == other);
	}

	template <typename TT>
	friend bool operator<=(const Vector<TT>& lhs, const Vector<TT>& other){
		return (lhs < other) || (lhs == other);
	}

	template <typename TT>
	friend bool operator>=(const Vector<TT>& lhs, const Vector<TT>& other){
		return !(lhs < other) || (lhs == other);
	}

	template <typename TT>
	friend bool operator<(const Vector<TT>& lhs, const Vector<TT>& other){
		for(unsigned int i = 0; i < other.sizee(); i++){
			if (lhs[i] != other[i]) {
					return lhs[i] < other[i];
			}
		}
		return lhs != other;
	}

	template <typename TT>
	friend bool operator>(const Vector<TT>& lhs, const Vector<TT>& other){
		return  !(lhs < other);
	}

	template<typename TT>
	friend void swap(Vector<TT>& lhs, Vector<TT>& rhs ){
		TT* tmpptr = lhs.data();
		size_t tmpsze = lhs.sizee();
		size_t tmpcpsty = lhs.capacity();

		lhs.container = rhs.data();
		lhs.sze = rhs.sizee();
		lhs.cpsty = rhs.capacity();

		rhs.container = tmpptr;
		rhs.sze = tmpsze;
		rhs.cpsty = tmpcpsty;

		lhs.invar();
		rhs.invar();
	}


	/**
	 * For testing
	 */
	friend std::ostream& operator<<(std::ostream& cout, const Vector& other){
			for (size_t i = 0; i < other.sizee(); ++i)
				cout << other[i];
			return cout;
	}
	friend bool operator==(const Vector& lhs, const char* other){
		unsigned int i = 0;
		for(char* ptr = lhs.container; ptr != lhs.container + lhs.sze; ptr++){
			if(*ptr != *(other + i)){
				return false;
			}
			i++;
		}
		return true;
	}
	Vector(const char* other);
};

/************************************************************************************************
 * Definition																					*
 * **********************************************************************************************/

template <typename T>
void Vector<T>::invar(){
	assert(Vector<T>::sze <= Vector<T>::cpsty);
	assert(Vector<T>::sze >= 0);
	assert(Vector<T>::cpsty >= 0);
}


template <typename T>
Vector<T>::Vector() {
	container = new T[2];
	sze = 0;
	cpsty = 2;
	invar();
}

template <typename T>
Vector<T>::~Vector() {
	invar();
	delete[] container;
}

template<typename T>
Vector<T>::Vector(const char* other) {
	this->sze = strlen(other);
	cpsty = sze + sze;
	container = new T[sze];
	int i = 0;
	for (T* tmpp = container; tmpp != container + sze; ++tmpp) {
		*tmpp = other[i];
		i++;
	}
	invar();
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
	cpsty = other.capacity();
	sze = other.sze;
	container = new T[sze];
	T* otherTptr = other.container;
	for (T* charp = container; charp != container + sze; ++charp) {
		*charp = *otherTptr;
		otherTptr++;
	}
	invar();
}

template<typename T>
Vector<T>::Vector(Vector&& other){
	delete[] container;
	container = other.container;
	other.container = nullptr;
	cpsty = other.cpsty;
	sze = other.sze;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other){
	invar();
	if(other.sze > cpsty){
	sze = other.sze;
	cpsty = other.capacity();
	T* tptr = new T[cpsty];
	int i = 0;
	for (T* tmpp = tptr; tmpp != tptr + sze; ++tmpp) {
		*tmpp = other[i];
		i++;
	}
	delete[] container;
	container = tptr;
	} else {
		int i = 0;
		for (T* tmpp = container; tmpp != container + other.sizee(); ++tmpp) {
			*tmpp = other[i];
			i++;
		}
		sze = other.sizee();
	}
	invar();
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other){
	invar();
	if (container != nullptr) {
		delete[] container;
	}
	sze = other.sze;
	cpsty = other.capacity();
	container = new T[cpsty];
	int i = 0;
	for (T* tmpp = container; tmpp != container + sze; ++tmpp) {
		*tmpp = *(other.container + i);
		i++;
	}
	invar();
	return *this;
}

template <typename T>
void Vector<T>::reserve(size_t n){
	if (n > cpsty) {
		T* cont = new T[n];
		int i = 0;
		for (T* tmpp = container; tmpp < container + sze; ++tmpp) {
			*(cont + i) = *tmpp;
			i++;
		}
		delete[] container;
		container = cont;
		cpsty = n;
		invar();
	}
}
template <typename T>
T& Vector<T>::operator[](size_t i){
	return container[i];
}

template <typename T>
T& Vector<T>::at(size_t i){
	if (i >= 0 && i < sze) {
			return container[i];
		} else {
			throw std::out_of_range("Cannot have negative parameter or bigger than size()");
		}
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const{
	return container[i];
}

template <typename T>
const T& Vector<T>::at(size_t i) const{
	if (i >= 0 && i < sze) {
			return container[i];
		} else {
			throw std::out_of_range("Cannot have negative parameter or bigger than size()");
		}
}

template <typename T>
T* Vector<T>::data() noexcept{
	return container;
}

template <typename T>
const T* Vector<T>::data() const noexcept{
	return container;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const{
	VectorItt<T> vitt = VectorItt<T>(&container[0]);
	return vitt;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const{
	VectorItt<T> vitt = VectorItt<T>(&container[sze]);
	return vitt;
}

template <typename T>
size_t Vector<T>::sizee() const noexcept{
	return sze;
}

template <typename T>
size_t Vector<T>::capacity() const noexcept{
	return cpsty;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
	if (cpsty != sze) {
		T* cont = new T[sze];
		int i = 0;
		for (T* tmpp = container; tmpp < container + sze; ++tmpp) {
			*(cont + i) = *tmpp;
			i++;
		}
		delete[] container;
		container = cont;
		cpsty = sze;
	//	invar();
	}
}

template<typename T>
void Vector<T>::push_back(T c) {
	invar();
	++sze;
	if (sze > cpsty) {
		cpsty = cpsty + cpsty;
		T* cont = new T[cpsty];
		int i = 0;
		for (T* tmpp = cont; tmpp != cont + sze; ++tmpp) {
			*tmpp = *(container + i);
			i++;
		}
		cont[sze - 1] = c;
		delete[] container;
		container = cont;
	} else {
		container[sze - 1] = c;
	}
	invar();
}

template <typename T>
void Vector<T>::resize(size_t n){
	if (n > cpsty) {
		T* cont = new T[n];
		int i = 0;
		for (T* tmpp = container; tmpp < container + sze; ++tmpp) {
			*(cont + i) = *tmpp;
			i++;
		}
		for (T* tmpp = container + sze; tmpp < container + n; ++tmpp) {
			*(cont + i) = T();
			i++;
		}
		delete[] container;
		container = cont;
		cpsty = n;
		sze = n;
		invar();
	}else if(n > sze){
		for (T* tmpp = container + sze; tmpp < container + n; ++tmpp) {
			*tmpp = T();
		}
		sze = n;
		invar();
	}else if(n < sze){
		sze = n;
		invar();
	}
}


#endif /* VECTOR_H_ */
