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

#include "rd88_app.h"
#include "rd88_main_frame.h"


// This macro will allow wxWindows to create the application object during program
// execution (it's better than using a static object for many reasons) and also
// declares the accessor function wxGetApp() which will return the reference of
// the right type (i.e. TheApp and not wxApp)
wxIMPLEMENT_APP(rd88snd::TheApp);


namespace rd88snd
{

//=======================================================================================
// TheApp implementation
//=======================================================================================

bool TheApp::OnInit()
{
    // `Main program' equivalent: the program execution "starts" here
    if ( !wxApp::OnInit() )
        return false;

    // Create the main application window
    MainFrame *frame = new MainFrame;
    frame->Show(true);

    return true;
    //On return, wxApp::OnRun() will be called which will enter the main message
    //loop and the application will run. If we return 'false' here, the
    //application would exit immediately.
}


}   //namespace rd88snd
