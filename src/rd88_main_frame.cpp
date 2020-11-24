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

#include "rd88_main_frame.h"
#include "rd88_string.h"

//wxWidgets
#include <wx/aboutdlg.h>
#include <wx/grid.h>
#include <wx/numdlg.h>       //wxGetNumberFromUser

//other
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

namespace rd88snd
{

// ============================================================================
// GridFrame: a window to display a grid
// ============================================================================

class GridFrame : public wxFrame
{
public:
    GridFrame(long sizeGrid)
        : wxFrame(nullptr, wxID_ANY, wxT("Scenes"),
                  wxDefaultPosition, wxSize(500, 450))
    {
        wxGrid* m_grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
        m_grid->CreateGrid(10, 4);
    }
};


const int k_id_export_scene = wxNewId();
const int k_id_display_grid = wxNewId();


//=======================================================================================
// MainFrame implementation
//=======================================================================================

wxBEGIN_EVENT_TABLE( MainFrame, wxFrame )
    EVT_MENU( wxID_ABOUT, MainFrame::on_about )
    EVT_MENU( wxID_EXIT, MainFrame::on_quit )
    EVT_MENU( k_id_export_scene, MainFrame::on_export_scene )
    EVT_MENU( k_id_display_grid, MainFrame::on_display_grid )

wxEND_EVENT_TABLE()


//---------------------------------------------------------------------------------------
MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, wxT("RD-88 Sounds manager"),
              wxDefaultPosition, wxSize(1000, 600))
{
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(k_id_export_scene, wxT("Export scene") );
    fileMenu->Append(k_id_display_grid, wxT("Display grid") );
    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X") );

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append( wxID_ABOUT, wxT("&About RD88Sounds") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( fileMenu, wxT("&File") );
    menuBar->Append( helpMenu, wxT("&Help") );

    SetMenuBar(menuBar);

    load_tones();
    load_svd_file();
    //display_bank(90, 65);
    display_scenes();

}

//---------------------------------------------------------------------------------------
MainFrame::~MainFrame()
{
}

//---------------------------------------------------------------------------------------
void MainFrame::load_tones()
{
#if 0
    m_textctrl = new wxTextCtrl(this, wxID_ANY,
                                wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE);
    ostream stream(m_textctrl);

    string msg = m_mngr.load_tones("/datos/cecilio/lm/projects/rd88sounds/sounds/tones.csv");

    stream << to_wx_string( msg );
    stream.flush();
#else
    m_mngr.load_tones("/datos/cecilio/lm/projects/rd88sounds/sounds/tones.csv");
#endif
}

//---------------------------------------------------------------------------------------
void MainFrame::load_svd_file()
{
#if 0
    m_textctrl = new wxTextCtrl(this, wxID_ANY,
                                wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE);
    ostream stream(m_textctrl);

    string msg = m_mngr.load_scenes("/datos/cecilio/lm/projects/rd88sounds/sounds/factory-new-sounds-r1.12.SVD");

    stream << to_wx_string( msg );
    stream.flush();
#else
    m_mngr.load_scenes("/datos/cecilio/lm/projects/rd88sounds/sounds/factory-new-sounds-r1.12.SVD");
#endif
}

//---------------------------------------------------------------------------------------
void MainFrame::display_scenes()
{
    size_t numScenes = m_mngr.num_scenes();

    m_grid = new wxGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(400, 300));

    m_grid->CreateGrid(numScenes, 4);

    m_grid->SetColLabelValue(0, "Scene");
    m_grid->SetColSize(0, 200);     //Scene name
    m_grid->SetColLabelValue(1, "UP1");
    m_grid->SetColSize(1, 200);     //First tone
    m_grid->SetColLabelValue(2, "UP2");
    m_grid->SetColSize(2, 200);     //Second tone
    m_grid->SetColLabelValue(3, "LOW");
    m_grid->SetColSize(3, 200);     //Third tone

    //list scenes
    int iRow = 0;
    for(size_t i=0; i < numScenes; ++i, ++iRow)
    {
        Scene* scene = m_mngr.get_scene(i);

        //scene number
        {
            stringstream ss;
            ss << std::dec << std::setw(3) << std::setfill('0') << (i+1);
            m_grid->SetRowLabelValue(iRow, to_wx_string(ss.str()) );
        }

        //scene name
        m_grid->SetCellValue(iRow, 0, to_wx_string(scene->name()) );

        //Tones
        for (int i=0; i < 3; ++i )
        {
            stringstream ss;
            //ss << std::dec << bank->MSB << "," <<  bank->LSB << "-"
            Tone* tone = scene->get_tone(i);
            ss << to_wx_string(tone->name);
            m_grid->SetCellValue(iRow, 1+i, to_wx_string(ss.str()) );
        }
    }

//    wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
//    topSizer->Add(m_grid, 1, wxEXPAND);
//
//    SetSizerAndFit( topSizer );
//
//    Centre();
}

//---------------------------------------------------------------------------------------
void MainFrame::display_bank(int msb, int lsb)
{
    Bank* bank = m_mngr.find_bank(msb, lsb);
    if (bank == nullptr)
    {
        stringstream ss;
        ss << "Bank " << std::dec << msb << "," << lsb << " does not exist !";
        m_textctrl = new wxTextCtrl(this, wxID_ANY,
                                    to_wx_string(ss.str()),
                                    wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE);
        return;
    }

    size_t numTones = bank->num_tones();

    m_grid = new wxGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(400, 300));

    m_grid->CreateGrid(numTones, 4);

    //m_grid->SetRowSize( 0, 60 );
    m_grid->SetColSize(0, 80);      //Bank name
    m_grid->SetColSize(1, 60);      //MSB,LSB
    m_grid->SetColSize(2, 80);      //Tone number
    m_grid->SetColSize(3, 200);     //Tone name

    //list bank 101, 64, EXZ001
    int iRow = 0;
    for(size_t i=0; i < numTones; ++i, ++iRow)
    {
        Tone* tone = bank->get_tone(i);

        //bank name
        m_grid->SetCellValue(iRow, 0, to_wx_string(bank->bankName) );

        //msb & lsb
        {
            stringstream ss;
            ss << std::dec << bank->MSB << "," <<  bank->LSB;
            m_grid->SetCellValue(iRow, 1, to_wx_string(ss.str()) );
        }

        //tone number
        {
            stringstream ss;
            ss << std::dec << (i+1);
            m_grid->SetCellValue(iRow, 2, to_wx_string(ss.str()) );
        }

        //tone name
        m_grid->SetCellValue(iRow, 3, to_wx_string(tone->name) );
    }

//    wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
//    topSizer->Add(m_grid, 1, wxEXPAND);
//
//    SetSizerAndFit( topSizer );
//
//    Centre();
}

//---------------------------------------------------------------------------------------
void MainFrame::on_about(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo aboutInfo;
    aboutInfo.SetName(wxT("RD-88 Sound Manager"));
    aboutInfo.SetDescription(_("A platform independent GUI tool for inspecting sounds (SVD files) for the Roland RD-88 stage piano."));
    aboutInfo.AddDeveloper(wxT("Cecilio Salmeron"));
    aboutInfo.SetWebSite(wxT("https://github.com/cecilios/rd88sounds"));

    wxAboutBox(aboutInfo);
}

//---------------------------------------------------------------------------------------
void MainFrame::on_quit(wxCommandEvent& WXUNUSED(event))
{
    Close( true );
}

//---------------------------------------------------------------------------------------
void MainFrame::on_export_scene(wxCommandEvent& WXUNUSED(event))
{
    long iScene = 1L;
    iScene = wxGetNumberFromUser(wxT("Enter the number of the scene"),
                                 wxT("Scene (1..500): "),
                                 wxT("Export to hex file"),
                                 iScene,
                                 1, 500, this);
    if (iScene == -1L)
        return; //dlg cancelled

    const wxString& dir = wxDirSelector("Choose a folder",
                                        "/datos/cecilio/lm/projects/rd88sounds/z_docs");
    if (dir.empty())
        return; //dlg cancelled

    stringstream ss;
    ss << to_std_string(dir) << "/" << std::dec << iScene << "-scene-dump.txt";
    m_mngr.export_scene( int(iScene-1), ss.str());
}

//---------------------------------------------------------------------------------------
void MainFrame::on_display_grid(wxCommandEvent& WXUNUSED(event))
{
    GridFrame* win = new GridFrame(1000);
        win->Show(true);
}


}   //namespace rd88snd
