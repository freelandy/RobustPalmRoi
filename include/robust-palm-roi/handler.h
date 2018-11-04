// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_HANDLER_H_
#define ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_HANDLER_H_

#include <map>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "robust-palm-roi/status.h"

namespace rpr {

class PalmInfoDTO;

class Handler {
 public:
  virtual Status Handle(PalmInfoDTO& palm) = 0;
  virtual Status Init(const YAML::Node& parameters) { return Status::Ok(); }
  virtual const char* name() = 0;
};


class HandlerFactory {
 public:
  static HandlerFactory& instance() {
    static HandlerFactory inst;
    return inst;
  }
  void RegisterHandler(const std::string& name, Handler* handler) {
    handlers_.emplace(name, std::shared_ptr<Handler>(handler));
  }
  std::shared_ptr<Handler> GetHandler(const std::string& name) {
    return handlers_.at(name);
  }

 private:
  std::map<std::string, std::shared_ptr<Handler> > handlers_;
};

#define REGISTER_HANDLER(HandlerClass) \
HandlerClass::HandlerClass() {  \
  HandlerFactory::instance().RegisterHandler(#HandlerClass, this); \
} \
const char* HandlerClass::name() { return #HandlerClass; }  \
HandlerClass* g_handler_of_##HandlerClass = new HandlerClass;

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_HANDLER_H_