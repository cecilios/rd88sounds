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

#include "rd88_tables.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

namespace rd88snd
{

//    Banks
//    ------------------------------------------------------------
//      Bank    MSB        LSB               Tone No.  Num.Tones
//    0 RD-88    71 = x47  71    = x47        1-38       38
//    1 PR-B     87 = x57  64-67 = x40-x43    1-128     459
//    2 PR-C     87 = x57  68    = x44        1-128     128
//    3 PR-D     87 = x57  69-77 = x45-x4D    1-128    1109
//    4 PR-E     87 = x57  78-84 = x4E-x54    1-128     896
//    5 CMN      87 = x57  85-91 = x55-x5B    1-128     837
//    6 PR-A     87 = x57  92-93 = x5C-x5D    1-128     239
//    7 SN PR-B  89 = x59  64    = x40        1-15       15
//    8 SN PR-A  90 = x5A  65    = x41        1-9         9
//    9 EXZ001  101 = x65  64    = x40        1-11       11

//---------------------------------------------------------------------------------------
TonesManager::TonesManager()
{
}

//---------------------------------------------------------------------------------------
TonesManager::~TonesManager()
{
}

//---------------------------------------------------------------------------------------
string TonesManager::load_tones(const string& path, ostream& logger)
{
    stringstream ss;
    fstream file;

	file.open(path, ios::in);
	if (!file)
    {
		ss << "File not found: '" << path << "'" << endl;
	}
	else
    {
        char delim = ';';   //delimiter to split by
        int lines=0;
        while(file.good())
        for (string line; getline(file, line); )
        {
            stringstream lineaux;
            string tmp;
            vector<string> words;

            //getline(file, line);
            lineaux << line;

            while (getline(lineaux, tmp, delim))
            {
                // Provide proper checks here for tmp like if empty
                // Also strip down symbols like !, ., ?, etc.
                // Finally push it.
                words.push_back(tmp);
            }

            ++lines;
            save_tone(words);
        }

        int i=0;
        for(auto it = m_banks.begin(); it != m_banks.end(); ++it, ++i)
        {
            ss << "Bank " << i << ":  " << (*it).MSB << ", " << (*it).LSB << ", "
               << (*it).bankName << endl;
        }
        ss << endl << endl;

        //list bank 101, 64, EXZ001
        Bank* bank = find_bank(87,78);
        ss << "Tones in bank 87, 78.  Num.tones = " << bank->num_tones() << endl;
        for(int i=0; i < 60; ++i)     //bank->num_tones()
        {
            Tone* tone = bank->get_tone(i);
            ss << i << ":  " << tone->name << endl;
        }

	}
	file.close();

    return ss.str();
}

//---------------------------------------------------------------------------------------
void TonesManager::save_tone(const vector<string>& words)
{
    //words[0] - Bank       words[1] - Tone number      words[2] - Tone name
    //words[3] - MSB        words[4] - LSB              words[5] - PC
    //words[6] - category


    if (m_banks.size() == 0)
    {
        m_banks.push_back( Bank( stoi(words[3]), stoi(words[4]), words[0]));
        auto bank = m_banks.back();
        bank.add_tone(stoi(words[5]), words[2], 0);
    }
    else
    {
        int msb = stoi(words[3]);
        int lsb = stoi(words[4]);
        Bank* bank = find_bank(msb, lsb);
        if (bank == nullptr)
        {
            m_banks.push_back( Bank(msb, lsb, words[0]) );
            bank = &m_banks[m_banks.size() - 1];
        }
        bank->add_tone(stoi(words[5]), words[2], 0);
    }
}

//---------------------------------------------------------------------------------------
Bank* TonesManager::find_bank(int msb, int lsb)
{
    for(auto it = m_banks.begin(); it != m_banks.end(); ++it)
    {
        if (msb == (*it).MSB && lsb == (*it).LSB)
            return &(*it);
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------
string TonesManager::load_scenes(const std::string& path, ostream& logger)
{
    stringstream ss;
    fstream file;

	file.open(path, ios::in);
	if (!file)
    {
		ss << "File not found: '" << path << "'" << endl;
	}
	else
    {
        m_svdPath = path;
        ss << read_header(file, logger);

        //read scenes
        ss << "Scenes:" << endl;
        size_t pos = 96;
        for (int i = 0; i < 500; ++i, pos += 976)
        {
            ss << read_scene(i, file, pos, logger);
		}
        ss << endl;

//        //read tones after scenes
//        pos += 16;
//        for (int i = 0; i < 500; ++i, pos += 976)
//        {
//            ss << read_scene(i, file, pos, logger);
//		}
//        ss << endl;
	}
	file.close();

    return ss.str();
}

//---------------------------------------------------------------------------------------
string TonesManager::read_header(fstream& file, ostream& logger)
{
    stringstream ss;
    ss << "Header:" << endl;
    //print header in hex
//        file.read((char*)header, 96);
    unsigned char ch;
    for (int i = 0; i < 96; ++i)
    {
        file >> ch;
        ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)ch << " ";
    }
    ss << endl << endl;

    return ss.str();
}

//---------------------------------------------------------------------------------------
string TonesManager::read_scene(int iScene, fstream& file, size_t pos, ostream& logger)
{
    stringstream ss;
//    file.seekg(pos);
//    ss << "Pos=" << std::dec << pos << " (hex " << std::hex << pos << "): ";
//    for (int j = 0; j < 16; ++j)
//    {
//        file >> ch;
//        ss << std::hex << (unsigned int)ch << " ";
//    }
//    ss << endl;

    //scene name
    file.seekg(pos);
    string sceneName(17, ' ');
    file.read(&sceneName[0], 16);
    ss << "Scene " << std::dec << iScene << ", pos "
       << pos << " (hex " << std::hex << pos << "): \""
       << sceneName << "\"";

    m_scenes.push_back( Scene(iScene, sceneName) );
    Scene* scene = &m_scenes[m_scenes.size()-1];

    //first tone
    size_t zpos = 0x003c;
    for (int iTone=0; iTone < 3; ++iTone, zpos += 0x004c)
    {
        file.seekg(pos + zpos);
        unsigned char msbc, lsbc, pcc;
        file >> msbc;
        file >> lsbc;
        file >> pcc;
//            ss << ", msb=" << std::hex << (unsigned int)msbc
//               << ", lsb=" << std::hex << (unsigned int)lsbc
//               << ", pc=" << std::hex << (unsigned int)pcc;
        int msb = msbc;
        int lsb = lsbc;
        int pc = pcc;
//            ss << std::dec << ", msb=" << msb
//               << ", lsb=" << lsb
//               << ", pc=" << pc;
        Tone* tone = nullptr;
        Bank* bank = find_bank(msb, lsb);
        if (bank)
        {
            if (pc >= 0 && pc <= 127)
            {
                tone = bank->get_tone(pc);
                ss << ",  tone " << (iTone+1) << "= " << bank->bankName << ": " << tone->name;
            }
            else
                ss << "invalid pc=" << pc;
        }
        scene->add_tone(iTone, tone);
    }

    ss << endl;


    return ss.str();
}

//---------------------------------------------------------------------------------------
void TonesManager::export_scene(int iScene, const std::string& path)
{
    ofstream out;
    out.open(path);
    fstream file;

	file.open(m_svdPath, ios::in);
	if (!file)
    {
		out << "File not found: '" << path << "'" << endl;
	}
	else
    {
        file.seekg(96 + 976 * iScene);
        unsigned char ch;
        for (int i = 0; i < 976; ++i)
        {
            if ((i != 0) && (i % 16 == 0))
                out << endl;
            file >> std::noskipws >> ch;
            out << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)ch << " ";
        }
        out << endl;
    }
}


}   //namespace rd88snd
