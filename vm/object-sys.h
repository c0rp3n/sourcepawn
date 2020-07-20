#ifndef _INCLUDE_SOURCEPAWN_OBJECT_SYS_H_
#define _INCLUDE_SOURCEPAWN_OBJECT_SYS_H_

#pragma once

#include <functional>
#include <utility>
#include <vector>

#include "plugin-context.h"
#include "plugin-runtime.h"

namespace sp
{
    class object_sys
    {
    public:
        typedef std::function<void(void*)> cleanup_func_t;

        inline object_sys() = default;
        inline ~object_sys() = default;

        size_t register_object(void* object, cleanup_func_t deleter);
        template<class T>
        inline T* get_object(size_t index);
        void release_object(size_t index);

        static cell_t close_object(IPluginContext* ctx, const cell_t* params);

    private:
        struct object_entry;

        std::vector<object_entry> m_objects;
        std::vector<size_t> m_free_obj_idxs;

        struct object_entry
        {
        public:
            void* object;
            cleanup_func_t deleter;

            object_entry();
            object_entry(void* object, cleanup_func_t deleter);
            ~object_entry();

            // only moveable
            object_entry (object_entry &&);
            object_entry& operator= (object_entry &&);
            inline object_entry (const object_entry &) = delete;
            inline object_entry& operator= (const object_entry &) = delete;
        };
    };
}

extern sp::object_sys g_object_sys;

template<class T>
T* sp::object_sys::get_object(size_t index)
{
    return reinterpret_cast<T*>(this->m_objects[index].object);
}


#endif // _INCLUDE_SOURCEPAWN_OBJECT_SYS_H_
