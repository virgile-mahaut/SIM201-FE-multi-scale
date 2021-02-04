#!/usr/bin/env bash
	echo "g++ -g *.cpp -o projet.exe"
	g++ -g *.cpp -o projet.exe
	echo "./projet.exe"
	./projet.exe
	echo "python3 affichage_python.py"
	python3 affichage_python.py