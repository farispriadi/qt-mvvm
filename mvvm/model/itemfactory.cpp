// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemfactory.h"
#include "sessionitem.h"
#include "propertyitem.h"
#include "compounditem.h"
#include "vectoritem.h"
#include "itemcatalogue.h"

using namespace ModelView;

ItemFactory::ItemFactory() = default;

ItemFactory::ItemFactory(std::unique_ptr<ItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{

}

ItemFactory::~ItemFactory() = default;

SessionItem* ItemFactory::createItem(const model_type& modelType)
{
    auto result = create_intern(modelType);
    return result.release();
}

SessionItem* ItemFactory::createEmptyItem()
{
    return new SessionItem;
}

std::unique_ptr<SessionItem> ItemFactory::create_intern(const model_type& modelType) const
{
    auto result = m_catalogue->create(modelType);
    return result;
}
