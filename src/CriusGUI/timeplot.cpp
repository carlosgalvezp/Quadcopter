#include "timeplot.h"

TimePlot::TimePlot(QCustomPlot * const plot, int n_time_points, int n_graphs):
    plot_(plot), n_time_points(n_time_points)
{
    // Initialize graphs
    QPen pen;
    std::vector<std::vector<double> > colors = { {255, 0 ,0},   {0, 255, 0},    {0, 0, 255},
                                                 {120, 87, 12}, {10, 120, 54},  {32, 98, 198}};
    this->graphs_data_ = QVector<QVector<double> >(n_graphs);

    for(int i = 0; i < n_graphs; ++i)
    {
        this->plot_->addGraph();
        pen.setColor(QColor(colors[i][0], colors[i][1], colors[i][2]));
        this->plot_->graph(i)->setPen(pen);
        this->graphs_data_[i] = QVector<double>(n_time_points);
    }

    // Initialize time
    this->time_ = QVector<double>(n_time_points);

    // Initialize QCustomPlot
    this->plot_->xAxis->setLabel("t");
    this->plot_->xAxis->setLabel("x");

    t0 = 0;
    this->plot_->xAxis->setRange(t0, t0+n_time_points);
    this->plot_->yAxis->setRange(-5000, 5000);

    for(int i = 0; i < n_time_points;++i)
    {
        this->time_[i] = i;
    }
}

TimePlot::~TimePlot()
{

}

void TimePlot::addPoint(const std::vector<double> &x)
{
    // Update each graph
    for(int i = 0; i < x.size(); ++i)
    {
        // Remove first point
        this->plot_->graph(i)->removeData(t0);

        // Add new point
        this->plot_->graph(i)->addData({t0 + this->n_time_points}, {x[i]});
    }    

    // Update initial pointer
    ++t0;

    // Update time range
    this->plot_->xAxis->setRange(t0, t0 + this->n_time_points);
    this->plot_->replot();
}
