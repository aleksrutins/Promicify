#include <functional>
#include <thread>
namespace Promicify {
    template<class T>
    class Promise {
        void defNext(T val) {};
        std::function<void *(T)> next;
    public:
        Promise(std::function<void(typename Promise<T>::Resolve, typename Promise<T>::Reject)> fn): next(defNext) {
            T value;
            void *error;
            struct fns {
                static void resolve(T val) {
                    value = val;
                }
                static void reject(void *err) {
                    error = err;
                }
            };
            std::thread thrd([&]() {
                try {
                    fn(&fns::resolve, &fns::reject);
                } catch(void *e) {
                    fns::reject(e);
                }
                if(error) {
                    return;
                }
                Promise([value, this]() {next(value);});
            });
            thrd.join();
        }
        template<class TNext>
        Promise then(std::function<TNext(T)> thenFn) {
            next = thenFn;
        }
        typedef void(*Resolve)(T);
        typedef void(*Reject)(void *);
    };
}