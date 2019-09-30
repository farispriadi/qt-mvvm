#include "google_test.h"
#include "qcustomplot.h"
#include "graphviewportplotcontroller.h"
#include "graphviewportitem.h"
#include "sessionmodel.h"
#include "data1ditem.h"
#include "graphitem.h"

using namespace ModelView;

//! Testing AxisPlotControllers.

class TestGraphViewportPlotController : public ::testing::Test
{
public:
    ~TestGraphViewportPlotController();
};

TestGraphViewportPlotController::~TestGraphViewportPlotController() = default;

//! Initial state.

TEST_F(TestGraphViewportPlotController, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Check ::setItem() method when no graphs exist.

TEST_F(TestGraphViewportPlotController, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto item = dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));
    controller.setItem(item);

    // no graphs in empty GraphViewportItem
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // axis should be [0, 1] as in defaule ViewportAxisItem
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, 0.0);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, 1.0);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, 0.0);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, 1.0);
}

//! Check ::setItem() method when ViewPortItem contains graphs.

TEST_F(TestGraphViewportPlotController, addGraphAndSetItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = dynamic_cast<GraphViewportItem*>(model.insertNewItem(Constants::GraphViewportItemType));

    auto data_item = dynamic_cast<Data1DItem*>(model.insertNewItem(Constants::Data1DItemType));
    const std::vector<double> expected_content = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setFixedBinAxis(3, 0.0, 3.0);
    data_item->setContent(expected_content);

    auto graph_item = dynamic_cast<GraphItem*>(model.insertNewItem(Constants::GraphItemType, viewport_item));
    graph_item->setDataItem(data_item);
    controller.setItem(viewport_item);

    // single graph on custom plot.
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // axis should be [0, 1] as in defaule ViewportAxisItem
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, expected_centers[0]);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, expected_centers[2]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, expected_content[0]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, expected_content[2]);
}