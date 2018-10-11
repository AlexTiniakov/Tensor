/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <otiniako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:28:35 by otiniako          #+#    #+#             */
/*   Updated: 2018/10/11 14:35:09 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tensor.hpp"

int main()
{
	Tensor<float> t1({5, 5, 5});
	Tensor<float> t2 = t1(3, 4);
	Tensor<float> t3 = t2;
	Tensor<float> t4;
	t4 = t1(3);
	Tensor<float> t5 = t1(3)(4)(2, 5);
	t5[{1}] = 100.0;
	t1[{3, 4, 4}] = -100.0;

	std::cout << std::setw(19) << "<--- t1 --->\n";
	std::cout << "len: " << t1.getLen() <<"\n";
	for (int i = 0; i < 5; i++) {
		std::cout << "x = " << i << "\n";
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++)
				std::cout << std::setw(4) << t1[{i, j, k}] << " ";
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	std::cout << std::setw(19) << "<--- t2 --->\n";
	std::cout << "len: " << t2.getLen() <<"\n";
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++)
				std::cout << std::setw(4) << t2[{i, j, k}] << " ";
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	std::cout << std::setw(19) << "<--- t3 --->\n";
	std::cout << "len: " << t3.getLen() <<"\n";
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++)
				std::cout << std::setw(4) << (int)t3[{i, j, k}] << " ";
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	std::cout << std::setw(19) << "<--- t4 --->\n";
	std::cout << "len: " << t4.getLen() <<"\n";
	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 5; k++)
			std::cout << std::setw(4) << t4[{j, k}] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
	std::cout << std::setw(19) << "<--- t5 --->\n";
	std::cout << "len: " << t5.getLen() <<"\n";
	for (int i = 0; i < 3; i++) {
		std::cout << std::setw(4) << t5[{i}] << " ";
	}
	std::cout << "\n";
}