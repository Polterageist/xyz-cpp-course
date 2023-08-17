#pragma once
#include <typeinfo>
#include <iostream>

// This function can be used only in Templates.cpp, as templates can't be linked
template<class T>
void BadTemplateFoo(T arg);

template<class T>
void GoodTemplateFoo(T arg)
{
	std::cout << "You can use me everywhere" << std::endl;
}

void LearnTemplates();
