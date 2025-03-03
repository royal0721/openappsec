// Copyright (C) 2022 Check Point Software Technologies Ltd. All rights reserved.

// Licensed under the Apache License, Version 2.0 (the "License");
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __SERVICE_HEALTH_UPDATE_EVENT_H__
#define __SERVICE_HEALTH_UPDATE_EVENT_H__

#include "event.h"
#include "singleton.h"
#include "config.h"
#include "debug.h"
#include "customized_cereal_map.h"

class ServiceHealthUpdateEvent : public Event<ServiceHealthUpdateEvent>
{
public:
    ServiceHealthUpdateEvent() {}
    ServiceHealthUpdateEvent(
        const std::string &_component,
        const std::string &_error)
            :
        component(_component),
        error(_error) {}

    bool isHealthyUpdate() const { return component.empty(); }
    const std::string & getComponent() const { return component; }
    const std::string & getError() const { return error; }

private:
    std::string component = "";
    std::string error = "";
};

#endif // __SERVICE_HEALTH_UPDATE_EVENT_H__
