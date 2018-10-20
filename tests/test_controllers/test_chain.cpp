// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handlers/enhancer.h"
#include "handlers/filter.h"
#include "handlers/binarizer.h"
#include "handlers/adjuster.h"
#include "handlers/detector.h"
#include "controllers/chain.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::Handler;
using rpr::LaplaceEnhancer;
using rpr::GaussianFilter;
using rpr::OtsuBinarizer;
using rpr::NoiseAdjuster;
using rpr::AngleAdjuster;
using rpr::PeakValleyDetector;

using rpr::HandlerChain;

class HandlerChainTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  HandlerChainTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(HandlerChainTestFixture, test_handler_chain) {
  HandlerChain chain;
  chain.Join(std::unique_ptr<Handler>(new GaussianFilter));
  chain.Join(std::unique_ptr<Handler>(new LaplaceEnhancer));
  chain.Join(std::unique_ptr<Handler>(new OtsuBinarizer));
  chain.Join(std::unique_ptr<Handler>(new NoiseAdjuster));
  chain.Join(std::unique_ptr<Handler>(new AngleAdjuster));
  chain.Join(std::unique_ptr<Handler>(new PeakValleyDetector));
  cv::Mat result;
  auto status = chain.Process(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace