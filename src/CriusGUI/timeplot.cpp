#include "timeplot.h"

TimePlot::TimePlot(QCustomPlot * const plot, int n_time_points, int n_graphs):
    plot_(plot)
{
    // Initialize graphs
    QPen pen;
    std::vector<std::vector<double> > colors = { {255, 0 ,0}, {0, 255, 0}, {0, 0, 255} };
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

    this->plot_->xAxis->setRange(0, n_time_points);
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
    for(int i = 0; i < this->graphs_data_.size(); ++i)
    {
        // Update internal data
        for (int j = 0; j < this->time_.size() - 1; ++j)
        {
            graphs_data_[i][j] = graphs_data_[i][j+1];
        }
        graphs_data_[i][this->time_.size()-1] = x[i];

        // Add to plot
        this->plot_->graph(i)->setData(this->time_, this->graphs_data_[i]);

    }

    this->plot_->replot();

}
