///////////////////////////////////////////////////////////////////////////////////
//
// PS_Import.cpp
//
///////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 Sandia Corporation. Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of Sandia Corporation nor the
//      names of its contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION: Platform specific but application independent code.
//              Base class for reading data from the Windows clipboard
//
///////////////////////////////////////////////////////////////////////////////////

#include "GenLibAfx.h"

#include <genClass/U_Str.h>

#include "PS_Import.h"

PS_Import::PS_Import()
  : PS_TxtClipboard(maxImportChars)
{
}

PS_Import::~PS_Import()
{
}


bool PS_Import::OpenClipboardImport()
{
    return OpenTxtClipboard(false);
}



bool PS_Import::GetLineDoubles(SC_DoubleArray& lineData)
{
    if (!ImportNextLine())
        return false;

    lineData.SetResizable(50);

    char* szToken = strtok(nextLine," \t\n" );
    while (szToken != NULL)
        {
            double val;
            if (IsValidReal(szToken, val))
                lineData += val;
            szToken = strtok(NULL," \t\n");
        }

    return true;
}


bool PS_Import::GetLineStrings(SC_StringArray& lineData)
{
    if (!ImportNextLine())
        return false;

    lineData.ForceMinStringLen(StringLength(nextLine));
    lineData.SetResizable(50);

    char* szToken = strtok(nextLine," \t\n" );
    while (szToken != NULL)
        {
            lineData += szToken;
            FullTrim(lineData.LastIndex());
            szToken = strtok(NULL," \t\n");
        }

    return true;
}


bool PS_Import::ImportNextLine()
{
    if (IsEOF())
        return false;
    try
        {
            ReadText(nextLine, maxImportChars);
        }
    catch (TextC::TextError)
        {
            return false;
        }

    return true;
}



void PS_Import::CloseImport()
{
    CloseTxtClipboard();
}

