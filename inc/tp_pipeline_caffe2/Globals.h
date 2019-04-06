#ifndef tp_pipeline_caffe2_Globals_h
#define tp_pipeline_caffe2_Globals_h

#include "tp_utils/StringID.h"

namespace tp_pipeline
{
class StepDelegateMap;
}

//##################################################################################################
//! Add caffe2 to the pipeline pipeline.
namespace tp_pipeline_caffe2
{
TDP_DECLARE_ID(                       caffe2SID,                          "Caffe 2")

//##################################################################################################
//! Add the step delegates that this module provides to the StepDelegateMap
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates);
}

#endif
