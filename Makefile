# Makefile for KNN

knn.out: main.cpp KNN.h KNN.cpp
	g++ -std=c++11 -O2 main.cpp KNN.cpp -o knn.out
