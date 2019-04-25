#ifndef tp_pipeline_caffe2_GraphComplexObject_h
#define tp_pipeline_caffe2_GraphComplexObject_h

#include "tp_pipeline_caffe2/Globals.h"

#include "tp_pipeline/AbstractComplexObject.h"
#include "tp_pipeline/AbstractComplexObjectFactory.h"

#include "tp_data/Collection.h"

#include "json.hpp"

namespace tp_pipeline_caffe2
{

//##################################################################################################
class GraphComplexObject: public tp_pipeline::AbstractComplexObject
{
public:
  //################################################################################################
  GraphComplexObject();

  //################################################################################################
  ~GraphComplexObject() override;

  //################################################################################################
  void setGraph(const std::string& predictNetData,
                const std::string& initNetData,
                const std::string& inBlobName,
                const std::string& outBlobName,
                const std::vector<int64_t>& inBlobShape);

  //################################################################################################
  std::vector<float> execute(std::string& error, const std::vector<float>& dataIn);

  //################################################################################################
  nlohmann::json saveBinary(const std::function<uint64_t(const std::string&)>& addBlob) const override;

  //################################################################################################
  AbstractComplexObject* clone() const override;

private:
  friend class GraphComplexObjectFactory;
  struct Private;
  friend struct Private;
  Private* d;
};

//##################################################################################################
class GraphComplexObjectFactory: public tp_pipeline::AbstractComplexObjectFactory
{
public:
  //################################################################################################
  tp_pipeline::AbstractComplexObject* create() const override;

  //################################################################################################
  tp_pipeline::AbstractComplexObject* loadBinary(const nlohmann::json& j, const std::vector<std::string>& blobs) const override;
};

}

#endif

