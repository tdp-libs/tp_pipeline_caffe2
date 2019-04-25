#ifndef tp_pipeline_caffe2_ExecuteGraphStepDelegate_h
#define tp_pipeline_caffe2_ExecuteGraphStepDelegate_h

#include "tp_pipeline_caffe2/Globals.h"
#include "tp_pipeline/AbstractStepDelegate.h"

namespace tp_pipeline_caffe2
{

//##################################################################################################
class ExecuteGraphStepDelegate: public tp_pipeline::AbstractStepDelegate
{
public:
  //################################################################################################
  ExecuteGraphStepDelegate();

  //################################################################################################
  void executeStep(tp_pipeline::StepDetails* stepDetails,
                   const tp_pipeline::StepInput& inputs,
                   tp_data::Collection& output) const override;

  //################################################################################################
  void fixupParameters(tp_pipeline::StepDetails* stepDetails)const override;

  //################################################################################################
  static tp_pipeline::StepDetails* makeStepDetails(const std::string& inName,
                                                   const std::string& outName,
                                                   const std::string& inBlobName,
                                                   const std::string& outBlobName,
                                                   const std::vector<int64_t>& inBlobShape,
                                                   const std::string& predictNetData,
                                                   const std::string& initNetData);
};

}

#endif
