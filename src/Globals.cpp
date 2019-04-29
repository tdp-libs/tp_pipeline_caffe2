#include "tp_pipeline_caffe2/Globals.h"
#include "tp_pipeline_caffe2/step_delegates/ExecuteGraphStepDelegate.h"

#include "tp_pipeline/StepDelegateMap.h"

//##################################################################################################
namespace tp_pipeline_caffe2
{
TDP_DEFINE_ID(                       caffe2SID,                          "Caffe 2")
TDP_DEFINE_ID(                 executeGraphSID,                    "Execute graph")
TDP_DEFINE_ID(                   inBlobNameSID,                     "In blob name")
TDP_DEFINE_ID(                  outBlobNameSID,                    "Out blob name")
TDP_DEFINE_ID(                    dataInputSID,                       "Data input")
TDP_DEFINE_ID(                  inBlobShapeSID,                    "In blob shape")
TDP_DEFINE_ID(                  graphObjectSID,                     "Graph object")

//##################################################################################################
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory)
{
  TP_UNUSED(collectionFactory);
  stepDelegates.addStepDelegate(new ExecuteGraphStepDelegate());
}

REGISTER_CREATE_STEP_DELEGATES;

//##################################################################################################
int staticInit()
{
  return 0;
}

}
