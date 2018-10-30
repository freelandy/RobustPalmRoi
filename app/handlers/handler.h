// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_HANDLER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_HANDLER_H_

#include <map>
#include <opencv2/opencv.hpp>
#include "common/status.h"
#include "common/palm.h"


namespace rpr {

class Handler {
 public:
  virtual Status Handle(PalmInfoDTO& palm) = 0;
  virtual Status Init() = 0;
};


class HandlerFactory {
 public:
  static HandlerFactory& instance() {
    static HandlerFactory inst;
    return inst;
  }
  void RegisterHandler(const std::string& name, Handler* handler) {
    handlers_.emplace(name, handler);
  }
  std::shared_ptr<Handler> GetHandler(const std::string& name) {
    return handlers_.at(name);
  }
  const std::map<std::string, std::shared_ptr<Handler> >& handers() {
    return handlers_;
  }

 private:
  std::map<std::string, std::shared_ptr<Handler> > handlers_;
};

#define REGISTER_HANDLER(HandlerClass) \
HandlerClass::HandlerClass() {  \
  HandlerFactory::instance().RegisterHandler(#HandlerClass, this); \
} \
static HandlerClass g_handler_of_##HandlerClass

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_HANDLER_H_
