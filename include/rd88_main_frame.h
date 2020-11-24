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

#ifndef __RD88_MAIN_FRAME_H__
#define __RD88_MAIN_FRAME_H__

#include "rd88_tables.h"

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <fstream>

class wxGrid;

namespace rd88snd
{

//---------------------------------------------------------------------------------------
class MainFrame : public wxFrame
{
public:
    MainFrame();
    ~MainFrame();

    void on_quit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
    void on_export_scene(wxCommandEvent& event);
    void on_display_grid(wxCommandEvent& event);

protected:
    void load_tones();
    void load_svd_file();
    void display_bank(int msb, int lsb);
    void display_scenes();

    wxTextCtrl* m_textctrl;
    wxGrid* m_grid;
    std::fstream m_file;
    TonesManager m_mngr;

    wxDECLARE_EVENT_TABLE();
};


}   //namespace rd88snd

#endif      // __RD88_MAIN_FRAME_H__
