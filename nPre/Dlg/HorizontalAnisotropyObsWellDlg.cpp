///////////////////////////////////////////////////////////////////////////////////
//
// HorizontalAnisotropyObsWellDlg.cpp
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
//      nPre dialog
//
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Resource.h"
#include "HorizontalAnisotropyObsWellDlg.h"

#include <genClass/U_Str.h>

#include <Var/G_Control.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameterFileDlg dialog


CHorizontalAnisotropyObsWellDlg::CHorizontalAnisotropyObsWellDlg(DataCaptureSpec& inSpec, CWnd* pParent /*=NULL*/)
    : CGenericDialog(CHorizontalAnisotropyObsWellDlg::IDD, pParent),
      dataCaptureSpec(inSpec)
{
    m_obsXLocation = dataCaptureSpec.obsXLocation;
    m_obsYLocation = dataCaptureSpec.obsYLocation;
}

BOOL CHorizontalAnisotropyObsWellDlg::OnInitDialog()
{
    m_uobsXLocation.Set(this, IDC_COMBO1, IDC_EDIT1, &m_obsXLocation,
                    NULL, -1.0E+7, 1.0E+07);
    m_uobsYLocation.Set(this, IDC_COMBO2, IDC_EDIT2, &m_obsYLocation,
                    NULL, -1.0E+7, 1.0E+07);

    CDialog::OnInitDialog();

    DoCtrlUpdate();

    InitData(true);

    return TRUE;
}

void CHorizontalAnisotropyObsWellDlg::CheckRestrictions()
{
}


void CHorizontalAnisotropyObsWellDlg::ResetAllControls()
{
    m_uobsXLocation.DoCtrlReset();
    m_uobsYLocation.DoCtrlReset();
}


void CHorizontalAnisotropyObsWellDlg::OnOK()
{
    // kluge to make sure that ctrl with current focus gets updated
    GotoDlgCtrl(GetDlgItem(IDOK));

    dataCaptureSpec.obsXLocation = m_obsXLocation;
    dataCaptureSpec.obsYLocation = m_obsYLocation;

    CDialog::OnOK();
}

void CHorizontalAnisotropyObsWellDlg::DoDataExchange(CDataExchange* pDX)
{
    CGenericDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CParameterFileDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHorizontalAnisotropyObsWellDlg, CGenericDialog)
    //{{AFX_MSG_MAP(CHorizontalAnisotropyObsWellDlg)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterFileDlg message handlers


