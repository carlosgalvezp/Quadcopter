#ifndef TIMEPLOT_H
#define TIMEPLOT_H

#include <qcustomplot.h>
#include <vector>

class TimePlot
{
public:
    TimePlot(QCustomPlot * const plot, int n_time_points, int n_graphs = 1);
    ~TimePlot();

    void addPoint(const std::vector<double> & x);
    void setXLimits(double x_min, double x_max);
    void setYLimits(double y_min, double y_max);

private:
    QCustomPlot * plot_;
    double t0;
    int n_time_points;

    QVector<QVector<double> > graphs_data_;
    QVector<double> time_;
};

#endif // TIMEPLOT_H
