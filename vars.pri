TARGET = tp_pipeline_caffe2
TEMPLATE = lib

DEFINES += TP_PIPELINE_CAFFE2_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_pipeline_caffe2/Globals.h


#-- Delegates --------------------------------------------------------------------------------------
SOURCES += src/step_delegates/ExecuteGraphStepDelegate.cpp
HEADERS += inc/tp_pipeline_caffe2/step_delegates/ExecuteGraphStepDelegate.h

#-- Complex objects --------------------------------------------------------------------------------

SOURCES += src/complex_objects/GraphComplexObject.cpp
HEADERS += inc/tp_pipeline_caffe2/complex_objects/GraphComplexObject.h
