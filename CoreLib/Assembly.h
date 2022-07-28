#pragma once

#include "Object.h"
#include "Type.h"
#include "Events.hpp"

namespace JxCoreLib
{
    class Assembly final : public Object
    {
        CORELIB_DEF_TYPE(AssemblyObject_JxCoreLib, JxCoreLib::Assembly, Object);
    private:
        string name_;
        Assembly(string_view name) : name_(name) {}
    public:
        string get_name() const { return this->name_; }
    public:
        Type* FindType(string_view name) const;
        array_list<Type*> GetTypes() const { return this->types; }
        void RegisterType(Type* type);

    public:
        static inline FunctionEvents<Action<>> OnReset;

        static Assembly* StaticBuildAssemblyByName(string_view name);
        static Assembly* StaticBuildAssembly(const AssemblyTypeObject& obj);

        static Assembly* StaticFindAssemblyByName(string_view name);
        static Assembly* StaticFindAssembly(const AssemblyTypeObject& obj);

        static void StaticUnloadAssemblyByName(string_view name);
    private:
        array_list<Type*> types;
    };
}