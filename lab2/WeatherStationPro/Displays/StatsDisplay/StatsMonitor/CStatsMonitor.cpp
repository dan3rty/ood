#include "CStatsMonitor.h"

void CStatsMonitor::Update(double value)
{
    if (value < m_min)
    {
        m_min = value;
    }

    if (value > m_max)
    {
        m_max = value;
    }

    m_accumulated += value;
    ++m_accumulatedCount;
}

Stats CStatsMonitor::GetStats() const
{
    return {
        .max = m_max,
        .min = m_min,
        .average = m_accumulated / m_accumulatedCount,
    };
}