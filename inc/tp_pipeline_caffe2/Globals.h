#ifndef tp_pipeline_caffe2_Globals_h
#define tp_pipeline_caffe2_Globals_h

#include "tp_utils/StringID.h"


namespace tp_data
{
class CollectionFactory;
}

namespace tp_pipeline
{
class StepDelegateMap;
}

//##################################################################################################
//! Add caffe2 to the pipeline pipeline.
namespace tp_pipeline_caffe2
{
TDP_DECLARE_ID(                       caffe2SID,                          "Caffe 2")
TDP_DECLARE_ID(                 executeGraphSID,                    "Execute graph")
TDP_DECLARE_ID(                   inBlobNameSID,                     "In blob name")
TDP_DECLARE_ID(                  outBlobNameSID,                    "Out blob name")
TDP_DECLARE_ID(                    dataInputSID,                       "Data input")
TDP_DECLARE_ID(                  inBlobShapeSID,                    "In blob shape")
TDP_DECLARE_ID(                  graphObjectSID,                     "Graph object")

//##################################################################################################
//! Add the step delegates that this module provides to the StepDelegateMap
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory);

//##################################################################################################
//! Static initialization of this module, see TP_STATIC_INIT in dependencies.pri
int staticInit();

}

#endif
