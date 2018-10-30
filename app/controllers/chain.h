// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_CONTROLLERS_CHAIN_H_
#define ROBUST_PALM_ROI_APP_CONTROLLERS_CHAIN_H_

#include <memory>
#include <list>
#include <opencv2/opencv.hpp>
#include "handlers/handler.h"
#include "common/status.h"

namespace rpr {

class HandlerChain {
 public:
  Status Process(PalmInfoDTO& palm);

 private:
  friend class ChainBuilder;
  HandlerChain& Join(std::shared_ptr<Handler> handler);

  std::list< std::shared_ptr<Handler> > handlers_;
};


class ChainBuilder {
 public:
  std::unique_ptr<HandlerChain> BuildAndInitChain();
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_CONTROLLERS_CHAIN_H_
