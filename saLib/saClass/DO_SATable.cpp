///////////////////////////////////////////////////////////////////////////////////
//
// DO_SATable.cpp
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
// DESCRIPTION:
//
//
//
///////////////////////////////////////////////////////////////////////////////////

#include <genClass/U_Str.h>

#include <saClass/DO_SATable.h>

char* DO_SATable::typeDesc = "SATable";

DO_SATable& DO_SATable::operator= (const DO_SATable& a)
{
    if (&a != this)
        saTable = a.saTable;

    return *this;
}

bool  DO_SATable :: DataOK()
{
    bool dataOK = false;

    if (saTable == 0)
        SetErrMsg("Transfer table data not set");
    else if (saTable->GetNStep() == 0)
        SetErrMsg("No steps in table");
    else if (saTable->GetNVariable() == 0)
        SetErrMsg("No variables in table");
    else if (saTable->GetNVector() == 0)
        SetErrMsg("No vectors in table");
    else
        dataOK = true;

    return dataOK;
}


const char* DO_SATable::GetID()
{
    const char* retVal = "not set";
    if (saTable != 0)
    {
        retVal = saTable->GetID();
        if (IsNull(retVal))
            retVal = "no ID";
    }
    return retVal;
}

