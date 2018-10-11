/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tensor.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <otiniako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:28:26 by otiniako          #+#    #+#             */
/*   Updated: 2018/10/11 14:34:47 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TENSOR_HPP
# define TENSOR_HPP
# include <vector>
# include <iostream>
# include <exception>
# include <stdlib.h>
#include <iomanip>

template < class T >
class Tensor {

public:
	/*
	* Exception
	*/
	struct WrongFormat: public std::exception {
        virtual const char* what() const throw() {
			return "Exception: Values ​​should be positive\n";
		}
    };

	struct WrongVector: public std::exception {
        virtual const char* what() const throw() {
			return "Exception: demention of vector not match to demention of tensor\n";
		}
    };

	/*
	* Empty constructor initialized empty tensor
	*/
	Tensor (): _dimSizes(0), _data(nullptr), _len(0) {}

	/*
	* Constructor with dimensions sizes
	* data is initialized by default T ()
	*/
	Tensor ( std :: vector <int > dimSizes ): _dimSizes(dimSizes), _data(nullptr), _len(1) {
		for (int n : dimSizes) {
			if (n > 0)
				_len *= n;
			else
				throw Tensor::WrongFormat();
		}
		this->_data = new T[_len];
	}

	/*
	* Copy - constructor , should copy entire tensor data
	*/
	Tensor ( const Tensor & rhs ) {
		*this = rhs;
	}

	/*
	* Move - constructor
	*/
	Tensor ( Tensor && rhs ) {
		*this = rhs;
	}

	/*
	* Copy - assignment , should copy entire tensor data
	*/
	Tensor & operator =( const Tensor & rhs ) {
		if (this != &rhs) {
			this->_dimSizes.clear();
			this->_dimSizes = rhs._dimSizes;
			this->_len = rhs._len;
			this->_data = new T[_len];
			for (int i = 0; i < this->_len; i++) {
				this->_data[i] = rhs._data[i];
			}
		}
		return (*this);
	}

	/*
	* Move - assignment
	*/
	Tensor & operator =( Tensor && rhs ) {
		if (this != &rhs)
		{
			_dimSizes = rhs._dimSizes;
			_len = rhs._len;
			_data = rhs._data;
			rhs._dimSizes.clear();
			rhs._len = 0;
			rhs._data = NULL;
		}
		return (*this);
	}

	/*
	* Returns dimensions sizes of tensor 1
	*/
	std :: vector < int > dim () const {
		return _dimSizes;
	}

	/*
	* Returns sub - tensor with indices in first dimension [ low , high )
	* !!! All changes applied further to sub - tensor would be
	* applied to this tensor as well and vice versa as well ,
	* in other words they would share their content !!!
	*/
	Tensor operator () ( int low , int high ) {
		if (low < 0 || high < 0 || low >= high || low > _dimSizes[0] || high > _dimSizes[0])
			throw Tensor::WrongFormat();
		Tensor<T> t;
		int size = _dimSizes.size();
		std :: vector <int > dimSizes = _dimSizes;
		int tmp = 1;

		dimSizes[0] = high - low;
		t._dimSizes = dimSizes;
		while (--size > 0)
			tmp *= _dimSizes[size];
		tmp *= low;
		t._len = 1;
		size = dimSizes.size();
		while (--size >= 0)
			t._len *= dimSizes[size];
		t._data = this->_data + (tmp > 1 ? tmp : 0);
		return t;
	}

	/*
	* Returns sub - tensor with index in first dimension pos
	* !!! All changes applied further to sub - tensor would be
	* applied to this tensor as well and vice versa as well ,
	* in other words they would share their content !!!
	*/
	Tensor operator () ( int pos ) {
		if (pos < 0 || pos > _dimSizes[0])
			throw Tensor::WrongFormat();
		Tensor<T> t;
		std :: vector <int > dimSizes;
		dimSizes.assign(_dimSizes.begin() + 1, _dimSizes.end());
		int size = _dimSizes.size();
		int tmp = 1;
		while (--size > 0)
			tmp *= _dimSizes[size];
		tmp *= pos;
		t._dimSizes = dimSizes;
		t._len = 1;
		size = dimSizes.size();
		while (--size >= 0)
			t._len *= dimSizes[size];
			
		t._data = _data + (tmp > 1 ? tmp : 0);
		return t;
	}

	/*
	* Returns value indexed by { pos [0] , pos [1] , pos [2]... pos [
	dim - 1]}
	* pos . size () should be equal to dim
	*/
	T& operator []( std :: vector <int > pos ) {
		if (pos.size() != _dimSizes.size())
			throw Tensor::WrongVector();
		int i = 0;
		for (int n : pos)
			if (n < 0 || n > _dimSizes[i++])
				throw Tensor::WrongVector();
			
		int size = pos.size();
		int tmp = 0;
		int tab;

		for (int i = 0; i < size; i++) {
			tab = 1;
			for (int j = i + 1; j < size; j++)
				tab *= _dimSizes[j];
			tmp += pos[i] * tab;
		}
		return (*(_data + tmp));
	}
	int getLen() {
		return _len;
	}

private:
	std :: vector <int > _dimSizes;
	T 					*_data;
	int					_len;
};


#endif