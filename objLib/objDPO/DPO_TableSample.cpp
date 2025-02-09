///////////////////////////////////////////////////////////////////////////////////
//
// DPO_TableSample.cpp
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
//    I/O and user interface for respective ../objDFO/DFO_XXX functional objects
//
//
///////////////////////////////////////////////////////////////////////////////////

#include "ObjLibAfx.h"

#include <objDPO/objDPOConfigFile.h>

#include "DPO_TableSample.h"
#ifndef ADCONSOLEAPP
#include "DPO_TableSamplePS.h"
#endif

static const char* objLongDesc = "Create/Add To Sample Table";

DPO_TableSample :: DPO_TableSample() :
    MenuObjC(this, objLongDesc)
{
}

DPO_TableSample :: DPO_TableSample(const DPO_TableSample& a) :
    DFO_TableSample(a),
    MenuObjC(this, objLongDesc)
{
}

DPO_TableSample& DPO_TableSample::operator= (const DPO_TableSample& a)
{
    if (&a != this)
       *((DFO_TableSample*) this) = a;
    return *this;
}


bool DPO_TableSample::ReadFromFile()
{
    ReadObjectHeader();
    ReadFuncObjRef(existingTableObjRef);

    createNewTable = ReadBool();
    nsamples = ReadInt();
    randomSeed = ReadInt();
    stratifySample = ReadBool();
    randomMix = ReadBool();

    sampVar.svDistribution = SC_SampVar::SVDistribution(ReadInt());
    if (currentObjReadMajorVersion == 0)
    {
        if (sampVar.svDistribution >= SC_SampVar::svdStudentT)
            sampVar.svDistribution = SC_SampVar::SVDistribution(int(sampVar.svDistribution) + 1);
    }

    sampVar.distMean        = ReadNullDouble();
    sampVar.distStdDev      = ReadNullDouble();
    sampVar.distLogStdDev   = ReadNullDouble();
    sampVar.distPeak        = ReadNullDouble();
    sampVar.distMin         = ReadNullDouble();
    sampVar.distMax         = ReadNullDouble();
    sampVar.poissonLambda   = ReadNullDouble();
    sampVar.weibullShape    = ReadNullDouble();
    sampVar.weibullScale    = ReadNullDouble();
    sampVar.betaP           = ReadNullDouble();
    sampVar.betaQ           = ReadNullDouble();

    ReadFuncObjRef(sampVar.userCDFInputObjRef); // added v3
    ReadFuncObjRef(sampVar.tableLookupObjRef); // added v4
    sampVar.tableLookupColumn = ReadInt();

    CheckForInputFailure("Reading DPO_TableSample");
    return true;
}

void DPO_TableSample::WriteToFile()
{
    const int objMajVer = 1; // added Student t
//    const int objMajVer = 0;
    const int objMinVer = 0;

    WriteObjectHeader(objMajVer, objMinVer);

    WriteFuncObjRef(existingTableObjRef);

    WriteBool(createNewTable);
    WriteInt(nsamples);
    WriteInt(randomSeed);
    WriteBool(stratifySample);
    WriteBool(randomMix);
    WriteLine();

    WriteInt(sampVar.svDistribution);
    WriteNullDouble(sampVar.distMean);
    WriteNullDouble(sampVar.distStdDev);
    WriteNullDouble(sampVar.distLogStdDev);
    WriteNullDouble(sampVar.distPeak);
    WriteNullDouble(sampVar.distMin);
    WriteNullDouble(sampVar.distMax);
    WriteNullDouble(sampVar.poissonLambda);
    WriteNullDouble(sampVar.weibullShape);
    WriteNullDouble(sampVar.weibullScale);
    WriteNullDouble(sampVar.betaP);
    WriteNullDouble(sampVar.betaQ);
    WriteLine();

    WriteFuncObjRef(sampVar.userCDFInputObjRef);
    WriteFuncObjRef(sampVar.tableLookupObjRef);
    WriteInt(sampVar.tableLookupColumn);
    WriteLine();
}

#ifndef ADCONSOLEAPP

DPO_TableSamplePS& DPO_TableSample::MenuRef()
{
    ASSERT(assocMenu);
    return static_cast<DPO_TableSamplePS&>(*assocMenu);
}

void DPO_TableSample::PropOpenMenu()
{
    MenuObjC::PropOpenMenu();
    assocMenu = new DPO_TableSamplePS();
    MenuRef().InitMenu();
    MenuRef().MenuOpen(*this);

    PropUpdate();
}

void DPO_TableSample::PropUpdate()
{
    if (UpdateOK())
        MenuRef().SetMenuData(*this);
}

void DPO_TableSample::PropApply()
{
    MenuRef().GetMenuData(*this);
    MenuObjC::PropApply();
}

#endif //!ADCONSOLEAPP

