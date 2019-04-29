#include "tp_pipeline_caffe2/step_delegates/ExecuteGraphStepDelegate.h"
#include "tp_pipeline_caffe2/complex_objects/GraphComplexObject.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data_math_utils/members/FloatsMember.h"

#include "tp_data_math_utils/members/FloatsMember.h"
#include "tp_data/Collection.h"

namespace tp_pipeline_caffe2
{

namespace
{

//##################################################################################################
void _fixupParameters(tp_pipeline::StepDetails* stepDetails)
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = dataInputSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The vector of floats to feed into the network.";
    param.type = tp_pipeline::namedDataSID();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = inBlobNameSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The name of the blob to feed data into.";
    param.type = tp_pipeline::stringSID();
    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = outBlobNameSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The name of the blob to read data from.";
    param.type = tp_pipeline::stringSID();
    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = inBlobShapeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "A comma separated list of input dimensions.";
    param.type = tp_pipeline::stringSID();
    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

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
  std::string error;
  TP_CLEANUP([&]{if(!error.empty())output.addError(error);});

  std::string dataInputName = stepDetails->parameterValue<std::string>(dataInputSID());
  if(dataInputName.empty())
  {
    error = "Failed to find input data name.";
    return;
  }

  const tp_data_math_utils::FloatsMember* src{nullptr};
  input.memberCast(dataInputName, src);
  if(!src)
  {
    error = "Failed to find input data. Member name: " + dataInputName;
    return;
  }

  tp_pipeline_caffe2::GraphComplexObjectFactory factory;
  auto p = dynamic_cast<tp_pipeline_caffe2::GraphComplexObject*>(stepDetails->complexObjectManager.complexObject(graphObjectSID(), &factory));
  if(!p)
  {
    error = "Faile to get graph object.";
    return;
  }

  auto outData = p->execute(error, src->data);
  if(!error.empty())
    return;

  auto outMember = new tp_data_math_utils::FloatsMember(stepDetails->lookupOutputName("Output data"));
  outMember->data = std::move(outData);
  output.addMember(outMember);
}

//##################################################################################################
void ExecuteGraphStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  _fixupParameters(stepDetails);
}

//##################################################################################################
tp_pipeline::StepDetails* ExecuteGraphStepDelegate::makeStepDetails(const std::string& inName,
                                                                    const std::string& outName,
                                                                    const std::string& inBlobName,
                                                                    const std::string& outBlobName,
                                                                    const std::vector<int64_t>& inBlobShape,
                                                                    const std::string& predictNetData,
                                                                    const std::string& initNetData)
{
  auto stepDetails = new tp_pipeline::StepDetails(executeGraphSID());
  _fixupParameters(stepDetails);

  std::string inBlobShape_;
  if(!inBlobShape.empty())
  {
    inBlobShape_ += std::to_string(inBlobShape.front());
    for(size_t i=1; i<inBlobShape.size(); i++)
      inBlobShape_ += ',' + std::to_string(inBlobShape.at(i));
  }

  stepDetails->setParameterValue(  dataInputSID(), inName      );
  stepDetails->setParameterValue( inBlobNameSID(), inBlobName  );
  stepDetails->setParameterValue(outBlobNameSID(), outBlobName );
  stepDetails->setParameterValue(inBlobShapeSID(), inBlobShape_);
  stepDetails->setOutputMapping({{"Output data", outName}});

  tp_pipeline_caffe2::GraphComplexObjectFactory factory;
  auto p = dynamic_cast<tp_pipeline_caffe2::GraphComplexObject*>(stepDetails->complexObjectManager.complexObject(graphObjectSID(), &factory));
  if(p)
    p->setGraph(predictNetData, initNetData, inBlobName, outBlobName, inBlobShape);

  return stepDetails;
}

}
