///////////////////////////////////////////////////////////////////////////////////
//
// PFO_GridFishnet.h
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
//    Plots grid data as a fishnet on 3D plots.
//
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef PFO_GRIDFISHNET_H
#define PFO_GRIDFISHNET_H

#include <genClass/C_Common.h>

#include <genPlotClass/PSC_ExtrusionSpec.h>
#include <genPlotClass/PSC_LegendOverride.h>
#include <genPlotClass/DO_SeriesLegendData.h>
#include <genPlotClass/C_PlotObj.h>

#include <objPlotClass/PSC_3DCoordMap.h>

#include <objClass/DC_GridData.h>

class PFO_GridFishnet : public PlotObjC  {
  protected:
      //  input objects
      FuncObjRef                  gridDataObjRef;
      // properties
      bool                        plotAsTubes;
      int                         gridPen;      // for all
      int                         gridLineThk;  // for line
      PlotLineType                gridLineType;

      PSC_TubeExtrusionSpec       tubeData;      // for tube
      PSC_LegendOverride          legendOverride;
      PSC_3DCoordMap              coordMap;

      int                         xplotModulus;
      int                         yplotModulus;
      bool                        plotLastX;
      bool                        plotLastY;

      // plotting data
      const DC_GridData*          gridDataDC;

  private:
      // output objects
      DO_SeriesLegendData         seriesLegendData;    // output for legend

  public:
                      PFO_GridFishnet(PlotDefC& assPlt);
                      PFO_GridFishnet(const PFO_GridFishnet& a, PlotDefC& assPlt);
                      ~PFO_GridFishnet();

      PFO_GridFishnet& operator= (const PFO_GridFishnet& a);

                      //  FuncObjC virtuals
      void            DoStatusChk();
      void            CalcOutput(FOcalcType  calcType);

                      //  PlotObjC  draw virtuals in derived PFO_GridFishnetGL
      Limit3D         GetPlotObjLimits();
      bool            ContainsLinesOnly();


  private:
      void            InitCommon();                         // common to normal and copy constructor
      void            LocalCopy(const PFO_GridFishnet& a);  // common to copy constructor and = operator
};

#endif // !PFO_GRIDFISHNET_H

