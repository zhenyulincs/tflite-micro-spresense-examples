/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "tensorflow/lite/micro/debug_log.h"

#include "tensorflow/lite/micro/spresense/debug_log_callback.h"
#include <stdio.h>

static DebugLogCallback debug_log_callback = nullptr;

void RegisterDebugLogCallback(void (*cb)(const char* s)) {
  debug_log_callback = cb;
}


void DebugLog(const char* format, va_list args) {
// #ifndef TF_LITE_STRIP_ERROR_STRINGS
  // Reusing TF_LITE_STRIP_ERROR_STRINGS to disable DebugLog completely to get
  // maximum reduction in binary size. This is because we have DebugLog calls
  // via TF_LITE_CHECK that are not stubbed out by TF_LITE_REPORT_ERROR
  if (debug_log_callback != nullptr) {
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    debug_log_callback(buffer);
  }
// #endif
}
// #ifndef TF_LITE_STRIP_ERROR_STRINGS
int DebugVsnprintf(char* buffer, size_t buf_size, const char* format,
                              va_list vlist) {
  return vsnprintf(buffer, buf_size, format, vlist);
}
// #endif

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus