/*
 * Copyright 2014 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "rgb-depth-sync/color_image.h"
#include "rgb-depth-sync/shader.h"

namespace rgb_depth_sync {

  ColorImage::ColorImage() {
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture_id_);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);

    texture_drawable_ = new rgb_depth_sync::TextureDrawable(shader::kColorCameraVertex,
                                                            shader::kColorCameraFragment);
  }

  void ColorImage::Draw(int width, int height) {
    if (height == 0 || width == 0) {
      LOGE("The Scene received an invalid height of 0 in SetupViewPort.");
    }
    texture_drawable_->RenderImage(width, height, texture_id_);
  }

  ColorImage::~ColorImage() { glDeleteTextures(1, &texture_id_); }

} // namespace rgb_depth_sync
