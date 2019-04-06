#ifndef tp_pipeline_caffe2_StubStepDelegate_h
#define tp_pipeline_caffe2_StubStepDelegate_h

#include "tp_pipeline_caffe2/Globals.h"
#include "tp_pipeline/AbstractStepDelegate.h"

namespace tp_pipeline_caffe2
{

//##################################################################################################
class StubStepDelegate: public tp_pipeline::AbstractStepDelegate
{
public:
  //################################################################################################
  StubStepDelegate();

  //################################################################################################
  void executeStep(tp_pipeline::StepDetails* stepDetails,
                   const tp_pipeline::StepInput& inputs,
                   tp_data::Collection& output) const override;

  //################################################################################################
  void fixupParameters(tp_pipeline::StepDetails* stepDetails)const override;
};

}

#endif
