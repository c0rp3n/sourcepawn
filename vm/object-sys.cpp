#include "object-sys.h"

sp::object_sys::object_entry::object_entry() : object(nullptr), deleter()
{
}

sp::object_sys::object_entry::object_entry(void* object,
                                           cleanup_func_t deleter) :
    object(object), deleter(deleter)
{
}

sp::object_sys::object_entry::object_entry(object_entry&& other) :
    object(other.object), deleter(std::move(other.deleter))
{
    other.object = nullptr;
}

sp::object_sys::object_entry& sp::object_sys::object_entry::operator=(object_entry&& other)
{
    this->object = other.object;
    this->deleter = std::move(other.deleter);
    other.object = nullptr;

    return *this;
}

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
    // if we have a unused index lets reuse it
    size_t index;
    if (this->m_free_obj_idxs.size() > 0)
    {
        index = this->m_free_obj_idxs.back();
        this->m_objects.emplace(this->m_objects.begin() + index, object, deleter);
        this->m_free_obj_idxs.pop_back();
    }
    else
    {
        index = this->m_objects.size();
        this->m_objects.emplace_back(object, deleter);
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
