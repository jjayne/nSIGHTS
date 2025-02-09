///////////////////////////////////////////////////////////////////////////////////
//
// DFO_ReadXY.cpp
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
//      Reads XY data from ASCII file in several formats
//
///////////////////////////////////////////////////////////////////////////////////

#include <genClass/U_Str.h>
#include <genClass/C_MessageLog.h>
#include <genClass/IO_XYData.h>

#include <objDFO/DFO_ReadXY.h>

DFO_ReadXY :: DFO_ReadXY() :
    FuncObjC("Read XY")
{
    SetToNull(xyFname);
    CopyString(dataID, "PDAT", DC_XYData::dataIDLen);
    InitCommon();
}

DFO_ReadXY::DFO_ReadXY(const DFO_ReadXY& a) : FuncObjC(a)
{
    LocalCopy(a);
    InitCommon();
}

void DFO_ReadXY::InitCommon()
{
    xyDataDO.xyData = &xyData;
    fileNameDO.SetTypeLabel("XY file");
    AddOutPort(xyDataDO);
    AddOutPort(fileNameDO);
    mpiFiles += NodeFile(xyFname, "XY file");

    DoStatusChk();
}

DFO_ReadXY& DFO_ReadXY::operator= (const DFO_ReadXY& a)
{
    if (&a != this)
    {
        FuncObjC::FullCopy(a);
        DSC_XYInputSpec::operator =(a);
        LocalCopy(a);
    }
    return *this;
}


void  DFO_ReadXY::LocalCopy(const DFO_ReadXY& a)
{
    CopyString(xyFname, a.xyFname, stdFileStrLen);
    CopyString(dataID, a.dataID, DC_XYData::dataIDLen);
    mpiFiles.CopyFrom(a.mpiFiles);
}

void  DFO_ReadXY:: DoStatusChk()
{
    FuncObjC::DoStatusChk();
    if (!xyDataDO.DataOK())
        SetObjErrMsg("No data read");
}

void DFO_ReadXY:: CalcOutput(FOcalcType  calcType)
{
    if ((calcType == foc_Full) || (calcType == foc_Apply))
    {
        xyData.DeAlloc();
        objStatus = os_OK;
        mpiFiles.StdCheckAndUpdate(*this);
        if (StatusNotOK())
            return;

        IO_XYData inFile;
        if (!inFile.ReadXYFile(xyFname, *this, xyData))
        {
            SetObjErrMsg(MessageLogC::GetLastMessage());
            return;
        }

        fileNameDO.SetFileValueLabel(xyFname);
        if ((xyFileFormat == xyffDate) || (!readColumnID))
        {
            CopyString(xyData.dataID, dataID, DC_XYData::dataIDLen);
        }

        SetDefaultFileID(xyFname);
    }

    DoStatusChk();
    if (StatusNotOK())
    {
        xyData.DeAlloc();
        return;
    }
}

