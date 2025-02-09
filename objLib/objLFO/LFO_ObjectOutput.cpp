///////////////////////////////////////////////////////////////////////////////////
//
// LFO_ObjectOutput.cpp
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
#include <genClass/U_Real.h>

#include <genClass/DO_Listing.h>

#include <objLFO/LFO_ObjectOutput.h>

LFO_ObjectOutput :: LFO_ObjectOutput(ListDefC& assLst)
    : ListObjC("List Object Output", assLst)
{
    InitCommon();
}

LFO_ObjectOutput::LFO_ObjectOutput(const LFO_ObjectOutput& a, ListDefC& assLst) : ListObjC(a, assLst)
{
    LocalCopy(a);
    InitCommon();
}

LFO_ObjectOutput :: ~LFO_ObjectOutput ()
{
}

void LFO_ObjectOutput::InitCommon()
{
    AddInPort(objectOutputObjRef, typeid(DO_Listing));
    DoStatusChk();
}

LFO_ObjectOutput& LFO_ObjectOutput::operator= (const LFO_ObjectOutput& a)
{
    if (&a != this)
        LocalCopy(a);
    return *this;
}


void LFO_ObjectOutput::LocalCopy(const LFO_ObjectOutput& a)
{
    objectOutputObjRef  = a.objectOutputObjRef;
}


void LFO_ObjectOutput::DoStatusChk()
{
    FuncObjC::DoStatusChk();
    CheckInputFO(objectOutputObjRef, "Object to list");
}


void LFO_ObjectOutput::CreateListing()
{
    listingData = static_cast<DO_Listing*>(GetInPortData(objectOutputObjRef))->GetListData();
}


