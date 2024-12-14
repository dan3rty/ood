#pragma once

#include <numeric>
#include <memory>

struct Stats
{
    double max = 0;
    double min = 0;
    double average = 0;
};

class CStatsMonitor
{
public:
    void Update(double value);
    [[nodiscard]] Stats GetStats() const;

private:
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_accumulated = 0;
    unsigned m_accumulatedCount = 0;
};