/*=========================================================================

  Program:   
  Module:    <CSVExtractor.cpp>

  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
  All rights reserved.
  See Copyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "CSVExtractor.h"
#include <cstring>

CSVExtractor::CSVExtractor() {
}

void CSVExtractor::input(const std::string & p_CSV) {
    m_Tokens.clear();
    std::string t_CSV;
    //strtok works on raw data which maybe not sync and we don't want to destroy input data
    t_CSV.append(p_CSV); 
    if(p_CSV.find(",") == std::string::npos) {
        return;
    }
    char * t_Token = std::strtok(const_cast<char *>(t_CSV.c_str()), ",");
   
        while(t_Token != NULL) {
        m_Tokens.push_back(t_Token);
        t_Token = std::strtok(NULL, ",");
    }
}

std::string CSVExtractor::getValue(unsigned int arg) {
    if(arg < m_Tokens.size()) {
        return m_Tokens[arg];
    } else { 
        return "";
    }
}

