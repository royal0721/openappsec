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

#ifndef __POLICY_MAKER_UTILS_H__
#define __POLICY_MAKER_UTILS_H__

#include <string>
#include <fstream>
#include <utility>
#include <sys/types.h>

#include <cereal/archives/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "debug.h"
#include "common.h"
#include "maybe_res.h"
#include "appsec_practice_section.h"
#include "ingress_data.h"
#include "settings_section.h"
#include "triggers_section.h"
#include "k8s_policy_common.h"
#include "exceptions_section.h"
#include "rules_config_section.h"
#include "trusted_sources_section.h"

USE_DEBUG_FLAG(D_NGINX_POLICY);

enum class AnnotationTypes {
    PRACTICE,
    TRIGGER,
    EXCEPTION,
    WEB_USER_RES,
    SOURCE_IDENTIFIERS,
    TRUSTED_SOURCES,
    COUNT
};

// LCOV_EXCL_START Reason: no test exist
class SecurityAppsWrapper
{
public:
    SecurityAppsWrapper(
        const AppSecWrapper &_waap,
        const TriggersWrapper &_trrigers,
        const RulesConfigWrapper &_rules,
        const ExceptionsWrapper &_exceptions,
        const std::string &_policy_version)
            :
        waap(_waap),
        trrigers(_trrigers),
        rules(_rules),
        exceptions(_exceptions),
        policy_version(_policy_version) {}

    void save(cereal::JSONOutputArchive &out_ar) const;

private:
    AppSecWrapper waap;
    TriggersWrapper trrigers;
    RulesConfigWrapper rules;
    ExceptionsWrapper exceptions;
    std::string policy_version;
};

class PolicyWrapper
{
public:
    PolicyWrapper(
        const SettingsWrapper &_settings,
        const SecurityAppsWrapper &_security_apps)
            :
        settings(_settings),
        security_apps(_security_apps) {}

    void save(cereal::JSONOutputArchive &out_ar) const;

private:
    SettingsWrapper settings;
    SecurityAppsWrapper security_apps;
};
// LCOV_EXCL_STOP
class PolicyMakerUtils
{
public:
    void clearElementsMaps();

    bool startsWith(const std::string &str, const std::string &prefix);

    bool endsWith(const std::string &str, const std::string &suffix);

    std::tuple<std::string, std::string, std::string> splitHostName(const std::string &host_name);

    std::string dumpPolicyToFile(const PolicyWrapper &policy, const std::string &policy_path) const;

    PolicyWrapper combineElementsToPolicy(const std::string &policy_version);

    void createPolicyElementsByRule(
        const ParsedRule &rule,
        const ParsedRule &default_rule,
        const AppsecLinuxPolicy &policy,
        const std::string &policy_name
    );

    void createPolicyElements(
        const std::vector<ParsedRule> &rules,
        const ParsedRule &default_rule,
        const AppsecLinuxPolicy &policy,
        const std::string &policy_name
    );

private:
    std::map<std::string, LogTriggerSection> log_triggers;
    std::map<std::string, WebUserResponseTriggerSection> web_user_res_triggers;
    std::map<std::string, InnerException> inner_exceptions;
    std::map<std::string, WebAppSection> web_apps;
    std::map<std::string, RulesConfigRulebase> rules_config;
};

#endif // __POLICY_MAKER_UTILS_H__