// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "GraphicsScene.h"

#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/customplotproxywidget.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/plotting/sceneadapterinterface.h>

namespace
{
const double scene_origin_x{0.0};
const double scene_origin_y{0.0};
const QRectF default_scene_rect{QPointF{scene_origin_x, scene_origin_y}, QSizeF{800, 600}};
} // namespace

//! The contructor
GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(default_scene_rect);
}

//! Initialise the GraphicsScene with its elements
void GraphicsScene::setContext()
{
    // clear();
    createPlotProxy(new ModelView::GraphCanvas);
}

//! The destructor
GraphicsScene::~GraphicsScene() = default;

//! Adjust size of scene and color map proxy.
void GraphicsScene::update_size(const QSize& newSize)
{
    if (plot_proxy) {
        plot_proxy->resize(newSize);
        setSceneRect(scene_origin_x, scene_origin_y, newSize.width(), newSize.height());
        plot_proxy->setPos(0.0, 0.0);
        advance(); // notifies all QGraphicsItem that it is time to replot themself using new status
                   // of scene adapter
    }
}

//! Create the Proxy item
void GraphicsScene::createPlotProxy(ModelView::GraphCanvas* plot_canvas)
{
    scene_adapter = plot_canvas->createSceneAdapter();
    plot_proxy = new CustomPlotProxyWidget(plot_canvas);
    addItem(plot_proxy);
}

//! Return the pointer of the scene adapter on request
ModelView::SceneAdapterInterface* GraphicsScene::getSceneAdapter() const
{
    return scene_adapter.get();
}

AxesRectangleView* GraphicsScene::axesView() const
{
    return axes_view;
}