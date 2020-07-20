#include "object-sys.h"

sp::object_sys::object_entry::object_entry() : object(nullptr), deleter()
{
}

sp::object_sys::object_entry::object_entry(void* object,
                                              cleanup_func_t deleter) :
    object(object), deleter(deleter)
{
}

/*
sp::object_sys::object_entry::object_entry(object_entry&& other) :
    object(other.object), deleter(std::move(other.deleter))
{
    other.object = nullptr;
}
*/

sp::object_sys::object_entry::~object_entry()
{
    if (this->object != nullptr)
    {
        this->deleter(this->object);
    }
}

sp::object_sys g_object_sys;

size_t sp::object_sys::register_object(void* object, cleanup_func_t deleter)
{
    auto entry = object_entry(object, deleter);
    // if we have a unused index lets reuse it
    size_t index;
    if (this->m_free_obj_idxs.size() > 0)
    {
        index = this->m_free_obj_idxs.back();
        this->m_objects[index] = std::move(entry);
        this->m_free_obj_idxs.pop_back();
    }
    else
    {
        this->m_objects.push_back(std::move(entry));
        index = std::distance(this->m_objects.end(), this->m_objects.begin());
    }

    return index;
}

void sp::object_sys::release_object(size_t index)
{
    // get object
    auto& entry = this->m_objects[index];

    // free object
    entry.deleter(entry.object);

    // clear index for reuse so that other index's are not invalidated
    entry.object = nullptr;
    entry.deleter = sp::object_sys::cleanup_func_t();
    this->m_free_obj_idxs.push_back(index);
}

/*
 * native void CloseObject(Object obj);
 */
cell_t sp::object_sys::close_object(IPluginContext* ctx, const cell_t* params)
{
    g_object_sys.release_object(static_cast<size_t>(params[1]));

    return 0;
}
