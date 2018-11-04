// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handler/extractor.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::EffectiveIncircleExtractor;

class ExtractorTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  ExtractorTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(ExtractorTestFixture, test_effective_incircle_extractor) {
  EffectiveIncircleExtractor extractor;
  auto status = extractor.Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kImageLowQualityError);
}

}   // namespace