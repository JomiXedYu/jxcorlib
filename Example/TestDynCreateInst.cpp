
#include "Assembly.h"

#include <cassert>

using namespace JxCoreLib;


class CreateFactory : public Object
{
    CORELIB_DEF_TYPE(AssemblyObject_Test, CreateFactory, Object);
    //create by factory
    CORELIB_DECL_DYNCINST() {
        auto p = new CreateFactory;
        p->i = 1;
        return p;
    }
public:
    int i;
};

class NonCreateFactory : public Object
{
    CORELIB_DEF_TYPE(AssemblyObject_Test, NonCreateFactory, Object);
public:
    int i;
    //create by default constructor
    NonCreateFactory()
    {
        i = 2;
    }
};



class NotImplCreate : public Object
{
    CORELIB_DEF_TYPE(AssemblyObject_Test, NotImplCreate, Object);
    //throw NotImplementException
    NotImplCreate(int)
    {
    }
};

void TestDynCreateInst()
{

    Assembly* assm = Assembly::StaticFindAssembly(AssemblyObject_Test);
    auto p1 = std::static_pointer_cast<CreateFactory>(assm->FindType("CreateFactory")->CreateSharedInstance({}));
    assert(p1->i == 1);

    int r = 0;

    try
    {
        assm->FindType("NotImplCreate")->CreateInstance({});
        
    }
    catch (const std::exception&)
    {
        r = 3;
    }

    assert(r == 3);

}