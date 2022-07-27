﻿#include <CoreLib/CoreLib.h>
#include <iostream>
#include <cassert>

using namespace JxCoreLib;



class ExampleClass : public Object
{
    CORELIB_DEF_TYPE(AssemblyObject_JxCoreLib, ExampleClass, Object);
public:


    CORELIB_REFL_DECL_FUNC(create)
        sptr<ExampleClass> create() { return mksptr(new ExampleClass); }
};

template<typename T, typename K>
class TemplateClass : public Object
{
public:
    CORELIB_DEF_TEMPLATE_TYPE(AssemblyObject_JxCoreLib, TemplateClass, Object, T, K);

};



void TestOOP()
{
    using namespace std;

    ExampleClass* exm = new ExampleClass;

    assert(exm->GetType()->get_base() == cltypeof<Object>());
    assert(exm->GetType()->get_name() == string("ExampleClass"));

    assert(cltypeof<Object>()->IsInstanceOfType(exm));
    
    ExampleClass::StaticType() == cltypeof<ExampleClass>();

    //assert(cltypeof<ExampleClass>()->IsSubclassOf(cltypeof<Object>()));

    //auto* templc = new TemplateClass<int, double>;
    //Type* templc_type = templc->GetType();

    //assert(templc_type->get_template_types()->at(0) == cltypeof<int>());
    //assert(templc_type->get_template_types()->at(1) == cltypeof<double>());
    //auto b = templc_type == cltypeof<TemplateClass<int, double>>();
    //assert(b);
}