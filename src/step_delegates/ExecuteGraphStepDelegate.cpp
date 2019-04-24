#include "tp_pipeline_caffe2/step_delegates/ExecuteGraphStepDelegate.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

namespace tp_pipeline_caffe2
{

namespace
{

//##################################################################################################
void _fixupParameters(tp_pipeline::StepDetails* stepDetails)
{
  stepDetails->setOutputNames({"Output image"});

  std::vector<tp_utils::StringID> validParams;
  //  const auto& parameters = stepDetails->parameters();

  //  {
  //    const auto& name = tp_pipeline_image_utils::colorImageSID();
  //    auto param = tpGetMapValue(parameters, name);
  //    param.name = name;
  //    param.description = "The source color image to draw on.";
  //    param.type = tp_pipeline::namedDataSID();

  //    stepDetails->setParamerter(param);
  //    validParams.push_back(name);
  //  }

  //  {
  //    const auto& name = tp_pipeline_math_utils::polygonsSID();
  //    auto param = tpGetMapValue(parameters, name);
  //    param.name = name;
  //    param.description = "The polygons to draw.";
  //    param.type = tp_pipeline::namedDataSID();

  //    stepDetails->setParamerter(param);
  //    validParams.push_back(name);
  //  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}

//##################################################################################################
ExecuteGraphStepDelegate::ExecuteGraphStepDelegate():
  tp_pipeline::AbstractStepDelegate(executeGraphSID(), {caffe2SID()})
{

}

//##################################################################################################
void ExecuteGraphStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                           const tp_pipeline::StepInput& input,
                                           tp_data::Collection& output) const
{
  TP_UNUSED(stepDetails);
  TP_UNUSED(input);
  TP_UNUSED(output);




  //    {
  //      TP_MUTEX_LOCKER(d->mutex);
  //      if(!d->netReady)
  //      {
  //        error = "Net not ready.";
  //        return;
  //      }

  //      tp_caffe2_utils::setBlob(d->workspace, "data", floatData, {1, 3, 224, 224});
  //      d->workspace.RunNetOnce(d->predictNet);
  //      tp_caffe2_utils::readBlob(d->workspace, "predictions", transformations);
  //    }




}

//##################################################################################################
void ExecuteGraphStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  _fixupParameters(stepDetails);
}

//##################################################################################################
tp_pipeline::StepDetails* ExecuteGraphStepDelegate::makeStepDetails(const std::string& inName,
                                                                    const std::string& outName,
                                                                    const std::string& predictNetData,
                                                                    const std::string& initNetData)
{
  auto stepDetails = new tp_pipeline::StepDetails(executeGraphSID());
  _fixupParameters(stepDetails);
#warning add a blob name field
  //stepDetails->setParameterValue(colorImageSID(), inName);
  //stepDetails->setOutputMapping({{"Output data", outName}});
  return stepDetails;
}

}
