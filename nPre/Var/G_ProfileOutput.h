///////////////////////////////////////////////////////////////////////////////////
//
// G_ProfileOutput.h
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

#ifndef G_PROFILEOUTPUT_H
#define G_PROFILEOUTPUT_H

#include <genClass/C_FuncObj.h>

#include <objClass/DC_GridData.h>

#include <nsClass/DO_SequenceTimes.h>
#include <nsClass/IO_ProfileSimResults.h>

#include <Var/C_FileOutput.h>


namespace nsOutputFiles  {


    //  reference to output packed in FO for correct updating on file read
    class ProfileForwardOutputFO : public FuncObjC, public FileOutputControl {
        public:
            FuncObjRef          seqTimesObjRef;         // sequence times from G_Sequence
            FuncObjRef          staticPressureObjRef;   // static pressure -- causes update

        private:
            ProfileSimRunResults    runResultData;          // results to be output
            DC_SequenceTimes*       sequenceTimesDC;        // current sequence times
            int                 nCase;
            int                 ncasePar;

            bool                doExtended; 
            DC_GridData         profileData;
            ExtendedProfile     extendedProfileData;

            double              startTime;
            double              endTime;
            int                 timeStepCount;
            double              staticPressure;
            double              thicknessToPressureConversion;
            SC_DoubleArray      waterTablePressure;
            int                 tsMod;
            int                 radMod;

        public:
                                ProfileForwardOutputFO();
                                ~ProfileForwardOutputFO(){};

            virtual bool        OutputSetup(bool& addError);    // prepare for simulation execution
            void                SimulationComplete();   // writes file as planned, cleans up

            void                DoStatusChk();
            void                CalcOutput(FOcalcType  calcType);

            //  for use by data capture routines
            void                CaseInit(const SC_DoubleArray& nodeRadius,
                                         const SC_DoubleArray& constantVertNodeZ,
                                         const double&          currThicknessToPressure);

            void                CaseAddTimeStep(const double&           currTime,
                                                const SC_DoubleArray&   nodePressure,
                                                const SC_DoubleArray&   uncThickness,
                                                const SC_DoubleMatrix&  uncPressure);

        protected:
            virtual void        Cleanup();  // common to both exit routines

        private:
            void                CalcNCase();
            void                AddNodeData(const SC_DoubleArray& nodeInput,
                                                  SC_DoubleArray& nodeOutput,
                                            const UnitIndex&      uConv);

    };

    // profile
    extern IO_ProfileSimResults     profileOutputFile;        // includes file name
    extern ProfileForwardOutputFO   profileOutputFO;          // data to output -- defaults to data capture XY Array output

};


//  assuming that if it's included, we want to use it and no name clashes with other nSight
using namespace nsOutputFiles;


#endif // G_PROFILEOUTPUT_H
