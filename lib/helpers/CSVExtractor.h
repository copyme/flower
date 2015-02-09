/*=========================================================================

  Program:   
  Module:    <CSVExtractor.h>

  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
  All rights reserved.
  See Copyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef CSVEXTRACTOR_H
#define CSVEXTRACTOR_H

#include <string>
#include <vector>

/*!
 \brief This class provide a tokenizer for CSV data. 
 
 UnitTest are in module UnitTestForAssigment_1

*/
class CSVExtractor
{
private:
    std::vector<std::string> m_Tokens;
public:
    CSVExtractor();
    /*!
     \brief Interface for seting a data for tokenizer.
     Old data is replaced with new input.
    
     \param p_CSV CSV data e.g. "value,value2"
    */
    void input(const std::string & p_CSV);
    /*!
    
     \return int number of well readed values.
    */
    int getSize() const { return m_Tokens.size();}
    /*!
     \brief Provide an interface for getting tokens. 
    
     \param arg index of value from 0 to n - 1
     \return std::string token with index k - 1 or empty string if arg is outsie the range
    */
    std::string getValue(unsigned int arg);
};

#endif // CSVEXTRACTOR_H
