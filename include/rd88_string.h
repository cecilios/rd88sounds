//----------------------------------------------------------------------------
//    RD-88 Sounds Manager
//    Copyright (c) 2020 Cecilio Salmeron
//    Contact: s.cecilio@gmail.com
//    License: MIT License
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.
//---------------------------------------------------------------------------------------

#ifndef __RD88_STRING_H__        //to avoid nested includes
#define __RD88_STRING_H__

//wxWidgets
#include <wx/wx.h>
#include <wx/wxprec.h>

//other
#include <iostream>
using namespace std;


namespace rd88snd
{


//---------------------------------------------------------------------------------------
// Conversion wxString <-> std::string
//---------------------------------------------------------------------------------------

extern wxString to_wx_string(const std::string& string);
extern std::string to_std_string(const wxString& wxstring);


}   // namespace rd88snd

#endif    // __RD88_STRING_H__

