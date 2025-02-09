///////////////////////////////////////////////////////////////////////////////////
//
// UPO_WriteColorMap.cpp
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
//      File I/O and user-interface for genUFO
//
///////////////////////////////////////////////////////////////////////////////////

#include "GenLibAfx.h"

#ifndef ADCONSOLEAPP
#include "UPO_WriteColorMapPS.h"
#endif

#include <genApp/AppConfigFile.h>

#include "UPO_WriteColorMap.h"


const char* UPO_WriteColorMap::objLongDesc = "Write Color Map";

UPO_WriteColorMap :: UPO_WriteColorMap() : MenuObjC(this, objLongDesc)
{
    RegisterFileName(outFname);
}

UPO_WriteColorMap :: UPO_WriteColorMap(const UPO_WriteColorMap& a) : UFO_WriteColorMap(a), MenuObjC(this, objLongDesc)
{
    RegisterFileName(outFname);
}

UPO_WriteColorMap::~UPO_WriteColorMap()
{
}


UPO_WriteColorMap& UPO_WriteColorMap::operator= (const UPO_WriteColorMap& a)
{
    if (&a != this)
       *((UFO_WriteColorMap*) this) = a;
    return *this;
}

bool  UPO_WriteColorMap::ReadFromFile()
{
    ReadObjectHeader();
    ReadFileName(outFname);
    ReadFuncObjRef(colorMapObjRef);
    CheckForInputFailure("Reading UPO_WriteColorMap");
    return true;
}


void UPO_WriteColorMap::WriteToFile()
{
    const int objMajVer = 0;
    const int objMinVer = 0;

    WriteObjectHeader(objMajVer, objMinVer);

    WriteText(outFname);
    WriteFuncObjRef(colorMapObjRef);
}

#ifndef ADCONSOLEAPP

// ************************* menu stuff


UPO_WriteColorMapPS& UPO_WriteColorMap::MenuRef()
{
    ASSERT(assocMenu);
    return static_cast<UPO_WriteColorMapPS&>(*assocMenu);
}


void UPO_WriteColorMap::PropUpdate()
{
    if (UpdateOK())
        MenuRef().SetMenuData(*this);
}


void UPO_WriteColorMap::PropOpenMenu()
{
    MenuObjC::PropOpenMenu();
    assocMenu = new UPO_WriteColorMapPS();
    MenuRef().InitMenu();
    MenuRef().MenuOpen(*this);

    PropUpdate();
}


void UPO_WriteColorMap::PropApply()
{
    MenuRef().GetMenuData(*this);
    MenuObjC::PropApply();
}


#endif // !ADCONSOLEAPP

