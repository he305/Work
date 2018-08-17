#include "epr.h"

EPR::EPR(int& angle, double& avrEPR, double& variance, AviationClasses aviationClass)
{
    this->angle = angle;
    this->EPRvariance.push_back(avrEPR);
    this->EPRvariance.push_back(variance);
    this->aviationClass = aviationClass;
}

EPRList::EPRList()
{
    init();
}

void EPRList::init()
{
    this->eprs.push_back(EPR(0, 12, 9, STRATEGIC));
    this->eprs.push_back(EPR(0, 5, 4, TACTIC));
    this->eprs.push_back(EPR(0, 10, 5, HELI));
    this->eprs.push_back(EPR(0, 1, 0.5, HYPERSONIC));
    this->eprs.push_back(EPR(0, 0.3, 0.1, ROCKET));

    this->eprs.push_back(EPR(20, 25, 14, STRATEGIC));
    this->eprs.push_back(EPR(20, 8, 5, TACTIC));
    this->eprs.push_back(EPR(20, 14, 5, HELI));
    this->eprs.push_back(EPR(20, 3, 1, HYPERSONIC));
    this->eprs.push_back(EPR(20, 1, 0.3, ROCKET));

    this->eprs.push_back(EPR(40, 17, 11, STRATEGIC));
    this->eprs.push_back(EPR(40, 11, 7, TACTIC));
    this->eprs.push_back(EPR(40, 28, 6, HELI));
    this->eprs.push_back(EPR(40, 4, 2, HYPERSONIC));
    this->eprs.push_back(EPR(40, 0.2, 0.1, ROCKET));


    this->eprs.push_back(EPR());

}
