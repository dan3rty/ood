#pragma once

struct AngleStats
{
    double average = 0;
};

class CAngleStatsMonitor
{
public:
    void Update(double value);
    [[nodiscard]] AngleStats GetStats() const;

private:
    static double DegreesToRadians(double value);
    static double RadiansToDegrees(double value);

    double m_sineSum = 0;
    double m_cosineSum = 0;
};