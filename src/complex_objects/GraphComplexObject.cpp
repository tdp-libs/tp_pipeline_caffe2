#include "tp_pipeline_caffe2/complex_objects/GraphComplexObject.h"

#include "tp_caffe2_utils/FillOps.h"
#include "tp_caffe2_utils/BlobUtils.h"

#include "tp_data/CollectionFactory.h"
#include "tp_data/AbstractMember.h"

#include "tp_utils/JSONUtils.h"
#include "tp_utils/DebugUtils.h"

namespace tp_pipeline_caffe2
{

struct GraphComplexObject::Private
{
  bool netReady{false};
  caffe2::NetDef predictNet;
  caffe2::NetDef initNet;
  caffe2::Workspace workspace;

  std::string predictNetData;
  std::string initNetData;

  std::string inBlobName;
  std::string outBlobName;
  std::vector<int64_t> inBlobShape;

  //################################################################################################
  Private()
  {

  }

  //################################################################################################
  ~Private()
  {
    deleteGraph();
  }

  //################################################################################################
  void deleteGraph()
  {
    netReady = false;
  }

  //################################################################################################
  void loadGraph(const std::string& predictNetData_, const std::string& initNetData_, std::string& error)
  {
    netReady = false;

    predictNetData = predictNetData_;
    initNetData    = initNetData_;

    if(!predictNet.ParseFromString(predictNetData))
    {
      error = "Failed to load net structure.";
      tpWarning() << error;
      return;
    }

    if(!initNet.ParseFromString(initNetData))
    {
      error = "Failed to load weights net.";
      tpWarning() << error;
      return;
    }

    caffe2::NetDef initPredictNet;
    initPredictNet.set_name("initPredict");
    tp_caffe2_utils::addConstantFillOp(initPredictNet, inBlobShape, 1.0f, inBlobName);

    workspace.RunNetOnce(initNet);
    workspace.RunNetOnce(initPredictNet);
    workspace.CreateNet (predictNet);

    netReady = true;
  }
};

//##################################################################################################
GraphComplexObject::GraphComplexObject():
  AbstractComplexObject(graphObjectSID()),
  d(new Private)
{

}

//##################################################################################################
GraphComplexObject::~GraphComplexObject()
{
  delete d;
}


//##################################################################################################
void GraphComplexObject::setGraph(const std::string& predictNetData,
                                  const std::string& initNetData,
                                  const std::string& inBlobName,
                                  const std::string& outBlobName,
                                  const std::vector<int64_t>& inBlobShape)
{
  d->inBlobName  = inBlobName;
  d->outBlobName = outBlobName;
  d->inBlobShape = inBlobShape;

  std::string error;
  d->loadGraph(predictNetData, initNetData, error);
  if(!error.empty())
    tpWarning() << "GraphComplexObject::setGraph Error: " << error;
}

//##################################################################################################
std::vector<float> GraphComplexObject::execute(std::string& error, const std::vector<float>& dataIn)
{
  std::vector<float> results;

  if(!d->netReady)
  {
    error = "Net not ready.";
    return results;
  }

  tp_caffe2_utils::setBlob(d->workspace, d->inBlobName, dataIn, d->inBlobShape);
  d->workspace.RunNetOnce(d->predictNet);
  tp_caffe2_utils::readBlob(d->workspace, d->outBlobName, results);

  return results;
}

//##################################################################################################
nlohmann::json GraphComplexObject::saveBinary(const std::function<uint64_t(const std::string&)>& addBlob) const
{
  nlohmann::json j;
  j["inBlobName"]     = d->inBlobName ;
  j["outBlobName"]    = d->outBlobName;

  j["inBlobShape"] = nlohmann::json::array();
  for(auto s : d->inBlobShape)
    j["inBlobShape"].push_back(s);

  j["predictNetData"] = addBlob(d->predictNetData);
  j["initNetData"]    = addBlob(d->initNetData);
  return j;
}

//##################################################################################################
tp_pipeline::AbstractComplexObject* GraphComplexObject::clone() const
{
  auto obj = new GraphComplexObject();
  obj->d->inBlobName  = d->inBlobName ;
  obj->d->outBlobName = d->outBlobName;
  obj->d->inBlobShape = d->inBlobShape;

  std::string error;
  obj->d->loadGraph(d->predictNetData, d->initNetData, error);

  return obj;
}

//##################################################################################################
tp_pipeline::AbstractComplexObject* GraphComplexObjectFactory::create() const
{
  return new GraphComplexObject();
}

//##################################################################################################
tp_pipeline::AbstractComplexObject* GraphComplexObjectFactory::loadBinary(const nlohmann::json& j, const std::vector<std::string>& blobs) const
{
  auto obj = new GraphComplexObject();

  obj->d->inBlobName  = TPJSONString(j, "inBlobName");
  obj->d->outBlobName = TPJSONString(j, "outBlobName");

  {
    obj->d->inBlobShape.clear();
    auto jj = TPJSON(j, "inBlobShape");
    if(jj.is_array())
      for(size_t i=0; i<jj.size(); i++)
        if(jj.is_number())
          obj->d->inBlobShape.push_back(jj);
  }

  if(size_t i = TPJSONSizeT(j, "predictNetData"); i<blobs.size())
    obj->d->predictNetData = blobs.at(i);

  if(size_t i = TPJSONSizeT(j, "initNetData"); i<blobs.size())
    obj->d->initNetData = blobs.at(i);

  std::string error;
  obj->d->loadGraph(obj->d->predictNetData, obj->d->initNetData, error);

  return obj;
}

}
