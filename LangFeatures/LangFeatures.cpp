// LangFeatures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Templates.h"

int main()
{
    // Lesson 1
    LearnTemplates();

    // This will produce linker error
    // BadTemplateFoo(45);

    // Template type can be deducted from argument
    GoodTemplateFoo(45);
}
