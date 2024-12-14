#include "CAngleStatsMonitor.h"
#include <cmath>

void CAngleStatsMonitor::Update(const double value)
{
    const auto angle = DegreesToRadians(value);
    m_sineSum += std::sin(angle);
    m_cosineSum += std::cos(angle);
}

AngleStats CAngleStatsMonitor::GetStats() const
{
    return {
        .average = RadiansToDegrees(std::atan2(m_sineSum, m_cosineSum)),
    };
}

double CAngleStatsMonitor::DegreesToRadians(double value)
{
    return value * M_PI / 180;
}

double CAngleStatsMonitor::RadiansToDegrees(double value)
{
    return value * 180 / M_PI;
}