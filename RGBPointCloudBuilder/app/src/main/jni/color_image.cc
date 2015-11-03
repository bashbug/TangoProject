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

namespace rgb_depth_sync {

ColorImage::ColorImage() {
  // bind an android view to texture
  glGenTextures(1, &texture_id_);
  glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture_id_);
  glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_EXTERNAL_OES, 0);
  // bind to frame buffer
  glGenFramebuffers(1, &fbo_handle_);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_EXTERNAL_OES,
                         texture_id_, 0);
  LOGE("glFramebufferTexture2D() returned error %d", glGetError());
}

ColorImage::~ColorImage() { glDeleteTextures(1, &texture_id_); }
}  // namespace rgb_depth_sync
