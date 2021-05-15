#ifndef CORELIB_EVENTS_HPP
#define CORELIB_EVENTS_HPP

#include <vector>
#include <functional>
#include <cstdint>

template<typename TReturn, typename... TParams>
class Events
{
public:
    using FunctionType = std::function<TReturn(TParams...)>;
    using FunctionPointer = TReturn(*)(TParams...);
protected:
    class FunctionInfo
    {
    public:
        uint32_t index;
        FunctionType func;
        intptr_t staticFuncPtr;
    public:
        FunctionInfo() : index(0), func(nullptr), staticFuncPtr((intptr_t)0)
        {
        }
        FunctionInfo(
            const uint32_t& index,
            const FunctionType& func,
            const intptr_t& staticFuncPtr
        ) : index(index), func(func), staticFuncPtr(staticFuncPtr)
        {
        }
    public:
        bool operator ==(const FunctionInfo& r) {
            return this->index == r.index;
        }
    };

protected:
    uint32_t index;
    std::vector<FunctionInfo> eventList;
public:
    int Count() const {
        return this->eventList.size();
    }
public:
    Events() : index(0) {}
protected:
    uint32_t Push(const FunctionType& func, const intptr_t& staticFuncPtr = 0) {
        this->eventList.push_back(FunctionInfo(++this->index, func, staticFuncPtr));
        return this->index;
    }
public:
    uint32_t AddListener(FunctionPointer funcPtr) {
        if ((intptr_t)funcPtr == 0) {
            return 0;
        }
        return this->Push(FunctionType(funcPtr), (intptr_t)funcPtr);
    }

    template<typename TOBJ>
    uint32_t AddListener(TOBJ* obj, TReturn(TOBJ::* ptr)(TParams...)) {
        return this->Push(std::bind(ptr, obj, TParams...));
    }

    uint32_t RemoveListener(FunctionPointer funcPtr) {
        if (funcPtr == nullptr) {
            return;
        }
        for (auto it = this->eventList.begin(); it != this->eventList.end(); it++) {
            if (it->staticFuncPtr == (intptr_t)funcPtr) {
                this->eventList.erase(it);
                return it->index;
            }
        }
        return 0;
    }

    uint32_t RemoveListenerByIndex(uint32_t index) {
        if (index == -1) {
            return;
        }
        for (auto it = this->eventList.begin(); it != this->eventList.end(); it++) {
            if (it->index == index) {
                this->eventList.erase(it);
                return index;
            }
        }
        return 0;
    }
    uint32_t operator+=(FunctionPointer ptr) {
        return this->AddListener(ptr);
    }

    uint32_t operator-=(FunctionPointer ptr) {
        return this->RemoveListener(ptr);
    }
};

template<typename TReturn, typename... TParams>
class Delegate : public Events<TReturn, TParams...>
{
public:
    void Invoke(const TParams&... t) {
        for (auto item : this->eventList) {
            item.func(t...);
        }
    }

    void RemoveAllListener() {
        this->eventList.clear();
    }
};

template<typename... TParams>
using ActionEvents = Events<void, TParams...>;

template<typename... TParams>
using Action = Delegate<void, TParams...>;

template<typename TReturn, typename... TParams>
using FunctionEvents = Events<TReturn, TParams...>;

template<typename TReturn, typename... TParams>
class Function : public Delegate<TReturn, TParams...>
{
public:
    std::vector<TReturn> InvokeResult(TParams&... args) {
        std::vector<TReturn> retList;
        for (auto item : this->eventList) {
            retList.push_back(item.func(args...));
        }
        return retList;
    }
};



#endif // !CORELIB_EVENTS_HPP