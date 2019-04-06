#include "tp_pipeline_caffe2/Globals.h"
//#include "tp_pipeline_caffe2/step_delegates/StubStepDelegate.h"

#include "tp_pipeline/StepDelegateMap.h"

//##################################################################################################
namespace tp_pipeline_caffe2
{
TDP_DEFINE_ID(                       caffe2SID,                          "Caffe 2")

//##################################################################################################
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates)
{
  TP_UNUSED(stepDelegates);
  //stepDelegates.addStepDelegate(new StubStepDelegate);
}
}
