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

#ifndef __RD88_TABLES_H__        //to avoid nested includes
#define __RD88_TABLES_H__


#include <vector>
#include <string>
#include <array>
#include <iostream>

namespace rd88snd
{


//---------------------------------------------------------------------------------------
struct Tone
{
    int category;
    std::string name;

    Tone(const std::string& n, int cat) : category(cat), name(n) {}
    Tone() : category(0), name("-- not defined --") {}
};

//---------------------------------------------------------------------------------------
struct Bank
{
    int MSB;
    int LSB;
    int maxTone;
    int numTones;
    std::string bankName;
    std::array<Tone, 128> tones;

    Bank(int msb, int lsb, const std::string& name)
        : MSB(msb), LSB(lsb), maxTone(0), numTones(0), bankName(name)
    {
    }

    void add_tone(int pc, const std::string& n, int cat)
    {
        ++numTones;
        tones[pc - 1] = Tone(n, cat);
        maxTone = std::max(maxTone, pc);
    }

    size_t num_tones() { return numTones; }
    Tone* get_tone(int i) { return &tones[i]; }

};

//---------------------------------------------------------------------------------------
class Scene
{
protected:
    int m_number;
    std::string m_name;
    std::array<Tone*, 3> m_tones;

public:
    Scene(int num, const std::string& name)
        : m_number(num), m_name(name)
    {
        for (int i=0; i < 3; ++i)
            m_tones[i] = nullptr;
    }

    const std::string& name() { return m_name; }
    void add_tone(int iTone, Tone* tone) { m_tones[iTone] = tone; }
    Tone* get_tone(int iTone) { return m_tones[iTone]; }

protected:

};

//---------------------------------------------------------------------------------------
class TonesManager
{
protected:
    std::vector<Bank> m_banks;
    std::vector<Tone> m_tones;
    std::vector<Scene> m_scenes;
    std::string m_svdPath;

public:
    TonesManager();
    ~TonesManager();

    std::string load_tones(const std::string& path, std::ostream& logger=std::cout);
    std::string load_scenes(const std::string& path, std::ostream& logger=std::cout);

    Bank* find_bank(int msb, int lsb);
    Scene* get_scene(int i) { return &m_scenes[i]; }
    size_t num_scenes() { return m_scenes.size(); }
    void export_scene(int iScene, const std::string& path);

protected:
    void save_tone(const std::vector<std::string>& words);
    std::string read_header(std::fstream& file, std::ostream& logger);
    std::string read_scene(int iScene, std::fstream& file, size_t pos, std::ostream& logger);

};


}   // namespace rd88snd

#endif    // __RD88_TABLES_H__

