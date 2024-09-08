#include <unordered_map>
#include <typeindex>
#include <cassert>

class FactoryContainer
{
public:
    template<typename T>
    T& Get() {
        auto index = std::type_index(typeid(T));
        if (not _factories[index].Singleton) {
            _factories[index].Singleton = Create<T>();
        }
        return *reinterpret_cast<T*>(_factories[index].Singleton);
    }

    template<typename T>
    T* Create() {
        auto index = std::type_index(typeid(T));
        return reinterpret_cast<T*>(_factories[index].Constructor(*this));
    }

    template<typename T>
    void Destroy(T* pObject) {
        auto index = std::type_index(typeid(T));
        Factory& factory = _factories[index];
        if (reinterpret_cast<void*>(pObject) == factory.Singleton) {
            assert(false and "Trying to destroy a singleton!");
        }
        factory.Destructor(pObject);
    }

    template<typename T>
    bool Contains() {
        auto index = std::type_index(typeid(T));
        return _factories.contains(index);
    }

    template<typename T>
    bool Add() {
        return Add<T>([](FactoryContainer& fc) { return new T(fc); } );
    }

    template<typename T>
    bool Add(T* (*constructor)(FactoryContainer&)) {
        if (Contains<T>()) return false;
        auto index = std::type_index(typeid(T));
        _factories[index].Constructor = reinterpret_cast<void* (*)(FactoryContainer&)>(constructor);
        _factories[index].Destructor = [](const void* pObject) { delete static_cast<const T*>(pObject); };
        return true;
    }

private:
    struct Factory
    {
        void* (*Constructor)(FactoryContainer&) {};
        void  (*Destructor)(const void*) {};
        void* Singleton{};

        ~Factory() {
            Destructor(Singleton);
        }
    };

    std::unordered_map<std::type_index, Factory> _factories{};
};