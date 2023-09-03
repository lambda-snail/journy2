#pragma once

#include <wx/wx.h>

class App{
public:
    static wxString const name;
};

class Config
{
public:
    static wxString const db_name;
    static wxString const last_db_location;
};