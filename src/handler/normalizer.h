// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_SRC_HANDLER_NORMALIZER_H_
#define ROBUST_PALM_ROI_SRC_HANDLER_NORMALIZER_H_

#include "robust-palm-roi/handler.h"
#include "common/palm.h"
#include "util/imgop.h"

namespace rpr {

class OrigNormalizer : public Handler {
 public:
  OrigNormalizer();
  Status Init(const YAML::Node& parameters) override;
  Status Handle(PalmInfoDTO& palm) override;
  const char* name() override;

 private:
  double scaling_;
  int width_;
};


class RoiNormalizer : public Handler {
 public:
  Status Handle(PalmInfoDTO& palm) override;

 protected:
  virtual Status Normalize(PalmInfoDTO& palm) = 0;

  int width_;
};

inline Status RoiNormalizer::Handle(PalmInfoDTO& palm) {
  if (palm.roi().empty() || palm.roi().channels() != 3) {
    return Status::LoadImageError("Roi of must be extracted from original palm image.");
  }

  cv::Mat roi(palm.roi());
  ResizeImageOperator rop(roi, width_);
  rop.Do(&roi);
  int radius = roi.cols / 2;
  WarpAffineImageOperator* wop = new WarpAffineImageOperator(roi, palm.roi_angle());
  wop->Do(&roi);

  palm.SetRoi(cv::Mat(roi, cv::Rect(roi.cols / 2 - radius, roi.rows / 2 - radius,
                                    2 * radius, 2 * radius)));
  return Normalize(palm);
}


class IncircleRoiNormalizer : public RoiNormalizer {
 public:
  IncircleRoiNormalizer();
  Status Init(const YAML::Node& parameters) override;
  const char* name() override;

 private:
  Status Normalize(PalmInfoDTO& palm) override;
  void MaskIncircle(const cv::Mat& src, cv::Mat* dst);
  void ColorBalance(const cv::Mat& src, cv::Mat* dst);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_SRC_HANDLER_NORMALIZER_H_