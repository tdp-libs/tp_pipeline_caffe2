TARGET = tp_pipeline_caffe2
TEMPLATE = lib

DEFINES += TP_PIPELINE_CAFFE2_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_pipeline_caffe2/Globals.h


#-- Delegates --------------------------------------------------------------------------------------
SOURCES += src/step_delegates/StubStepDelegate.cpp
HEADERS += inc/tp_pipeline_caffe2/step_delegates/StubStepDelegate.h


#-- Members ----------------------------------------------------------------------------------------
SOURCES += src/members/StubMember.cpp
HEADERS += inc/tp_pipeline_caffe2/members/StubMember.h
