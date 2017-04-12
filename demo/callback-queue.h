/* -----------------------------------------------------------------------------
Copyright 2017 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
----------------------------------------------------------------------------- */

// Author: Kevin P. Barry [ta0kira@gmail.com] [kevinbarry@google.com]

#ifndef CALLBACK_QUEUE_H_
#define CALLBACK_QUEUE_H_

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

namespace demo {

class CallbackQueue {
 public:
  CallbackQueue(bool active = true) : active_(active) {}

  void Push(std::function<void()> callback);
  bool PopAndCall();
  void WaitUntilEmpty();
  void Activate();
  void Terminate();

 private:
  std::mutex queue_lock_;
  std::condition_variable condition_;
  bool terminated_ = false;
  bool active_;
  std::queue<std::function<void()>> queue_;
};

}  // namespace demo

#endif  // CALLBACK_QUEUE_H_