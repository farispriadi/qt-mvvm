// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <mvvm/model/sessionitem.h>
#include <mvvm/serialization/jsonitembackupstrategy.h>
#include <mvvm/serialization/jsonitemconverter.h>

using namespace ModelView;

struct JsonItemBackupStrategy::JsonItemBackupStrategyImpl {
    std::unique_ptr<JsonItemConverterInterface> m_converter;
    QJsonObject m_json;
};

JsonItemBackupStrategy::JsonItemBackupStrategy(const ItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemBackupStrategyImpl>())
{
    p_impl->m_converter = std::make_unique<JsonItemConverter>(item_factory);
}

JsonItemBackupStrategy::~JsonItemBackupStrategy() = default;

std::unique_ptr<SessionItem> JsonItemBackupStrategy::restoreItem() const
{
    return p_impl->m_converter->from_json(p_impl->m_json);
}

void JsonItemBackupStrategy::saveItem(const SessionItem* item)
{
    p_impl->m_json = p_impl->m_converter->to_json(item);
}
