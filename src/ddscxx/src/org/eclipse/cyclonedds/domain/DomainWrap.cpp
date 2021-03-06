/*
*                         Vortex Lite
*
*   This software and documentation are Copyright 2006 to 2014 PrismTech
*   Limited and its licensees. All rights reserved. See file:
*
*                     $LITE_HOME/LICENSE
*
*   for full copyright notice and license terms.
*
*/
#include <org/eclipse/cyclonedds/domain/DomainWrap.hpp>
#include <org/eclipse/cyclonedds/core/ReportUtils.hpp>
#include <org/eclipse/cyclonedds/domain/Domain.hpp>

org::eclipse::cyclonedds::domain::DomainWrap::DomainWrap(dds_domainid_t id, const std::string& config)
{
    this->ddsc_domain = -1;
    /*
     * If the config string is not empty, we have to create the domain
     * explicitly to get that config into the system.
     *
     * If not, don't do anything and let the system decide what config
     * to use.
     */
    if (!config.empty()) {
        ISOCPP_BOOL_CHECK_AND_THROW(id != org::eclipse::cyclonedds::domain::default_id(),
                                    ISOCPP_INVALID_ARGUMENT_ERROR,
                                    "When explicitly provide a config, a specific domain id has to be provided as well.");
        this->ddsc_domain = dds_create_domain(id, config.c_str());
        ISOCPP_DDSC_RESULT_CHECK_AND_THROW(this->ddsc_domain, "Failed to create domain explicitly.");
    }
}

org::eclipse::cyclonedds::domain::DomainWrap::~DomainWrap()
{
    if (this->ddsc_domain > 0) {
        /* The domain was explicitly created, which means we have
         * to explicitly delete it. */
        dds_delete(this->ddsc_domain);
    }
}
